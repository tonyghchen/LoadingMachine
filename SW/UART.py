import os, serial

# UART Definition
ArrUART_WriteHeadCode = {

    "defUART_wSlow"             : {'HeadCode' : 0xDD, 'SendByte' : 2},
    'defUART_wStop'             : {'HeadCode' : 0xA0, 'SendByte' : 0},
    'defUART_wReset'            : {'HeadCode' : 0xA2, 'SendByte' : 0},
    "defUART_wVR_AUTO"          : {'HeadCode' : 0xAB, 'SendByte' : 1},

    "defUART_wCurrProductQty"   : {'HeadCode' : 0xA4, 'SendByte' : 4},
    "defUART_wSetProductQty"    : {'HeadCode' : 0xA5, 'SendByte' : 4},
    "defUART_wCurrFailQty"      : {'HeadCode' : 0xA6, 'SendByte' : 1},
    "defUART_wSetFailQty"       : {'HeadCode' : 0xA7, 'SendByte' : 1},
    #"defUART_wFullRun"          : {'HeadCode' : 0xA8, 'SendByte' : 0},
    #"defUART_wTestRun"          : {'HeadCode' : 0xA9, 'SendByte' : 0},  
    "defUART_wSPD"              : {'HeadCode' : 0x2C, 'SendByte' : 1},

    'defUART_wManualUpDown'     : {'HeadCode' : 0xC0, 'SendByte' : 1},      #軸號, 手動加減(0:-加 1:減)
    'defUART_wPosition'         : {'HeadCode' : 0xC2, 'SendByte' : 4},
    'defUART_wMode'             : {'HeadCode' : 0xC3, 'SendByte' : 2},      # 模式 ()
    "defUART_wAIR_SET"          : {'HeadCode' : 0xC4, 'SendByte' : 2},

    "START_ACT"                 : {'HeadCode' : 0x2A, 'SendByte' : 0},
	"END_ACT"                   : {'HeadCode' : 0x2B, 'SendByte' : 0},
    "SPD_CHANGE"                : {'HeadCode' : 0x2D, 'SendByte' : 1},      # G9 SPD 按照當時程式

    "MOVE"			            : {'HeadCode' : 0xD0, 'SendByte' : 23},      # MOVE (0xD0) , Axis(1) , N(2), Start ms(4), ms(2), idms(2), step(4), dst_pos(4)
    "START_MOVE_STEP"           : {'HeadCode' : 0xD1, 'SendByte' : 0},
    "MOVE_STEP"                 : {'HeadCode' : 0xD2, 'SendByte' : 8},
    "END_MOVE_STEP"             : {'HeadCode' : 0xD3, 'SendByte' : 0},

    "START_VR"                  : {'HeadCode' : 0xD4, 'SendByte' : 0},
    "MOVE_VR"                   : {'HeadCode' : 0xD5, 'SendByte' : 19},
    "END_VR"                    : {'HeadCode' : 0xD6, 'SendByte' : 0},
    "TOUCH"                     : {'HeadCode' : 0xD7, 'SendByte' : 11},
    "MOVE_TOUCH"                : {'HeadCode' : 0xD8, 'SendByte' : 23},
    "MOVE_R"	                : {'HeadCode' : 0xD9, 'SendByte' : 19},      # MOVE (0xD0) , Axis(1) , N(2), Start ms(4), ms(2), idms(2), step(4), dst_pos(4)
    "defUART_wProgramToolRun"   : {'HeadCode' : 0xDA, 'SendByte' : 0},
    "defUART_AxisSwitch"        : {'HeadCode' : 0xDB, 'SendByte' : 4},
    "defUART_FAxisPosition"     : {'HeadCode' : 0xDC, 'SendByte' : 1},
    "defUART_Shutdown"          : {'HeadCode' : 0xDD, 'SendByte' : 0},
    "defUART_HandWheelPower"    : {'HeadCode' : 0xDE, 'SendByte' : 1},
    "defUART_HandWheelAxis"     : {'HeadCode' : 0xDF, 'SendByte' : 1},      # 軸對應(PHY軸)
    "defUART_AIR"               : {'HeadCode' : 0xE0, 'SendByte' : 9},
    "defUART_SetCurrLogiPos"    : {'HeadCode' : 0xE1, 'SendByte' : 5},      # SET_POS Axis(1),Pos(4)
    "defUART_SetNearPos"        : {'HeadCode' : 0xE2, 'SendByte' : 3},      # SET_NearPOS Axis(1),Pos(2)
    "defUART_REPEAT"            : {'HeadCode' : 0xE3, 'SendByte' : 10},     # Repeat_Startms(4). Repeat_Endms(4),Repeat_CNT(2)

    "defUART_CurrentState"      : {'HeadCode' : 0xF0, 'SendByte' : 1},      #0: Normal State 1: 原點 (Home State), 2. 測試 (Test State), 3. 測試修改-手輪可以+微調 (Test Edit State)  
                                                                            #4. 生產 (Production State) 5. 執行快速切刀 (Cutting State), 6. AI區塊測試 (AI Test State), 
                                                                            #7. 進入AI區塊單步執行-等待手輪+/-轉(AI Step Test State), 8. 
    'defUART_wSendRReal'        : {'HeadCode' : 0xFE, 'SendByte' : 1},     #SendRaspberryOK
    'defUART_wSendChk'          : {'HeadCode' : 0xFF, 'SendByte' : 1},     #SendRaspberryOK
    "defUART_wSmartBack"        : {'HeadCode' : 0xE6, 'SendByte' : 1},     # 0:OFF/1: ON
}

