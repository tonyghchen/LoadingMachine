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

from functools          import partial
from PySide6            import QtWidgets, QtGui, QtCore
from PySide6.QtWidgets  import QApplication, QMainWindow, QButtonGroup, QMessageBox
from PySide6.QtCore     import Qt, QTimer
from PySide6.QtGui      import QMovie

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
            "defUART_rErrorMsg"         : { lsHandler:self.fUARTCmd_rErrorMsg,          lsDel : False },
            "defUART_rPosition"         : { lsHandler:self.fUARTCmd_rPosition,          lsDel : True  },
            "defUART_rKeyboard"         : { lsHandler:self.fUARTCmd_rKeyboard,          lsDel : False },
            "defUART_rCurrProductQty"   : { lsHandler:self.fUARTCmd_rCurrProductQty,    lsDel : False },
            "defUART_rCurrProductTime"  : { lsHandler:self.fUARTCmd_rCurrProductTime,   lsDel : False },
            "defUART_rCurrFailQty"      : { lsHandler:self.fUARTCmd_rCurrFailQty,       lsDel : False },
            "defUART_rOverUnderFlow"    : { lsHandler:self.fUARTCmd_rOverUnderFlow,     lsDel : False },
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

    def fUARTCmd_rErrorMsg(self, receiver_data, lCmd, liCmdReadBytes):
        lErrorAxis = receiver_data[2]
        lErrorCode = receiver_data[3]
        self.fUART_rErrorMsg(lErrorAxis, lErrorCode)         
        
    def fUARTCmd_rPosition(self, receiver_data, lCmd, liCmdReadBytes):  
        # clear sync 
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
    # UART interrupt process
    # Description: UART interrupt interval
    # ----------------------------------------------------------------------   
    def fUART_Interval(self):    

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
                self.gdicParaData["PowerUpDown"] = self.gdicParaData.get("PowerUpDown", 0) + 1

                if  self.gdicParaData["PowerUpDown"] >= 3:
                    self.gdicParaData["PowerUpDown"] = 0
                self.fDisplay_PWR("UpDown", self.gdicParaData["PowerUpDown"])

            else:
                self.gdicParaData["PowerFrontRear"] = self.gdicParaData.get("PowerFrontRear", 0) + 1

                if  self.gdicParaData["PowerFrontRear"] >= 3:
                    self.gdicParaData["PowerFrontRear"] = 0

                self.fDisplay_PWR("FrontRear",self.gdicParaData["PowerFrontRear"])

   # ----------------------------------------------------------------------
    # Power level switch
    # Description: fRun_PWRSwitch
    # Input : None
    # Return: None
    # ----------------------------------------------------------------------
    def fDisplay_PWR(self, lsType , liPower):

        lsPWR = ""
        if  liPower == 1:
            lsPWR = "x10"
        elif liPower == 2:
            lsPWR = "x100"
        else:
            lsPWR = "x1"

        if  lsType == "UpDown":
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

        self.gdicPosData["UpDown"] = 0 
        self.gdicPosData["FR"] = 0

        self.fRun_UpDownValueDisplay(self.gdicPosData["UpDown"])
        self.fRun_FRValueDisplay(self.gdicPosData["FR"])

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
                self.gdicParaData["ValueFrontRear1"] = int(self.label_FrontRearValue1.text())
                self.label_FrontRear1.setText(str(self.gdicParaData["ValueFrontRear1"]))
            elif objName == "pushButton_FRSet2" :       # FrontRear Set
                self.gdicParaData["ValueFrontRear2"] = int(self.label_FrontRearValue1.text())
                self.label_FrontRear2.setText(str(self.gdicParaData["ValueFrontRear2"]))
            
            # Up Down
            elif objName == "pushButton_Updown1" :       # FrontRear Set
                self.gdicParaData["ValueUpDown1"] = int(self.label_UpDownValue1.text())
                self.label_Updown1.setText(str(self.gdicParaData["ValueUpDown1"]))

            elif objName == "pushButton_Updown2" :       # FrontRear Set
                self.gdicParaData["ValueUpDown2"] = int(self.label_UpDownValue1.text())
                self.label_Updown2.setText(str(self.gdicParaData["ValueUpDown2"]))
              
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
            if self.gdicParaData["PowerUpDown"] > 3:
                self.gdicParaData["PowerUpDown"] = 2
            
            liPower = 10 ** self.gdicParaData["PowerUpDown"]

            if objName == "pushButton_Up":
                self.gdicPosData["UpDown"] = self.fRun_UpDownValueDisplay(self.gdicPosData["UpDown"]+liPower)
            else:
                self.gdicPosData["UpDown"] = self.fRun_UpDownValueDisplay(self.gdicPosData["UpDown"]-liPower)
        # Front Rear
        else:
            if self.gdicParaData["PowerFrontRear"] > 3:
                self.gdicParaData["PowerFrontRear"] = 2
            
            liPower = 10 ** self.gdicParaData["PowerFrontRear"]

            if objName == "pushButton_Front":
                self.gdicPosData["FR"] = self.fRun_FRValueDisplay(self.gdicPosData["FR"]-liPower)
            else:
                self.gdicPosData["FR"] = self.fRun_FRValueDisplay(self.gdicPosData["FR"]+liPower)


    def fRun_FRValueDisplay(self, value = 0):

        if value > 1000:
            value = 1000
        elif value < 0:
            value = 0

        self.label_FrontRearValue1.setText(str(value))
        self.label_FrontRearValue2.setText(str(value))
        return value


    def fRun_UpDownValueDisplay(self, value = 0):

        if value > 1000:
            value = 1000
        elif value < 0:
            value = 0

        self.label_UpDownValue1.setText(str(value))
        self.label_UpDownValue2.setText(str(value))
        return value

    # ===================================================================
    #    File Process
    # ===================================================================
    # Description:     File
    # Function: Get Default Parameter
    # Input:    none
    # Return:   None
    # ----------------------------------------------------------------------
    def fFile_GetParaDefaultData(self):

        defaultData = dict()
        defaultData.update(ParamTable.ArrPara_TableDefault)
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
        self.pushButton_Up.clicked.connect(self.fRun_Position)
        self.pushButton_Down.clicked.connect(self.fRun_Position)
        self.pushButton_Front.clicked.connect(self.fRun_Position)
        self.pushButton_Rear.clicked.connect(self.fRun_Position)

        # Process Button Switch
        self.pushButton_Process1.clicked.connect(self.fRun_ProcessSwitch)
        self.pushButton_Process2.clicked.connect(self.fRun_ProcessSwitch)

        self.buttonGroup = QButtonGroup(self)
        self.buttonGroup.addButton(self.radioButton_English, 1)
        self.buttonGroup.addButton(self.radioButton_Chinese, 2)
        self.buttonGroup.addButton(self.radioButton_Simplified, 3)
        self.buttonGroup.buttonClicked.connect(self.fAll_LanguageRadioClicked)
        self.buttonGroup.button(self.gdicParaData["Language"]+1).setChecked(True)

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
        self.gdicPosData["UpDown"] = 0
        self.gdicPosData["FR"] = 0

        self.gfProcessSwitch = "Process12"          # 設定成初始為 Process 1-2
        self.gfAllKeySW = 0                         # 1: Key lock, 2: Switch on, 3: Reset On
        self.gfVRRunMode = 0                        # 1: Test Mode, 2: Production Mode

        self.gwLoadCellData = [0,0,0,0]
        self.fUARTInit()

    # ----------------------------------------------------------------------
    # Description:  UI initialize
    # Function:     initUi
    # Input :       
    # Return:       None
    # ----------------------------------------------------------------------
    def fAll_initUI(self):

        self.fDisplay_PWR("UpDown", self.gdicParaData["PowerUpDown"])
        self.fDisplay_PWR("FrontRear", self.gdicParaData["PowerFrontRear"])

        self.fAll_LanguageDisplay(self.gdicParaData["Language"])
        self.fRun_UpDownValueDisplay(self.gdicPosData["UpDown"])
        self.fRun_FRValueDisplay(self.gdicPosData["FR"])

        # Vaule display update
        self.label_FrontRear1.setText(str(self.gdicParaData["ValueFrontRear1"]))
        self.label_FrontRear2.setText(str(self.gdicParaData["ValueFrontRear2"]))           
        self.label_Updown1.setText(str(self.gdicParaData["ValueUpDown1"]))
        self.label_Updown2.setText(str(self.gdicParaData["ValueUpDown2"]))

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
