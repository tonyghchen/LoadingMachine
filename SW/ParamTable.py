
# ------------------------------------------------------------------
#   Gereral Paramters
# ------------------------------------------------------------------
ArrPara_TableDefault= {
    "Power"         : 0,            # 0:x1, 1:x10, 2: x100 (10^)
	"Language"      : 1,            # 0: English, 1: 繁體, 2: 簡體, 3: 其他
    "ValueUpDown0"  : 0,
    "ValueUpDown1"  : 0,
    "ValueUpDown2"  : 0,
    "ValueFR1"      : 0,
    "ValueFR2"      : 0,
}

# ------------------------------------------------------------------
#   Display Panel
# ------------------------------------------------------------------
MainPanel_TableForm = {
    "Updown0"  :{"Group": "UpDown"  , "DigitFormat":"Digs3_Format"     ,"ObjName" : "label_Updown0"     ,"on_background": "#181818" ,"background" : "#08d"   ,"Enable": 1  },
    "Updown1"  :{"Group": "UpDown"  , "DigitFormat":"Digs3_Format"     ,"ObjName" : "label_Updown1"     ,"on_background": "#181818" ,"background" : "#08d"   ,"Enable": 1  },
    "Updown2"  :{"Group": "UpDown"  , "DigitFormat":"Digs3_Format"     ,"ObjName" : "label_Updown2"     ,"on_background": "#181818" ,"background" : "#08d"   ,"Enable": 1  },
    "FR1"      :{"Group": "FR"      , "DigitFormat":"Digs3_Format"     ,"ObjName" : "label_FR1Value"    ,"on_background": "#181818" ,"background" : "#08d"   ,"Enable": 1  },
    "FR2"      :{"Group": "FR"      , "DigitFormat":"Digs3_Format"     ,"ObjName" : "label_FR2Value"    ,"on_background": "#181818" ,"background" : "#08d"   ,"Enable": 1  },
}  

# ------------------------------------------------------------------
#   PushBotton - have clicked event
# ------------------------------------------------------------------
PushBotton_ObjectName = {
    "pushButton_Up"         :   "Left", 
    "pushButton_Down"       :   "Right",
}

