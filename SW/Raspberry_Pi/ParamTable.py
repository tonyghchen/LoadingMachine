def ArrPara_AxisMapping(lsLMAxis):
    switch = {
                "X1" : "FrontRear"  ,     # UpDown
                "X2" : "UpDown"     ,     # FrontRear
              }
    return switch.get(lsLMAxis, "")
"""
def ArrPara_PHYAxisMapping(lsAxis):
    switch = {
                "X1"     :  1 ,     # UpDown
                "X2"     :  2 ,     # FrontRear
              }
    
    return switch.get(lsAxis, 1)
"""
def ArrPara_PHYAxisMapping(liAxis):
    switch = {
                1 : "X1",    # UpDown
                2 : "X2",    # FrontRear
              }
    
    return switch.get(liAxis, "")    
    

# ------------------------------------------------------------------
#   Gereral Paramters
# ------------------------------------------------------------------
ArrPara_TableDefault= {
	"Language"  : 1,            # 0: English, 1: 繁體, 2: 簡體, 3: 其他
    "PowerX2"   : 1,            # 0:x1, 1:x10, 2: x100 (10^)
    "PowerX1"   : 1,            # 0:x1, 1:x10, 2: x100 (10^)
    "Value1X2"  : 0,
    "Value2X2"  : 0,
    "Value1X1"  : 0,
    "Value2X1"  : 0,
}

# ------------------------------------------------------------------
#   Display Panel
# ------------------------------------------------------------------
MainPanel_TableForm = {
    "Updown0"   :{"Group": "UpDown"     , "DigitFormat":"Digs3_Format"     ,"ObjName" : "label_Updown0"     ,"on_background": "#181818" ,"background" : "#08d"   ,"Enable": 1  },
    "Updown1"   :{"Group": "UpDown"     , "DigitFormat":"Digs3_Format"     ,"ObjName" : "label_Updown1"     ,"on_background": "#181818" ,"background" : "#08d"   ,"Enable": 1  },
    "Updown2"   :{"Group": "UpDown"     , "DigitFormat":"Digs3_Format"     ,"ObjName" : "label_Updown2"     ,"on_background": "#181818" ,"background" : "#08d"   ,"Enable": 1  },
    "FrontRear1":{"Group": "FrontRear"  , "DigitFormat":"Digs3_Format"     ,"ObjName" : "label_FR1Value"    ,"on_background": "#181818" ,"background" : "#08d"   ,"Enable": 1  },
    "FrontRear2":{"Group": "FrontRear"  , "DigitFormat":"Digs3_Format"     ,"ObjName" : "label_FR2Value"    ,"on_background": "#181818" ,"background" : "#08d"   ,"Enable": 1  },
}  