ArrUART_ReadHeadCode= {
    "defUART_rErrorMsg"         : {'HeadCode' : 0x40, 'ReadByte' : 2},  # Error Msg 錯誤警示
    
    "defUART_rPosition"         : {'HeadCode' : 0x51, 'ReadByte' : 5},  # 位置讀取: 軸號, Byte 0,1,2  
    "defUART_rMotorType"        : {'HeadCode' : 0x52, 'ReadByte' : 3},  # 馬達型態,馬達型態: 軸數, 馬達Type 
    "defUART_rKeyboard"         : {'HeadCode' : 0x55, 'ReadByte' : 1},  # Keyboard read 
    "defUART_rKeySpeed"         : {'HeadCode' : 0x56, 'ReadByte' : 1},  # Keyboard speed 
    "defUART_rCurrProductQty"   : {'HeadCode' : 0x57, 'ReadByte' : 4},  # 目前生產量 - 表格
    "defUART_rCurrProductTime"  : {'HeadCode' : 0x58, 'ReadByte' : 4},  # 目前生產時間 (ms) - 時間軸
    "defUART_rCurrFailQty"      : {'HeadCode' : 0x59, 'ReadByte' : 1},  # 目前失誤量 
    "defUART_rOverUnderFlow"    : {'HeadCode' : 0x5A, 'ReadByte' : 2},  # Overflow / Underflow 
    "defUART_rN"                : {'HeadCode' : 0x5B, 'ReadByte' : 2},  # Keyboard read 
    "defUART_rFeedLength"       : {'HeadCode' : 0x5C, 'ReadByte' : 4},  # 累積送線長度
    "defUART_rProduceStop"      : {'HeadCode' : 0x5D, 'ReadByte' : 1},  # 生產停止 - State(1) - 0:停機按鈕, 1:生產數量到, 2: 探針失誤量到
    "defUART_rTest2Product"     : {'HeadCode' : 0x5E, 'ReadByte' : 0},  # 測試轉生產
    
    "defUART_rMOVE_STEP_OK"     : {'HeadCode' : 0x61, 'ReadByte' : 1},  # MOVE STEP OK
    "defUART_rMOVE_VR_STEP_OK"  : {'HeadCode' : 0x62, 'ReadByte' : 1},  # MOVE VR STEP OK
    "defUART_rTouchStatus"      : {'HeadCode' : 0x63, 'ReadByte' : 5},  # Touch Status
    "defUART_rTouchOK"          : {'HeadCode' : 0x64, 'ReadByte' : 1},  # Touch OK status
    "defUART_rHandWheel"        : {'HeadCode' : 0x65, 'ReadByte' : 1},  # 簡易手輪0x01:+, 0x02:-
    "defUART_VersionNo"         : {'HeadCode' : 0x66, 'ReadByte' : 4},  # (Byte0).(Byte1).(Byte3-4)
    "defUART_PowerDown"         : {'HeadCode' : 0x67, 'ReadByte' : 0},  # 關機準備中

    "defUART_LoadCellData"      : {'HeadCode' : 0x70, 'ReadByte' : 8},  # Byte0~7 (Byte 0-1 Cell 0/Byte 2-3 Cell 1/Byte 4-5 Cell 2/Byte 6-7 Cell 3)
}

ArrUART_ReadKeyCode = {
    0x01    :{ "KeyName": "KeyLock"    ,"KeySWLock":  1 },
    0x02    :{ "KeyName": "KeyUnLock"  ,"KeySWLock":  1 },
    0x03    :{ "KeyName": "Home"       ,"KeySWLock":  0 },
    0x04    :{ "KeyName": "StartProd"  ,"KeySWLock":  0 },
    0x05    :{ "KeyName": "Test"       ,"KeySWLock":  0 },
    0x06    :{ "KeyName": "StopProd"   ,"KeySWLock":  0 },
    0x07    :{ "KeyName": "ResetON"    ,"KeySWLock":  0 },
    0x08    :{ "KeyName": "ResetOFF"   ,"KeySWLock":  0 },
    0x09    :{ "KeyName": "SwitchON"   ,"KeySWLock":  1 },
    0x0a    :{ "KeyName": "SwitchOFF"  ,"KeySWLock":  1 },
    0x0b    :{ "KeyName": "F_Up"       ,"KeySWLock":  1 },
    0x0c    :{ "KeyName": "F_Down"     ,"KeySWLock":  1 },
    0x0d    :{ "KeyName": "RW_Up"      ,"KeySWLock":  1 },
    0x0e    :{ "KeyName": "RW_Down"    ,"KeySWLock":  1 },
    0x0f    :{ "KeyName": "RW_Home"    ,"KeySWLock":  1 },
}
# ----------------------------------------------------------------------
# Function      : Send_wUpdateCurrentPos
# Description   : Send Current Logi Position
# Input         : SET_POS Axis(1),Pos(4)2
# Return        : lArrSendData
# ----------------------------------------------------------------------
def Send_wUpdateCurrentPos(liAxis, liCurrentLogiPos):

    lArrSendData = [""]* 50         # array initialize

    # MOVE VR (0xD5) , Axis(1) , ms(4), idms(2), step_frw(4),step(4),dst_pos(4)
    lArrSendData[0] = ArrUART_WriteHeadCode["defUART_SetCurrLogiPos"]["HeadCode"] 
    # Axis - 1 Bytes after AxisMapping
    #lArrSendData[1] = DataFormat.ArrAxisMapping[ldicActable[liRowCnt]["Axis"]
    lArrSendData[1] = liAxis

    ByteConverter = int(liCurrentLogiPos).to_bytes(4 , byteorder='little' , signed=True )
    lArrSendData[2:5] = ByteConverter[0:]  # Copy 4 bytes to Arry 14~17

    return  lArrSendData

