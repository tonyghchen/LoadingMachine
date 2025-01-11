#define NOSET3701CMD     4
#define NOSAVEKEYBUF  15



struct SET3701CMD{
		BYTE   axis ;
		BYTE   dir ;
		DWORD  ref ;
		DWORD mov ;
		DWORD rmov ;
		DWORD nref ;
		BYTE off_cmd ;
} ;

struct ERR{
	BYTE status[MAX_AXIS] ;
	struct SET3701CMD set3701cmd[NOSET3701CMD] ;
	int idx_set3701cmd ;
	BYTE SaveKeyBuf[NOSAVEKEYBUF] ;
	int idx_SaveKeyBuf ;
} ;




typedef struct
{
	short type;
	COLOR_T main_col;
	COLOR_T black_col, dark_col, middle_col, light_col;
}Frame_t;

typedef struct
{
	unsigned	style;
	short		lx, ly, rx, ry;
	short		title_fcol, title_bcol;
	char far	*title;
	short		icon;
	Frame_t 	frame;
}WinStyle_t;
typedef struct
{
	BYTE key;
	void (*proc)(void);
	WORD avail_mode;
}KeyMap_t;




typedef struct
{
	WORD x, y;
	BYTE type, nibble;
	void *sign, *var;
	BYTE chk_axis, ref_scrn;
	void (*PrevProc)(void);
	void (*PostProc)(void);
	void (*ModyProc)(void);
}CursorData_t;

typedef struct
{
	BYTE		 first;
	CursorData_t **ptr;
}Cursor_t;
struct CHPAT{
	long idx ;
	int width ;
	int height ;
} ;
typedef struct
{
	BYTE	bygcode;
	BYTE	byth, bytd;
	BYTE	byair;
	BYTE	byseq[MAX_PROG_AXIS];
	BYTE	bysign[MAX_PROG_AXIS+1];
	BYTE	align_byte ;	//for align
#if COMPILER== DJ_COMPILER
	uint32	dval[MAX_PROG_AXIS+1+2]  __attribute__ ((packed)) ;// +2為了汽缸畫面
#else	
	uint32	dval[MAX_PROG_AXIS+1+2];  // +2為了汽缸畫面
#endif
	WORD	wspd;
	WORD	wjmp;
}ProgType_t;


typedef struct
{
	BYTE	bygcode;
	BYTE	byth, bytd;
	BYTE	byair;
	BYTE	byseq[MAX_PROG_AXIS];
	BYTE	bysign[MAX_PROG_AXIS+1];
	BYTE	align_byte ;	//for align
#if COMPILER== DJ_COMPILER
	uint32	dval[MAX_PROG_AXIS+1+2]  __attribute__ ((packed)) ;// +2為了汽缸畫面
#else	
	uint32	dval[MAX_PROG_AXIS+1+2];  // +2為了汽缸畫面
#endif
	WORD	wspd;
	WORD	wjmp;
	BYTE	ins0_del1;
}ProgType_RE;	//回復



typedef struct
{
	BYTE LineComment;
	BYTE spare[19] ;
}ProgTypeex_t;

typedef struct
{
	BYTE MarkerColor;
	BYTE Sparement[19];
	
}ProgTypeExlarge_t;


typedef struct
{
	BYTE	cmd;
	BYTE	next;
	DWORD	ref;
	DWORD  idms ;
	SDWORD	mov;
	SDWORD	sdchk_pos;
	
	union
	{
		BYTE	air;
		struct{
			BYTE	touch;
			BYTE	stop_axis ;
		}t ;
		WORD	line;
		WORD	loop_idx;
		WORD	cnt8254;
		SDWORD	dst_pos;
		WORD	Delay ;
	}u;
	struct{
		WORD start ;
		WORD end ;
	}utouch ;
	bool StartWire ;
	bool chk_touch9 ;
	SDWORD break_cnt;
	SDWORD loopmov ;
	DWORD	loopref;
	
	struct{
		WORD sc8254;
		WORD spd;
		WORD speed;
		DWORD	ref;//x
	}spd_th ;

}ActTbl_t;

typedef struct
{
	BYTE	cmd;
	SDWORD	chk_pos;
	BYTE    dir ;
	union
	{
		BYTE	air;
		struct{
			BYTE	touch;
			BYTE	stop_axis ;
		}t ;
	}u;
	WORD line ;
	struct{
		WORD start ;
		WORD end ;
	}utouch ;
	int16 offset_line;	
	struct{
		WORD	sc8254;
		WORD spd;
		WORD speed;
		DWORD	ref;//x
	}spd_th ;
}AirTbl_t;

struct CP{
	BYTE   cmd ; 
	WORD   chk_pos ;
} ;
struct AUTO_HOOK {
	BYTE byaxis ;
	BYTE byline ;
	WORD wstartx ;
	WORD wendx ;
	WORD wlpos ;
	WORD wlastlines;
	WORD widx ;
	WORD wlastline ;
	bool bomdyzrt;
	bool boauto_mode ;
} ;
struct G9_STRUCT {
	WORD  startl,endl ;
	SDWORD  incy ;
} ;
struct INDEX_STRUCT {
	WORD  loc_x ;
	WORD  start_x ;
	WORD x,y ;
	BYTE Content[16][26] ;
	BYTE fileno ;
} ;
struct STOP_SPIN{
	bool flag ;
	BYTE axis ;
	WORD wlast_line ;
} ;
