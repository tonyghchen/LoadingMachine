def fONOFFSelect(No):
    switch = {0 : "OFF", 
              1 : "ON",
              }
    return switch.get(No, "OFF")
    
def fIsUseSelect(No):
    switch = {0 : "NonUse", 
              1 : "Use",
              }

    return switch.get(No, "NonUse")


# Display                0: English, 1: 繁體中文, 2:簡體中文, 3: 義大利文
ArrLanguage = { 
    " "             :[' '           ,' '           ,' '            ,' '],
    "No"            :['No'          ,'編號'         ,'编号'         ,'No'],
    "Indirect"      :['Indirect'    ,'間接'         ,'间接'         ,'Indirect'],
    "Direct"        :['Direct'      ,'立即'         ,'立即'         ,'Direct'],
    "LANG_SET"      :["ENG"         ,"繁體"         ,"简体"         ,"Itali"],
    "_PAUSE"        :["-PAUSE-"     ,"-暫停-"       ,"-暂停-"       ,"-PAUSE-"],
    "Select"        :["Select"      ,"選擇"         ,"选择"         ,"Select"],    
    "CANCEL"        :["Cancel"      ,"取消"         ,"取消"         ,"Cancel"],    
    "TIME"          :["TIME"        ,"時間"         ,"时间"         ,"TIME"],

    "RUN"           :["RUN"         ,"執行"         ,"执行"         ,"RUN"],
    "SET"           :["SET"         ,"設定"         ,"设置"         ,"SET"],

    "PARA"          :["PARAMTER"    ,"參數"         ,"参数"         ,"PARAMTER"],
    "Memory"        :["MEMORY SAVE" ,"記憶"       ,"记忆"           ,"MEMORY SAVE"],   
    "NoMemory"      :["NO MEMORY SAVE","不記憶"     ,"不记忆"       ,"NO MEMORY SAVE"],   
    "NoUpdate"      :["NO UPDATE"     ,"不更新"     ,"不更新"       ,"NO UPDTE"],   

    "HELP"          :["HELP"        ,"說明 "        ,"说明 "        ,"HELP"],   
    "FileSave"      :["SAVE"        ,"存檔 "        ,"存档"         ,"SAVE"],
    "FileCopy"      :["COPY"        ,"複製 "        ,"复制"         ,"COPY"],
    "FileOpen"      :["OPEN"        ,"開啟 "        ,"开啟"         ,"OPEN"],

    "OFF"           :["OFF"         ,"關閉"         ,"关闭"         ,"OFF"],
    "ON"            :["ON"          ,"開啟"         ,"开启"         ,"ON"],
    "NonUse"        :["NonUse"      ,"不使用"       ,"不使用"       ,"NonUse"],
    "Use"           :["Use"         ,"使用"         ,"使用"         ,"Use"],
    "Language"      :["Language"    ,"語言設定"     ,"语言设定"     ,"Language"    ],
    "SPACE"         :["SPACE"        ,"空白"         ,"空白"        ,"SPACE"              ],
    "RESET"         :["RESET"       ,"重置"         ,"重置"        ,"RESET"             ],

    "ZERO"          :["RETURN"      ,"歸零"         ,"归零"        ,"RETURN"     ],
    "Home"          :["HOME"        ,"歸位"         ,"归位"        ,"HOME"     ],

    "START"         :["START"       ,"起始"         ,"起始"        ,"START"],
    "Load"          :["Load"        ,"負載"         ,"负载"        ,"Load"],
    "Process"       :["Process"     ,"程序"         ,"程序"        ,"Process" ],
    "g"             :["g"           ,"公克"         ,"公克"        ,"g" ],
    "Error"         :[ "Error!! "   ,"錯誤!! "      ,"错误!! "     ,"Error!! " ],
    "Range"         :[ "Range"      ,"範圍"         ,"范围"         ,"Range" ],
    "AXIS"          :["Axis"        ,"軸"           ,"轴"           ,"Axis"],

    "OutOfRange"     :[ "Out Of Range ",
                        "超出範圍 ",
                        "超出范围 ",
                        "Out Of Range "
                        ],

    "File_Open_Error"   :[ "File Open Error !!!",
                        "檔案開啟錯誤 !!!",
                        "档案开启错误 !!!",
                        "File Open Error !!!"],
    "File_No_Exist"     :[ "File Non-Existent !!!",
                        "文件不存在 !!!",
                        "文件不存在 !!!",
                        "File Non-Existent !!!"],
    "File_ExistSelOther"  :[ "File Existent !!! Please select other",
                        "文件已存在 !!! 請選擇其他",
                        "文件已存在 !!! 请选择其他",
                        "File Existent !!! Please select other"],
    "File_No_Found"  :[ "File No Found, Load Default",
                        "文件未找到, 載入初始值",
                        "文件未找到, 载入初始值",
                        "File No Found, Load Default"],

    "File_Overwrite"    :[ "File Existent !!! Overwrite File",
                        "文件已存在 !!! 覆蓋文件",
                        "文件已存在 !!! 覆盖文件",
                        "File Existent !!! Overwrite File"],

    "USB_NotFound"      :[  "USB Disk Open Error",
                        "USB磁碟讀取錯誤",
                        "USB磁碟读取错误",
                        "USB Disk Open Error"],
    "Warning"           :["Warn",
                        "警告",
                        "警告",
                        "Warn"],
                       
    "ConfirmUpdateMsg"     :["Are you sure you want to use the following file to perform the update?",
                        "確定要使用如下檔案執行更新嗎 ?",
                        "确定要使用如下档案执行更新吗 ?",
                        "Are you sure you want to use the following file to perform the update?"],                       
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