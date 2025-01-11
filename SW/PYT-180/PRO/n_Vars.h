//2011_12------新達新增功能，Gcod標記時，送線暫停(開||關)
EXTERN bool PAUSE_Y;		//送線暫停用(align_byte&0x80)
EXTERN int cnt;
//2011_12
EXTERN  int	LoopStar_idx;						//用於RunAutoActTbl，作為註記LOOP_START的idx旗標用

EXTERN  bool ReMake_flag;

//2012_07讀KEY版本日期---------------
EXTERN  bool ReadKeyDate_flag;
EXTERN  uint8 ReadKeyDate_val[3];

EXTERN bool ChkActtblEnd;		//送線暫停用(align_byte&0x80)
EXTERN int RecIdx,ActId;
EXTERN  uint8 axis_idx;



