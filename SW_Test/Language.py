def fONOFFSelect(No):
    switch = {0 : '0_OFF', 
              1 : '1_ON',
              }

    return switch.get(No, '0_OFF')
    
def fZRTModeSelect(No):
    switch = {0 : '0_DIR', 
              1 : '1_INDIR',
              2 : '2_IMMED',
              }

    return switch.get(No, '0_DIR')

def fSpeedModeSelect(No):
    switch = {0 : '0_UltraSPD', 
              1 : '1_AVDSPD',
              2 : '2_SelfSPD',
              }

    return switch.get(No, '0_UltraSPD')

def fZRTSignalSelect(No):
    switch = {0 : '0_Low', 
              1 : '1_High',
              2 : '2_NoRef',
              }

    return switch.get(No, '0_Low')

def fCoreCalibrateSelect(No):
    switch = {0 : '0_DEFAULT', 
              1 : '1_USER',
              }

    return switch.get(No, '0_DEFAULT')

def fXEncoderSelect(No):
    switch = {0 : '0_DEFAULT', 
              1 : '1_4000',
              }

    return switch.get(No, '0_DEFAULT')

def fYEncoderSelect(No):
    switch = {0 : '0_DEFAULT', 
              1 : '1_4000',
              }

    return switch.get(No, '0_DEFAULT')


def fMotorModelSelect(No):
    switch = {0 : '0_DEFAULT', 
              1 : '1_DELTA',
              }

    return switch.get(No, '0_DEFAULT')

def fUnitSelect(No):
    switch = {0 : '0_STEP', 
              1 : '1_ANGLE',
              2 : '2_mm',
              3 : '3_Turns',
              }
    return switch.get(No, '0_STEP')             # 當找不到時 返回 Error

def fIsUseSelect(No):
    switch = {0 : '0_NonUse', 
              1 : '1_Use',
              }

    return switch.get(No, '0_NonUse')



Select_OnOff =  {
        0 : '0_OFF', 
        1 : '1_ON',
}

def GetMotorUnit(litem):
    for lAxis, lData in Select_UnitCell.items():
        if lData == litem :
            return lAxis
    return ("")

Select_UnitCell = {
        0 : '0_STEP', 
        1 : '1_ANGLE',
        2 : '2_mm',
        3 : '3_Turns',
}

Select_MotorType = {
        0 : 'SANYO', 
        1 : 'Panasonic',
        2 : 'Delta',
        3 : "YASKAWA",
}

Select_Axis = {
        0 : 'X1', 
        1 : 'X2',
        2 : 'X3',
        3 : 'X4',
        4 : 'X5',
        5 : 'X6',
        6 : 'X7',
        7 : 'X8',
}


def GetMotorFunction(litem):
    for lAxis, lData in Select_MotorFunction.items():
        if lData == litem :
            return lAxis
    return ("")

Select_MotorFunction = {
        0 : 'Cam'     ,
        1 : 'Feeding' ,
        2 : 'Rotating',
        3 : 'Turning' ,
        4 : 'Reeling' ,
        5 : 'Cutter'  ,
        6 : 'Clamping',
        7 : 'Sliding' ,
        8 : 'Fold'    ,
        9 : 'Shift'  ,
}
        # 8 : 'Scobing' ,

Select_DigitMode = {
        0 : "DOS",
        1 : "Window"  ,
}

Select_UnitExchange = {
        0 : "0-Indirect",
        1 : "1-Direct"  ,
}
Select_PNFunction = {
        0 : "0-S-Type",
        1 : "1-T-Type"  ,
}
Select_Touch = {
        0 : " ",
        1 : "T1-TouchStop",
        2 : "T2-TouchStop",
        3 : "T3-TouchStop",
        4 : "T4-TouchStop",
        5 : "T1-TouchNoStop",
        6 : "T2-TouchNoStop",
        7 : "T3-TouchNoStop",
        8 : "T4-TouchNoStop",
        9 : "TouchFailGo",
}
Select_MatchAir = {
        0 : " ",
        1 : "AIR1",
        2 : "AIR2",
        3 : "AIR3",
        4 : "AIR4",
        5 : "AIR5",
        6 : "AIR6",
        7 : "AIR7",
        8 : "AIR8",
}

# Get Touch String 
def GetTouchAirStr(lTouchProgramNo):

        liProgramNo = int(lTouchProgramNo/10)
        lTouch      = lTouchProgramNo % 10
        lsTouch     = GetTouchStr(lTouch)
        lsProgramNo = ""

        # 工具程式
        if liProgramNo > 0:
             liProgramNo = int(lTouchProgramNo/10)
             lsProgramNo = '{:04d}'.format(liProgramNo)              # 工具程式- 檔案名稱
        #lAir = GetAirStr(lAir)
        if lsTouch == "":
             lDisplay = ""
        elif lsProgramNo == "":
             lDisplay = lsTouch                                           
        else:
             lDisplay = lsTouch + "+" + lsProgramNo                                           
        return  lDisplay

def GetTouchStr(lTouch):

        if lTouch in [1,2,3,4]:      lTouch = "T" + str(lTouch)
        #elif lTouch == 9:            lTouch = "■"
        elif lTouch == 5:            lTouch = "T" + "①"
        elif lTouch == 6:            lTouch = "T" + "②"
        elif lTouch == 7:            lTouch = "T" + "③"
        elif lTouch == 8:            lTouch = "T" + "④"
        else:lTouch =""
        return  lTouch

# Get Touch String 
def GetAirStr(lAir):
        if lAir in [1,2,3,4,5,6,7,8]:
                lAir = "AIR" + str(lAir)
        else:    
                lAir =""
        return  lAir