# ----------------------------------------------------------------------
# Function      : Send_wUpdateCurrentPos
# Description   : Send Current Logi Position
# Input         : SET_POS Axis(1),Pos(4)2
# Return        : lArrSendData
# ----------------------------------------------------------------------
def Send_wSetNearPosition(liAxis, liNearPos):

    lArrSendData = [""]* 50         # array initialize

    # SET_POS Axis(1),NearPos(2)
    lArrSendData[0] = ArrUART_WriteHeadCode["defUART_SetNearPos"]["HeadCode"] 
    # Axis - 1 Bytes after AxisMapping
    lArrSendData[1] = liAxis

    ByteConverter = int(liNearPos).to_bytes(2 , byteorder='little' , signed=False )
    lArrSendData[2:3] = ByteConverter[0:]  # Copy 4 bytes to Arry 14~17

    return  lArrSendData

# ----------------------------------------------------------------------
# Function      : Send_wMOVEs
# Description   : "MOVE", "MOVE_TOUCH"
# Input         : MOVE (0xD0) , Axis(1) , FileNo(2), N(2), Start ms(4), ms(2), idms(2), step_frw(4), step(4), dst_pos(4)
# Return        : lArrSendData
    # # MOVE (0xD0) , Axis(1) , FileNo(2), N(2), Start ms(4), ms(2), idms(2), step_frw(4), step(4), dst_pos(4)
    # self.fUART_wMOVE(lsAxis, liFileNo , liN, liStartms, lims, lidms, lfrw, lstep, ldst_pos )
# ----------------------------------------------------------------------
def Send_wMOVE(liAxis, liFileNo , liN, liStartms, lims, lidms, lfrw, lstep, ldst_pos ):
    lArrSendData = Send_wMOVEs("MOVE", liAxis, liFileNo , liN, liStartms, lims, lidms, lfrw, lstep, ldst_pos )
    return lArrSendData


def Send_wMOVE_TOUCH(liAxis, liFileNo , liN, liStartms, lims, lidms, lfrw, lstep, ldst_pos ):
    lArrSendData = Send_wMOVEs("MOVE_TOUCH", liAxis, liFileNo , liN, liStartms, lims, lidms, lfrw, lstep, ldst_pos )
    return lArrSendData

def Send_wMOVEs(lsCmd, liAxis, liFileNo , liN, liStartms, lims, lidms, lfrw, lstep, ldst_pos ):
        
    lArrSendData = [""]* 50         # array initialize

    # MOVE_TOCUH 當探針失敗後執行
    lArrSendData[0] = ArrUART_WriteHeadCode[lsCmd]["HeadCode"] 
    # Axis - 1 Bytes after AxisMapping
    
    #lArrSendData[1] = DataFormat.ArrAxisMapping[ldicActable[liRowCnt]["Axis"]]
    lArrSendData[1] = liAxis
    # File No - 2 Bytes
    ByteConverter = int(liFileNo).to_bytes(2 , byteorder='little' , signed=True )
    lArrSendData[2:3] = ByteConverter[0:]  # Copy 4 bytes to Arry 2~3
    # N - 2 Bytes
    ByteConverter = int(liN).to_bytes(2 , byteorder='little' , signed=True )
    lArrSendData[4:5] = ByteConverter[0:]  # Copy 4 bytes to Arry 3~4
    # Start ms : WORD - 4 bytes
    ByteConverter = int(liStartms).to_bytes(4 , byteorder='little' , signed=True )
    lArrSendData[6:9] = ByteConverter[0:]  # Copy 4 bytes to Arry 6~9
    # ms : 2 bytes
    ByteConverter = int(lims).to_bytes(2 , byteorder='little' , signed=True )
    lArrSendData[10:11] = ByteConverter[0:]  # Copy 2 bytes to Arry 10~11
    # idms : 2 bytes
    ByteConverter = int(lidms).to_bytes(2 , byteorder='little' , signed=True )
    lArrSendData[12:13] = ByteConverter[0:]  # Copy 4 bytes to Arry 12~13

    # frw step : 4 bytes
    ByteConverter = lfrw.to_bytes(4 , byteorder='little' , signed=True )
    lArrSendData[14:17] = ByteConverter[0:]  # Copy 4 bytes to Arry 14~17

    # step : 4 bytes
    ByteConverter = int(lstep).to_bytes(4 , byteorder='little' , signed=True )
    lArrSendData[18:21] = ByteConverter[0:]  # Copy 4 bytes to Arry 18~21
    
    # dst_pos : 4 bytes
    ByteConverter = ldst_pos.to_bytes(4 , byteorder='little' , signed=True )
    lArrSendData[22:25] = ByteConverter[0:]  # Copy 4 bytes to Arry 22~25

    print(lsCmd, ",Send Data", lArrSendData)
    return  lArrSendData

