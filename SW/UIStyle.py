# ---------------------------------------------------------
# Scroll Bar Style 
ScrollHBarSize = """
    QScrollBar:horizontal {
        height: 28px;
    }
"""
ScrollVBarSize = """
    QScrollBar:vertical {
        width: 28px;
    }
"""

ScrollHBarHandle = """
    QScrollBar:horizontal:handle {
        background: #888;  /* 手柄颜色 */
        min-width: 60px;   /* 手柄的最小宽度 */
    }
    QScrollBar:horizontal:add-line, QScrollBar:horizontal:sub-line {
        background: #555;  /* 箭头背景颜色 */
        width: 30px;       /* 箭头的宽度 */
        border: none;      /* 无边框 */
    }
    QScrollBar:horizontal:add-line:hover, QScrollBar:horizontal:sub-line:hover {
        background: white;  /* 鼠标悬停时的箭头背景颜色 */
    }
    QScrollBar:horizontal:corner {
        background: none;  /* 角落背景 */
    }                                            
"""
# -------------------------------------------------------------------------------
#	編輯表格 

TimeWidge_foregroud     = "#FFFFFF"
TimeWidge_OFFforegroud  = "#000000"
TimeWidge_Different     = "#FF0000"

TableWidge_style = """
    QTableWidget {
        background-color: #614F4F; 
        color: #FFFFFF; 
        selection-background-color: rgb(42, 150, 171); 
        selection-color: yellow;
    }
    QHeaderView {
        background-color: #614F4F;  
        color: black;  
    }
    QScrollBar:horizontal {
        height: 30px;
    }
    QScrollBar:horizontal:handle {
        background: #888;  /* 手柄颜色 */
        min-width: 30px;   /* 手柄的最小宽度 */
    }
    QScrollBar:horizontal:add-line, QScrollBar:horizontal:sub-line {
        background: #555;  /* 箭头背景颜色 */
        width: 30px;       /* 箭头的宽度 */
        border: none;      /* 无边框 */
    }
    QScrollBar:horizontal:add-line:hover, QScrollBar:horizontal:sub-line:hover {
        background: white;  /* 鼠标悬停时的箭头背景颜色 */
    }
    QScrollBar:horizontal:corner {
        background: none;  /* 角落背景 */
    }
"""
# -------------------------------------------------------------------------------------
# 生產控制Label Button Style
ProdButtonReleaseStyle = '''
    background-color: #EFFBFD;
    border-radius: 5px;
    border: 1px solid #8c8c8c;
    font-weight: bold;
    font-size: 20pt;
    font-family: "微軟正黑體";
    padding: 10px;
    box-shadow: 5px 5px 10px #666666, -5px -5px 10px #ffffff;
'''
ProdButtonPressStyle = '''
    background-color: rgb(255, 255, 255);
    border-radius: 3px;
    border: 3px groove gray;
    border-style: inset;
    font-weight: bold;
    font-size: 20pt;
    font-family: "微軟正黑體";
    padding: 10px;
    box-shadow: 5px 5px 5px #888888;
'''
# -------------------------------------------------------------------------------------
ButtonPressStyle = 'background-color: rgb(255, 255, 255); border-radius: 3px; border: 3px groove gray; border-style: inset; '
ButtonReleaseStyle = """
    QLabel {
        background-color: #F0F0F0;
        border-radius: 3px;
        border: 1px groove gray;
        border-style: inset;
        color: black; /* 保持文本颜色 */
    }
    QLabel:disabled {
        background-color: #F0F0F0;
        border-radius: 3px;
        border: 1px groove gray;
        border-style: inset;
        color: black; /* 保持文本颜色 */
    }
    QLabel:disabled::pixmap {
        background-color: transparent; /* 图片背景透明 */
        /* border: none;  取消图片边框 */
    }
"""
# -----------------------------------------------------------------
# 自定义颜色主题
ChartStyle = {
    'axes.facecolor': '#614F4F',     # 设置坐标轴的背景颜色
    'axes.edgecolor': '#614F4F',     # 设置坐标轴的边框颜色
    'axes.labelcolor': '#FFFFFF',    # 设置坐标轴标签的颜色
    'text.color': '#FFFFFF',         # 设置文本颜色
    'xtick.color': '#FFFFFF',        # 设置x轴刻度线颜色
    'ytick.color': '#FFFFFF',        # 设置y轴刻度线颜色
    'figure.facecolor': '#614F4F',   # 设置图形背景颜色
    'grid.color': '#CCCCCC',         # 设置网格线颜色
}

# -----------------------------------------------------------------
#   File list
FileSelectStyle = """
    QTableWidget {
        background-color: white; 
        color: rgb(250, 250, 130); 
        selection-background-color: rgb(42, 150, 171); 
        selection-color: blue;
    }
"""

FileNoSelectStyle = """
    QTableWidget {
        background-color: white; 
        color: rgb(0, 0, 0); 
        selection-background-color: rgb(42, 150, 171); 
        selection-color: rgb(250, 250, 130);
    }
"""
