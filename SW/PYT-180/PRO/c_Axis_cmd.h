#define MAX_SAVE_AXIS_CMD    1000
struct SAVE_AXIS_CMD_BUF{
	BYTE *addr ;
	unsigned long val   ;
	BYTE flag ;
	DWORD loop_times ;
	WORD timer2 ;
} ;
class	AXIS_CMD {
		struct SAVE_AXIS_CMD_BUF  *buf;
		int idx ;
		long no ;
	public:
		bool err_mark;
		int err_cnt ;
		bool err_markPC_CMD ;
		int err_cntPC_CMD ;
		bool err_markINV_PC_CMD ;
		int err_cntINV_PC_CMD ;
		DWORD timer2 ;
		int loop_cnt ;
		BYTE cmd ;
		AXIS_CMD(int no) ;
		void SaveBuf(BYTE *base , unsigned long val,BYTE flag,DWORD loop_times,unsigned timer2) ;
		void SaveFile() ;
		~AXIS_CMD() ;
} ;
EXTERN   AXIS_CMD axis_cmd
#ifdef GLOBAL 
(MAX_SAVE_AXIS_CMD)
#endif 
;
