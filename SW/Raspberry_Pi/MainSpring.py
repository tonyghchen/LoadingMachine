"""
    New Medical Project : Start from 2024/11/15
    Editor: Tony Gh Chen
     
"""
import sys, json, os, copy
import globals
import orjson       as json
import Language     as Language
import ParamTable   as ParamTable
import DataFormat   as DataFormat
import UART         as UART
import math
import ctypes

from functools          import partial
from PySide6            import QtWidgets, QtGui, QtCore
from PySide6.QtWidgets  import QApplication, QMainWindow, QButtonGroup, QMessageBox
from PySide6.QtCore     import Qt, QTimer
from PySide6.QtGui      import QMovie, QGuiApplication

from Ui_MainForm        import *
from Ui_Progres         import * 

from datetime import    datetime

# ------------------------------------------------------------------
#   Definition 
# ------------------------------------------------------------------

# ------------------------------------------------------------------
#  FILE Tab
# ------------------------------------------------------------------
defProgramPath      = '/Paramter'
defParameterFile    = 'Parameter.js'

if os.name=='posix': # Raspi Testing
    if "tmp" in __file__:
        current_directory   = '/mnt/xinda'
    else:
        current_directory   = os.path.dirname(os.path.abspath(__file__))
else:
    current_directory  = os.path.dirname(os.path.abspath(__file__))

# ------------------------------------------------------------------
#   AdvancedParam Table
# ------------------------------------------------------------------
Dialoglast2key      = 0
Dialoglastkey       = 0    

#if os.name=='posix': # Raspi Testing
# ----------------------------------------------------------------------
# Http Download
# ----------------------------------------------------------------------
MainVersion = "0.0.1" 
condition_to_print  = 1

def my_print(*args, **kwargs):
    if condition_to_print:
        now = datetime.now()

        # 格式化时间字符串，包含毫秒
        formatted_time = now.strftime("%Y-%m-%d %H:%M:%S.%f")	
        print(formatted_time, *args, **kwargs)

