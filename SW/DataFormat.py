import re

def fGetDigitFormatFromType (digitFormat):
    switch = {"Digs1_Format" : Digs1_Format, 
              "Digs2_Format" : Digs2_Format, 
              "Digs3_Format" : Digs3_Format, 
              "Digs4_Format" : Digs4_Format, 
              "Digs5_Format" : Digs5_Format, 
              "Digs6_Format" : Digs6_Format, 
              "Digs7_Format" : Digs7_Format, 
              "Digs8_Format" : Digs8_Format, 
              "Digs9_Format" : Digs9_Format, 
              "Digs10_Format" : Digs10_Format, 
              "Digs1Dot1_Format" : Digs1Dot1_Format, 
              "Digs1Dot2_Format" : Digs1Dot2_Format,             
              "Digs1Dot3_Format" : Digs1Dot3_Format,
              "Digs1Dot4_Format" : Digs1Dot4_Format,             
              "Digs3Dot3_Format" : Digs3Dot3_Format,              
              "Digs4Dot4_Format" : Digs4Dot4_Format,
              "Digs4Dot2_Format" : Digs4Dot2_Format,
              "Digs3Dot3_Format" : Digs3Dot3_Format,
              "Digs3Dot2_Format" : Digs3Dot2_Format,
              "Digs3Dot1_Format" : Digs3Dot1_Format,
              "Digs2Dot1_Format" : Digs2Dot1_Format,
              "Digs2Dot2_Format" : Digs2Dot2_Format,
              "Digs1_PN_Format" : Digs1_PN_Format,
              "Digs3_PN_Format" : Digs3_PN_Format,
              "Digs4_PN_Format" : Digs4_PN_Format,
              "Digs5_PN_Format" : Digs5_PN_Format,
              "Digs6_PN_Format" : Digs6_PN_Format,
              "Digs7_PN_Format" : Digs7_PN_Format,         
              "Digs1Dot4_PN_Format" : Digs1Dot4_PN_Format,             
              "Digs4Dot2_PN_Format" : Digs4Dot2_PN_Format,
              "Digs2Dot3_PN_Format" : Digs2Dot3_PN_Format,
              "Digs3Dot3_PN_Format" : Digs3Dot3_PN_Format,
              "Digs3Dot2_PN_Format" : Digs3Dot2_PN_Format,
              "Digs4Dot1_PN_Format" : Digs4Dot1_PN_Format,
              "Digs5Dot1_PN_Format" : Digs5Dot1_PN_Format,
              "Digs5Dot2_PN_Format" : Digs5Dot2_PN_Format
              }
    
    return switch.get(digitFormat, Digs1_Format)  

# ----------------------------------------------------------------------
# Description:  fAll_GetDigiDot
# Function:     Get Digits and Dot number
# Input :       DataType
# Return:       Digits, Dot
# ----------------------------------------------------------------------
def GetDigiDot(lsDataType ):

    lreDigis = re.search(r'Digs(\d+)', lsDataType)
    lreDot = re.search(r'Dot(\d+)',  lsDataType)
    lrePN = re.search(r'PN', lsDataType)
    lfSign = 1 if lrePN else 0

    if  lrePN is not None:
        pass

    liDigis = 0
    liDot   = 0

    if lreDigis:
        liDigis = lreDigis.group(1)

    if lreDot:
        liDot = lreDot.group(1)

    #print("DataType",lsDataType, "Digis:",liDigis, "Dot:",liDot)
    return  int(liDigis), int(liDot), lfSign

# ----------------------------------------------------------------------
# Description:  TansferDotBack
# Function:     Transfer back Dot number
# Input :       DataType
# Return:       Digits, Dot
# ----------------------------------------------------------------------
def TansferDotNumber(lsDataType, lfData):

    lreDot = re.search(r'Dot(\d+)',  lsDataType)
    liDot   = 0

    if lreDot:
        liDot = lreDot.group(1)

    lfTransfer = round(lfData/ 10**int(liDot),int(liDot))

    return  lfTransfer