# Display                0: English, 1: 繁體中文, 2:簡體中文, 3: 義大利文
ArrLanguage = { 
    "DOS"           :["DOS"         ,"DOS"         ,"DOS"         ,"DOS"],
    "Window"        :["Window"      ,"Window"      ,"Window"      ,"Window"],
    " "             :[' '           ,' '           ,' '            ,' '],
    "No"            :['No'          ,'編號'         ,'编号'         ,'No'],
    "0-Indirect"    :['Indirect'    ,'間接'         ,'间接'         ,'Indirect'],
    "1-Direct"      :['Direct'      ,'立即'         ,'立即'         ,'Direct'],
    "0-S-Type"      :['S-Type'      ,'S型'          ,'S型'         ,'S-Type'],
    "1-T-Type"      :['T-Type'      ,'T型'          ,'T型'         ,'T-Type'],
    "LANG_SET"      :["ENG"         ,"繁體"         ,"简体"         ,"Itali"],
    "N"             :[ "N"          ,"N"            ,"N"            ,"N"],
    "G"             :[ "G"          ,"G"            ,"G"            ,"G"],
    "SPD"           :[ "SPD"        ,"SPD"          ,"SPD"          ,"SPD"],
    "T"             :[ "T"          ,"T"            ,"T"            ,"T"],
    "_PAUSE"        :["-PAUSE-"     ,"-暫停-"       ,"-暂停-"       ,"-PAUSE-"],
    "_OFF"          :["-OFF-"       ,"-關閉-"       ,"-关闭-"       ,"-OFF-"],
    "OFF"           :["OFF"         ,"關閉"         ,"关闭"         ,"OFF"],
    "AIR"           :["AIR"         ,"汽缸"         ,"汽缸"         ,"Cilindro"],
    "TH1"           :["TH1"         ,"探針1"        ,"探针1"        ,"Probe1"],
    "TH2"           :["TH2"         ,"探針2"        ,"探针2"        ,"Probe2"],
    "MODE"          :["MODE"        ," 模式"        ," 模式"        ,"MODE"],
    "MISSCNT"       :["MISS CNT"    ,"目前失誤量"   ,"目前失误量"   ,"MISS CNT"],
    "SETMISS"       :["SET MISS"    ,"設定失誤量"   ,"设定失误量"   ,"SET MISS"],
    "RATE"          :["RATE"        ,"生產速率"     ,"生产速率"     ,"RATE"],
    "QTYCNT"        :["QTY CNT"     ,"目前生產量"   ,"目前生产量"   ,"QTY CNT"],
    "SETQTY"        :["SET QTY"     ,"設定生產量"   ,"设定生产量"   ,"SET QTY"],
    "FILENO"        :["FILE"        ,"調機程式"     ,"调机程式"      ,"FILE"],
    "ToolProgram"   :["Tool Program","工具程式"     ,"工具程式"     ,"Tool Program"],
    "AXIS"          :["Axis"        ,"軸"           ,"轴"           ,"Axis"],
    "AXISMode"      :["AXIS"        ,"刀具"         ,"刀具"         ,"AXIS"],
    "POS"           :["POS"         ,"位置"         ,"位置"         ,"POS"],
    "MAN"           :["MAN"         ,"手動"         ,"手动"         ,"MAN"],
    "MPG"           :["MPG"         ,"手輪"         ,"手轮"         ,"MPG"],
    "MPGPWR"        :["MPG PWR"     ,"手輪倍率"     ,"手轮倍率"      ,"MPG PWR"],
    "EDIT"          :["EDIT"        ,"表格 "        ,"表格"        ,"EDIT"],
    "TIMELINE"      :["AUTO LINK"    ,"表格微調"     ,"表格微调"     ,"AUTO LINK"],
    "TOOL"          :["TOOL"        ,"工具"         ,"工具"         ,"TOOL"],

    "Select"        :["Select"      ,"選擇"         ,"选择"         ,"Select"],    
    "CANCEL"        :["Cancel"      ,"取消"         ,"取消"         ,"Cancel"],    

    "TIME"          :["TIME"        ,"時間"         ,"时间"         ,"TIME"],
    "ACTION"        :["ACTION"      ,"動作"         ,"动作"         ,"ACTION"],

    "All"           :["ALL"         ,"全部"         ,"全部"         ,"ALL"], 
    "WORK"          :["WORK"        ,"生產測試"     ,"生产测试"     ,"WORK"], 
    "FILE"          :["FILE"        ,"檔案"         ,"档案"        ,"FILE"],
    "ADD"           :["ADD"         ,"增加"         ,"增加"         ,"ADD"],
    "InsertL"       :["Insert Left" ,"向左插入"     ,"向左插入"      ,"Insert Left"],
    "InsertR"       :["Insert Right","向右插入"     ,"向右插入"      ,"Insert Right"],

    "Copy2Tool"     :["Copy2Tool"   ,"複製到工具庫"  ,"复制到工具库"  ,"Copy2Tool" ],
    "Copy2Edit"     :["Copy2Edit"   ,"複製到調機庫"  ,"复制到调机库"  ,"Copy2Edit" ],


    "CopySel2Local" :["Select To Local" ,"複製選擇到本地"  ,"复制选择到本地"    ,"Select To Local" ],
    "CopyAllLocal"  :["All to Local"    ,"複製全部到本地"  ,"复制全部到本地"    ,"All to Local"    ],
    "CopySel2USB"   :["Select to USB"   ,"複製選擇到USB"   ,"复制选择到本地"    ,"Select to USB"   ],
    "CopyAll2USB"   :["All to USB"      ,"複製全部到USB"   ,"复制全部到本地"    ,"All to USB"      ],

    "FILE_List"     :["FILE List"     ,"調機程式庫"    ,"调机程式库"    ,"FILE List"],
    "PARA_List"     :["PARAMTER List" ,"參數清單"      ,"参数清单"      ,"PARAMTER List"],
    "Tool_List"     :["Tool List"     ,"工具程式庫"    ,"工具程式库"     ,"Tool List"],

    "TEST"          :["TEST"          ,"測試 "        ,"测试 "        ,"TEST"],
    "TESTEdit"      :["TEST\nEditable","測試\n修改"   ,"测试\n修改"    ,"TEST\nEditable"],
    "AITEST"        :["AI\nSEG TEST"  ,"AI\n區塊測試" ,"AI\n区段测试"    ,"AI\nSEG TEST"],


    "Knob_0"        :["Knob Must 0" ,"旋鈕請歸零"   ,"旋钮请归零"  ,"Knob Must 0"],
    "STEP"          :["STEP"        ,"單步 "        ,"单步 "        ,"STEP"],
    "STOP"          :["STOP"        ,"停機"         ,"停机"        ,"STOP"],
    "MODY"          :["EDIT"        ,"修改 "        ,"修改 "        ,"EDIT"],
    "PARA"          :["PARAMTER"    ,"參數"         ,"参数"         ,"PARAMTER"],

    "PARA_Simple"   :["SIMPLE PARAMTER","簡易參數"   ,"简易参数"     ,"SIMPLE PARAMTER"],
    "PARA_Advance"  :["ADV. PARAMTER"  ,"進階參數"   ,"进阶参数"     ,"ADV. PARAMTER"],

    "GoHome"        :["Back Home"   ,"回主程式"      ,"回主程式"        ,"Back Home"],
    "GoToolProgram" :["Back Tool"   ,"回工具視窗"    ,"回工具视窗"    ,"Back Tool"],

    "Modified"      :["Modifided\nWait To STOP" ,"編輯修改\n等待停止"    ,"编辑修改\n等待停止" ,"Modifided\nWait To STOP"],

    "Memory"        :["MEMORY SAVE"   ,"記憶"       ,"记忆"         ,"MEMORY SAVE"],   
    "NoMemory"      :["NO MEMORY SAVE","不記憶"     ,"不记忆"       ,"NO MEMORY SAVE"],   
    "NoUpdate"      :["NO UPDATE"     ,"不更新"     ,"不更新"       ,"NO UPDTE"],   

    "HELP"          :["HELP"        ,"說明 "        ,"说明 "        ,"HELP"],   
    "FileSave"      :["SAVE"        ,"存檔 "        ,"存档"         ,"SAVE"],
    "FileCopy"      :["COPY"        ,"複製 "        ,"复制"         ,"COPY"],
    "FileOpen"      :["OPEN"        ,"開啟 "        ,"开啟"         ,"OPEN"],
    "FileParaOpen"  :["OPEN PARAMTER","開啟參數 "    ,"开啟参数"      ,"OPENPARAMTER"],
    "FileDelete"    :["DELETE"      ,"刪除"        ,"删除"          ,"DELETE"],
    "FileNew"       :["NEW"         ,"新增"        ,"新增"          ,"NEW"],
    "ProgramNew"    :["NEW"         ,"新增調機程式" ,"新增调机程式"   ,"NEW"],
    "ToolNew"       :["NEW TOOL"    ,"新增工具程式" ,"新增工具程式"   ,"NEW TOOL"],
    "PhotoAdd"      :["ADD PHOTO"   ,"添加照片"     ,"添加照片"      ,"ADD PHOTO"],
    "PhotoRemove"   :["REMOVE PHOTE","刪除照片"     ,"删除照片"      ,"REMOVE PHOTE"],
    "ProdSpeed"     :["CURR SPD"    ,"目前產速"     ,"目前产速"      ,"CURR SPD"],
    "FeedLength"    :["FEED LENGTH" ,"累積送線"     ,"累积送线"      ,"FEED LENGTH"],
    "PWRReset"      :["PWR RESET"   ,"軸倍率重置"   ,"轴倍率重置"    ,"PWR RESET"],
    "DigitMode"     :["Digit Mode"  ,"數字模式"     ,"数字模式"      ,"Digit Mode"],
    "0_OFF"         :["OFF"         ,"關閉"         ,"关闭"         ,"OFF"],
    "ON"            :["ON"          ,"開啟"         ,"开启"         ,"ON"],
    "1_ON"          :["ON"          ,"開啟"         ,"开启"         ,"ON"],
    "0_DIR"         :["0-DIRECT"    ,"0-直接"       ,"0-直接"       ,"0-DIRECT"],
    "1_INDIR"       :["1-IN-DIR"    ,"1-間接"       ,"1-间接"       ,"1-INDIR"],   
    "2_IMMED"       :["2-Immed"     ,"2-立即"       ,"2-立即"       ,"2-Immed"],
    "3_TurnWire"    :["3-Turn"      ,"3-轉線"       ,"3-转线"       ,"3-Turn"],   
    "0_NonUse"      :["0-NonUse"    ,"0-不使用"     ,"0-不使用"     ,"0-NonUse"],
    "1_Use"         :["1-Use"       ,"1-使用"       ,"1-使用"       ,"1-Use"],
    "CYCLE"         :["cyc."        ,"週期"         ,"1-周期"       ,"cyc."],     
    "0_DEFAULT"     :["0-DEFAULT"   ,"0-預設"       ,"0-预设"       ,"0-DEFAULT"], 
    "1_4000"        :["1-4000"      ,"1-4000型"     ,"1-4000型"     ,"1-4000"],    
    "1_USER"        :["1-USER"      ,"1-自定義"     ,"1-自定义"     ,"1-USER"],     
    "1_DELTA"       :["1-DELTA"     ,"1-台達"       ,"1-台达"       ,"1-DELTA"], 
    "0_UltraSPD"    :["1-Ultra"     ,"0-超速率"     ,"0-超速率"     ,"0-Ultra"],     
    "1_AVDSPD"      :["1-AVG"       ,"1-均速率"     ,"1-均速率"     ,"1-AVG"],     
    "2_SelfSPD"     :["2-Self"      ,"2-自"         ,"2-自"        ,"2-Self"],  
    "Cam"           :["Cam"         ,"凸輪"         ,"凸轮"         ,"Cam"],
    "Feeding"       :["Feeding"     ,"送料"         ,"送料"         ,"Feeding"],
    "Rotating"      :["Rotating"    ,"轉芯"         ,"转芯"         ,"Rotating"],
    "Turning"       :["Turning"     ,"翻線"         ,"翻线"         ,"Turning"],
    "Reeling"       :["Reeling"     ,"捲取"         ,"卷取"         ,"Reeling"],
    "Cutter"        :["Cutter"      ,"切刀"         ,"切刀"         ,"Cutter"],
    "Clamping"      :["Clamping"    ,"夾耳"         ,"夹耳"         ,"Clamping"],
    "Sliding"       :["Sliding"     ,"滑座"         ,"滑座"         ,"Sliding"],
    "Folding"       :["Fold"        ,"折角"         ,"折角"         ,"Fold"]	,
    "Trans"         :["Shift"       ,"平移"         ,"平移"         ,"Shift"],
    "0_STEP"        :["SETP"        ,"格數"         ,"格数"       ,"SETP"],
    "1_ANGLE"       :["ANGLE"       ,"角度"         ,"角度"       ,"ANGLE"],
    "2_mm"          :["mm"          ,"mm"           ,"mm"         ,"mm"],
    "3_Turns"       :["Turns"       ,"圈數"         ,"圈数"       ,"Turns"],
    "SANYO"         :["SANYO"       ,"山洋"         ,"山洋"         ,"SANYO"],   
    "Panasonic"     :["Panasonic"     ,"松下"         ,"松下"         ,"Panasonic"],
    "Delta"         :["Delta"       ,"台達"         ,"台达"         ,"Delta"],
    "YASKAWA"       :["YASKAWA"     ,"安川"         ,"安川"         ,"YASKAWA"],
    "SEC"           :["Sec"         ,"秒"           ,"秒"           ,"Sec"  ],
    "MIN"           :["Min"         ,"分鐘"         ,"分钟"         ,"Min"  ],
    "SPEED"         :["Speed"       ,"速度"         ,"速度"         ,"Speed"],
    "RATE"          :["Rate"        ,"速率"         ,"速率"         ,"Rate"],
    "0_Low"         :["0-Low"       ,"0-Low"        ,"0-Low"        ,"0-Low"],
    "1_High"        :["1-High"      ,"1-High"       ,"1-High"       ,"1-High"],
    "2_NoRef"       :["2-No Ref"    ,"2-不參考"     ,"2-不参考"     ,"2-No Ref"],
    "DEG"           :["(Deg)"       ,"(角度)"       ,"(角度)"       ,"(Deg)"],
   
    # PARA Pububuttom
    "MotorNo"       :["MOTOR NO"    ,"馬達編號"     ,"马达编号"     ,"MOTOR NO"    ],
    "MotorName"     :["Name"        ,"馬達名稱"     ,"马达名称"     ,"Name"        ],
    'Unit'          :['Unit'        ,'單位'         ,'单位'        ,'Unit'],   
    "MotorStep"     :["Step"        ,"馬達格數"     ,"马达格数"     ,"Step"    ],
    "MotorType"     :["Type"        ,"馬達型態"     ,"马达型态"     ,"Type"    ],
    "MotorFunction" :["FUNC"        ,"馬達功能"     ,"马达功能"     ,"FUNC"    ],
    "ZRTOrder"      :["HOME"        ,"原點順序"     ,"原点顺序"     ,"HOME"     ],
    "ZRTMode"       :["ZRT MODE"    ,"原點模式"     ,"原点模式"     ,"ZRT MODE"    ],
    "ZRTNew"        :["ZRT SET"     ,"新設原點"     ,"新设原点"     ,"ZRT SET"     ],
    "ZRTMapping"    :["ZRT CORR"    ,"原點對應"     ,"原点对应"     ,"ZRT CORR"    ],
    "MaxLimit"      :["Axis Max"    ,"最大極限"     ,"最大极限"     ,"Axis Max"    ],
    "MinLimit"      :["Axis Min"    ,"最小極限"     ,"最小极限"     ,"Axis Min"    ],
    "FeedSignal"    :["MOT NEAR"    ,"回報信號"     ,"回报信号"     ,"MOT NEAR"    ],
    "Language"      :["Language"    ,"語言設定"     ,"语言设定"     ,"Language"    ],
    "ModelName"     :["Model"       ,"機器型號"     ,"机器型号"     ,"Model"       ],
    "Y_Encoder"     :["Y-Encode"    ,"Y-編碼器"     ,"Y-编码器"     ,"Y-Encode"    ],
    "SafeDoor"      :["SHIELD"      ,"安全門"       ,"安全门"       ,"SHIELD"      ],
    "SafeEquip"     :["SENSOR"      ,"安全裝置"     ,"安全装置"     ,"SENSOR"      ],
    "Alarm"         :["W.LIGHT"     ,"警示燈"       ,"警示灯"       ,"W.LIGHT"     ],
    "CutDist"       :["Cut Dist"    ,"切刀距離"     ,"切刀距离"     ,"Cut Dist"    ],
    "SpeedMode"     :["RateMode"    ,"速率模式"     ,"速率模式"     ,"RateMode"    ],
    "SPDMode"       :["SPD Mode"    ,"SPD 模式"     ,"SPD 模式"     ,"SPD Mode"    ],
    "ZRTPosition"   :["ZRT POS"     ,"原點位置"     ,"原点位置"     ,"ZRT POS"     ],
    "ZRTCNT"        :["ZRT CYE"     ,"原點圈數"     ,"原点圈数"     ,"ZRT CYE"     ],
    "Gear0"         :["Gear"        ,"齒輪比"       ,"齿轮比"     ,"Gear"       ],
    "Gear1"         :["Gear"        ,"齒輪比"       ,"齿轮比"     ,"Gear"       ],
    "Mumer"         :["ENCR0"       ,"分周分子"     ,"分周分子"     ,"ENCR0"       ],
    "Demon"         :["ENCR1"       ,"分周分母"     ,"分周分母"     ,"ENCR1"       ],
    "ABReverse"     :["A/B Dir"     ,"A/B 反向"     ,"A/B 反向"     ,"A/B Dir"     ],
    "ZRTSignal"     :["Sensor"      ,"原點信號"     ,"原点信号"     ,"Sensor"      ],
    "FixedCheck"    :["ChkToPos"    ,"定點檢查"     ,"定点检查"     ,"ChkToPos"    ],
    "T1DecDist"     :["T1DecDis"    ,"T1 減距離"    ,"T1 减距离"    ,"T1DecDis"    ],
    "T2DecDist"     :["T2DecDis"    ,"T2 減距離"    ,"T2 减距离"    ,"T2DecDis"    ],
    "T3DecDist"     :["T3DecDis"    ,"T3 減距離"    ,"T3 减距离"    ,"T3DecDis"    ],
    "T4DecDist"     :["T4DecDis"    ,"T4 減距離"    ,"T4 减距离"    ,"T4DecDis"    ],
    "GearSpeed"     :["HAND SPD"    ,"手輪速度"     ,"手轮速度"     ,"HAND SPD"    ],
    "WireDist"      :["Wire Gap"    ,"送線間距"     ,"送线间距"     ,"Wire Gap"    ],
    "LINE"          :["LINE"        ,"LINE"         ,"LINE"         ,"LINE"        ],
    "LOGO"          :["LOGO"        ,"LOGO"         ,"LOGO"         ,"LOGO"        ],
    "OneProdut"     :["ONE"         ,"單一生產"     ,"单一生产"     ,"ONE"         ],
    "LockProduct"   :["LOCK PWD"    ,"鎖生產量"     ,"锁生产量"     ,"LOCK PWD"    ],
    "CoreCalibrate" :["ROTQ MDY"    ,"轉蕊校正"     ,"转蕊校正"     ,"ROTQ MDY"    ],
    "WireCalibrate" :["SPIN MDY"    ,"卷取校正"     ,"卷取校正"     ,"SPIN MDY"    ],
    "LOT"           :["BATCH"       ,"批量"         ,"批量"         ,"BATCH"       ],
    "SimFAST"       :["SIM FAST"    ,"模擬 FAST"    ,"模拟 FAST"    ,"SIM FAST"    ],
    "XEncoder"      :["X-Encode"    ,"X-編碼器"     ,"X-编码器"     ,"X-Encode"    ],
    "MotorModel"    :["MOT NO"      ,"馬達型號"     ,"马达型号"     ,"MOT NO"      ],
    "MotorSpeed"    :["Speed"       ,"馬達速度"     ,"马达速度"     ,"Speed"],
    "ZRTPosition"   :["Home-POS"    ,"原點位置"     ,"原点位置"     ,"O-POS"],
    "MotorLogicalPosition":["LOGI"  ,"邏輯格數"     ,"逻辑格数"     ,"LOGI"],
    "ZRTSpeed"      :["O-SPD"       ,"原點速度"     ,"原点速度"     ,"O-SPD"],
    "PNSpeed"       :["ACC/DE"      ,"加减速"       ,"加减速"      ,"ACC/DE"],
    "PNFunction"    :["PN"          ,"加减"         ,"加减"        ,"PN"],
    "UnitExchange"  :["Unit-COV"    ,"單位換算"     ,"单位换算"     ,"Unit-COV"],
    "AxisMapping"   :["Mapping"     ,"軸對應"       ,"轴对应"       ,"Mapping"],
    "AIRSet"        :["CYLINDER SETUP","汽缸設定"    ,"汽缸设定"    ,"CYLINDER SETUP"],
    "AllOpen"       :["All OPEN"    , "全開啟"      ,"全开启"       ,"All OPEN"],
    "AllClose"      :["All CLOSE"   , "全關閉"      ,"全关闭"       ,"All CLOSE"],
    "TouchSet"      :["TOUCH SETUP" ,"探針設定"    ,"探针设定"      ,"TOUCH SETUP"],

    "MatchAir"      :["MATCH AIR"   ,"搭配汽缸"    ,"搭配汽缸"       ,"MATCH AIR"],
    "Touch"         :["TOUCH"       ,"探針"        ,"探针"          ,"TOUCH"],
    "TouchAir"      :["TOUCH AIR"   ,"探針汽缸設定" ,"探针汽缸设定"  , "TOUCH AIR"],

    "T1-TouchStop"  :["T1-TOUCH AND STOP","T1-探到後停線","T1-探到后停线","T1-TOUCH AND STOP"],
    "T2-TouchStop"  :["T2-TOUCH AND STOP","T2-探到後停線","T2-探到后停线","T2-TOUCH AND STOP"],
    "T3-TouchStop"  :["T3-TOUCH AND STOP","T3-探到後停線","T3-探到后停线","T3-TOUCH AND STOP"],
    "T4-TouchStop"  :["T4-TOUCH AND STOP","T4-探到後停線","T4-探到后停线","T4-TOUCH AND STOP"],
    "T1-TouchNoStop":["T①-TOUCH AND STOP","T①-探到後不停線","T①-探到后不停线","T①-TOUCH AND STOP"],
    "T2-TouchNoStop":["T②-TOUCH AND STOP","T②-探到後不停線","T②-探到后不停线","T②-TOUCH AND STOP"],
    "T3-TouchNoStop":["T③-TOUCH AND STOP","T③-探到後不停線","T③-探到后不停线","T③-TOUCH AND STOP"],
    "T4-TouchNoStop":["T④-TOUCH AND STOP","T④-探到後不停線","T④-探到后不停线","T④-TOUCH AND STOP"],
    "TouchFailGo"   :["TOUCH FAIL GO" ,"探針失敗後執行","探针失败后执行","TOUCH FAIL GO"],
    "MatchAir"      :["MATCH AIR"   ,"搭配汽缸"    ,"搭配汽缸",   "MATCH AIR"],

    "FRW_POS"       :["Turning COMP" ,"翻線補償"        ,"翻线补偿"     ,"Turning COMP"],
    "ProductStatus" :["PROD. STATUS", "生產進度"    ,"生产进度"     ,"PROD. STATUS"],
    "LeftTime"      :["LEFT TIME"   , "剩餘時間"    ,"剩余时间"     ,"LEFT TIME"],
    "EstTime"       :["EST. TIME"   , "預計時間"    ,"预计时间"     ,"EST. TIME"],
    "KeyLock"       :["Keyboard Lock"  ,"鍵盤鎖住"    ,"键盘锁住"   ,"Keyboard Lock"],
    "TestOK"        :["Touch OK"       ,"測試正常"    ,"测试正常"   ,"Test OK"],
    "KeySW"         :["Keyboard Switch","鍵盤切換"    ,"键盘切换"   ,"Keyboard Switch"],
    "ResetON"       :["Resetting"      ,"重置中"      ,"重置中"     ,"Resetting"],

    "SPACE"         :["SPACE"        ,"空白"         ,"空白"        ,"SPACE"              ],

    "AutoOFF"       :["Auto Power"  ,"自動關電"     ,"自动关电"     ,"Auto Power"       ],
    "AUTO"          :["AUTO"        ,"自動"         ,"自动"        ,"AUTO"              ],
    "VR"            :["MAN"         ,"手動"         ,"手动"        ,"MAN"],

    "HOME"          :["HOME"        ,"原點"         ,"原点"        ,"HOME"              ],
    "SPHome"        :["SP-HOME"     ,"選軸原點"     ,"选轴原点"     ,"SP-HOME"          ],
    "Feeding"       :["F"           ,"送線"         ,"选轴"        ,"F"                 ],
    "Clr"           :["Clr"         ,"清除"         ,"清除"        ,"Clr"               ],
    "Pow"           :["Pow"         ,"倍率"         ,"倍率"        ,"Pow"               ],
    "RESET"         :["RESET"       ,"重置"         ,"重置"        ,"RESET"             ],

    "MOVEUP"        :["MOVE UP"     ,"上移"          ,"上移"       ,"MOVE UP"           ],
    "MOVEDOWN"      :["MOVE DOWN"   ,"下移"          ,"下移"       ,"MOVE DOWN"         ],
    "RUN"           :["RUN"         ,"執行"          ,"执行"       ,"RUN"               ],
    "DELETE"        :["DELETE"      ,"刪除"          ,"删除"       ,"DELETE"            ],
    "AI_TEST"       :[" AI SEG TEST"," AI 區塊測試"   ," AI 区段测试"," AI SEG TEST"       ],

    "VRDecoding"    :["Virtaul Home Decoding"   ,"虛擬原點解析中"   ,"虚拟原点解析中"   ,"Virtaul Home Decoding"     ],

    "GOAI_Start"    :["Please use VR \nGoto the AI start" ,"請使用VR\n前往AI起點"      ,"请使用VR\n前往AI起点"      ,"Please use VR \nGoto the AI start"     ],

    "GOHOME"        :["GOING HOME"  ,"回原點中"      ,"回原点"      ,"GOING HOME"       ],
    "GOHOME_VR"     :["GOING HOME\nUsing VR Return Home"  ,"回原點中\n請用VR回原點"      ,"回原点\n请用VR回原点"      ,"GOING HOME\nUsing VR Return Home"     ],
    "GOVHome_VR"    :["Back Virtual Home\nUsing VR Return Virtual Home" ,
                      "回虛擬原點中\n請用VR回虛擬原點"  ,
                      "回虚拟原点中\n请用VR回虚拟原点"  ,
                      "Back Virtual Home\nUsing VR Return Virtual Home" ],
    "GOVHome"       :["Back Virtual Home" ,"回虛擬原點中"  ,"回虚拟原点中"      ,"Back Virtual Home"    ],

     # 外徑補償
    "CompProbe"         :["Probe"            ,"探針"    ,"探针"      ,"Probe"        ],
    "CompOutside"       :["Out Diameter"     ,"外徑"    ,"外径"      ,"Out Diameter" ],
    "CompDiameter"      :["Diameter"         ,"線徑"    ,"线径"      ,"Diameter"     ],
    "CompLaps"          :["Laps"             ,"圈數"    ,"圈数"      ,"Laps"         ],
    "CompPitch"         :["Pitch"            ,"節距"    ,"节距"      ,"Pitch"        ],
    "OutTolerence"      :["Out Tol."         ,"外徑公差"    ,"外径公差"         ,"Out Tol." ],
    "CompValue"         :["Value"            ,"補償量"  ,"补偿量"    ,"Value"   ],
    "CompRatio"         :["Ratio"            ,"補償比例","补偿比例"  ,"Ratio"   ],
    "Complimit"         :["Comp Limit"        ,"補償限制"     ,"补偿限制"  ,"Comp Limit"   ],
    "PreDevlivery"      :["Pre-Delivery"      ,"預送線"     ,"预送线"   ,"Pre-Delivery"   ],
    "ProbeValue"        :["Probe Value"       ,"探針值"     ,"探针值"   ,"Probe Value"   ],
    "CorrectUp"         :["Up Correct"        ,"修正上"     ,"修正上"   ,"Up Correct"   ],
    "CorrectDown"       :["Down Correct"      ,"修正下"     ,"修正下"   ,"Down Correct"   ],
    "CompUplimit"       :["Comp Up"           ,"補償上限"     ,"补偿上限"  ,"Comp Up"   ],
    "CompDownlimit"     :["Comp Down"         ,"補償下限"     ,"补偿下限下"  ,"Comp Down"   ],
    "CompAsix"          :["Comp Axis"         ,"補償軸"     ,"补偿轴"   ,"Comp Axis"    ],
    "StdValue"          :["Std Value"         ,"標準量"     ,"标准量"   ,"Std Value"],

    "CurrentQty"    :["Current Qty" ,"目前生產量"     ,"目前生产量"   ,"Current Qty"     ],
    "TargetQty"     :["Target Qty"  ,"設定生產量"     ,"设定生产量"   ,"Target Qty"     ],
    "Qty"           :["Qty"         ,"生產量"         ,"生产量"      ,"Qty"     ],
    "MissCounter"   :["Miss Counter","目前探針失誤量" ,"目前失误辆"   ,"Touch Miss Counter"     ],
    "MissLimit"     :["Miss Limit"  ,"設定探針失誤量" ,"设定失误辆"   ,"Touch Miss Limit"     ],
    "Probe1"        :["Touch1"      ,"探針1"         ,"探针1"       ,"Touch1"     ],
    "Probe2"        :["Touch2"      ,"探針2"         ,"探针2"       ,"Touch2"     ],
    "Probe3"        :["Touch3"      ,"探針3"         ,"探针3"       ,"Touch3"     ],
    "Probe4"        :["Touch4"      ,"探針4"         ,"探针4"       ,"Touch4"     ],
    "Touch"         :["Touch"       ,"探針"          ,"探针"        ,"Touch"     ],   
    "Near"          :["NEAR"        ,"接近值"        ,"接近值"      ,"Near"     ],   
    "ScreenProt"    :["Screen Saver","螢幕保護"     ,"萤幕保护"     ,"Screen Saver"],
    "ProducePWD"    :["PD PWD"      ,"生產密碼"     ,"生产密码"     ,"PD PWD"],
    "PRODUTION"     :["PRODUCTION"  ,"生產"         ,"生产"         ,"PRODUCTION"],

    # File Table
    "CurrentFileNo" :["Current File No.", "目前檔案編號", "目前档案编号"  ,"Current File No."],
    "Modfied_Time"  :["Modified Time"   , "修改時間"    , "修改时间"     ,"Modified Time"],
    "Created_Time"  :["Created Time"    , "建立時間"    , "建立时间"     ,"Created Time"],
    "FileComment"   :["File Comment"    , "檔案註解"    , "文件注释"     ,"File Comment" ],

    "USBDisk"       :["USB DISK"        , "USB磁碟"    , "USB盘"        ,"USB DISK" ],
    "LocalDisk"     :["LOCAL DISK"      , "本地磁碟"   , "本地盘"       ,"LOCAL DISK" ],

    #Download
    "ID"            :["ID"          ,"ID"           ,"ID"           ,"ID"           ],
    "Version"       :["Version"     ,"版本"         ,"版本"         ,"Version"      ],
    "ChangeLog"     :["Log"         ,"歷史紀錄"     ,"历史纪录"      ,"Log"      ],
    "Menu"          :["Menu"        ,"說明書"       ,"说明书"        ,"Menu"      ],
    "Version"       :["Version"     ,"版本"         ,"版本"         ,"Version"      ],
    "VersionMain"   :["Main System Version"        ,"主程式版本"    ,"主程式版本:"      ,"Main System Version"      ],
    "VersionSub"    :["Control System Version"     ,"控制程式版本"  ,"控制程式版本"     ,"Control System Version"      ],
    "USB_Update"    :["USB Update"  ,"USB 更新"     ,"USB 更新"     ,"USB Update"      ],

    "YTotal"        :["Total Y"     ,"總送線量"     ,"总送线量"      ,"Total Y"     ],
    "Total"         :["Total"       ,"總共"         ,"总共"         ,"Total"       ],
    "CameraON"      :["Camera ON"   ,"相機開啟"     ,"相机开启"      ,"Camera ON"     ],
    "Shot"          :["SHOT"        ,"拍照"         ,"拍照"         ,"SHOT"     ],

    #None Data
    "None"          :["None"        ,"未知"         ,"未知"         ,"None"     ],
    'Cam'           :['Cam'         ,'凸輪'         ,'凸轮'         ,'Cam'],
    'Feeding'       :['Feeding'     ,'送料'         ,'送料'         ,'Feeding'],
    'Rotating'      :['Rotating'    ,'轉芯'         ,'转芯'         ,'Rotating'],
    'Turning'       :['Turning'     ,'翻線'         ,'翻线'         ,'Turning'],
    'Reeling'       :['Reeling'     ,'捲取'         ,'卷取'         ,'Reeling'],
    'Cutter'        :['Cutter'      ,'切刀'         ,'切刀'         ,'Cutter'],
    'Clamping'      :['Clamping'    ,'夾耳'         ,'夹耳'         ,'Clamping'],
    'Sliding'       :['Sliding'     ,'滑座'         ,'滑座'         ,'Sliding'],
    'Scobing'       :['Scobing'     ,'翻線'         ,'翻线'         ,'Scobing'],
    'Fold'          :['Fold'        ,'折角'         ,'折角'         ,'Fold'],
    'Shift'         :['Shift'       ,'平移'         ,'平移'         ,'Shift'],
    "DAY"           :['D'           ,'天'           ,'天'           ,'D'],
    "HOUR"          :['H'           ,'小時'         ,'小时'         ,'H'],
    "MIN"           :['M'           ,'分'           ,'分'           ,'M'],
    "SECOND"        :['S'           ,'秒'           ,'秒'           ,'S'],
    "QUIT"          :['QUIT'        ,'離開'         ,"离开"         ,'QUIT'],
    "SETTING"       :['SETTING'     ,'設定'         ,"设置"         ,'SETTING'],

    "PDFViewer"     :['Menu Viewer' ,'文件說明'     ,"文件说明"      ,'Menu Viewer'],
    "VideoViewer"   :['Video Viewer','視頻說明'     ,"视频说明"      ,'Video Viewer'],
    "Error"         :[ "Error!! "   ,"錯誤!! "      ,"错误!! "      ,"Error!! " ],
    "File_Exist"    :[ "File Existent"  , "文件已存在", "文件已存在",   "File Existent"],
    
    "SelPhoto"      :[ "Select new photo"   ,"選擇新相片"      ,"选择新相片"      ,"Select new photo" ],
    "SelFolder"     :[ "Select directory"   ,"選擇目錄"      ,"选择目录"      ,"Select director" ],      
    "ConfirmDelete" :[ "Confirm Deletion"   ,"確認刪除"      ,"确认删除"      ,"Confirm Deletion" ],
    "DelMsg"        :[ "Are you sure you want to delete?"   ,"確定要刪除嗎？"   ,"确定要删除吗？"       ,"Are you sure you want to delete?" ],     
    "DelPhotoMsg"   :[ "Are you sure you want to delete the selected photo"   ,"'確定要刪除選中的相片嗎？"      ,"确定要删除选中的相片吗？"      ,"Are you sure you want to delete the selected photo" ],     
    "COMP"          :[ "COMP."          ,"外徑補償"     ,"外径补偿"     ,"COMP."        ],
    "SmartHome"     :[ "Smart Home"     ,"智慧到位"     ,"智慧到位"     ,"Smart Home" ],
    "Range"         :[ "Range"          ,"範圍"         ,"范围"         ,"Range" ],
    "Column"        :[ "Column"         ,"行"           ,"行"           ,"Column" ],

    "GraphTransfer" :[ "AUTO LINK Transfering"   ,"表格微調轉換中" ,"表格微调转换中" ,"AUTO LINK Transfering"],

    "Final_POS_Different" :[ "Final POS Different"  ,"最終位置不同"  ,"最终位置不同"  ,"Final POS Different" ],

    "AdjBehindData"  :["Need to adjust the behind data?"  ,
                       "需要調整後面的資料嗎？"    ,
                       "需要调整后面的资料吗?"   ,
                       "Need to adjust the behind data?"     ],


    "TargetQtyOver"  :["Target Qty Over \nPlease Set Target Qty"  ,
                       "生產量已超過設定 \n請設定生產量"    ,
                       "生产量已超過设定 \n请设定生产量"   ,
                       "Target Qty Over \nPlease Set Target Qty"     ],

    "TargetQty0Error":["Target Qty = 0 \nPlease Set Target Qty"  ,
                       "設定生產量 = 0 \n請設定生產量"    ,
                       "设定生产量 = 0 \n请设定生产量"   ,
                       "Target Qty = 0 \nPlease Set Target Qty"     ],

    "CameraOpenError":[ "Camera Open Error !!! \nPlease Check Camera",
                        "相機開啟錯誤!!!\n 請確認相機",
                        "摄像头开启错误!!!\n 请确认摄像头",
                        "Camera Open Error !!! \nPlease Check Camera"
                        ],

    "EditNoSync"     :[ "Edit and Timeline No SYNC\n Needs Sync then Editable",
                        "表格與表格微调不一致 \n需要同步後才可修改",
                        "编辑表格和表格微调不同步 \n需要同步后才可修改",
                        "Edit and Timeline No SYNC \n Needs Sync then Editable"
                        ],

    "GraphTranError"   :[ "LINK Transfer Error",
                        "表格微调轉換錯誤",
                        "时间轴转换错误",
                        "LINK Transfer Error"
                        ],

    "TolerenceOover" :[ "Tolerance must be less than Diameter",
                        "公差必須小於線徑",
                        "公差必须小于线径",
                        "Tolerance must be less than Diameter"
                        ],


    "ActableEmpty"      :[ "Action Table Empty",
                        "空的 Action Table ",
                        "空的 Action Table",
                        "Action Table Empty"
                        ],


    "NeedSelectGraph"   :[ "Please select Graph Bar first",
                        "請先選擇時間軸",
                        "請先选择时间轴",
                        "Please select Graph Bar first"
                        ],

    "NeedSelectAixs"   :[ "Please select Axis first",
                        "請先選擇軸",
                        "請先选择轴",
                        "Please select Axis first"
                        ],

    "CutterNoSet"     :[ "Cutter No Setting",
                        "切刀未設定 ",
                        "切刀未设定",
                        "Cutter No Setting"
                        ],

    "OutOfRange"     :[ "Out Of Range ",
                        "超出範圍 ",
                        "超出范围 ",
                        "Out Of Range "
                        ],
    "BarOverlay"     :[ "Timeline Overlay",
                        "時間軸重疊",
                        "时间轴重叠",
                        "Timeline Overlay"
                        ],
    "OverSelection"   :[ "Choose over",
                        "選擇超過",
                        "选择超过",
                        "Choose over"
                        ],
    "File_No_Found"  :[ "File No Found, Load Default",
                        "文件未找到, 載入初始值",
                        "文件未找到, 载入初始值",
                        "File No Found, Load Default"],

    "File_No_Select"  :[ "File No Selection, Please Select",
                        "檔案未選擇, 請選擇檔案",
                        "档案未选择, 请选择档案",
                        "File No Selection, Please Select"],
    "Photo_No_Select" :[ "Photo No Selection, Please Select",
                        "照片未選擇, 請選擇檔案",
                        "照片未选择, 请选择档案",
                        "Phote No Selection, Please Select"],
    "Unable_Delete_used":[ "Unable to delete currently used file",
                        "正在使用中!!! 無法刪除",
                        "正在使用中!!! 无法删除",
                        "Unable to delete currently used file"],

    "FileDuplicate"  :["File Duplicate!!! ","檔案重複!! "   ,"档案重复!!! "      ,"File Duplicate!!! "],


    "File_Open_Error":[ "File Open Error !!!",
                        "檔案開啟錯誤 !!!",
                        "档案开启错误 !!!",
                        "File Open Error !!!"],
    "File_No_Exist"  :[ "File Non-Existent !!!",
                        "文件不存在 !!!",
                        "文件不存在 !!!",
                        "File Non-Existent !!!"],

    "File_ExistSelOther"  :[ "File Existent !!! Please select other",
                        "文件已存在 !!! 請選擇其他",
                        "文件已存在 !!! 请选择其他",
                        "File Existent !!! Please select other"],

    "File_Overwrite"  :[ "File Existent !!! Overwrite File",
                        "文件已存在 !!! 覆蓋文件",
                        "文件已存在 !!! 覆盖文件",
                        "File Existent !!! Overwrite File"],

    "Connection_Fail":[ "Connection Fail",
                        "連線異常",
                        "连线异常",
                        "Connection Fail"],
    "AnyKeyExit"     :[ "Any Key Exit",
                        "任何鍵離開",
                        "任何键离开",
                        "Any Key Exit"],
    "G8_Error"      :[  "Loop Setting Error",
                        "迴圈設定值錯誤",
                        "循环设定值错误",
                        "Loop Setting Error"],
    "USB_NotFound"      :[  "USB Disk Open Error",
                        "USB磁碟讀取錯誤",
                        "USB磁碟读取错误",
                        "USB Disk Open Error"],
    "PROG_ZOFF_ERR"     :["Above Z-Axis have a program,but been off",
                        "Z軸以上有輸入程式,卻被關閉\n請使用測試模式",
                        "Z轴以上有输入程式,却被关闭\n请使用测试模式",
                        "Above Z-Axis have a program,but been off"],
    "Not_found_G0"     :["Please enter G0",
                        "請輸入程式結束",
                        "请输入程式结束",
                        "Please enter G0"],
    "N"     :["Please enter G0",
                        "請輸入程式結束",
                        "请输入程式结束",
                        "Please enter G0"],
    "FixedPWR"         :["Fixed Power. Can't adjusted!! \n Need switch Power Mode",
                        "固定 1x1 倍率,無法調整!! \n需更換倍率模式",
                        "固定 1x1 倍率,无法调整!! \n需更换倍率模式",
                        "Fixed Power. Can't adjusted!! \n Need switch Power Mode"],
    "Nofound_G9File"   :["No Found Program Tool No!! \n Please check Program Tool list",
                        "工具程式未發現!!\n請確認工具程式庫",
                        "工具程式未发现!!\n请确认工具程式库",
                        "No Found Program Tool No!! \n Please check Program Tool list"],
    "Warning"     :["Warn",
                        "警告",
                        "警告",
                        "Warn"],
                        
    "ConfirmUpdateMsg"     :["Are you sure you want to use the following file to perform the update?",
                        "確定要使用如下檔案執行更新嗎 ?",
                        "确定要使用如下档案执行更新吗 ?",
                        "Are you sure you want to use the following file to perform the update?"],                       

}

