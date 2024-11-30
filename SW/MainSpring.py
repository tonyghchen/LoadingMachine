"""
    New Medical Project : Start from 2024/11/15
    Editor: Tony Gh Chen
     
"""
import sys, json, os, copy
import globals
import Language     as Language
import ParamTable   as ParamTable
import orjson       as json

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

   # ----------------------------------------------------------------------
   #    Tab : Run - Program
   # ----------------------------------------------------------------------
   # ----------------------------------------------------------------------
    # Power level switch
    # Description: fRun_PWRSwitch
    # Input : None
    # Return: None
    # ----------------------------------------------------------------------
    def fRun_PWRSwitch(self):

        self.gdicParaData["Power"] = self.gdicParaData.get("Power", 0) + 1

        if  self.gdicParaData["Power"] >= 3:
            self.gdicParaData["Power"] = 0

        self.fDisplay_PWR(self.gdicParaData["Power"])

        my_print("PWR Switch:",self.gdicParaData["Power"])

   # ----------------------------------------------------------------------
    # Power level switch
    # Description: fRun_PWRSwitch
    # Input : None
    # Return: None
    # ----------------------------------------------------------------------
    def fDisplay_PWR(self, liPower):

        lsPWR = ""
        if  liPower == 1:
            lsPWR = "x10"
        elif liPower == 2:
            lsPWR = "x100"
        else:
            lsPWR = "x1"

        self.pushButton_Power.setText(lsPWR)
        my_print("PWR Switch")

   # ----------------------------------------------------------------------
    # Reset Processs
    # Description: fRun_Reset
    # Input : None
    # Return: None
    # ----------------------------------------------------------------------
    def fRun_Reset(self):

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
        objName = sender.objectName()

        my_print("ObjName:", objName)

    # ----------------------------------------------------------------------
    #    File Process
    # ----------------------------------------------------------------------
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

    # ----------------------------------------------------------------------
    # Function : Change Language by iLanguage setting
    # Input : None
    # Return: None
    # ----------------------------------------------------------------------
    def fLanguage_radioClicked(self, button):
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

        self.pushButton_0Set.setText(self.Language.GetText("SET"))
        self.pushButton_1Set.setText(self.Language.GetText("SET"))
        self.pushButton_2Set.setText(self.Language.GetText("SET"))
        self.pushButton_FRSet.setText(self.Language.GetText("SET"))

        if  self.gdicParaData["Language"] == 0: # English
            self.label_0Label.setStyleSheet("font-size: 26px;")
        else:
            self.label_0Label.setStyleSheet("font-size: 36px;")

        self.label_0Label.setText(self.Language.GetText("START"))

        self.pushButton_Reset.setText(self.Language.GetText("RESET"))
        self.pushButton_Zero.setText(self.Language.GetText("ZERO"))

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

    # ----------------------------------------------------------------------
    #                       Initialize
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
        self.pushButton_Power.clicked.connect(self.fRun_PWRSwitch)
        self.pushButton_Reset.clicked.connect(self.fRun_Reset)
        self.pushButton_Zero.clicked.connect(self.fRun_Zero)

        self.pushButton_0Set.clicked.connect(self.fRun_Set)
        self.pushButton_1Set.clicked.connect(self.fRun_Set)
        self.pushButton_2Set.clicked.connect(self.fRun_Set)
        self.pushButton_FRSet.clicked.connect(self.fRun_Set)

        self.buttonGroup = QButtonGroup(self)
        self.buttonGroup.addButton(self.radioButton_English, 1)
        self.buttonGroup.addButton(self.radioButton_Chinese, 2)
        self.buttonGroup.addButton(self.radioButton_Simplified, 3)
        self.buttonGroup.buttonClicked.connect(self.fLanguage_radioClicked)
        self.buttonGroup.button(self.gdicParaData["Language"]+1).setChecked(True)

        my_print("End of fAll_InitEvent Function")

    # ----------------------------------------------------------------------
    # Description:  Initial all Variable
    # Function:     initVariable
    # Input :       
    # Return:       None
    # ----------------------------------------------------------------------
    def initVariable(self):

        self.gsDisplayMode  = None
        self.gsKeyinData = ""
        self.giKeyInterruptCnt = 0
        self.gsKeyCmdData       = []
        self.gFilePath = current_directory + defProgramPath

        self.gdicErrorMsg   = {}             # Reset Error String       
        
    # ----------------------------------------------------------------------
    # Description:  UI initialize
    # Function:     initUi
    # Input :       
    # Return:       None
    # ----------------------------------------------------------------------
    def fAll_initUI(self):

        self.fDisplay_PWR(self.gdicParaData["Power"])
        self.fAll_LanguageDisplay(self.gdicParaData["Language"])

        my_print("End of initUI Function")

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

        self.tabWidget_Main.setCurrentWidget(self.tab_Run)
        self.msg_box_hint.setWindowTitle(self.Language.GetText("Error"))

        # -------------------------------------------------------------
        # Timwer initialize
        self.timer = QTimer()
        self.timer.setTimerType(Qt.PreciseTimer)  # 设置为精确计时器
        self.timer.setInterval(5)
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