def fData_DicRemoveString(dicData):
    converted_data = {}

    for key, value in dicData.items():
        # 尝试将键转换为整数，若失败则保留原始键
        try:
            converted_key = int(key) if key.isdigit() else key
        except ValueError:
            converted_key = key
        
        # 处理字典中的值，确保是字典且可以转换
        if isinstance(value, dict):
            try:
                converted_value = {int(subkey): subvalue for subkey, subvalue in value.items()}
            except ValueError:
                converted_value = value  # 如果转换失败，则保留原始的 value
        else:
            try:
                converted_value = int(value)  # 如果 value 不是字典，直接保留
            except:
                converted_value = value  # 如果 value 不是字典，直接保留

        converted_data[converted_key] = converted_value

    # for key, value in dicData.items():
    #     converted_key = int(key) if key.isdigit() else key
    #     converted_value = {int(subkey): subvalue for subkey, subvalue in value.items()}
    #     converted_data[converted_key] = converted_value

    return  converted_data


# ------------------------------------------------------------------
#   Run Button Status
#   Button Mode 0 : Disable mode, 1: Enable Mode, 2: Disable + 首輪倍率顯示
# ------------------------------------------------------------------
ArrUART_RunButtonType = {    
    "Spring_Up"         : { "Type": "PushButton",  "Color": 'black' },
    "Spring_Down"       : { "Type": "PushButton",  "Color": "black" },
    "Slide_Up"          : { "Type": "PushButton",  "Color": "black" },
    "Slide_Down"        : { "Type": "PushButton",  "Color": "black" },
    "RQ_Up"             : { "Type": "PushButton",  "Color": "black" },
    "RQ_Down"           : { "Type": "PushButton",  "Color": "black" },
    "RW_Up"             : { "Type": "PushButton",  "Color": "black" },
    "RW_Down"           : { "Type": "PushButton",  "Color": "black" },
    "F_Up"              : { "Type": "PushButton",  "Color": "black" },
    "F_Down"            : { "Type": "PushButton",  "Color": "black" },
    "F_Pow"             : { "Type": "PushButton",  "Color": "black" },
    "F_Clr"             : { "Type": "PushButton",  "Color": "black" },
    "AIFF"              : { "Type": "PushButton",  "Color": "black" },
    "AIRR"              : { "Type": "PushButton",  "Color": "black" },
    "Timeline_Single"   : { "Type": "PushButton",  "Color": "black" },
    "Timeline_Group"    : { "Type": "PushButton",  "Color": "black" },
    "Timeline_All"      : { "Type": "PushButton",  "Color": "black" },
    "Timeline_Teach"    : { "Type": "PushButton",  "Color": "black" },
    "Timeline_RInsert"  : { "Type": "PushButton",  "Color": "black" },
    "Timeline_Del"      : { "Type": "PushButton",  "Color": "black" }
}

# ------------------------------------------------------------------
#   State Control
#   Button Mode 0 : Disable mode, 1: Enable Mode, 2: Disable + 首輪倍率顯示
# ------------------------------------------------------------------
ArrUART_StateCode= {
    "NormalState"   : { "UART_Code" : 0 , "ButtonMode" : 1 },   # O
    "HomeState"     : { "UART_Code" : 1 , "ButtonMode" : 0 },   # X
    "TestState"     : { "UART_Code" : 2 , "ButtonMode" : 2 },   # O
    "TestEditState" : { "UART_Code" : 3 , "ButtonMode" : 3 },   # O
    "ProductState"  : { "UART_Code" : 4 , "ButtonMode" : 0 },   # O
    "CuttingState"  : { "UART_Code" : 5 , "ButtonMode" : 0 },   # O
    "AIState"       : { "UART_Code" : 6 , "ButtonMode" : 5 },   # O AI State 
    "VRHOMEState"   : { "UART_Code" : 8 , "ButtonMode" : 0 },   # X
    "SPHomeState"   : { "UART_Code" : 9 , "ButtonMode" : 0 },   # O
    "TestStartState": { "ButtonMode": 0 },                      # O
    "ToolRunState"  : { "ButtonMode": 1 },                      # X
    "KeySWState"    : { "ButtonMode": 0 },                      # X
}