# ----------------------------------------------------------------------
# Function      : Send_wAIR
# Description   : "AIR"
# Input         : MOVE VR (0xD5) , Axis(1) , ms(4), idms(2), step_frw(4),step(4),dst_pos(4)
# Return        : lArrSendData
# ----------------------------------------------------------------------
def Send_wMOVE_VR(liAxis, lims, lidms, lfrw, lstep, ldst_pos ):
    lArrSendData = Send_wMOVE_VR_STEP("MOVE_VR", liAxis, lims, lidms, lfrw, lstep, ldst_pos )
    return  lArrSendData

def Send_wMOVE_STEP(liAxis, lims, lidms, lfrw, lstep, ldst_pos ):
    lArrSendData = Send_wMOVE_VR_STEP("MOVE_STEP", liAxis, lims, lidms, lfrw, lstep, ldst_pos )
    return  lArrSendData

def Send_wMOVE_VR_STEP(lsCmd, liAxis, lims, lidms, lfrw, lstep, ldst_pos ):

    lArrSendData = [""]* 50         # array initialize

    # MOVE VR (0xD5) , Axis(1) , ms(4), idms(2), step_frw(4),step(4),dst_pos(4)
    lArrSendData[0] = ArrUART_WriteHeadCode[lsCmd]["HeadCode"] 
    # Axis - 1 Bytes after AxisMapping
    #lArrSendData[1] = DataFormat.ArrAxisMapping[ldicActable[liRowCnt]["Axis"]
    lArrSendData[1] = liAxis
    # ms : 4 bytes
    ByteConverter = int(lims).to_bytes(4 , byteorder='little' , signed=True )
    lArrSendData[2:5] = ByteConverter[0:]  # Copy 2 bytes to Arry 8~9
    # idms : 2 bytes
    ByteConverter = int(lidms).to_bytes(4 , byteorder='little' , signed=True )
    lArrSendData[6:7] = ByteConverter[0:]  # Copy 4 bytes to Arry 12~15

    ByteConverter = int(lfrw).to_bytes(4 , byteorder='little' , signed=True )
    lArrSendData[8:11] = ByteConverter[0:]  # Copy 4 bytes to Arry 12~15

    # step : 4 bytes
    ByteConverter = int(lstep).to_bytes(4 , byteorder='little' , signed=True )
    lArrSendData[12:15] = ByteConverter[0:]  # Copy 4 bytes to Arry 12~15

    ByteConverter = int(ldst_pos).to_bytes(4 , byteorder='little' , signed=True )
    lArrSendData[16:19] = ByteConverter[0:]  # Copy 4 bytes to Arry 12~15

    print(lsCmd,",Send Data", lArrSendData)
    return  lArrSendData

# ----------------------------------------------------------------------
# Function      : Send_wMOVE_R
# Description   : "MOVE_R"
# Input         : MOVE_R (0xD9) , Axis(1) , FileNo(2), N(2), Start ms(4), ms(2), idms(2), step(4), dst_pos(4)
# Return        : lArrSendData
# ----------------------------------------------------------------------
def Send_wMOVE_R(liAxis, liFileNo , liN, liStartms, lims, lidms, lstep, ldst_pos):

    lArrSendData = [""]* 50         # array initialize

    lArrSendData[0] = ArrUART_WriteHeadCode["MOVE_R"]["HeadCode"] 
    # Axis - 1 Bytes after AxisMapping
    
    #lArrSendData[1] = DataFormat.ArrAxisMapping[ldicActable[liRowCnt]["Axis"]]
    lArrSendData[1] = liAxis
    # File No - 2 Bytes
    ByteConverter = int(liFileNo).to_bytes(2 , byteorder='little' , signed=True )
    lArrSendData[2:3] = ByteConverter[0:]  # Copy 4 bytes to Arry 2~3
    # N - 2 Bytes
    ByteConverter = int(liN).to_bytes(2 , byteorder='little' , signed=True )
    lArrSendData[4:5] = ByteConverter[0:]  # Copy 4 bytes to Arry 4~5
    # Start ms : WORD - 4 bytes
    ByteConverter = int(liStartms).to_bytes(4 , byteorder='little' , signed=True )

    lArrSendData[6:9] = ByteConverter[0:]  # Copy 4 bytes to Arry 6~9
    # ms : 2 bytes
    ByteConverter = int(lims).to_bytes(2 , byteorder='little' , signed=True )
    lArrSendData[10:11] = ByteConverter[0:]  # Copy 2 bytes to Arry 10~11
    # idms : 2 bytes
    ByteConverter = int(lidms).to_bytes(2 , byteorder='little' , signed=True )
    lArrSendData[12:13] = ByteConverter[0:]  # Copy 4 bytes to Arry 12~13

    # step : 4 bytes
    ByteConverter = int(lstep).to_bytes(4 , byteorder='little' , signed=True )
    lArrSendData[14:17] = ByteConverter[0:]  # Copy 4 bytes to Arry 14~17
    # dst_pos : 4 bytes

    ByteConverter = int(ldst_pos).to_bytes(4 , byteorder='little' , signed=True )
    lArrSendData[18:21] = ByteConverter[0:]  # Copy 4 bytes to Arry 18~21
    print("MOVE_R,Send Data", lArrSendData)

    return  lArrSendData