ArrErrorMessageBox = { 
        0x01:   ["Motor Wire drop",
                "軸 馬 達 線 掉 了 ",
                "轴 马 达 线 掉 了",
                "Motor Wire drop"],
        0x02:   ["Return to origin failed",
                "軸 回 原 點 失 敗",
                "轴 回 原 点 失 败",
                "Return to origin failed"],
        0x03:   ["Jam !",#滑座x
                "動 作 錯 誤 !",
                "动 作 错 误 !",
                "Jam !"],
        0x04:   ["Test OK !",#滑座x
                "測 試 正 常 !",
                "测 试 正 常 !",
                "Test OK !"],
        0x05:   [" Fail\n START/TEST/STEP----Continue produce\nRESET------Return To Edit Screen",#探針
                " 失 誤\n啟 動/測 試/單 步 鍵----繼 續 生 產\n重 置 鍵---------回 到 編 輯 畫 面",
                " 失 误\n启 动/测 试/单 步 键----继 续 生 产\n重 置 键---------回 到 编 辑 画 面",
                " Fail\n START/TEST/STEP----Continue produce\nRESET------Return To Edit Screen"],
        0x06:   ["Test OK !",#探針
                "測 試 正 常",
                "测 试 正 常",
                "Test OK !"],
        0x07:   [" Oil System Failure ",
                "供 油 系 統 錯 誤",
                "供 油 系 统 错 误",
                "PROBLEMA SISTEMA OLIO"],
        0x08:   [" Ext. Device Failure ",
                "線 架 設 備 錯 誤",
                "线 架 设 备 错 误",
                " PROBLEMA SISTEMA ESTERNO "],
        0x09:   [" External Encoder Error ...",
                "外 接 解 碼 器 錯 誤",
                "外 接 解 码 器 错 误",
                " External Encoder Error ..."],
        0x0a:   ["Servo Failure !",
                "伺 服 失 敗!",
                "伺 服 失 败!",
                "Servo Failure !"],
        0x0b:   ["Servo Cutter Failure !",
                "伺 服 切 刀 失 敗",
                "伺 服 切 刀 失 败",
                "Servo Cutter Failure !"],
        0x0c:   [" Over SLide Limit Failure !\n\n RESET------Return To Edit Screen",
                "超 過 伺 服 滑 座 極 限 失 敗 !\n\n 重 置 鍵---------回 到 編 輯 畫 面",
                "超 过 伺 服 滑 座 极 限 失 败 !\n\n 重 置 键---------回 到 编 辑 画 面",
                " Over SLide Limit Failure !\n\n RESET------Return To Edit Screen"],
        0x0d:   [" Over software Limit!",
                "超 過 軟 體 極 限!",
                "超 过 软 体 极 限!",
                " Over software Limit!"],
        0x0e:   ["Go Home ...",
                "回 原 點 中.....",
                "回 原 点 中.....",
                "TORNA HOME ... "],
        0x0f:   [" Door Error ",
                "安 全 門 錯 誤",
                "安 全 门 错 误",
                " Door Error "],
        0x10:   [" Go Virtual Home ... ",
                "移 到 虛 擬 原 點 中 ...",
                "移 到 虚 拟 原 点 中 ...",
                "TORNA Virtual HOME ... "],
        0x11:   ["Test Knob not at Zero ",
                "測 試 旋 鈕 沒 有 關 成 零",
                "测 试 旋 钮 没 有 关 成 零",
                "Test Knob not at Zero "],
        0x12:   ["MPG Is Not Detected!!!",
                "未 偵 測 到 手 輪",
                "未 侦 测 到 手 轮",
                "MPG Is Not Detected!!!"],
        0x13:   ["Reach Miss No !",
                "超 過 失 誤 量 !",
                "超 过 失 误 量 !",
                "Reach Miss No !"],
        0x14:   [" Reach QTY No !",
                "超 過 生 產 量 !",
                "超 过 生 产 量 !",
                " Reach QTY No !"],
        0x15:   ["Press -A or +A Make ROTW-Axis Go Home !",
                "按 -A 或 +A 導 引 翻 線 回 原 點!",
                "按 -A 或 +A 导 引 翻 线 回 原 点!",
                "Press -A or +A Make ROTW-Axis Go Home !"],
        0x16:   ["Automatic Go Home ....",
                "自 動 回 原 點 中.....",
                "自 动 回 原 点 中.....",
                "Automatic Go Home ...."],
        # 0x17:   ["USB Disk Not Exist",
        #         "USB磁碟不存在",
        #         "USB磁碟不存在",
        #         "USB Disk Not Exist"],
        0x17:   ["New Function\n*** Hook-axis is ON ***\n can auto execution",
                "新功能\n***夾耳已打開***\n具有自動執行功能",
                "新功能\n***夹耳已打开***\n具有自动执行功能",
                "New Function\n*** Hook-axis is ON ***\n can auto execution"],
        # 0x18:   ["Motor Wire drop",
        #         "軸馬達線掉了",
        #         "轴马达线掉了",
        #         "Motor Wire drop"],
        # 0x19:   ["Motor Wire drop",
        #         "軸馬達線掉了",
        #         "轴马达线掉了",
        #         "Motor Wire drop"],
        # 0x1a:   ["Motor Wire drop",
        #         "軸馬達線掉了",
        #         "轴马达线掉了",
        #         "Motor Wire drop"],
        # 0x1b:   ["Motor Wire drop",
        #         "軸馬達線掉了",
        #         "轴马达线掉了",
        #         "Motor Wire drop"],
        0xA1:   ["Serial Encoder Internal Error 1",
                "序列編碼器內部異常1",
                "串行编码器内部异常1",
                "Serial Encoder Internal Error 1"],

        0xD1:   ["Over Position deviation",
                "位置偏差過大",
                "位置偏差过大",
                "Over Position deviation"],

}