# ----------------------------------------------------------------------
# Main Window
# ----------------------------------------------------------------------
class MyMainWindow(QMainWindow, Ui_MainWindow): 

    # ===================================================================
    #       UART  Functions
    # ===================================================================
    # -----------------------------------------------------------------
    # Description:  UART hand shaking initialize
    # Function:     fUART_handshake
    # Input:        none
    # Return:       None
    # -----------------------------------------------------------------
    def fUART_handshake(self):
     
        my_print("UART initialize hadnshake")

    # ----------------------------------------------------------------------
    # UART Initial process
    # Description: UART interrup interval
    # ----------------------------------------------------------------------  
    def fUARTInit(self):

        self.UARTCmd = UART.UARCommand(self, my_print, self.fgetVRRunMode)                                        
        lsHandler = "Handler" 
        lsDel = "Del"
        recCmdHandler = {
            "defUART_rPosition"         : { lsHandler:self.fUARTCmd_rPosition,          lsDel : True  },
            "defUART_rKeyboard"         : { lsHandler:self.fUARTCmd_rKeyboard,          lsDel : False },
            "defUART_rCurrProductQty"   : { lsHandler:self.fUARTCmd_rCurrProductQty,    lsDel : False },
            "defUART_rCurrProductTime"  : { lsHandler:self.fUARTCmd_rCurrProductTime,   lsDel : False },
            "defUART_rCurrFailQty"      : { lsHandler:self.fUARTCmd_rCurrFailQty,       lsDel : False },
            "defUART_VersionNo"         : { lsHandler:self.fUARTCmd_rVersionNo,         lsDel : False },
            "defUART_LoadCellData"      : { lsHandler:self.fUARTCmd_rLoadCellData,      lsDel : False }
        }
        for Code, Data in recCmdHandler.items():
            self.UARTCmd.RegisterReceiverCodeHandler(Code, Data[lsHandler], Data[lsDel])

     # ----------------------------------------------------------------------
    #  UART Functions
    # ----------------------------------------------------------------------
    def fgetVRRunMode(self):
        return (self.gfVRRunMode)
       
    def fUARTCmd_rPosition(self, receiver_data, lCmd, liCmdReadBytes):  
       
        self.fClearSyncforSpringAxisUpDown()

        # defUART_rPosition(0x51),軸號(1),Sign(1)-0:正/1:負, Position(4)
        my_print("Axis Position Decode")                   
        if len(receiver_data) >= (liCmdReadBytes+1):
            # --------------------------------------------------------------------
            #               檢查重複目標值後刪除 保留最後一筆
            liAxis  = receiver_data[2]
            lReverse = ~lCmd & 0xFF  # 反相并确保结果在0-255范围内
            target_values = [lCmd, lReverse,liAxis]
            lvalue  = (receiver_data[6] << 24) | (receiver_data[5] << 16) | (receiver_data[4] << 8) | receiver_data[3]
            # 检查是否存在目标值
            while len(receiver_data) >= 7:
                if receiver_data[0: len(target_values)] == target_values:
                    lvalue  = (receiver_data[6] << 24) | (receiver_data[5] << 16) | (receiver_data[4] << 8) | receiver_data[3]
                    del receiver_data[0:7] # 刪除找到的值
                    my_print("-- Find and delete -- ")
                else:
                    break  

            my_print("New UART data:",receiver_data)
            self.fUART_rPosition(liAxis, lvalue, len(receiver_data))            
        
    def fUARTCmd_rKeyboard(self, receiver_data, lCmd, liCmdReadBytes):
        sKeyData = UART.ArrUART_ReadKeyCode.get(receiver_data[2])
        if  sKeyData is not None:
            sKeycode = sKeyData.get("KeyName")
            my_print("Key swith", self.gfAllKeySW, "Key code:",sKeycode)
            # 1: Key lock, 2: Switch on, 3: Reset O
            if self.gfAllKeySW == 1 :    # Key lock skip all key (except Unlock)
                if  sKeycode !="KeyUnLock" :
                    my_print("Keylock - All key skip !!!")
                    sKeycode = ""
            elif self.gfAllKeySW == 2:
                if  sKeyData.get("KeySWLock") == 0:
                    sKeycode = ""
        # KeyLock 
        my_print("Key code:",receiver_data[2], "Key:",sKeycode)      # Print key data
        if  sKeycode == "KeyLock":
            self.fUART_rKeyboard_KeyLock()
        elif  sKeycode == "KeyUnLock":
            self.fUART_rKeyboard_KeyUnLock()
        # 鍵盤切換(Switch)ON---螢幕岀現"鍵盤切換(",並且不允許任何輸入(PC鍵盤,滑鼠及觸控螢幕),只允許機上操作盒+Y,-Y,+A,-A,AHome
        elif  sKeycode == "StartProd":       # 回原點 
            self.fUART_rKeyboard_StartProd()
        elif  sKeycode == "StopProd":       # 回原點 
            self.fUART_rKeyboard_StopProd()

    def fUARTCmd_rVersionNo(self, receiver_data, lCmd, liCmdReadBytes):
        lVersion1 =  receiver_data[2]
        lVersion2 =  receiver_data[3]
        lVersion3 =  int((receiver_data[5] << 8) | receiver_data[4])
        lsVersion = str(lVersion1) + "." + str(lVersion2) + "." + str(lVersion3)
        self.label_VersionSub.setText(lsVersion)

    def fUARTCmd_rLoadCellData(self, receiver_data, lCmd, liCmdReadBytes):
        self.gwLoadCellData[0] =  (receiver_data[3] << 8) | receiver_data[2]
        self.gwLoadCellData[1] =  (receiver_data[5] << 8) | receiver_data[4]
        self.gwLoadCellData[2] =  (receiver_data[7] << 8) | receiver_data[6]
        self.gwLoadCellData[3] =  (receiver_data[9] << 8) | receiver_data[8]

        self.progressBar1.setValue(self.gwLoadCellData[0])
        self.progressBar2.setValue(self.gwLoadCellData[1])
        self.progressBar3.setValue(self.gwLoadCellData[2])
        self.progressBar4.setValue(self.gwLoadCellData[3])

        my_print("LoadCell Data:",self.gwLoadCellData ) 


    def fUARTCmd_rCurrProductQty(self, receiver_data, lCmd, liCmdReadBytes):
        lCurrentQty  = int((receiver_data[5] << 24) | (receiver_data[4] << 16) | (receiver_data[3] << 8) | receiver_data[2])
        self.fUART_rCurrProductQty(lCurrentQty)           
        
    def fUARTCmd_rCurrProductTime(self, receiver_data, lCmd, liCmdReadBytes):        
        if len(receiver_data) >= (liCmdReadBytes+1):             
            lCurrentTime  = int((receiver_data[5] << 24) | (receiver_data[4] << 16) | (receiver_data[3] << 8) | receiver_data[2])
            self.fUART_rCurrProductTime(lCurrentTime)
        else:
            my_print("defUART_rCurrProductTime Date Error !!!!!") 

    def fUARTCmd_rCurrFailQty(self, receiver_data, lCmd, liCmdReadBytes):
        lMissQty  = int(receiver_data[2])
        self.fUART_rCurrFailQty(lMissQty)

    def fUARTCmd_rOverUnderFlow(self, receiver_data, lCmd, liCmdReadBytes):
        liAxis = receiver_data[2]
        lKeyData  = receiver_data[3]	
        self.fUART_rOverUnderFlow(liAxis, lKeyData)

    # ----------------------------------------------------------------------
    # Function: fUART_ManualUpDownSendProvider 
    # Description: UART Axis send out Provider
    # Input : 軸號 , Sign(0:加/1:減), Byt 0~2(PHY), Byt 0~3(Logi) 補數
    # Return: None
    # ----------------------------------------------------------------------
    def fUART_ManualUpDownSendProvider(self, lsAxis, lUpDown, lPHYData, lLogiData):

        headCodeFormat = UART.ArrUART_WriteHeadCode.get("defUART_wManualUpDown")

        #liAxis = EditTable.ArrAxisMapping[lsAxis]     # Axia Table mapping
        newAxis = "AxisMapping" + lsAxis
        liAxis = self.gdicParaData.get(newAxis, 0)      # 避免軸對應輸入超過

        if liAxis == 0 :
            return

        my_print("lsAxis:",lsAxis, "lAxis:",liAxis)
       
        lfrw = 0
        #lLogiData = abs(lLogiData)
        BfrwConverter = lfrw.to_bytes(4, 'little',signed=True)       # Negative + 4 Byte converter
        BPHYConverter = lPHYData.to_bytes(4, 'little',signed=True)       # Negative + 4 Byte converter
        BLogConverter = lLogiData.to_bytes(4, 'little', signed=True)

        # defUART_wManualUpDown Axis(1), up/down(1),step_frw(4), step(4),curr_pos(4)
        liData = bytes([headCodeFormat['HeadCode'], liAxis, lUpDown, BfrwConverter[0] , BfrwConverter[1] ,BfrwConverter[2] , BfrwConverter[3] ,\
                        BPHYConverter[0], BPHYConverter[1], BPHYConverter[2], BPHYConverter[3], \
                        BLogConverter[0], BLogConverter[1], BLogConverter[2], BLogConverter[3]])
        self.UARTCmd.Send(liData)
        liSimulator = False

        if (os.name !='posix'or liSimulator == True):
            if (headCodeFormat['HeadCode'] == 0xC0):
                 liCmd = [0x51, 0xAE, liAxis, BLogConverter[0], BLogConverter[1], BLogConverter[2], BLogConverter[3] ]
                 self.UARTCmd.AddReceiverBuf(liCmd)        

    # ----------------------------------------------------------------------
    # fUART_rKeyboard_ResetON
    # Description:  ResetON
    # Input : 
    # Return: None
    # ----------------------------------------------------------------------
    def fUART_rKeyboard_ResetON(self):					

        global  gUART_Received_data

        self.fShow_DialogAllClose()                  # All Dialog window close
        self.UARTCmd.SendProvider('defUART_wReset')    # send         
        ErrorMsg = self.Language.GetText("ResetON")
        self.fShow_PressbarBox(ErrorMsg, 1, "ResetMode")      # 顯示兩秒
        self.fFile_SaveEditTable()              # 儲存目前所有資料
        self.fFile_SaveParamter()               # 儲存參數修改資料

        gUART_Received_data = []                # 強制清空UART Buffer  
        self.fUART_Product_Reset()
      
        self.timer.start()                          # 重新启动定时器
        self.gfTestStartPolling = 0                 # Test Start Notice for 原點回復再開始測試
        self.gfVRRunMode        = 0
        self.fProgramTool_Run   = 0 
        self.giSendPos = 9999  # Reset
        
        self.giZRTReceivedPos   = {}
        self.giTestCnt = 60

    # ----------------------------------------------------------------------
    # fUART_rPosition
    # Description: position of Axis from UART
    # Input : 
    # Return: None
    # ----------------------------------------------------------------------
    def fUART_rPosition(self, liAxis, lvalue, lUART_Received_Len):

        lsAxisName = ParamTable.ArrPara_PHYAxisMapping(int(liAxis))      
        my_print("UART rPostion:",liAxis, "lxAxisName:",lsAxisName)

        if lsAxisName != "":
            lsLMAxis = ParamTable.ArrPara_PHYAxisMapping(lsAxisName)
            self.fRun_ValueDisplay(lsLMAxis)
            my_print("----- rPositon --- Axis:",lsAxisName, "Received Pos:",lvalue)
                       
        my_print("End of fUART_rPosition")

    # ----------------------------------------------------------------------
    # UART interrupt process
    # Description: UART interrupt interval
    # ----------------------------------------------------------------------   
    def fUART_Interval(self):    

        if os.name=='posix': # Raspi Testing
            self.UARTCmd.CheckReceiverCmd()

    # ===================================================================
    #       Key Functions
    # ===================================================================
    #-------------------------------------------------------------
    # Initialize Windows Key interrupt
    # Description: Key press interrupt procedure
    # Input : None
    # Return: None
    #-------------------------------------------------------------
    def keyPressEvent(self, event):
        if event.key() == QtCore.Qt.Key_Control:
            self.ctrl_pressed = True

    def keyReleaseEvent(self, event):
        # 如果 Ctrl 键被释放，重置 ctrl_pressed 标志
        if event.key() == QtCore.Qt.Key_Control:
            self.ctrl_pressed = False


    def Init_Keyinterrupt(self):

        #Key Press Interrupt Setting
        liKeyDict = {
                "0": QtCore.Qt.Key_0,			"1":QtCore.Qt.Key_1,		"2":QtCore.Qt.Key_2,
                "3": QtCore.Qt.Key_3,			"4":QtCore.Qt.Key_4,		"5":QtCore.Qt.Key_5,	
                "6": QtCore.Qt.Key_6,		    "7":QtCore.Qt.Key_7,		"8":QtCore.Qt.Key_8,
                "9": QtCore.Qt.Key_9,
                
                "A": QtCore.Qt.Key_A,		    "B":QtCore.Qt.Key_B,	    "C":QtCore.Qt.Key_C,	
                "D": QtCore.Qt.Key_D,		    "E":QtCore.Qt.Key_E,	    "F":QtCore.Qt.Key_F,
                "G": QtCore.Qt.Key_G,		    "H":QtCore.Qt.Key_H,	    "I":QtCore.Qt.Key_I,	
                "J": QtCore.Qt.Key_J,		    "K":QtCore.Qt.Key_K,	    "L":QtCore.Qt.Key_L,
                "M": QtCore.Qt.Key_M,		    "N":QtCore.Qt.Key_N,	    "O":QtCore.Qt.Key_O,	
                "P": QtCore.Qt.Key_P,		    "Q":QtCore.Qt.Key_Q,	    "R":QtCore.Qt.Key_R,
                "S": QtCore.Qt.Key_S,		    "T":QtCore.Qt.Key_T,	    "U": QtCore.Qt.Key_U,   
                "V": QtCore.Qt.Key_V,	        "W":QtCore.Qt.Key_W,        "X": QtCore.Qt.Key_X,
                "Y": QtCore.Qt.Key_Y,	        "Z":QtCore.Qt.Key_Z,
                
                "Space":    QtCore.Qt.Key_Space,				"Backspace":QtCore.Qt.Key_Backspace,        
                "PageUp":   QtCore.Qt.Key_PageUp,			    "PageDown":QtCore.Qt.Key_PageDown,
                "Delete":   QtCore.Qt.Key_Delete,				"Insert":QtCore.Qt.Key_Insert,        
                "Right":    QtCore.Qt.Key_Right,		    	"Left":QtCore.Qt.Key_Left, 
                "Up":       QtCore.Qt.Key_Up,		        	"Down":QtCore.Qt.Key_Down, 	
                "Tab":      QtCore.Qt.Key_Tab,		           	"-":QtCore.Qt.Key_Minus, 	
                "+":        QtCore.Qt.Key_Plus,		        	"RESET":QtCore.Qt.Key_Escape,          
                "CtrlY":    Qt.CTRL | QtCore.Qt.Key_Y,		    "CtrlZ":Qt.CTRL | QtCore.Qt.Key_Z,			 
                "X_FULL":   Qt.ALT | QtCore.Qt.Key_Down,	    "I_FULL":Qt.ALT | QtCore.Qt.Key_Up,
                "Ctrl_Right":Qt.CTRL | QtCore.Qt.Key_Right,     "Ctrl_Left":Qt.CTRL | QtCore.Qt.Key_Left,	
                "Ctrl_Up":  Qt.CTRL | QtCore.Qt.Key_Up,         "Ctrl_Down":Qt.CTRL | QtCore.Qt.Key_Down,
                "Enter":    QtCore.Qt.Key_Return,               ".":QtCore.Qt.Key_Period,
            }            
        
        liKeyDuplicateDict = {		
		    "Enter":QtCore.Qt.Key_Enter
		    }

        for key, value in liKeyDict.items():	
            QtGui.QShortcut(QtGui.QKeySequence(value), self, partial(self.fAll_KeyDecode, key))
		
		# 重複的key將只保留最後的設定，因此獨立設定
        for key, value in liKeyDuplicateDict.items():	
            QtGui.QShortcut(QtGui.QKeySequence(value), self, partial(self.fAll_KeyDecode, key))        

    # ----------------------------------------------------------------------
    # Function : fAll_KeyInterval
    # Description: Key Interval
    # Input : None
    # Return: None
    # ----------------------------------------------------------------------
    def fAll_KeyInterval(self):

        self.giKeyInterruptCnt += 1

        # -------------------------------------------------------------
        # Key in process
        if  (self.gsKeyinData != "") and (self.giKeyInterruptCnt >= 1):
            try:    # 避免錯誤發生 導致無限迴圈
                my_print("Key Process:",self.gsKeyinData)
                self.fAll_KeyProcess(self.gsKeyinData)

            except Exception as e:
                my_print(f"An error occurred: {e}")

            finally:    
                self.giKeyInterruptCnt = 0
                self.gsKeyinData = ""       

        # -------------------------------------------------------------
        # Key command process 
        if  len(self.gsKeyCmdData) > 0:      # Key command buffer 

            try:    # 避免錯誤發生 導致無限迴圈
                my_print("Key Command Process:",self.gsKeyCmdData)
                self.fAll_KeyCmdProcess()

            except Exception as e:
                my_print(f"An error occurred: {e}")

    def fClearSyncforSpringAxisUpDown(self):
       
       if (len(self.gsKeyCmdData) > 0):
            sKeyCmdcode = self.gsKeyCmdData[0]
            state       = sKeyCmdcode.get("State")
            if (state == 1):
                self.gsKeyCmdData = []

    # ----------------------------------------------------------------------
    # Function      : Key in decode
    # Description   : Tab Buttom color update
    # Input : None
    # Return: None
    # ----------------------------------------------------------------------
    def fAll_KeyDecode(self, sKeycode):

        self.gsKeyinData = sKeycode       # Key buffer in
        my_print("Key click:",sKeycode)

    # ----------------------------------------------------------------------
    # Function : fAll_KeyProcess
    # Description: Tab Buttom color update
    # Input : None
    # Return: None
    # ----------------------------------------------------------------------
    def fAll_KeyProcess(self, sKeycode):

        global Dialoglastkey, Dialoglast2key

        Dialoglast2key    = Dialoglastkey
        Dialoglastkey     = sKeycode

        if self.gsKeyinData == "":
            return

        # ================================================================
        #  Home/File/Parameter Tab Page Process
        # ================================================================
        lCurrentTab = self.tabWidget_Main.currentWidget().objectName()

        if lCurrentTab == "tab_Run":

            if sKeycode in ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9",".", "Space","Backspace"]:
                print("1-9")
            elif sKeycode in ["Left", "Right", "Up", "Down"]: 
                print("1-9")
            elif sKeycode in ["Enter"]:
                print("1-9")

        elif lCurrentTab == "tab_Paramter":
            if sKeycode in ["X_FULL"]:
                self.showNormal()
                # Exist Full Screen
                my_print("Exit Full Screen")
            elif sKeycode in ["I_FULL"]:
                # Full Screen
                self.showFullScreen()       
                my_print("Exit Full Screen")

    # ----------------------------------------------------------------------
    # Function      : fAll_KeyCmdProcess
    # Description   : Key command Interval process
    # Input         : None
    # Return        : None
    # ----------------------------------------------------------------------
    def fAll_KeyCmdProcess(self):

        #for sKeyCmdcode in list(self.gsKeyCmdData[:]):  # 這裡使用列表的副本
        if (len(self.gsKeyCmdData) > 0):

            sKeyCmdcode = self.gsKeyCmdData[0]
            my_print("KeyCmd Scan Code:", sKeyCmdcode)
            lsCommand = sKeyCmdcode.get("Command")  # Get command

            # ManualUp, ManualDown
            if lsCommand in ["ManualUp","ManualDown"]:
                
                lfUpdownTrigger = 0
                if  lsCommand == "ManualUp":        lupdown = 0
                else:                               lupdown = 1

                my_print("lsCommand Exec",lsCommand )
                # Get command info
                lsAxisName  = sKeyCmdcode.get("Axis")
                lMoveStep   = sKeyCmdcode.get("MoveStep")
                updownData  = sKeyCmdcode.get("X2Data")
                oldupdown   = sKeyCmdcode.get("oldupdown")
                state       = sKeyCmdcode.get("State")
                
                # wait sync
                if os.name == 'posix':#Raspberry
                    if (state == 1):
                        return

                # Update Paramter Tab 
                my_print(" ----------->>> Current Pos:", self.gdicPosData.get(lsAxisName), "OldDown:", oldupdown , "SendPos:", self.giSendPos)
                #self.gsKeyCmdData.remove(sKeyCmdcode)  # 已處理不再重複
                if  self.giSendPos == updownData :
                    my_print("========= Send Pos = updown , Same , skip !!")
                    self.giSendPos = 9999  # Reset
                    lfUpdownTrigger = 0 
                else:
                    if os.name != 'posix':#Raspberry
                        self.gdicPosData[lsAxisName] = updownData   # Display position 參照 read rPosition

                    lcurrentPHYStep = self.fDecode_CalPHY_step(lsAxisName,updownData)
                    lnewPHYStep = self.fDecode_CalPHY_step(lsAxisName,oldupdown)           
                    lPHYMoveStep = abs(lnewPHYStep -lcurrentPHYStep )
                    my_print("Axis",lsAxisName, "Move Step:", lPHYMoveStep ," = New Step:",lnewPHYStep ,"-Current Step:", lcurrentPHYStep, "X2 Date:",updownData )
                    lfUpdownTrigger = 1

                if lfUpdownTrigger == 1:
                    if self.gsKeyCmdData:
                        # 如果不为空，檢查第一個元素是否包含 'State' 鍵
                        if 'State' in self.gsKeyCmdData[0]:
                            self.gsKeyCmdData[0]['State'] = 1
                        else:
                            # 如果沒有 'State' 鍵，初始化 'State' 鍵值
                            self.gsKeyCmdData[0]['State'] = 1
                    else:
                        # 如果 self.gsKeyCmdData 為空列表，初始化並新增字典包含 'State' 鍵
                        self.gsKeyCmdData.append({'State': 1})
                    # self.gsKeyCmdData.append({'State': 1})
                    #self.gsKeyCmdData[0]['State'] = 1
                    self.giSendPos = int(updownData) 
                    # 軸號, Up/Down (0:up/1:down)(1), PHY Move Step(3), Step(4)        
                    self.fUART_ManualUpDownSendProvider(lsAxisName, lupdown, abs(int(lPHYMoveStep)), int(updownData) )
                    self.fRun_ValueDisplay(lsAxisName)
                    #self.fSpring_LabelObjUpdate(lsAxisName)

            if os.name != 'posix':# Window Mode
                self.fClearSyncforSpringAxisUpDown()

    # ----------------------------------------------------------------------
    # Function : fAll_KeyPushProcess
    # Description: Push Button Key Process
    # Input : None
    # Return: None
    # ----------------------------------------------------------------------
    def fAll_PushButtonRelease(self):

        sender = self.sender()  # Get the button that emitted the signal
        objName = sender.objectName()
        my_print("Object Button Release:", objName)
       
    def fAll_PushButtonPress(self):
        if (self.axis_long_press_timer.isActive()):
            return 
            
        self.axis_long_press_timeout_count=0
        self.axis_long_press_event_count=0
        self.axis_long_press_timer.start()            
        sender = self.sender()  # Get the button that emitted the signal
        objName = sender.objectName()
        self.gfPushButtonPress = objName
        self.gfPushButtonPressName = objName
        my_print("Object Button Press:", objName)


    def fAxisLongPressTimeout(self):
        #手動滑鼠按住"+/-"時 即使離開"+"仍持續是"+/-"功能
        def doKeyPushEvent():
            self.axis_long_press_event_count+=1
            self.gfPushButtonPress = self.gfPushButtonPressName
            self.fAll_KeyPushProcess()            
            
        if (QGuiApplication.mouseButtons() == Qt.LeftButton):
            # debounce 400ms
            self.axis_long_press_timeout_count+=1
            if (self.axis_long_press_timeout_count >= 8):            
                doKeyPushEvent()
        else:
            self.axis_long_press_timer.stop()
            if (self.axis_long_press_event_count == 0):
                doKeyPushEvent()

    def fGetAxisName_UpDown(self, objName):
        keyupdown = 0
        lsAxisName = ""
        
        if  "Down" in objName:          
            keyupdown = 0       # 0 - Down
            lsAxisName = "X2"
        elif "Up"  in objName:          
            keyupdown = 1       # 1 - Up
            lsAxisName = "X2"
        elif "Front"  in objName:          
            keyupdown = 1       # 1 - Up
            lsAxisName = "X1"
        elif "Rear"  in objName:          
            keyupdown = 1       # 1 - Up
            lsAxisName = "X1"

        return (keyupdown, lsAxisName)

    def fAll_KeyPushProcess(self):

        if self.gfPushButtonPress is not None:
            objName = self.gfPushButtonPress
            self.gfPushButtonPress = None
            my_print(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Key Press - ", objName)
            keyupdown, lsAxisName = self.fGetAxisName_UpDown(objName)
              
            # AxisName update
            self.fSpring_AxisManualUpDown(keyupdown, lsAxisName)       # 0: Down, 1:Up

    # ----------------------------------------------------------------------
    # Buton Up/Down/Front/Rear control
    # Description: fSpring_AxisManualUpDown
    # Input : None
    # Return: None
    # ----------------------------------------------------------------------
    def fSpring_AxisManualUpDown(self , keyupdown = None, lsAxisName = None):

        if self.msg_box_hint.isVisible():   # 錯誤訊息打開 不接受動作
            return

        my_print("fSpring_AxisManualUpDown")
       
        if  lsAxisName is None:
            sender = self.sender()  # 取得觸發事件的按鈕      
            objName = sender.objectName()            
            keyupdown, lsAxisName = self.fGetAxisName_UpDown(objName)
            if lsAxisName == "" :
                return  # no Axis click

        lsLogCmd = ""              
        updownData  = self.gdicPosData.get(lsAxisName)
        oldupdown   = updownData       

        lMoveStep      = self.gdicParaData.get("Power"+lsAxisName)
        lsMoveDisplay  = self.fEDIT_UnitFormat(lsAxisName , lMoveStep )
        lsMoveDisplay  = lsMoveDisplay.lstrip('+-')

        #  先確認原先就超過
        maxlimit = self.gdicParaData.get("MaxLimit"+lsAxisName) 
        minlimit = self.gdicParaData.get("MinLimit"+lsAxisName)
        lsmaxlimit = self.fEDIT_UnitFormat(lsAxisName, maxlimit)
        lsminlimit = self.fEDIT_UnitFormat(lsAxisName, minlimit)

        error_range_text = self.Language.GetErrorMessage("OutOfRange") + "," + self.Language.GetErrorMessage("Range") + "%s~%s" % (lsmaxlimit,lsminlimit)
        if  oldupdown > maxlimit or oldupdown < minlimit:
            updownData = minlimit
            self.fAll_Open_messagebox(error_range_text, 1)
            self.gfPushButtonPress = None       # Clear Key press, 避免迴圈
        else:
            if keyupdown == 1 :     # Up
                updownData = updownData + lMoveStep
                if updownData > maxlimit :
                    self.fAll_Open_messagebox(error_range_text, 1)
                    self.gfPushButtonPress = None       # Clear Key press, 避免迴圈
                    lMoveStep = maxlimit - oldupdown
                    updownData = maxlimit
                    # return                   
                else:
                    lMoveStep = updownData + oldupdown
                lsAxisMotorName = self.gdicParaData.get(("MotorName_" + lsAxisName),"") 
                lsLogCmd = self.Language.GetText("AXIS") + lsAxisMotorName + ": +" + str(lsMoveDisplay)                  
            elif keyupdown == 0:    # Down
                updownData = updownData - lMoveStep
                if updownData < minlimit :
                    self.fAll_Open_messagebox(error_range_text, 1)
                    self.gfPushButtonPress = None       # Clear Key press, 避免迴圈
                    lMoveStep = oldupdown - minlimit
                    updownData = minlimit
                    #return                   
                else:
                    lMoveStep = updownData - oldupdown
                lsAxisMotorName = self.gdicParaData.get(("MotorName_" + lsAxisName),"") 
                
            lupdown = 0 if (updownData > oldupdown) else 1    # 0:加/1:減
            my_print("Limit:", maxlimit if keyupdown == 1 else minlimit, "X2 data:", updownData, "Move Data:", lMoveStep)

        # Key command process
        if  keyupdown != None:              # 確定按鈕有被按下, 避免連按Lost  
            if (len(self.gsKeyCmdData) == 0):
                my_print("Axis Up/Down : go")                
                if  lupdown == 0:       # 0:加/1:減
                    self.gsKeyCmdData.append({"Command": "ManualUp", "Axis" : lsAxisName , "MoveStep": lMoveStep, "X2Data" : updownData , "oldupdown" : oldupdown, "State" : 0 })   
                else:
                    self.gsKeyCmdData.append({"Command": "ManualDown", "Axis" : lsAxisName , "MoveStep": lMoveStep, "X2Data" : updownData , "oldupdown" : oldupdown, "State" : 0 })   

                lsLogCmd = self.Language.GetText("AXIS") + lsAxisName + self.fEDIT_UnitFormat(lsAxisName ,oldupdown) + self.fEDIT_UnitFormat(lsAxisName ,lMoveStep) + " =" +  self.fEDIT_UnitFormat(lsAxisName ,updownData)
                self.fLog_AddTable(lsLogCmd) 
            else:
                my_print("Axis Up/Down : Skip")

        # if os.name =='posix':       # Raspi mode check

        my_print("End of fSpring_AxisManualUpDown")

    # ----------------------------------------------------------------------
    # Function : Setup Format by "Unit" setup
    # Input : SubTable keyin item
    # Return: Format SubTable item by "Unit" type
    # ----------------------------------------------------------------------
    def fEDIT_UnitFormat(self, lsAxisName, sValue):
       
        if sValue == None or sValue == "":
            return ""

        sValue = int(float(sValue))
        return  DataFormat.Digs4Dot2_PN_Format.format(sValue/100)       # mm 回復

    # ----------------------------------------------------------------------
    # Description:  Add Log Table
    # Function:     fLog_AddTable
    # Input :       
    # Return:       None
    # ----------------------------------------------------------------------
    def fLog_AddTable(self, action = ""):

        #lsHistoryFile = current_directory + '/' + defHistoryFile

        time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        actData  = {'time': str(time), "action": action}

        # if os.path.exists(lsHistoryFile):
        #     with open(lsHistoryFile,'r',encoding='utf-8') as fileStream:  # load file to Json file
        #         jsonData = json.load(fileStream)
        self.gArractData.insert(0, actData)
        #self.gArractData.append(actData )

        # with open(lsHistoryFile, 'w', encoding='utf-8') as fileStream:
        #     json.dump(jsonData, fileStream, indent=2, ensure_ascii=False)

    # ----------------------------------------------------------------------
    # fShow_DialogAllClose
    # Description:  ResetON
    # Input : 
    # Return: None
    # ----------------------------------------------------------------------
    def fShow_DialogAllClose(self):					

        # 關閉已開啟視窗
        dialogs = [ self.progress_widget]

        for dialog in dialogs:
            if dialog.isVisible():
                dialog.close()

    # ----------------------------------------------------------------------
    #    Progressbar Window , 沙漏顯示動畫 Timer.gif
    # ----------------------------------------------------------------------
    def fShow_PressbarBox(self,lMessage, lDisplayCnt = None, lDisplayMode = None):

        self.gsDisplayMode = lDisplayMode
       
        if self.msg_box_hint.isVisible():   # 錯誤訊息打開 關閉
            self.fAll_Close_messagebox()

        if lDisplayCnt:
            self.giWarningBoxCnt = lDisplayCnt * 20             # x 50 = 1秒
        else:
            self.giWarningBoxCnt = 0
        
        self.progress.label_Text.setWordWrap(True)
        self.progress.label_Text.setScaledContents(True)
        self.progress.label_Text.setAlignment(Qt.AlignCenter)
        self.progress.label_Text.setText(lMessage)
        # 设置 QLabel 的自动字体大小调整策略

        if not self.progress_widget.isVisible():
            #self.progress.movie = QMovie(":/Movie/gif/Timer.gif")                       
            #self.progress.label_Movie.setMovie(self.progress.movie)
            self.progress_widget.show()
            self.progress.movie.start()
        
        QApplication.processEvents()  # 强制刷新 UI

    def fShow_PressbarBoxClose(self):

        if self.gfAllKeySW != 2 and self.progress_widget.isVisible() :   # # 1: Key lock, 2: Switch on, 3: Reset On, 鍵盤切換 不關閉
            self.progress_widget.close()
            self.progress.movie.stop()
            self.gsDisplayMode = None
        else:
            my_print("ProssBar No close, Key SW:", self.gfAllKeySW)

        self.giSendPos = 9999  # Reset

    # ===================================================================
    #    Tab : Decode
    # ===================================================================

    # ---------------------------------------------------------------
    # Function: fDecode_CalPHY_step
    # Calculate ms, step from Table data
    # Input : None
    # Return: None
    #----------------------------------------------------------------
    def fDecode_CalPHY_step(self, lsAxisName, liTblData, Mod = None):

        lstep = 0.0
        unitCellName = "Unit"+ lsAxisName
        my_print("fDecode_CalPHY_step input:",lsAxisName, "liTblData", liTblData, "Mod",Mod)

        if (liTblData != "" and liTblData != None) and (self.gdicParaData.get("Gear1"+ lsAxisName, 0 ) > 0):
            # Data conversiob
            liTblData = int(liTblData)
            self.gdicParaData["MotorStep"+ lsAxisName] = int(self.gdicParaData["MotorStep"+ lsAxisName])

            lGearRation = int(self.gdicParaData["Gear0"+ lsAxisName]) / int(self.gdicParaData["Gear1"+ lsAxisName]) 
            #cellForm = self.fAdvancedParam_GetFormByCellName("ZRTPosition"+lsAxisName)
            # 0:格數 / 1:角度 / 2:mm / 3:圈數
            # 0:格數 Digs6_PN / 1:角度 Digs4Dot1_PN / 2:mm Digs4Dot2_PN / 3:圈數 Digs2Dot3_PN
            if self.gdicParaData[unitCellName] == 0 and (self.gdicParaData.get("MotorLogicalPosition"+ lsAxisName,0) > 0) :    # 格數
                lstep = (liTblData * self.gdicParaData["MotorStep"+ lsAxisName] * lGearRation) / (self.gdicParaData["MotorLogicalPosition"+ lsAxisName])
                my_print(" 0:格數 :馬達格數 x 齒輪比 / 邏輯格數 x 差異值=", lstep)
            elif self.gdicParaData[unitCellName] == 1:  # 角度
                if Mod == 1:                            # 虛擬原點 找最近圈數
                    lstep = (((math.fmod(liTblData, 3600)) * self.gdicParaData["MotorStep"+ lsAxisName] ) * lGearRation) / 3600
                    #lstep = (((liTblData%3600) * self.gdicParaData["MotorStep"+ lsAxisName]) * lGearRation)/3600
                    #print("ParaData", self.gdicParaData["MotorStep"+ lsAxisName], "Gear Ration",lGearRation)
                else:                                   # 角度
                    lstep = ((liTblData * self.gdicParaData["MotorStep"+ lsAxisName]) * lGearRation)/3600
                my_print("角度 = 馬達格數 x 齒輪比 / 360 x 差異值=", lstep)
            elif self.gdicParaData[unitCellName] == 2:  # mm
                my_print("liTblData:",liTblData, ",Data:",self.gdicParaData["UnitExchange"+ lsAxisName])
                lstep = (liTblData * self.gdicParaData["UnitExchange"+ lsAxisName])/10000  # # 0.01mm
#                lstep = liTblData * (int(self.gdicParaData["UnitExchange"+ lsAxisName]) )/10/100     # 0.01mm
                my_print(" mm = 單位換算 x 差異值=", lstep, ",Data:", liTblData, ",UnitExchange:", self.gdicParaData["UnitExchange"+ lsAxisName])
            elif self.gdicParaData[unitCellName] == 3:  # 圈數
                lstep = ((liTblData * self.gdicParaData["MotorStep"+ lsAxisName]) * lGearRation)/1000
                my_print(" 圈數 =  馬達格數 x 齒輪比 x 差異值 =", lstep)
        return  int(lstep)

    # ===================================================================
    #    Tab : Run - Program
    # ===================================================================
    # ----------------------------------------------------------------------
    # Power level switch
    # Description: fRun_PWRSwitch
    # Input : None
    # Return: None
    # ----------------------------------------------------------------------
    def fRun_PWRSwitch(self):

        sender = self.sender()  # Get the button that emitted the signal

        if  sender is not None:
            objName = sender.objectName()

            if  objName == "pushButton_PowerUpDown":
                if  self.gdicParaData["PowerX2"] == 1:
                    self.gdicParaData["PowerX2"] = 10
                elif    self.gdicParaData["PowerX2"] == 10:
                    self.gdicParaData["PowerX2"] = 100
                else:
                    self.gdicParaData["PowerX2"] = 1

                self.fDisplay_PWR("X2", self.gdicParaData["PowerX2"])

            else:
                if  self.gdicParaData["PowerX1"] == 1:
                    self.gdicParaData["PowerX1"] = 10
                elif    self.gdicParaData["PowerX1"] == 10:
                    self.gdicParaData["PowerX1"] = 100
                else:
                    self.gdicParaData["PowerX1"] = 1

                self.fDisplay_PWR("X1",self.gdicParaData["PowerX1"])

   # ----------------------------------------------------------------------
    # Power level switch
    # Description: fRun_PWRSwitch
    # Input : None
    # Return: None
    # ----------------------------------------------------------------------
    def fDisplay_PWR(self, lsType , liPower):

        lsPWR = "x" + str(liPower)

        if  lsType == "X2":
            self.pushButton_PowerUpDown.setText(lsPWR)
        else:
            self.pushButton_PowerFrontRear.setText(lsPWR)

        my_print("PWR Switch:",lsType ,",Power:",lsPWR)

   # ----------------------------------------------------------------------
    # Reset Processs
    # Description: fRun_Reset
    # Input : None
    # Return: None
    # ----------------------------------------------------------------------
    def fRun_Reset(self):

        self.gdicPosData["X2"] = 1
        self.gdicPosData["X1"] = 1

        self.fRun_UpDownValueDisplay(self.gdicPosData["X2"])
        self.fRun_FRValueDisplay(self.gdicPosData["X1"])

        my_print("fRun_Reset")

    # ----------------------------------------------------------------------
    # Zero Process
    # Description: fRun_Zero
    # Input : None
    # Return: None
    # ----------------------------------------------------------------------
    def fRun_Zero(self):

        my_print("fRun_Zero")


    # ----------------------------------------------------------------------
    # Set Process
    # Description: fRun_Set
    # Input : None
    # Return: None
    # ----------------------------------------------------------------------
    def fRun_Set(self):

        sender = self.sender()  # Get the button that emitted the signal

        if  sender is not None:
            objName = sender.objectName()
            #try:
            #  Front Rear
            if objName == "pushButton_FRSet1" :       # FrontRear Set
                self.gdicParaData["Value1X1"] = int(self.label_FrontRearValue1.text())
                self.label_FrontRear1.setText(str(self.gdicParaData["Value1X1"]))
            elif objName == "pushButton_FRSet2" :       # FrontRear Set
                self.gdicParaData["Value2X1"] = int(self.label_FrontRearValue1.text())
                self.label_FrontRear2.setText(str(self.gdicParaData["Value2X1"]))
            
            # Up Down
            elif objName == "pushButton_Updown1" :       # FrontRear Set
                self.gdicParaData["Value1X2"] = int(self.label_UpDownValue1.text())
                self.label_Updown1.setText(str(self.gdicParaData["Value1X2"]))

            elif objName == "pushButton_Updown2" :       # FrontRear Set
                self.gdicParaData["Value2X2"] = int(self.label_UpDownValue1.text())
                self.label_Updown2.setText(str(self.gdicParaData["Value2X2"]))
              
            #except ValueError:
            #    my_print("轉換錯誤")

        self.fFile_SaveParamter()

        my_print("ObjName:", objName)

    # ----------------------------------------------------------------------
    # Function : Change Language by iLanguage setting
    # Input : None
    # Return: None
    # ----------------------------------------------------------------------
    def fRun_ProcessSwitch(self):

        sender = self.sender()  # Get the button that emitted the signal
        if  sender is not None:
            objName = sender.objectName()

            if  objName == "pushButton_Process1":
                self.gfProcessSwitch = "Process12"
            else:
                self.gfProcessSwitch = "Process2"
        
        self.fRun_ProcessButtonDisplay()

    def fRun_ProcessButtonDisplay(self):

        if  self.gfProcessSwitch == "Process2":
            self.pushButton_Process1.setStyleSheet("background-color: white;")
            self.pushButton_Process2.setStyleSheet("background-color: #55FFFF;")
            # Running GIF 
            self.movie = QMovie(":/Movie/gif/Process1.gif")          

        else:
            self.pushButton_Process1.setStyleSheet("background-color: #55FFFF;")
            self.pushButton_Process2.setStyleSheet("background-color: white;")

            # Running GIF 
            self.movie = QMovie(":/Movie/gif/Process12.gif")          

        self.label_GIF.setMovie(self.movie)
        self.movie.start()

    # ----------------------------------------------------------------------
    # Set Process
    # Description: fRun_Position
    # Input : None
    # Return: None
    # ----------------------------------------------------------------------
    def fRun_Position(self):

        sender = self.sender()  # Get the button that emitted the signal
        objName = sender.objectName()
        my_print("ObjName:", objName)

        # Up Down
        if objName in ["pushButton_Up", "pushButton_Down"]:
            if self.gdicParaData["PowerX2"] > 100:
                self.gdicParaData["PowerX2"] = 1
            
            if objName == "pushButton_Up":
                self.gdicPosData["X2"] = self.fRun_UpDownValueDisplay(self.gdicPosData["X2"]+self.gdicParaData["PowerX2"])
            else:
                self.gdicPosData["X2"] = self.fRun_UpDownValueDisplay(self.gdicPosData["X2"]-self.gdicParaData["PowerX2"])
        # Front Rear
        else:
            if self.gdicParaData["PowerX1"] > 100:
                self.gdicParaData["PowerX1"] = 1
            
            if objName == "pushButton_Front":
                self.gdicPosData["X1"] = self.fRun_FRValueDisplay(self.gdicPosData["X1"]-self.gdicParaData["PowerX1"])
            else:
                self.gdicPosData["X1"] = self.fRun_FRValueDisplay(self.gdicPosData["X1"]+self.gdicParaData["PowerX1"])

    def fRun_AxisDisplay(self, lsAxisName , value = 0 ):

        if  lsAxisName == "X1":
            self.gdicPosData["X1"] = value
            self.fRun_FRValueDisplay(value)
        else:
            self.gdicPosData["X2"] = value
            self.fRun_UpDownValueDisplay(value)


    def fRun_FRValueDisplay(self, value = 0):

        if value > 1000:
            value = 1000
        elif value < 0:
            value = 0

        self.label_FrontRearValue1.setText(str(value))
        self.label_FrontRearValue2.setText(str(value))
        return value


    def fRun_UpDownValueDisplay(self, value = 0):

        if value > 100:
            value = 100
        elif value < 0:
            value = 0

        self.label_UpDownValue1.setText(str(value))
        self.label_UpDownValue2.setText(str(value))
        return value

    # ----------------------------------------------------------------------
    # Function: fRun_ValueDisplay
    # Description: Value Display
    # Input : None
    # Return: None
    # ----------------------------------------------------------------------
    def fRun_ValueDisplay(self, lsAxis):

        lsMachineAxis = ParamTable.ArrPara_AxisMapping(lsAxis)

        print("Axis:",lsAxis, "LMAxis:",lsMachineAxis)

        if  lsMachineAxis == "FrontRear":
            self.fRun_FRValueDisplay(self.gdicPosData[lsAxis])
        else:
            self.fRun_UpDownValueDisplay(self.gdicPosData[lsAxis])

        my_print("fRun_Reset")

    # ===================================================================
    #    File Process
    # ===================================================================
    # Description:     File
    # Function: Get Default Parameter
    # Input:    none
    # Return:   None
    # ----------------------------------------------------------------------
    def fFile_GetParaDefaultData(self):

        def update_default_data(defaultData, paramForm):
            for CellName, CellForm in paramForm.items():
                # Panel_TabeleForm load default
                if CellForm.get('Item') is not None:
                    for item in CellForm['Item']:
                        defaultData[item['CellName']] = item['DefautlValue']
                else:
                    # Panel_TabeleForm load default
                    if isinstance(CellForm, dict):
                        for item, Data in CellForm.items():
                            if Data.get("DefautlValue") is not None:
                                defaultData[item] = Data['DefautlValue']

        defaultData = dict()
        defaultData.update(ParamTable.ArrPara_TableDefault)

        update_default_data(defaultData, ParamTable.AdvancedParam_TableForm)

        return defaultData


    # ----------------------------------------------------------------------
    # Description:     File
    # Function: Load Parameter
    # Input:    none
    # Return:   None
    # ----------------------------------------------------------------------
    def fFile_LoadParameter(self, lForceLoad = ""):
               
        newData = self.fFile_GetParaDefaultData()       # Load default data
        loadData    = {}

        filePath = self.gFilePath 
        fileName = filePath + '/' + defParameterFile
       
        # ----------------------------------------------------------------
        # Load Paramter file      
        my_print("Paramter folder: " + fileName)
        try:
            if os.path.exists(fileName):
                with open(fileName, 'r', encoding='utf-8') as fileStream:  # load file from Json file
                    fileContent = fileStream.read()  # 读取文件内容为字符串
                    if not fileContent:
                        loadData = {}
                    else:
                        loadData = json.loads(fileContent)  # 将字符串加载为 Python 对象
                    
                if loadData and isinstance(loadData, dict):
                    if loadData.get("gdicParameter") is None:       # Check old Paramter type
                        lParamterData           = copy.deepcopy(newData)
                        self.gdicParaData       = {}
                    else:
                        lParamterData   = loadData.get('gdicParameter'  , {})
                        #newData   = copy.deepcopy(lParamterData)      # 將 位置轉換成 Int 因為 所有Int 都會被轉換成 String
                else:
                    lParamterData           = copy.deepcopy(newData)
                    self.gdicParaData       = {}

                for CellName, CellValue in list(lParamterData.items()):     # Load ParamterData
                    newData[CellName] = CellValue

            elif lForceLoad == "":            # Force load 為開新檔案, 強制讀取Default data
                my_print("Paramter File Not Found")     # 開檔錯誤 關閉程式
                self.gdicParaData = newData  
                self.Language = Language.Language(self.gdicParaData["Language"])         

                ErrorMsg = self.Language.GetText("PARA") + self.Language.GetErrorMessage("File_No_Found")
                self.fAll_Open_messagebox(ErrorMsg, 3)
                #sys.exit(1)  # 关闭应用程序
        finally:
            self.gdicParaData = newData  
            self.fFile_SaveParamter()

    # ----------------------------------------------------------------------
    # Description:     File
    # Function: Save Parameter
    # Input:    none
    # Return:   None
    # ----------------------------------------------------------------------
    def fFile_SaveParamter(self, lSaveContent=True ):

        # Check /Program path fist       
        filePath = self.gFilePath
        fileName = filePath + '/' + defParameterFile
        if not os.path.isdir(filePath):                 os.mkdir(filePath)

        my_print("Paramter File Save:" + fileName)
        combined_dict = {
            'gdicParameter'  : self.gdicParaData,
        }

        try:
            if (lSaveContent == True):        
                self.fFile_SaveJsonFile(fileName, combined_dict)   
           
        except:
            my_print("Paramter Error")

    # ----------------------------------------------------------------------
    # Description   : save json to json file
    # Function      : fFile_CopyButtonEvent
    # Input         : json data, 
    # Return        : None
    # ----------------------------------------------------------------------
    def fFile_SaveJsonFile(self, lFilename, jsonData):     
         
        def convert_keys_to_str(d):
            """将字典中的所有键转换为字符串"""
            if isinstance(d, dict):
                return {str(key): convert_keys_to_str(value) for key, value in d.items()}
            elif isinstance(d, list):
                return [convert_keys_to_str(item) for item in d]
            else:
                return d

        jsonstr = convert_keys_to_str(jsonData)
        json_bytes = json.dumps(jsonstr, option=json.OPT_INDENT_2)

        # 以二进制模式打开文件并写入字节串
        with open(lFilename, "wb") as fileStream:
            fileStream.write(json_bytes)

    # ===================================================================
    #    Global Generic Functions
    # ===================================================================
    # ----------------------------------------------------------------------
    # Function : Change Language by iLanguage setting
    # Input : None
    # Return: None
    # ----------------------------------------------------------------------
    def fAll_LanguageRadioClicked(self, button):
        # Get the ID of the selected radioButton
        selected_id = self.buttonGroup.id(button)
        self.Language.SetIndex(selected_id-1)
        self.fAll_LanguageDisplay(selected_id-1, 1)
        self.fFile_SaveParamter()

    #Set Title Language
    def fAll_LanguageDisplay(self, Language, RefreshAll = 0 ):

        if Language > 3:    Language = 3        # Language Max
        self.gdicParaData["Language"] = Language

        self.tabWidget_Main.setTabText(0, self.Language.GetText("RUN"))
        self.tabWidget_Main.setTabText(1, self.Language.GetText("PARA"))

        self.pushButton_Updown1.setText(self.Language.GetText("SET"))
        self.pushButton_Updown2.setText(self.Language.GetText("SET"))
        self.pushButton_FRSet1.setText(self.Language.GetText("SET"))
        self.pushButton_FRSet2.setText(self.Language.GetText("SET"))

        self.label_LoadLable1.setText(self.Language.GetText("Load")+"-1")
        self.label_LoadLable2.setText(self.Language.GetText("Load")+"-2")
        self.label_LoadLable3.setText(self.Language.GetText("Load")+"-3")
        self.label_LoadLable4.setText(self.Language.GetText("Load")+"-4")

        self.pushButton_HomeUpDown.setText(self.Language.GetText("Home"))
        self.pushButton_HomeFrontRear.setText(self.Language.GetText("Home"))

        # 程序按鍵
        self.pushButton_Process1.setText(self.Language.GetText("Process")+" 1->2")
        self.pushButton_Process2.setText(self.Language.GetText("Process")+" 2")

        self.label_1Label.setText(self.Language.GetText("Process")+"1")
        self.label_2Label.setText(self.Language.GetText("Process")+"2")

        # Progress Format display
        process_text = self.Language.GetText("g")  # 获取动态文本
        self.progressBar1.setFormat(f"%v {process_text}")
        self.progressBar2.setFormat(f"%v {process_text}")
        self.progressBar3.setFormat(f"%v {process_text}")
        self.progressBar4.setFormat(f"%v {process_text}")


        my_print("Language:",Language)

    # ----------------------------------------------------------------------
    # Description:  Error Msg
    # Function:     Error Message display, close by timer
    # Input :       Display Msg, Closetime (Sec)
    # Return:       Digits, Dot
    # ----------------------------------------------------------------------
    def fAll_Open_messagebox(self, ErrorMsg, liclosetime = 1):

        if self.progress_widget.isVisible():
            self.fShow_PressbarBoxClose()

        self.msg_box_hint.setText(ErrorMsg)
        self.msg_box_hint.show()      
        # 使用 QTimer 延迟显示消息框
        QTimer.singleShot(0, self.msg_box_hint.show)        
        QApplication.processEvents()
        QTimer.singleShot((liclosetime*1000), self.fAll_Close_messagebox)

    def fAll_Close_messagebox(self):
        #self.msg_box_hint.close()
        self.msg_box_hint.hide()

    # ===================================================================
    #                       Initialize
    # ===================================================================
    # ----------------------------------------------------------------------
    # File All Event inialize
    # Description: fAll_InitEvent
    # Input : None
    # Return: None
    # ----------------------------------------------------------------------
    def fAll_InitEvent(self):

        # Windows Key interrupt initialize
        self.Init_Keyinterrupt()

        # Push Button Process
        self.pushButton_PowerFrontRear.clicked.connect(self.fRun_PWRSwitch)
        self.pushButton_PowerUpDown.clicked.connect(self.fRun_PWRSwitch)
        self.pushButton_HomeFrontRear.clicked.connect(self.fRun_Zero)
        self.pushButton_HomeUpDown.clicked.connect(self.fRun_Zero)

        # Updown, Front Rear Setup
        self.pushButton_Updown1.clicked.connect(self.fRun_Set)
        self.pushButton_Updown2.clicked.connect(self.fRun_Set)
        self.pushButton_FRSet1.clicked.connect(self.fRun_Set)
        self.pushButton_FRSet2.clicked.connect(self.fRun_Set)

        # Updown, Front Rear Position 
        # self.pushButton_Up.clicked.connect(self.fRun_Position)
        # self.pushButton_Down.clicked.connect(self.fRun_Position)
        # self.pushButton_Front.clicked.connect(self.fRun_Position)
        # self.pushButton_Rear.clicked.connect(self.fRun_Position)

        # Process Button Switch
        self.pushButton_Process1.clicked.connect(self.fRun_ProcessSwitch)
        self.pushButton_Process2.clicked.connect(self.fRun_ProcessSwitch)

        self.buttonGroup = QButtonGroup(self)
        self.buttonGroup.addButton(self.radioButton_English, 1)
        self.buttonGroup.addButton(self.radioButton_Chinese, 2)
        self.buttonGroup.addButton(self.radioButton_Simplified, 3)
        self.buttonGroup.buttonClicked.connect(self.fAll_LanguageRadioClicked)
        self.buttonGroup.button(self.gdicParaData["Language"]+1).setChecked(True)

        # 上下左右控制
        buttons = {
            "Button_Up"     : self.pushButton_Up,
            "Button_Down"   : self.pushButton_Down,
            "Button_Rear"   : self.pushButton_Rear,
            "Button_Front"  : self.pushButton_Front,
        }
        # 按钮的Event link
        for button_name, button in buttons.items():
            button.pressed.connect(self.fAll_PushButtonPress)
            button.released.connect(self.fAll_PushButtonRelease)
            button.setAutoRepeat(False)

        my_print("End of fAll_InitEvent Function")

    # ----------------------------------------------------------------------
    # Description:  Initial all Variable
    # Function:     initVariable
    # Input :       
    # Return:       None
    # ----------------------------------------------------------------------
    def initVariable(self):

        self.gsDisplayMode = None
        self.gsKeyinData = ""
        self.giKeyInterruptCnt = 0
        self.gsKeyCmdData = []
        self.gFilePath = current_directory + defProgramPath
        self.gdicErrorMsg = {}             # Reset Error String       

        self.gdicPosData = {}
        self.gdicPosData["X2"] = 1
        self.gdicPosData["X1"] = 0
        self.gdicParameterTemp = {}

        self.gfProcessSwitch = "Process12"          # 設定成初始為 Process 1-2
        self.gfAllKeySW = 0                         # 1: Key lock, 2: Switch on, 3: Reset On
        self.gfVRRunMode = 0                        # 1: Test Mode, 2: Production Mode

        self.gwLoadCellData = [0,0,0,0]
        self.gArractData = []
        self.giSendPos = 9999

        self.fUARTInit()

    # ----------------------------------------------------------------------
    # Description:  UI initialize
    # Function:     initUi
    # Input :       
    # Return:       None
    # ----------------------------------------------------------------------
    def fAll_initUI(self):

        self.fDisplay_PWR("X2", self.gdicParaData["PowerX2"])
        self.fDisplay_PWR("X1", self.gdicParaData["PowerX1"])

        self.fAll_LanguageDisplay(self.gdicParaData["Language"])
        self.fRun_UpDownValueDisplay(self.gdicPosData["X2"])
        self.fRun_FRValueDisplay(self.gdicPosData["X1"])

        # Vaule display update
        self.label_FrontRear1.setText(str(self.gdicParaData["Value1X1"]))
        self.label_FrontRear2.setText(str(self.gdicParaData["Value2X1"]))           
        self.label_Updown1.setText(str(self.gdicParaData["Value1X2"]))
        self.label_Updown2.setText(str(self.gdicParaData["Value2X2"]))

        self.fRun_ProcessSwitch()

        my_print("End of initUI Function")

    # ----------------------------------------------------------------------
    # Description:  UI initialize
    # Function:     initUi
    # Input :       
    # Return:       None
    # ----------------------------------------------------------------------
    def fAll_initUIStyle(self):

        self.setCentralWidget(self.tabWidget_Main)
        self.tabWidget_Main.setStyleSheet("QTabWidget {border: 3px dashed blue;}")
        lClockTabSize = 10             # Clock Label width size

        tab_bar = self.tabWidget_Main.tabBar()
        tab_bar.setStyleSheet("""
            QTabBar::tab {
                height: 50px;   
                width: 492px;
                border-radius: 4px;
                background-color: %s;
                color: %s;
                font-weight: bold;  
            }
            QTabBar::tab:selected {
                background-color: %s;                              
                color: %s;
            }
            QTabBar::tab:first {
                background-repeat: no-repeat;
                margin-left: %spx;
            }                              
       """ % ("#CDCDCD", "#585858", "#888888", "white", lClockTabSize ))        

    # ----------------------------------------------------------------------
    # Description:  Main Window initialize
    # Function:     Main System All initialize
    # Input :       
    # Return:       None
    # ----------------------------------------------------------------------
    def __init__(self, parent=None):

        super(MyMainWindow, self).__init__(parent)
        self.setupUi(self)

        self.save_thread = None # Save thread

        # -------------------------------------------------------------
        # Progress Window Setup
        self.progress_widget = QtWidgets.QDialog(self)
        self.progress = Ui_ProgressBar()

        self.progress.setupUi(self.progress_widget)
        self.progress_widget.setWindowFlags(self.progress_widget.windowFlags() & ~QtCore.Qt.WindowContextHelpButtonHint)
        self.progress_widget.setFixedSize(self.progress_widget.size())
        self.progress.movie = QMovie(":/Movie/gif/Timer.gif")                       
        self.progress.label_Movie.setMovie(self.progress.movie)
        
        self.progressBar1.setRange(0, 5000);
        self.progressBar2.setRange(0, 5000);
        self.progressBar3.setRange(0, 5000);
        self.progressBar4.setRange(0, 5000);        

        self.msg_box_hint = QMessageBox()
        self.msg_box_hint.setIcon(QMessageBox.Warning)
        # -------------------------------------------------------------
        self.initVariable()
        self.fFile_LoadParameter()
        self.Language = Language.Language(self.gdicParaData["Language"])         

        self.fAll_InitEvent()
        self.fAll_initUI()
        self.fAll_initUIStyle()

        if (self.UARTCmd is not None):
            self.UARTCmd.ClearReceiverBuf()             # delete all UART Buffer     

        self.msg_box_hint = QMessageBox()
        self.msg_box_hint.setIcon(QMessageBox.Warning)
        self.msg_box_hint.setWindowTitle(self.Language.GetText("Error"))

        self.tabWidget_Main.setCurrentWidget(self.tab_Run)
        self.msg_box_hint.setWindowTitle(self.Language.GetText("Error"))

        # -------------------------------------------------------------
        # Timwer initialize
        self.timer = QTimer()
        self.timer.setTimerType(Qt.PreciseTimer)  # 设置为精确计时器
        self.timer.setInterval(5)
        self.timer.timeout.connect(self.fUART_Interval)             # UART interval check
        self.timer.timeout.connect(self.fAll_KeyInterval)     # Key interval check
        self.timer.start() 

        #軸常按鍵的處理,不使用autorepeat.
        self.axis_long_press_timer = QTimer()
        self.axis_long_press_timer.setInterval(50)
        self.axis_long_press_timer.setTimerType(Qt.PreciseTimer)  # 设置为精确计时器
        self.axis_long_press_timer.timeout.connect(self.fAxisLongPressTimeout)

        if os.name=='posix': # Raspi Testing
            self.showFullScreen()

# ----------------------------------------------------------------------
# Function : Main Program
# ----------------------------------------------------------------------
if __name__=="__main__":

    globals.initialize()            # global initialize

    app = QApplication(sys.argv)
    app.setStyle('Windows')

    myWin = MyMainWindow()
    myWin.show()
    sys.exit(app.exec())