# ----------------------------------------------------------------------
# Function      : Send_wSPD_CHANGE
# Description   : "SPD CHANGE"
# Input         : SPD Value
# Return        : lArrSendData
# ----------------------------------------------------------------------
def Send_wSPD_CHANGE(liSPD ):

    lArrSendData = [""]* 50         # array initialize

    lArrSendData[0] = ArrUART_WriteHeadCode["SPD_CHANGE"]["HeadCode"] 
    # SPD - 1 Bytes
    lArrSendData[1] = liSPD
    print("SPD Change ,Send Data", lArrSendData)

    return  lArrSendData

# ----------------------------------------------------------------------
# Function      : Send_wTOUCH
# Description   : "TOUCH"
# Input         : TOUCH(0xD7),N(2), TOUCH探針(1),FileNo(2),Start ms(4),ms(2)
# Return        : lArrSendData
# ----------------------------------------------------------------------
def Send_wTOUCH(liN, liTouch, liFileNo, liStartms, lims):

    lArrSendData = [""]* 50         # array initialize

    ## TOUCH(0xD7), N(2), TOUCH探針(1),FileNo(2),Start ms(4),ms(2)
    lArrSendData[0] = ArrUART_WriteHeadCode["TOUCH"]["HeadCode"] 

    # N - 2 Bytes
    ByteConverter = int(liN).to_bytes(2 , byteorder='little' , signed=False )
    lArrSendData[1:2] = ByteConverter[0:]  # Copy 4 bytes to Arry 2~3
    # Axis - 1 Bytes after AxisMapping
    lArrSendData[3] = liTouch

    # Start ms : WORD - 4 bytes
    ByteConverter = int(liFileNo).to_bytes(2 , byteorder='little' , signed=False )
    lArrSendData[4:5] = ByteConverter[0:]  # Copy 4 bytes to Arry 4~7

    ByteConverter = int(liStartms).to_bytes(4 , byteorder='little' , signed=False )
    lArrSendData[6:9] = ByteConverter[0:]  # Copy 4 bytes to Arry 4~7
    # ms : 2 bytes
    ByteConverter = int(lims).to_bytes(2 , byteorder='little' , signed=False )
    lArrSendData[10:11] = ByteConverter[0:]  # Copy 2 bytes to Arry 8~9
    print("TOUCH,Send Data", lArrSendData)

    return  lArrSendData


# ----------------------------------------------------------------------
# Function      : Send_wREPEAT
# Description   : "REPEAT"
# Input         : REPEAT(0xE3) Repeat_Startms(4). Repeat_Endms(4),Repeat_CNT(2)
# Return        : lArrSendData
# ----------------------------------------------------------------------
def Send_wREPEAT(liN, liStartms, liEndms, liCnt):

    lArrSendData = [""]* 50         # array initialize

    lArrSendData[0] = ArrUART_WriteHeadCode["defUART_REPEAT"]["HeadCode"] 

    ByteConverter = int(liStartms).to_bytes(4 , byteorder='little' , signed=False )
    lArrSendData[1:4] = ByteConverter[0:]  # Copy 4 bytes to Arry 4~7

    ByteConverter = int(liEndms).to_bytes(4 , byteorder='little' , signed=False )
    lArrSendData[5:8] = ByteConverter[0:]  # Copy 4 bytes to Arry 4~7

    # ms : 2 bytes
    ByteConverter = int(liCnt).to_bytes(2 , byteorder='little' , signed=False )
    lArrSendData[9:10] = ByteConverter[0:]  # Copy 2 bytes to Arry 8~9
    print("REPEAT ,Send Data", lArrSendData)

    return  lArrSendData

# ----------------------------------------------------------------------
# Function      : Send_wAIR
# Description   : "AIR"
# Input         : AIR (0xD9), N(2), AIR汽缸(1),Start ms(4),ms(2)
# Return        : lArrSendData
# ----------------------------------------------------------------------
def Send_wAIR(liN, liAIR, liStartms, lims):

    lArrSendData = [""]* 50         # array initialize

    # AIR (0xD9), N(2), AIR汽缸(1),Start ms(4),ms(2)
    lArrSendData[0] = ArrUART_WriteHeadCode["defUART_AIR"]["HeadCode"] 
    # N - 2 Bytes
    ByteConverter = int(liN).to_bytes(2 , byteorder='little' , signed=False )
    lArrSendData[1:2] = ByteConverter[0:]  # Copy 4 bytes to Arry 2~3
    # Axis - 1 Bytes after AxisMapping
    # Start ms : WORD - 4 bytes
    lArrSendData[3] = liAIR

    ByteConverter = int(liStartms).to_bytes(4 , byteorder='little' , signed=False )
    lArrSendData[4:7] = ByteConverter[0:]  # Copy 4 bytes to Arry 4~7
    # ms : 2 bytes
    ByteConverter = int(lims).to_bytes(2 , byteorder='little' , signed=False )
    lArrSendData[8:9] = ByteConverter[0:]  # Copy 2 bytes to Arry 8~9

    print("AIR,Send Data", lArrSendData)
    return  lArrSendData