# ------------------------------------------------------------------
#   AdvancedParam
# ------------------------------------------------------------------
AdvancedParam_TableForm = {
    "MotorName" : { 
        "Row" : 0, 
        "Type": "lineEdit",
        "Item": [
            {"CellName": "MotorName_X1"     , "Column" : 0, "DefautlValue" : "X1",      "ObjName" : "lineEdit_MotorName_X1"      ,"AdvanceMode" : 0, "Keyboard": "Keyboard"  },
            {"CellName": "MotorName_X2"     , "Column" : 1, "DefautlValue" : "X2",      "ObjName" : "lineEdit_MotorName_X2"      ,"AdvanceMode" : 0, "Keyboard": "Keyboard"  },
        ]},
    "Unit" : { 
        "Row" : 1, 
        "Type": "comboBox",
        "Item": [
            {"CellName": "UnitX1"       , "Column" : 0, "DefautlValue" : 0, "ObjName" : "comboBox_UnitX1"    , "ComboList": "Select_UnitCell" , "UARTHeadCodeName" : "defUART_wUnit", "MinValue" : 0, "MaxValue" : 3 ,"AdvanceMode" : 0, "Keyboard": "Typical" },
            {"CellName": "UnitX2"       , "Column" : 1, "DefautlValue" : 0, "ObjName" : "comboBox_UnitX2"    , "ComboList": "Select_UnitCell" , "UARTHeadCodeName" : "defUART_wUnit", "MinValue" : 0, "MaxValue" : 3 ,"AdvanceMode" : 0, "Keyboard": "Typical" },
        ]},
    "MotorType" : { 
        "Row" : 2, 
        "Type": "comboBox",
        "Item": [
            {"CellName": "MotorTypeX1"       , "Column" : 0, "DefautlValue" : 0, "ObjName" : "comboBox_MotorTypeX1"    , "ComboList": "Select_MotorType" , "UARTHeadCodeName" : "defUART_wUnit", "MinValue" : 0, "MaxValue" : 3 ,"AdvanceMode" : 0, "Keyboard": "Typical" },
            {"CellName": "MotorTypeX2"       , "Column" : 1, "DefautlValue" : 0, "ObjName" : "comboBox_MotorTypeX2"    , "ComboList": "Select_MotorType" , "UARTHeadCodeName" : "defUART_wUnit", "MinValue" : 0, "MaxValue" : 3 ,"AdvanceMode" : 0, "Keyboard": "Typical" },
        ]},
    "MotorSpeed" : { 
        "Row" : 3, 
        "Type": "lineEdit",
        "Item": [
            {"CellName": "MotorSpeedX1"    , "Column" : 0, "DefautlValue" : 2000, "ObjName" : "lineEdit_MotorSpeedX1"    , "DigitFormat" : "Digs4_Format", "MinValue" : 0, "MaxValue" : 9999 ,"AdvanceMode" : 0, "Keyboard": "Typical" },
            {"CellName": "MotorSpeedX2"    , "Column" : 1, "DefautlValue" : 2000, "ObjName" : "lineEdit_MotorSpeedX2"    , "DigitFormat" : "Digs4_Format", "MinValue" : 0, "MaxValue" : 9999 ,"AdvanceMode" : 0, "Keyboard": "Typical" },
        ]},   
    "MotorStep" : { 
        "Row" : 4, 
        "Type": "lineEdit",
        "Item": [
            {"CellName": "MotorStepX1"    , "Column" : 0, "DefautlValue" : 131072, "ObjName" : "lineEdit_MotorStepX1"    , "DigitFormat" : "Digs8_Format", "UARTHeadCodeName" : "defUART_wMotorStep", "MinValue" : 0, "MaxValue" : 99999999 ,"AdvanceMode" : 0, "Keyboard": "Typical" },
            {"CellName": "MotorStepX2"    , "Column" : 1, "DefautlValue" : 131072, "ObjName" : "lineEdit_MotorStepX2"    , "DigitFormat" : "Digs8_Format", "UARTHeadCodeName" : "defUART_wMotorStep", "MinValue" : 0, "MaxValue" : 99999999 ,"AdvanceMode" : 0, "Keyboard": "Typical" },
        ]},
   "ZRTPosition" : { #N
       "Row" : 5, 
        "Type": "lineEdit",
       "Item": [
           {"CellName": "ZRTPositionX1"    , "Column" : 0, "DefautlValue" : 0, "ObjName" : "lineEdit_ZRTPositionX1"    , "DigitFormat" : "Digs10_Format", "UARTHeadCodeName" : "defUART_wZRTPosition", "MinValue" : 0, "MaxValue" : 9999999999 ,"AdvanceMode" : 0, "Keyboard": "Typical" },
           {"CellName": "ZRTPositionX2"    , "Column" : 1, "DefautlValue" : 0, "ObjName" : "lineEdit_ZRTPositionX2"    , "DigitFormat" : "Digs10_Format", "UARTHeadCodeName" : "defUART_wZRTPosition", "MinValue" : 0, "MaxValue" : 9999999999 ,"AdvanceMode" : 0, "Keyboard": "Typical" },
       ]},      
    "AxisMapping": {
        "Row" : 6, 
        "Type": "lineEdit",
        "Item": [
            {"CellName": "AxisMappingX1"    , "Column" : 0, "DefautlValue" : 3, "ObjName" : "lineEdit_AxisMappingX1"    , "DigitFormat" : "Digs2_Format", "UARTHeadCodeName" : "defUART_wZRTOrder" ,"AdvanceMode" : 0, "MinValue" : 0, "MaxValue" : 15, "Keyboard": "Typical" },
            {"CellName": "AxisMappingX2"    , "Column" : 1, "DefautlValue" : 4, "ObjName" : "lineEdit_AxisMappingX2"    , "DigitFormat" : "Digs2_Format", "UARTHeadCodeName" : "defUART_wZRTOrder" ,"AdvanceMode" : 0, "MinValue" : 0, "MaxValue" : 15, "Keyboard": "Typical" },
        ]},  

    "ZRTOrder" : { 
        "Row" : 7, 
        "Type": "lineEdit",
        "Item": [
            {"CellName": "ZRTOrderX1"    , "Column" : 0, "DefautlValue" : 1, "ObjName" : "lineEdit_ZRTOrderX1"    , "DigitFormat" : "Digs2_Format", "UARTHeadCodeName" : "defUART_wZRTOrder" ,"AdvanceMode" : 0, "MinValue" : 0, "MaxValue" : 14, "Keyboard": "Typical" },
            {"CellName": "ZRTOrderX2"    , "Column" : 1, "DefautlValue" : 1, "ObjName" : "lineEdit_ZRTOrderX2"    , "DigitFormat" : "Digs2_Format", "UARTHeadCodeName" : "defUART_wZRTOrder" ,"AdvanceMode" : 0, "MinValue" : 0, "MaxValue" : 14, "Keyboard": "Typical" },
        ]},  
   "MotorLogicalPosition" : { #N
       "Row" : 8, 
        "Type": "lineEdit",
       "Item": [
           {"CellName": "MotorLogicalPositionX1"    , "Column" : 0, "DefautlValue" : 16000, "ObjName" : "lineEdit_MotorLogicalPositionX1"    , "DigitFormat" : "Digs5_Format", "UARTHeadCodeName" : "defUART_wZRTPosition", "MinValue" : 1, "MaxValue" : 99999 ,"AdvanceMode" : 0, "Keyboard": "Typical" },
           {"CellName": "MotorLogicalPositionX2"    , "Column" : 1, "DefautlValue" : 16000, "ObjName" : "lineEdit_MotorLogicalPositionX2"    , "DigitFormat" : "Digs5_Format", "UARTHeadCodeName" : "defUART_wZRTPosition", "MinValue" : 1, "MaxValue" : 99999 ,"AdvanceMode" : 0, "Keyboard": "Typical" },
       ]},      
    "ZRTSpeed" : { 
        "Row" : 9, 
        "Type": "lineEdit",
        "Item": [
            {"CellName": "ZRTSpeedX1"    , "Column" : 0, "DefautlValue" :  60, "ObjName" : "lineEdit_ZRTSpeedX1"    , "DigitFormat" : "Digs4_Format", "MinValue" : 0, "MaxValue" : 9999 ,"AdvanceMode" : 0, "Keyboard": "Typical" },
            {"CellName": "ZRTSpeedX2"    , "Column" : 1, "DefautlValue" :  60, "ObjName" : "lineEdit_ZRTSpeedX2"    , "DigitFormat" : "Digs4_Format", "MinValue" : 0, "MaxValue" : 9999 ,"AdvanceMode" : 0, "Keyboard": "Typical" },
        ]},   
    "MotorFunction" : { 
        "Row" : 10, 
        "Type": "comboBox",
        "Item": [
            {"CellName": "MotorFunctionX1"    , "Column" : 0, "DefautlValue" : 7, "ObjName" : "comboBox_MotorFunctionX1"    , "ComboList": "Select_MotorFunction" , "DigitFormat" : "Digs2_Format", "UARTHeadCodeName" : "defUART_wMotorFunction" ,"AdvanceMode" : 0, "Keyboard": "Typical" },
            {"CellName": "MotorFunctionX2"    , "Column" : 1, "DefautlValue" : 7, "ObjName" : "comboBox_MotorFunctionX2"    , "ComboList": "Select_MotorFunction" , "DigitFormat" : "Digs2_Format", "UARTHeadCodeName" : "defUART_wMotorFunction" ,"AdvanceMode" : 0, "Keyboard": "Typical" },
        ]},
    "PNSpeed" : { 
        "Row" : 11, 
        "Type": "lineEdit",
        "Item": [
            {"CellName": "PNSpeedX1"    , "Column" : 0, "DefautlValue" :  15, "ObjName" : "lineEdit_PNSpeedX1"    , "DigitFormat" : "Digs3_Format", "UARTHeadCodeName" : "defUART_wPNSpeed", "MinValue" : -999, "MaxValue" : 999 ,"AdvanceMode" : 1, "Keyboard": "Typical" },
            {"CellName": "PNSpeedX2"    , "Column" : 1, "DefautlValue" :  15, "ObjName" : "lineEdit_PNSpeedX2"    , "DigitFormat" : "Digs3_Format", "UARTHeadCodeName" : "defUART_wPNSpeed", "MinValue" : -999, "MaxValue" : 999 ,"AdvanceMode" : 1, "Keyboard": "Typical" },
        ]},
    "PNFunction" : { 
        "Row" : 12, 
        "Type": "comboBox",
        "Item": [
            {"CellName": "PNFunctionX1"    , "Column" : 0, "DefautlValue" : 1, "ObjName" : "comboBox_PNFunctionX1"    , "ComboList": "Select_PNFunction" , "UARTHeadCodeName" : "defUART_wMotorFunction" ,"AdvanceMode" : 0 },
            {"CellName": "PNFunctionX2"    , "Column" : 1, "DefautlValue" : 1, "ObjName" : "comboBox_PNFunctionX2"    , "ComboList": "Select_PNFunction" , "UARTHeadCodeName" : "defUART_wMotorFunction" ,"AdvanceMode" : 0 },
        ]},
    "UnitExchange" : { 
        "Row" : 13, 
        "Type": "lineEdit",
        "Item": [
            {"CellName": "UnitExchangeX1"    , "Column" : 0, "DefautlValue" : 10000, "ObjName" : "lineEdit_UnitExchangeX1"    , "DigitFormat" : "Digs4Dot4_Format", "UARTHeadCodeName" : "defUART_wPNSpeed", "MinValue" : 1, "MaxValue" : 99999999 ,"AdvanceMode" : 1, "Keyboard": "Typical" },
            {"CellName": "UnitExchangeX2"    , "Column" : 1, "DefautlValue" : 10000, "ObjName" : "lineEdit_UnitExchangeX2"    , "DigitFormat" : "Digs4Dot4_Format", "UARTHeadCodeName" : "defUART_wPNSpeed", "MinValue" : 1, "MaxValue" : 99999999 ,"AdvanceMode" : 1, "Keyboard": "Typical" },
        ]},   
    "MaxLimit" : { 
        "Row" : 14, 
        "Type": "lineEdit",
        "Item": [
            {"CellName": "MaxLimitX1"    , "Column" : 0, "DefautlValue" : 8000, "ObjName" : "lineEdit_MaxLimitX1"    , "DigitFormat" : "Digs4_PN_Format", "UARTHeadCodeName" : "defUART_wMaxLimit", "MinValue" : -999999, "MaxValue" : 999999, "Keyboard": "Typical" },
            {"CellName": "MaxLimitX2"    , "Column" : 1, "DefautlValue" : 8000, "ObjName" : "lineEdit_MaxLimitX2"    , "DigitFormat" : "Digs4_PN_Format", "UARTHeadCodeName" : "defUART_wMaxLimit", "MinValue" : -999999, "MaxValue" : 999999, "Keyboard": "Typical" },
        ]}, 
    "MinLimit" : { 
        "Row" : 15, 
        "Type": "lineEdit",
        "Item": [
            {"CellName": "MinLimitX1"    , "Column" : 0, "DefautlValue" : 0         , "ObjName" : "lineEdit_MinLimitX1"   , "DigitFormat" : "Digs4_PN_Format", "UARTHeadCodeName" : "defUART_wMinLimit", "MinValue" : -999999, "MaxValue" : 999999, "Keyboard": "Typical" },
            {"CellName": "MinLimitX2"    , "Column" : 1, "DefautlValue" : 0         , "ObjName" : "lineEdit_MinLimitX2"   , "DigitFormat" : "Digs4_PN_Format", "UARTHeadCodeName" : "defUART_wMinLimit", "MinValue" : -999999, "MaxValue" : 999999, "Keyboard": "Typical" },
        ]}, 
    "Gear0" : { 
        "Row" : 16, 
        "Type": "lineEdit",
        "Item": [
            {"CellName": "Gear0X1"    , "Column" : 0, "DefautlValue" : 8, "ObjName" : "lineEdit_Gear0X1"    , "DigitFormat" : "Digs3_Format", "UARTHeadCodeName" : "defUART_wGear0", "MinValue" : 1, "MaxValue" : 999, "Keyboard": "Typical" },
            {"CellName": "Gear0X2"    , "Column" : 1, "DefautlValue" : 8, "ObjName" : "lineEdit_Gear0X2"    , "DigitFormat" : "Digs3_Format", "UARTHeadCodeName" : "defUART_wGear0", "MinValue" : 1, "MaxValue" : 999, "Keyboard": "Typical" },
        ]},  
    "Gear1" : { 
        "Row" : 17, 
        "Type": "lineEdit",
        "Item": [
            {"CellName": "Gear1X1"    , "Column" : 0, "DefautlValue" : 1, "ObjName" : "lineEdit_Gear1X1"    , "DigitFormat" : "Digs3_Format", "UARTHeadCodeName" : "defUART_wGear1", "MinValue" : 1, "MaxValue" : 999, "Keyboard": "Typical" },
            {"CellName": "Gear1X2"    , "Column" : 1, "DefautlValue" : 1, "ObjName" : "lineEdit_Gear1X2"    , "DigitFormat" : "Digs3_Format", "UARTHeadCodeName" : "defUART_wGear1", "MinValue" : 1, "MaxValue" : 999, "Keyboard": "Typical" },
        ]},  
    "Near" : { 
        "Row" : 18, 
        "Type": "lineEdit",
        "Item": [
            {"CellName": "NearX1"     , "Column" : 0, "DefautlValue" : 1, "ObjName" : "lineEdit_NearX1"    , "DigitFormat" : "Digs5_Format", "UARTHeadCodeName" : "defUART_SetNearPos", "MinValue" : 0, "MaxValue" : 65535, "Keyboard": "Typical" },
            {"CellName": "NearX2"     , "Column" : 1, "DefautlValue" : 1, "ObjName" : "lineEdit_NearX2"    , "DigitFormat" : "Digs5_Format", "UARTHeadCodeName" : "defUART_SetNearPos", "MinValue" : 0, "MaxValue" : 65535, "Keyboard": "Typical" },
        ]},  
}

# ------------------------------------------------------------------
#   PushBotton - have clicked event
# ------------------------------------------------------------------
PushBotton_ObjectName = {
    "pushButton_Up"         :   "Left", 
    "pushButton_Down"       :   "Right",
}