ArrErrorCode = {
	0x01: {'ErrorCode' : 'Unconnect'       ,'ReciveByte' : 3},
	0x02: {'ErrorCode' : 'GoHomeFail'      ,'ReciveByte' : 3},
	0x03: {'ErrorCode' : 'SlideError'       ,'ReciveByte' : 3},
	0x04: {'ErrorCode' : 'SlideTest'       ,'ReciveByte' : 3},
	0x05: {'ErrorCode' : 'Miss\n START/TEST/STEP----Continue produce\n RESET------Return To Edit Screen'          ,'ReciveByte' : 3},
	0x06: {'ErrorCode' : 'Test'          ,'ReciveByte' : 3},
	0x07: {'ErrorCode' : 'OilError'         ,'ReciveByte' : 2},   
	0x08: {'ErrorCode' : 'Ext.DeviceError'  ,'ReciveByte' : 2},
	0x09: {'ErrorCode' : 'ExtEncoderError'  ,'ReciveByte' : 2},
	0x0a: {'ErrorCode' : 'ServoFail'       ,'ReciveByte' : 2},
	0x0b: {'ErrorCode' : 'CutterFail'      ,'ReciveByte' : 2},
	0x0c: {'ErrorCode' : 'OverSlideLimit'  ,'ReciveByte' : 2},
	0x0d: {'ErrorCode' : 'OverSoftLimit'   ,'ReciveByte' : 2},
    0x0e: {'ErrorCode' : 'GoHome'           ,'ReciveByte' : 2},
    0x0f: {'ErrorCode' : 'SafeError'        ,'ReciveByte' : 2},
    0x10: {'ErrorCode' : 'VirtualHome'      ,'ReciveByte' : 3},
    0x11: {'ErrorCode' : 'AdcNotZero'       ,'ReciveByte' : 2},
    0x12: {'ErrorCode' : 'NoMPG'            ,'ReciveByte' : 2},
    0x13: {'ErrorCode' : 'OverMiss'         ,'ReciveByte' : 2},
    0x14: {'ErrorCode' : 'OverQuan'         ,'ReciveByte' : 2},
    0x15: {'ErrorCode' : 'ManualSet'        ,'ReciveByte' : 3},
    0x16: {'ErrorCode' : 'AutoHome'         ,'ReciveByte' : 3},
    0x17: {'ErrorCode' : 'DispHook'         ,'ReciveByte' : 2},
}

# ------------------------------------------------------------------
#   Digits format - https://mkaz.blog/code/python-string-format-cookbook/
# ------------------------------------------------------------------

Digs1_Format     = "{:0>1d}"        # "0"
Digs2_Format     = "{:0>2d}"        # "00"
Digs3_Format     = "{:0>3d}"        # "000"
Digs4_Format     = "{:0>4d}"        # "0000"
Digs5_Format     = "{:0>5d}"        # "00000"
Digs6_Format     = "{:0>6d}"        # "00000"
Digs7_Format     = "{:0>7d}"        # "000000"
Digs8_Format     = "{:0>8d}"        # "0000000"
Digs9_Format     = "{:0>9d}"        # "00000000"
Digs10_Format    = "{:0>10d}"      # "000000000"
Digs2Dot0_Format = "{:02.0f}"       # "0.0",
Digs1Dot1_Format = "{:03.1f}"       # "0.0",
Digs1Dot2_Format = "{:04.2f}"       # "0.00"
Digs1Dot3_Format = "{:05.3f}"       # "0.000"
Digs1Dot4_Format = "{:06.4f}"       # "0.0000"
Digs4Dot2_Format = "{:07.2f}"       # "0000.00"
Digs4Dot4_Format = "{:09.4f}"       # "0000.0000
Digs3Dot3_Format = "{:07.3f}"       # "000.000"
Digs3Dot1_Format = "{:05.1f}"       # "000.0"
Digs3Dot2_Format = "{:06.2f}"       # "0000.00"
Digs2Dot1_Format = "{:04.1f}"       # "00.0"
Digs2Dot2_Format = "{:05.2f}"       # "00.0"

Digs1_PN_Format  = "{:+01d}"         # "+0"
Digs3_PN_Format  = "{:+04d}"         # "+000"
Digs4_PN_Format  = "{:+05d}"        # "+00000"
Digs5_PN_Format  = "{:+06d}"        # "+00000"
Digs6_PN_Format  = "{:+07d}"        # "+000000"
Digs7_PN_Format  = "{:+08d}"        # "+000000"

Digs0Dot4_PN_Format = "{:+06.4f}"  # "+.0000"
Digs1Dot4_PN_Format = "{:+07.4f}"  # "+0.0000"
Digs4Dot2_PN_Format = "{:+08.2f}"  # "+0000.00"
Digs3Dot2_PN_Format = "{:+07.2f}"  # "+000.00"
Digs2Dot3_PN_Format = "{:+07.3f}"  # "+00.000"
Digs3Dot3_PN_Format = "{:+08.3f}"  # "+000.000"
Digs4Dot1_PN_Format = "{:+07.1f}"  # "+000.00"
Digs5Dot1_PN_Format = "{:+08.1f}"   #"+00000.0",
Digs5Dot2_PN_Format = "{:+09.2f}"   #"+00000.00",