# ----------------------------------------------------------------------
# Function      : Send_wSTART_END
# Description   : "START_VR" ,"END_VR","START_MOVE_STEP","END_MOVE_STEP"]
# Input         : MOVE VR (0xD5) , Axis(1) , ms(4), idms(2), step_frw(4),step(4),dst_pos(4)
# Return        : lArrSendData
# ----------------------------------------------------------------------
def Send_wSTART_VR():
    lArrSendData = Send_wSTART_END("START_VR")
    return  lArrSendData

def Send_wEND_VR():
    lArrSendData = Send_wSTART_END("END_VR")
    return  lArrSendData

def Send_wSTART_MOVE_STEP():
    lArrSendData = Send_wSTART_END("START_MOVE_STEP")
    return  lArrSendData

def Send_wEND_MOVE_STEP():
    lArrSendData = Send_wSTART_END("END_MOVE_STEP")
    return  lArrSendData

def Send_wSTART_END(lsCmd):
      
    lArrSendData = [""]* 50         # array initialize
    lArrSendData[0] = ArrUART_WriteHeadCode[lsCmd]["HeadCode"]
    print(lsCmd, ",Send Data", lArrSendData)
    return  lArrSendData

# ----------------------------------------------------------------------
# Function      : Send_wSTART_END
# Description   : "END_ACT"
# Input         : State(1), 0: End, 1: Continous
# Return        : lArrSendData
# ----------------------------------------------------------------------
def Send_END_ACT(liEndState = None):
      
    lArrSendData = [""]* 50         # array initialize
    lArrSendData[0] = ArrUART_WriteHeadCode["END_ACT"]["HeadCode"]

    if  liEndState == None:
        liEnd = 0
    else:
        liEnd = liEndState

    lArrSendData[1] = liEnd
    print("End ACT,Send Data", lArrSendData)
    return  lArrSendData

# ----------------------------------------------------------------------
# Function      : Send_wSTART_ACT
# Description   : "START_ACT" 
# Input         : ProgramNo(2), 0xFFFF:主程式, 其他:工具程式)
# Return        : lArrSendData
# ----------------------------------------------------------------------
def Send_wSTART_ACT(liFileNo = None):
      
    lArrSendData = [""]* 50         # array initialize
    lArrSendData[0] = ArrUART_WriteHeadCode["START_ACT"]["HeadCode"]

    if  liFileNo == None:
        liNo = 0xFFFF
    else:
        liNo = liFileNo

    ByteConverter = liNo.to_bytes(2 , byteorder='little' , signed=False )    # File No
    lArrSendData[1:2] = ByteConverter[0:]  # Copy 2 bytes to Arry 2~3

    print("START_ACT,Send Data", lArrSendData)
    return  lArrSendData


