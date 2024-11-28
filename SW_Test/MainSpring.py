"""
    New Medical Project : Start from 2024/11/15
    Editor: Tony Gh Chen
     
"""
import PySide6
import Language     as Language
import sys
import globals

from PySide6.QtWidgets import QApplication, QMainWindow
from Ui_MainForm        import *
from datetime import    datetime

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

   # ----------------------------------------------------------------------
    # File All Event inialize
    # Description: fAll_InitEvent
    # Input : None
    # Return: None
    # ----------------------------------------------------------------------
    def fAll_InitEvent(self):

        # Windows Key interrupt initialize
#        self.Init_Keyinterrupt()
        my_print("End of fAll_InitEvent Function")

    # ----------------------------------------------------------------------
    # Description:  Initial all Variable
    # Function:     initVariable
    # Input :       
    # Return:       None
    # ----------------------------------------------------------------------
    def initVariable(self):

        self.gsDisplayMode  = None
           
        
    # ----------------------------------------------------------------------
    # Description:  UI Style initialize
    # Function:     initUi
    # Input :       
    # Return:       None
    # ----------------------------------------------------------------------
    def initUIStyle(self):

        my_print("End of initUIStyle Function")

    # ----------------------------------------------------------------------
    # Description:  Main Window initialize
    # Function:     Main System All initialize
    # Input :       
    # Return:       None
    # ----------------------------------------------------------------------
    def __init__(self, parent=None):

        super(MyMainWindow, self).__init__(parent)
        self.setupUi(self)

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