# Display                0: English, 1: 繁體中文, 2:簡體中文, 3: 義大利文
ArrComment = {
    "MotorName"     :[ "[MOTOR NAME] Manually enter the motor name - letters A~Z or numbers 0~9. Double-click to enter other text input (Space key back to default)",
                       "[馬達名稱] 馬達名稱手動輸入 A~Z 字母, 0~9 數字, 連按兩下進入其他文字輸入模式 (空白鍵回復初始)",
                       "[马达名称] 马达名称手动输入 A~Z 字母, 0~9 数字, 连按两下进入其他文字输入模式 (空白键回复初始)",
                       "[MOTOR NAME] Manually enter the motor name - letters A~Z or numbers 0~9. Double-click to enter other text input. (Space key back to default)"
                        ],
    "Unit"          :[  "[Unit] SETP, ANGEL, mm , CIRCLE",
                        "[單位] 格数, 角度, mm, 圈数",
                        "[单位] 格數, 角度, mm, 圈數",
                        "[Unit] SETP, ANGEL, mm , CIRCLE"],
    "MotorType"     :[  "[Motor Type] Set according to the motor type： 0-SANYO, 1-Panasonic, 2-Delta Motor.",
                        "[馬達型態] 馬達廠牌設定：0-山洋、1-松下、2-台達馬達",
                        "[马达型态] 马达厂牌设定：0-山洋、1-松下、2-台达马达",
                        "[Motor Type] Set according to the motor type： 0-SANYO, 1-Panasonic, 2-Delta Motor."],
    "MotorSpeed"    :[  "[Motor Speed] Motor speed setting",
                        "[馬達速度] 馬達速度調整 ",
                        "[马达速度] 马达速度调整",
                        "[Motor Speed] Motor speed setting"],
    "MotorStep"     :[  "[MOTOR STEP SETTING] Physical Motor Step setting (Space key back to default)",   
                        "[馬達格數設定] 實際馬達格數設定 (空白鍵回復初始)",
                        "[马达格数设定] 实际马达格数设定 (空白键回复初始)",
                        "[MOTOR STEP SETTING] Physical Motor Step setting (Space key back to default)"] ,
    "ZRTPosition"   :[  "[Origin Position] Set the absolute value motor origin position",
                        "[原點位置] 設定絕對值馬達原點位置。",
                        "[原点位置] 设定绝对值马达原点位置。",
                        "[Origin Position] Set the absolute value motor origin position"],
    "MotorLogicalPosition":[    "[MOTOR LOGICAL STEP SETTING] Logical Motor step Setup ",   
                                "[馬達邏輯格數設定] 馬達邏輯格數設定",
                                "[马达逻辑格数设定] 马达逻辑格数设定",
                                "[MOTOR LOGICAL STEP SETTING] Logical Motor step Setup"],
    "MotorFunction" :[  "[Motor function] 0-Cam, 1-Feeding, 2-Rotating, 3-Turning, 4-Reeling, 5-Cutter, 6-Clamping, 7-Sliding, 8-Scobing (trimming, required Matching parameters), 9-Fold, 10-Shift.",
                        "[馬達功能] 0-凸輪、1-送料、2-轉芯、3-翻線、4-捲取、5-切刀、6-夾耳、7-滑座、8-翻線(修整，須配合參數)，9-折角，10-平移。",
                        "[马达功能] 0-凸轮、1-送料、2-转芯、3-翻线、4-卷取、5-切刀、6-夹耳、7-滑座、8-翻线(修整，须配合参数)，9-折角，10-平移。",
                        "[Motor function] 0-Cam, 1-Feeding, 2-Rotating, 3-Turning, 4-Reeling, 5-Cutter, 6-Clamping, 7-Sliding, 8-Scobing (trimming, required Matching parameters), 9-Fold, 10-Shift."],
    "ZRTOrder"      :[  "[Origin sequence] The running direction and sequence of returning to the origin. The smaller number returns to the origin first, and the same number returns to the origin at the same time.",
                        "[原點順序] 執行回原點的運轉方向及先後順序, 數字小的先回原點，數字一樣同時回原點。",
                        "[原点顺序] 执行回原点的运转方向及先后顺序, 数字小的先回原点，数字一样同时回原点。",
                        "[Origin sequence] The running direction and sequence of returning to the origin. The smaller number returns to the origin first, and the same number returns to the origin at the same time."],
    "ZRTSpeed"      :[  "[Origin Speed] Running speed for returning to origin",
                        "[原點速度] 執行回原點的運轉速度。",
                        "[原点速度] 执行回原点的运转速度。",
                        "[Origin Speed] Running speed for returning to origin"],

    "PNFunction"      :["[PN Type] Set the motor to reach the Max speed type (S-Type,T Type)",
                        "[加减速型式] 設定馬達從 0 到達最高速時間型式(S-Type,T Type)",
                        "[加减速型式] 设定马达从 0 到达最高速时间型式(S-Type,T Type)",
                        "[ACC and DeACC] Set the motor to reach the Max speed type (S-Type,T Type)"],

    "PNSpeed"       :[  "[ACC and DeACC] Set the motor to reach the Max speed from 0 (unit: ms)",
                        "[加减速] 設定馬達從 0 到達最高速時間(單位ms)",
                        "[加减速] 设定马达从 0 到达最高速时间(单位ms)",
                        "[ACC and DeACC] Set the motor to reach the Max speed from 0 (unit: ms)"],
    "UnitExchange"  :[  "[Unit-Conversion] 1mm relative motor step",
                        "[單位換算] 1mm 相對馬達格數",
                        "[单位换算] 1mm 相对马达格数",
                        "[Unit-Conversion] 1mm relative motor step"],
    "MaxLimit"      :[  "[Max Limit] Max distance each axis can move, check when editing the program and manually",
                        "[最大極限] 各軸往正方向能移動的最大距離，編輯程式及手動時檢查。",
                        "[最大极限] 各轴往正方向能移动的最大距离，编辑程式及手动时检查。",
                        "[Max Limit] Max distance each axis can move, check when editing the program and manually"],
    "MinLimit"      :[  "[Min Limit] Min distance each axis can move, check when editing the program and manually",
                        "[最小極限] 各軸往正方向能移動的最大距離，編輯程式及手動時檢查。",
                        "[最小极限] 各轴往正方向能移动的最大距离，编辑程式及手动时检查。",
                        "[Min Limit] Min distance each axis can move, check when editing the program and manually"],
    "Gear0"         :[  "[Gear Ratio Numerator] Default = 1, Absolute motor gear ratio numerator (Gear ratio = Gear Ratio-numerator/Gear ratio-Denominator)",
                        "[齒輪比 分子] 預設為1，絕對值馬達齒輪比 分子 (齒輪比 = 齒輪比分子/齒輪比分母)。",
                        "[齿轮比 分子] 预设为1，绝对值马达比 分子。 (齿轮比 = 齿轮比分子/齿轮比分母)",
                        "[Gear Ratio Numerator] Default = 1, Absolute motor gear ratio numerator (Gear ratio = Gear Ratio-numerator/Gear ratio-Denominator)"],
    "Gear1"         :[  "[Gear Ratio Denominator] Default = 1, Absolute motor gear ratio denumerator (Gear ratio = Gear Ratio-numerator/Gear ratio-Denominator)",
                        "[齒輪比 分母] 預設為1，絕對值馬達齒輪比 分母 (齒輪比 = 齒輪比分子/齒輪比分母)。",
                        "[齿轮比 分母] 预设为1，绝对值马达比 分母 (齿轮比 = 齿轮比分子/齿轮比分母)。",
                        "[Gear Ratio Denominator] Default = 1, Absolute motor gear ratio denumerator (Gear ratio = Gear Ratio-numerator/Gear ratio-Denominator)"],

    "ZRTMode"       :[  "[Origin Mode]",
                        "[原點模式] 0-直接、1-間接、2-立即、3-轉線；模式設定與馬達接線方式有關，詳細內容請參考說明檔。",
                        "[原点模式] 0-直接、1-间接、2-立即、3-转线；模式设定与马达接线方式有关，详细内容请参考说明档。",
                        "[Origin Mode]"],
    "ZRTNew"        :[  "[New Origin]",
                        "[新設原點] 回原點後再偏移的格數值，+/-表示偏移的方向。",
                        "[新设原点] 回原点后再偏移的格数值，+/-表示偏移的方向。",
                        "[New Origin]"],
    "ZRTMapping"    :[  "[Origin Mapping]",
                        "[原點對應] 適用於原點模式為 1-間接，2-立即：原點IO信號對應。",
                        "[原点对应] 适用于原点模式为 1-间接，2-立即：原点IO信号对应。",
                        "[Origin Mapping]"],
    "FeedSignal"    :[  "[Signal Report ",
                        "[回報信號] 參數設定 0 時：馬達線未接會回報錯誤；設定 1 時：馬達線未接不會回到錯誤，詳細內容請參考說明檔。",
                        "[回报信号] 参数设定 0 时：马达线未接会回报错误；设定 1 时：马达线未接不会回到错误，详细内容请参考说明档。",
                        "[Signal Report "],
    "Language"      :[  "[Language] 0-English, 1-Traditional Chinese, 2-Simplified Chinese",    #, 3-Italian
                        "[語言設定] 0-英文、1-繁體中文、2-簡體中文。",  # 、3-義大利文
                        "[语言设定] 0-英文、1-繁体中文、2-简体中文。",  # 、3-义大利文
                        "[Language] 0-English, 1-Traditional Chinese, 2-Simplified Chinese"],   # , 3-Italian
    "Model"         :[  "[Machine model] Set according to the customer's machine model",
                        "[機器型號] 依客戶機器型號設定",
                        "[机器型号] 依客户机器型号设定",
                        "[Machine model] Set according to the customer's machine model"],
    "Y_Encoder"     :[  "[Y Encoder]",
                        "[Y編碼器]",
                        "[Y编码器]",
                        "[Y Encoder"],
    "SafeDoor"      :[  "[Safety door] When safety door is installed, the opening function can be selected; V: Open",
                        "[安全門] 有加裝安全門時，可選擇開啟功能；V 開啟。",
                        "[安全门] 有加装安全门时，可选择开启功能；V-开启。",
                        "[Safety door] When safety door is installed, the opening function can be selected; V: Open"],
    "SafeEquip"     :[  "[Safety Equipment]",
                        "[安全裝置]", 
                        "[安全装置]",
                        "[Safety Equipment]"],
    "Alarm"         :[  "[Alarm] When machine sends out an error message, turn off the output light as a warning; 0-, 1-on, IO point is (B2), only applicable to SW v3.52 and later versions",
                        "[警示燈] 機台發生錯誤訊息時，以黃燈閃爍作為警示；0-關閉、1-開啟，IO輸出點為(B2)，僅適用於軟體v3.52以後版本。",
                        "【提醒】机台发出错误消息时，以关闭输出灯作为警示；0-、1-开启，IO点为（B2），仅适用于软体v3.52以后版本。",
                        "[Alarm] When machine sends out an error message, turn off the output light as a warning; 0-, 1-on, IO point is (B2), only applicable to SW v3.52 and later versions"],
    "CutDist"       :[  "[Cutter distance]",
                        "[切刀距離] 伺服切刀固定來回的移動距離，最大值設限15,000格，修改此參數系統會自動將[切刀距離]填入切刀軸[最大極限]，當作軟體極限設定。",
                        "[切刀距离] 伺服切刀固定来回的移动距离，最大值设限15,000格，修改此参数系统会自动将[切刀距离]填入切刀轴[最大极限]，当作软体极限设定。",
                        "[Cutter distance] "],
    "SpeedMode"     :[  "[Speed Ratio Mode]",
                        "[速率模式] 0-超速率(盡量使X軸保持生產速率，其他軸可能超過生產速率)、1-均速率(各軸不超過生產速率)、2-自(自各軸生產速率)。",
                        "[速率模式] 0-超速率(尽量使X轴保持生产速率，其他轴可能超过生产速率)、1-均速率(各轴不超过生产速率)、2-自(自各轴生产速率)。",
                        "[Speed Ratio Mode]"],
    "SPDMode"       :[  "[SPD mode] 0-SPD can input 2 digits, 1-SPD can input 3 digits, the lowest digit represents the number after the decimal",
                        "[SPD 模式] 0-SPD可輸入2位數、1-SPD可輸入3位數，最低位代表小數點後的數字。",
                        "[SPD 模式] 0-SPD可输入2个、1-SPD可输入3个数字后，最低位代表小数的数字。",
                        "[SPD mode] 0-SPD can input 2 digits, 1-SPD can input 3 digits, the lowest digit represents the number after the decimal"],
    "ZRTCNT"        :[  "[Origin Coil Number]",
                        "[原點圈數] 由密碼輸入 5217，設定絕對值馬達原點位置。",
                        "[原点圈数] 由密码输入 5217，设定绝对值马达原点位置。",
                        "[Origin Coil Number]"],
    "AxisMapping"   :[  "[Axis Mapping] Relative position of motor installation",
                        "[軸對應] 馬達安裝對應位置。",
                        "[轴对应] 马达安装相对位置。",
                        "[Axis Mapping] Relative position of motor installation"],

    "Mumer"         :[  "[Division numerator] ",
                        "[分周分子] 預設為1,000，調整驅動器回授信號分周比。",
                        "[分周分子] 预设为1,000，调整驱动器回授信号分周比。",
                        "[Division numerator]"],
    "Demon"         :[  "[Division denominator] ",
                        "[分周分母] 預設為1,000，調整驅動器回授信號分周比。",
                        "[分周分子] 预设为1,000，调整驱动器回授信号分周比。",
                        "[Division denominator]"],
    "ABReverse"     :[  "[A/B Reverse]",
                        "[A/B 反向] 設定驅動器回授信號是否反向；0-不反向、1-反向。",
                        "[A/B 反向] 设置驱动器回授信号是否反向；0-不反向、1-反向。",
                        "[A/B Reverse]"],
    "ZRTSignal"     :[  "[Origin signal]",
                        "[原點信號] 預設為 1- High，馬達無安裝 Sensor或有外接Encoder時，若[原點模式]為 0-直接，[原點信號]需視情況調整，(與驅動器設定相關)[New] 2-不參考。",
                        "[原点信号] 预设为 1- High，马达无安装 Sensor或有外接Encoder时，若[原点模式]为 0-直接，[原点信号]需视情况调整，(与驱动器设定相关)[New] 2-不参考。",
                        "[Origin signal]"],
    "FixedCheck"    :[  "[Position check]",
                        "[定位檢查] 使用到定位功能時（常用參數[到定位]設定 1，或是程式有壓紅字），設定幾個週期時間檢查一次（一個週期=100us），視各軸馬達情況調整。",
                        "[定位检查] 使用到定位功能时（常用参数[到定位]设置 1，或是程序有压红字），设置几个周期时间检查一次（一个周期=100us），视各轴马达情况调整。",
                        "[Position check]"],
    "T1DecDist"     :[  "[T1 Distance Reduction]",
                        "[T1 減距離]",
                        "[T1 减距离]",
                        "[T1 Distance Reduction]"],
    "T2DecDist"     :[  "[T2 Distance Reduction]",
                        "[T2 減距離]",
                        "[T2 减距离]",
                        "[T2 Distance Reduction]"],
    "T3DecDist"     :[  "[T3 Distance Reduction]",
                        "[T3 減距離]",
                        "[T3 减距离]",
                        "[T3 Distance Reduction]"],
    "T4DecDist"     :[  "[T4 Distance Reduction]",
                        "[T4 減距離]",
                        "[T4 减距离]",
                        "[T4 Distance Reduction]"],
    "GearSpeed"     :[   "[Handwheel Speed]",
                        "[手輪速度]",
                        "[手轮速度]",
                        "[Handwheel Speed]"],
    "Near"          :[   "[NEAR]",
                        "[接近值]",
                        "[接近值]",
                        "[NEAR]"],

    "WireDist"      :[  "[Feeding gap]",
                        "[送線間隙]",
                        "[送线间隙]",
                        "[Feeding gap]"],
    "LINE"          :[  "[LINE]",
                        "[LINE]",
                        "[LINE]",
                        "[LINE]"],
    "LOGO"          :[  "[LOGO]",
                        "[LOGO]",
                        "[LOGO]",
                        "[LOGO]"],
    "OneProdut"     :[  "[Production Lot]", 
                        "[單一生產]",
                        "[单一生产]",
                        "[Production Lot]"],
    "LockProduct"   :[  "[Production Lock]",
                        "[鎖生產量]",
                        "[锁生产量]",
                        "[Production Lock]"],
    "CoreCalibrate" :[  "[Core Calibration]",
                        "[轉芯校正]",
                        "[转芯校正]",
                        "[Core Calibration]"],
    "WireCalibrate" :[  "[Rewinder Calibration]",
                        "[捲取校正]",
                        "[卷取校正]",
                        "[Rewinder Calibration]"],
    "LOT"           :[  "[LOT]",
                        "[批量]",
                        "[批量]",
                        "[LOT]"], 
    "SimFAST"       :[  "[Fast Simulation]",
                        "[模擬FAST]"
                        "[模拟FAST]"
                        "[Fast Simulation]"],
    "XEncoder"      :[  "[X Encoder]",
                        "[X 編碼器]",
                        "[X 编码器]",
                        "[X Encoder]"],
    "MotorModel"    :[  "[Motor Type]",
                        "[馬達型號]",
                        "[马达型号]",
                        "[Motro Type]"],
    "BoxT"          :[  "[Inch Move T]",
                        "[寸動 T]",
                        "[寸动 T]",
                        "[Inch Move T]"],
    "ProbeDelay"    :[  "[Probe Delay]",
                        "[探針延遲]",
                        "[探针延迟]",
                        "[Probe Delay]"],
    #PARA_SIM Comment
    "ZeroSpeed"     :[  "[Zero Speed]",
                        "[歸零速度]",
                        "[归零速度]",
                        "[Zero Speed]"],
    "Delay"         :[  "[Delay]",
                        "[延遲]",
                        "[延迟]",
                        "[Delay]"],
    "ToPos"         :[  "[Go Position]",
                        "[到定位]",
                        "[到定位]",
                        "[Go Position]"],
    "ZeroGo"        :[  "[Zero Pre-Go]",
                        "[歸零預走]",
                        "[归零预走]",
                        "[[Zero Pre-Go]"],
    "SelfSpeed"     :[  "[Self-Rate]",
                        "[自速率]",
                        "[自速率]",
                        "[Self-Rate]"],
    "BIOSReset"     :[  "[BIOS Reset]",
                        "[BIOS重置]",
                        "[BIOS重置]",
                        "[BIOS Reset]"],
    "ScreenProt"    :[  "[Screen Saver] V: Screen saver function is turned on ",
                        "[螢幕保護] V: 螢幕保護功能開啟",
                        "[萤幕保护] V: 萤幕保护功能开启",
                        "[Screen Saver] V: Screen saver function is turned on"],
    "AutoPower"     :[  "[Auto Power Off] V: Auto Power OFF function  is turned on ",
                        "[自動關電] V: 自動關機功能開啟",
                        "[自动关电] V: 自动关机功能开启",
                        "[Auto Power Off] V: Auto Power OFF function  is turned on"],
    "FoldAngle"     :[  "[Flod Angle]",
                        "[翻線角度]",
                        "[翻线角度]",
                        "Flod Angle]"],
    "WireAcc"       :[  "[Wire Frame ACC]",
                        "[線架加速]",
                        "[线架加速]",
                        "[Wire Frame ACC]"],
    "USBDisk"       :[  "[USB Disk]",
                        "[USB磁碟]",
                        "[USB磁碟]",
                        "[USB Disk]"],
    "SlideLimit"    :[  "[Slide Limit]",
                        "[滑座極限]",
                        "[滑座极限]",
                        "[Slide Limit]"],
    "CylinderRel"   :[  "[Cylinder Release]",
                        "[汽缸解除]",
                        "[汽缸解除]",
                        "[Cylinder Release]"],
    "WireReset"     :[  "[Rewind To Zero]",
                        "[捲取歸零]",
                        "[卷取归零]",
                        "[Rewind To Zero]"],
    "ManX100"       :[  "[Handwheel X100]",
                        "[手輪X100]",
                        "[手轮X100]",
                        "[Handwheel X100]"],
    "WirePause"     :[  "[Feeding Pause]",
                        "[送線暫停]",
                        "[送线暂停]",
                        "[Feeding Pause]"],
    "WireTime"       :[ "[Wire Time]",
                        "[線架時間]",
                        "[线架時間]",
                        "[Wire Time]"],
    "WireMode"      :[  "[Wire Frame Mode]",
                        "[線架模式]",
                        "[线架模式]",
                        "[Wire Frame Mode]"],
    "WorkMode"      :[  "[Work Mode]",
                        "[工作模式] 0-速度、1-速率",
                        "[工作模式] 0-速度、1-速率",
                        "[Work Mode]"],
    "PNAccSW"       :[  "[ACC and DeACC]",
                        "[加減速] 0-使用、1-不使用",
                        "[加減速] 0-使用、1-不使用",
                        "[ACC and DeACC]"],
    "ProbeTime"     :[  "[Probe Time]",
                        "[探針時間]",
                        "[探针时间]",
                        "[Probe Time]"],
    "ProdPWD"       :[  "[Production Password]",
                        "[生產密碼]",
                        "[生产密码]",
                        "[Production Password]"],
    "ProdDelay"     :[  "[Production Delay]",
                        "[生產延遲] 0-使用、1-不使用",
                        "[生产延迟] 0-使用、1-不使用",
                        "[Production Delay]"],
    "XReverse"      :[  "[X-axis Reverse]",
                        "[X軸反向] 0-使用、1-不使用",
                        "[X轴反向] 0-使用、1-不使用",
                        "[X-axis Reverse]"],
    "KeyLock"       :[  "[Keyboard Lock]",
                        "[鍵盤鎖住] 0-使用、1-不使用",
                        "[键盘锁住] 0-使用、1-不使用",
                        "[Keyboard Lock]"],
    "CheckOff"      :[  "[Oil Check Lifted]",
                        "[油檢解除] 0-關閉、1-開啟",
                        "[油检解除] 0-关闭、1-开启",
                        "[Oil Check Lifted]"],



}


class Language():
    def __init__(self, liLanaguageIndex=-1):
        self.liLanaguageIndex = self.getValidateIndex(liLanaguageIndex)

    def getValidateIndex(self, liLanaguageIndex):
        if (liLanaguageIndex == -1 or (liLanaguageIndex < 0 or liLanaguageIndex > 3)):
            liLanaguageIndex = 1
        else:
            liLanaguageIndex = liLanaguageIndex 
        return (liLanaguageIndex)
  
    def GetIndex(self): 
        return (self.liLanaguageIndex)                
  
    def SetIndex(self, liLanaguageIndex): 
        self.liLanaguageIndex = self.getValidateIndex(liLanaguageIndex)        
        
    def GetText(self, key, liLanaguageIndex=-1):
        if (liLanaguageIndex == -1):
            liLanaguageIndex = self.liLanaguageIndex

        if ArrLanguage.get(key) is None:
                return None
        else:
                return ArrLanguage[key][liLanaguageIndex]
        
    def GetErrorMessage(self, key, liLanaguageIndex=-1):
        return self.GetText(key, liLanaguageIndex)        

    def GetErrorCode(self, key, liLanaguageIndex=-1):
        return self.GetText(key, liLanaguageIndex)        