class UARCommand:
    def __init__(self, parent, debug_output, VRRunMode): 
        self.lsHeadCode = "HeadCode"
        self.lsKeyToken = "Key"     
        self.lsReadBytesToken = "ReadByte"        
        self.lsHandlerToken = "Handler"
        self.lsDelToken     = "Del"
        self.empty_value = -1
        self.parent = parent
        self.debug_output = debug_output 
        self.getVRRunMode = VRRunMode
        self.Init()
        
        self.open()

    def Init(self):
      
        self.ReceivedDatas = []
        self.ReceivedReportCount  = 0
        self.giUART_Process_Packket_Cnt = 0
        self.giUART_Low_Data_cnt = 0
        
        self.InitReceiverHandler()
        
    def InitReceiverHandler(self):
        self.ReceiverCodeMap = []

        for x in range(256):
            self.ReceiverCodeMap.append({
                                         self.lsKeyToken : None,
                                         self.lsReadBytesToken : self.empty_value,
                                         self.lsHandlerToken : None,
                                         self.lsDelToken : False
                                         })
            
        for Code, Data in ArrUART_ReadHeadCode.items():
            liCmdCode = Data[self.lsHeadCode]
            self.ReceiverCodeMap[liCmdCode][self.lsKeyToken] = Code
            self.ReceiverCodeMap[liCmdCode][self.lsReadBytesToken] = Data[self.lsReadBytesToken]            
       
    def open(self):
        if os.name=='posix': # Raspi Testing
            #Serial Port initialize
            self.ser = serial.Serial("/dev/ttyAMA0", 115200)
            #ser = serial.Serial("/dev/serial0", 115200)
            self.ser.ReadBufferSize  = 12800
            self.ser.WriteBufferSize = 12800
            self.ser.timeout = 0.5          #non-block read 0.5s
            self.ser.writeTimeout = 0.5     #timeout for write 0.5s
            self.ser.xonxoff = False    #disable software flow control
            self.ser.rtscts = False     #disable hardware (RTS/CTS) flow control
            self.ser.dsrdtr = False     #disable hardware (DSR/DTR) flow control
        else:
            # Debug_Error
            self.ser = serial.Serial()

            try:
                #ser =serial.Serial('COM5')
                #115200,N,8,1
                self.ser.baudrate = 115200
                self.ser.bytesize = serial.EIGHTBITS #number of bits per bytes
                self.ser.parity = serial.PARITY_NONE #set parity check
                self.ser.stopbits = serial.STOPBITS_ONE #number of stop bits
                self.ser.timeout = 0.5          #non-block read 0.5s
            except:
                self.ser.timeout = 0.5          #non-block read 0.5s  
        
    def RegisterReceiverCodeHandler(self, pattern, handler, isSkipDelBuf=False):
        for Code, Data in ArrUART_ReadHeadCode.items():
            if (pattern == Code):
                CmdCode  = Data[self.lsHeadCode]
                self.ReceiverCodeMap[CmdCode][self.lsHandlerToken] = handler
                self.ReceiverCodeMap[CmdCode][self.lsDelToken] = isSkipDelBuf
                return  True   

        return False
  
    # ----------------------------------------------------------------------
    # UART Send 
    # Description: UART Axis send out Provider
    # Input : None
    # Return: None
    # ----------------------------------------------------------------------
    def fUART_Hexmy_print(self, liData):

        hex_liData = ' '.join(format(x, '02X') for x in liData)
        self.debug_output("UART Send Byte:", hex_liData)
        return  hex_liData
        
    def SetTimeout(self, TimeOutMilSeconds):
        currentTimeout = self.ser.timeout  #backup current read timeout setting  
        self.ser.timeout = TimeOutMilSeconds
        return (currentTimeout)
     
    # ----------------------------------------------------------------------
    # UART Read process
    # Description: UART Read Data
    # Input : liReadBytes 期望讀取的字元數
    # Return: 實際讀取的字元數
    # ----------------------------------------------------------------------
    def Read(self, liReadBytes):
        liReturnReadBytes = self.ser.read(liReadBytes)
        return (liReturnReadBytes)
        
    # ----------------------------------------------------------------------
    # UART Write process
    # Description: UART Write Data
    # Input : None
    # Return: None
    # ----------------------------------------------------------------------
    def Send(self,lbArray, liRevertByte1=True):

        # Byte 1 插入 Byte 0 反相值
        # 获取要反相的值（lbArray Byte0 的反相值）
        lbArray = bytearray(lbArray)        # 将 lbArray 转换为 bytearray
        if (liRevertByte1 == True):
            value_to_insert = ~lbArray[0] & 0xFF  # 反相并确保结果在0-255范围内        
            lbArray.insert(1, value_to_insert)              # 使用切片操作插入值
        self.debug_output("Array Data:",lbArray)

        self.fUART_Hexmy_print(lbArray)            # self.debug_output 

        if self.ser.isOpen():
            self.ser.write(lbArray)
        else:
            self.ser.close()
            self.debug_output ("open serial port error")	        

    def SendProvider(self, lsHeadCodeName, liUARTData = ""):
        
        liData  = None
        headCodeFormat = ArrUART_WriteHeadCode.get(lsHeadCodeName)
        #if headCodeFormat is None: return        
        self.debug_output("Current Data:", liUARTData)

        if headCodeFormat['SendByte'] == 0:
            #self.fUART_HeadSend(headCodeFormat['HeadCode'])
            liData = bytes([headCodeFormat['HeadCode']])
        elif headCodeFormat['SendByte'] == 1:
            liData = bytes([headCodeFormat['HeadCode'], int(liUARTData)])
        elif headCodeFormat['SendByte'] == 2:
            #self.fUART_2ByteSend(headCodeFormat['HeadCode'], liUARTData)
            ByteConverter = liUARTData.to_bytes(2, 'big')
            liData = bytes([headCodeFormat['HeadCode'],ByteConverter[1],ByteConverter[0]]) #+ ByteConverter
        elif headCodeFormat['SendByte'] == 3:
            #self.fUART_3ByteSend(headCodeFormat['HeadCode'], liUARTData)
            ByteConverter = liUARTData.to_bytes(3, 'big',signed=True)       # Negative + 3 Byte converter
            liData = bytes([headCodeFormat['HeadCode'],ByteConverter[2],ByteConverter[1],ByteConverter[0]]) #+ ByteConverter
        elif headCodeFormat['SendByte'] == 4:
            #self.fUART_4ByteSend(headCodeFormat['HeadCode'], liUARTData)
            ByteConverter = liUARTData.to_bytes(4, 'big',signed=True)       # Negative + 3 Byte converter
            liData = bytes([headCodeFormat['HeadCode'],ByteConverter[3],ByteConverter[2],ByteConverter[1],ByteConverter[0]]) #+ ByteConverter

        if liData is not None:
            self.Send(liData)
            self.debug_output("UART Send:",liData)        
        
    def AddReceiverBuf(self, datas):
        self.ReceivedDatas += datas
        
    def ClearReceiverBuf(self):
        del self.ReceivedDatas[0:] 
        
    def CheckReceiverCmd(self):
        liTimerTrigger = True
        liUARTProcessPacketCount = 0
        liSimulator = False

        if (liSimulator == True):
            #self.ReceivedDatas += [ 0x40, 0xBF, 1, 0x2] # Error Msg 錯誤警示
            #self.ReceivedDatas += [ 0x51, 0xAE, 1, 1, 0, 0, 0, 0x51, 0xAE, 1, 2, 0, 0, 0] # 位置讀取
            #self.ReceivedDatas += [ 0x55, 0xAA, 1, ] # Keyboard             
            #self.ReceivedDatas += [ 0x56, 0xA9, 10, 0x56, 0xA9, 20] # Keyboard speed     
            #self.ReceivedDatas += [ 0x57, 0xA8, 1, 0, 0, 0] # 目前生產量  
            #self.ReceivedDatas += [ 0x58, 0xA7, 2, 0, 0, 0] # 目前生產時間 (ms)
            #self.ReceivedDatas += [ 0x59, 0xA6, 1] # 目前失誤量  
            #self.ReceivedDatas += [ 0x5A, 0xA5, 1, 2] # Overflow / Underflow
            #self.ReceivedDatas += [ 0x5B, 0xA4, 1, 0] # rN  
            #self.ReceivedDatas += [ 0x5C, 0xA3, 1, 0, 0, 0] # 累積送線長度 
            #self.ReceivedDatas += [ 0x5D, 0xA2, 1] # 生產停止 - State(1) - 0:停機按鈕, 1:生產數量到, 2: 探針失誤量到
            #self.ReceivedDatas += [ 0x5E, 0xA1] # 測試轉生產  
            #self.ReceivedDatas += [ 0x61, 0x9E, 1] # MOVE STEP OK 
            self.ReceivedDatas += [ 0x62, 0x9D, 1] # MOVE VR STEP OK 
            self.ReceivedDatas += [ 0x63, 0x9C, 1, 1, 0, 0, 0] # Touch Status 
            self.ReceivedDatas += [ 0x64, 0x9B, 1] #  Touch OK status
            self.ReceivedDatas += [ 0x65, 0x9A, 1] # 簡易手輪0x01:+, 0x02:-
            self.ReceivedDatas += [ 0x67, 0x98] # 關機準備中            
        if self.ser.isOpen() or os.name !="posix" :                      # Debug test check             
            if os.name =='posix':       # Raspi mode check
                data_left = self.ser.inWaiting()                         # Check for remaining byte
                self.ReceivedDatas += self.ser.read(data_left)          # + self.ReceivedDatas 
                
            if  len(self.ReceivedDatas) > 0 :
                self.debug_output("--UART Data:", self.ReceivedDatas)
            # -----------------------------------------------------------
            #       Start Decode
            # -----------------------------------------------------------
            #if len(self.ReceivedDatas) > 0:    # 至少大於 Header + 反向Header 資料 
      
            while (len(self.ReceivedDatas) > 0 and liUARTProcessPacketCount < 30):  # 至少大於 Header + 反向Header 資料    
                if (liTimerTrigger == True):
                    liTimerTrigger = False                    
   
                    self.ReceivedReportCount += 1 
                    if self.ReceivedReportCount > 20:        # 200ms 回傳 buffer size
                        self.ReceivedReportCount = 0                            
                        liSendSpeedDownCmd = True
                        liDataLen          = 0
                        if (self.getVRRunMode() == 1):
                            liDataLen = len(self.ReceivedDatas)                    
                            if liDataLen > 100:
                                self.giUART_Low_Data_cnt = 0
                            else:
                                self.giUART_Low_Data_cnt +=1
                                if (self.giUART_Low_Data_cnt >= 2):
                                    liSendSpeedDownCmd = False
                                    self.giUART_Low_Data_cnt = 2
                                else:
                                    liSendSpeedDownCmd = True
                        
                        if liSendSpeedDownCmd == True:
                            self.SendProvider('defUART_wSlow', liDataLen)
                            self.debug_output("*****************UART Size:", liDataLen)
                liUARTProcessPacketCount+=1
				
                self.debug_output("Received:",str(self.ReceivedDatas))
                if len(self.ReceivedDatas) < 2:        # 必須 > 2 位Header
                    del self.ReceivedDatas[0:]
                    return
                    
                # Byte1 反向值
                # 将十六进制值转换为二进制字符串，并去掉前缀'0b'
                reversed_hex = (~self.ReceivedDatas[1]) & 0xFF # 反相并确保结果在0-255范围内
                if self.ReceivedDatas[0] != reversed_hex : # 反向確認
                    del self.ReceivedDatas[0:]
                    self.debug_output("Header check error")
                    return
                   
                # 確認 HeadCode 是否存在
                lUART_Code = None
                liCmdCode = self.ReceivedDatas[0]
                liCmdReadBytes = self.ReceiverCodeMap[liCmdCode][self.lsReadBytesToken]
                if (liCmdReadBytes == self.empty_value):
                    del self.ReceivedDatas[0:]
                    return
                
                self.giUART_Process_Packket_Cnt +=1
                self.debug_output("P:", self.giUART_Process_Packket_Cnt, "L:",liUARTProcessPacketCount, "S:", len(self.ReceivedDatas)) 
                #self.debug_output("Received code:", lUART_Code)

                lUART_Code = self.ReceiverCodeMap[liCmdCode][self.lsKeyToken]
                Handler = self.ReceiverCodeMap[liCmdCode][self.lsHandlerToken]
                if (Handler is not None):
                    Handler(self.ReceivedDatas, liCmdCode, liCmdReadBytes)
                else:
                    self.debug_output("Received code: no register handler", liCmdCode)

        
                if (self.ReceiverCodeMap[liCmdCode][self.lsDelToken] == True):     # Check indicator received
                    self.debug_output("Delete Skip")
                else:               
                    del self.ReceivedDatas[0:(liCmdReadBytes+2)]             # delete Array 0,1
                    self.debug_output("Code:",lUART_Code,",Delete number:",liCmdReadBytes+2,",New Date:",str(self.ReceivedDatas))
                    

 