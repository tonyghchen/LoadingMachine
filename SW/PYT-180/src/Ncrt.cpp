#include "header.h"
#include "help.h"
#include "c_pccond.h"

//static BYTE Reset=1;
//static BYTE SendCmdID=0 ;

#if DISP_TOUCHXY
static char *TouchTitle_crt[][2]={
	{"     TH 1", "    Y POS"},
	{"    探針1", "    Y位置"}
};
#else
static char *TouchTitle_crt[][2]={
	{"     TH 1", "     TH 2"},
	{"    探針1", "    探針2"} ,
	{"     TH 1", "     TH 2"},
};
#endif

static char *MissTitle[][2]={
	{"    MISS CNT  ", "    SET MISS  " },
	{"    目前失誤量", "    設定失誤量" } ,
	{"    Q.TA'MANC.", "     SET MANC." },
};
static char *QuanTitle[][2]={
	{"     QTY CNT  ", "     SET QTY  "},
	{"    目前生產量", "    設定生產量"} ,
	{"    Q.TA'PROD ", "    Q.TA'SET  "},
};
static char *ModeTitle[][1]={
	{"    MODE "},
	{"    模式 "},
	{"    MODO "},
};



static char *SafeTitle[][1]={
	{"     SENSOR "},
	{"    安全裝置"} ,
	{"    SENSORE "},
};

static char *SafeMode[][3]={
	{"OFF ", " ON ", "TEST"},
	{"關閉", "啟動", "測試"} ,
	{"OFF ", " ON ", "TEST"},
};

static char *AxisTitle[][1]={
	{"    AXIS "},
	{"     軸  "},
	{"    ASSE "},
};
static char *PosTitle[][1]={
	{"    POS  "},
	{"    位置 "},
	{"    POSIZ"},
};
static char *HandTitle[][1]={
	{"    MPG  "},
	{"    手輪 "},
	{"    MPG  "},
};
static char *ToolBarTitle[][7]={
	{"EDIT", "WORK", "TEST", "STEP", "MDFY", "PARA", "HELP"},
	{"編輯", "生產", "測試", "單步", "修改", "參數", "說明"} ,
	{"EDIT", "LAVORA", "TEST", "PASSO", "MODIFICA", "PARAM", "AIUTO"},
};
////////////////////////////////////////////////////////////////////////////////
//
//自動format 起始點
//

void Gen68KInterrupt (BYTE cmd)
{
	*(BYTE far *)(DP_GEN_INT_ADDR) = cmd;
}

BYTE Clr68KInterrupt (void)
{
	return(*(BYTE far *)(DP_CLR_INT_ADDR));
}


static short SendDPCmd (BYTE cmd)
{
	cmd=cmd ;
	return(1) ;
}

#if USE_DOS_FILE
#include <fcntl.h>
#include <io.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <errno.h>
typedef struct
{
	BYTE	gcode;
	BYTE	th, td;
	BYTE	air;
	BYTE	seq[MAX_PROG_AXIS];
	BYTE	sign[MAX_PROG_AXIS+1];
	BYTE	align_byte ;	//for align
	DWORD	val[MAX_PROG_AXIS+1]   __attribute__ ((packed));  // +2為了汽缸畫面
	WORD	spd;
	WORD	jmp;
}ProgType_t_old;

void ini_axis_zabc()
{
	for(int j=AXIS_Z ; j < MAX_AXIS ; j++){
		
		EPT_IDX(j, CurProgBuf.dval);
		CurProgBuf.dval[j]=PROG_VAL_NULL ;
		Adjust_DWORD(&CurProgBuf.dval[j]) ;
	}
}
void ini_progline()
{
	memset((void *)&CurProgBuf,0,sizeof(ProgType_t)) ;
	CurProgBuf.bygcode=' ' ;
	ini_axis_zabc() ;
	CurProgBuf.wjmp=PROG_VAL_NULL ;
	Adjust_WORD(&CurProgBuf.wjmp) ;
}

void conv_ccyfile(uint8 disk)
{
	//只存到C磁碟,不破壞ccyfile所在的磁碟
	ProgType_t_old CurProgBuf_old ;
	FILE *fp_old, *fp_c;
	fp_old= (disk==0)?FOPEN(CCYFILE_D,"rb"):FOPEN(CCYFILE_C,"rb") ;
	fp_c= FOPEN(HUANG01_C,"wb") ;
	//檢查程式長度為100/500
	int prog_line = (int)(filesize(fp_old)/MAX_FILE_NO /sizeof(ProgType_t_old));
	for(int fileno=0 ; fileno < MAX_FILE_NO ; fileno++){
		for(int l=0 ; l < MAX_PROG_LINE ; l++){
//			unsigned char *p= (unsigned char *)&CurProgBuf_old ;
			if(l < prog_line){
				fread(&CurProgBuf_old,1,sizeof(ProgType_t_old) ,fp_old) ;

				memcpy((void *)&CurProgBuf,(void *)&CurProgBuf_old,sizeof(ProgType_t_old)) ;
				CurProgBuf.wspd=CurProgBuf_old.spd ;
				if(prog_line ==100){
					Adjust_WORD(&CurProgBuf.wspd) ;
					CurProgBuf.wspd=(WORD)dBinToBcd(3,CurProgBuf.wspd) ;
					Adjust_WORD(&CurProgBuf.wspd);
					if(CurProgBuf.bygcode ==0xff){
						CurProgBuf.bygcode=' '  ;
					}
					else if(CurProgBuf.bygcode ==0x0){
						ini_axis_zabc() ;
					}
				}
				
				EPT_IDX(MAX_PROG_AXIS+1, CurProgBuf.dval);
				EPT_IDX(MAX_PROG_AXIS+2, CurProgBuf.dval);
				CurProgBuf.wjmp=CurProgBuf_old.jmp ;
				CurProgBuf.dval[MAX_PROG_AXIS+1]= 0 ;
				CurProgBuf.dval[MAX_PROG_AXIS+2]= 0 ;
			}
			else if(l == prog_line){
				ini_progline() ;
			}
			else{
			}
			fwrite(&CurProgBuf , 1,sizeof(ProgType_t) , fp_c) ;
		}
	}
	FCLOSE(fp_old) ;
	FCLOSE(fp_c) ;
	for(int fileno=0 ; fileno < MAX_FILE_NO ; fileno++){
		ReadFullFile(fileno);
		Convg0ToSpace(FillProgEnd(fileno),fileno);
	}
}
bool chk_ccyfile()
{
	FILE *fp ;
	fp=FOPEN(HUANG01_C,"rb") ;
	if(fp != NULL){
		FCLOSE(fp) ;
		return(true) ;
	}
	fp= FOPEN(CCYFILE_D,"rb") ;
	if(fp != NULL){
		FCLOSE(fp) ;
		DispMsgWin_q(-1, -1, MSG_WIN," 使 用 者 檔 案 轉 換 ..."," User-File Convertion ..."," User-File Convertion ...");
		FORCE_PROC_QUEUE ;
		conv_ccyfile(0) ;
		ClrMsgWin_q();
		return(true) ;
	}
	fp= FOPEN(CCYFILE_C,"rb") ;
	if(fp != NULL){
		FCLOSE(fp) ;
		DispMsgWin_q(-1, -1, MSG_WIN," 使 用 者 檔 案 轉 換 ..."," User-File Convertion ..."," User-File Convertion ...");
		FORCE_PROC_QUEUE ;
		conv_ccyfile(1) ;
		ClrMsgWin_q();
		return(true) ;
	}
	return(false) ;
}
void Gccyfile()
{
	FILE *fp_c, *fp_d ;
	fp_c= FOPEN(HUANG01_C,"wb") ;
	if(DDisk){
		fp_d=FOPEN(HUANG01_D,"wb") ;
	}
	ini_progline() ;
	for(long l=0 ; l < (long)MAX_PROG_LINE*MAX_FILE_NO ; l++){
		fwrite(&CurProgBuf ,1,sizeof(ProgType_t) ,fp_c) ;
		if(DDisk){
			fwrite(&CurProgBuf ,1,sizeof(ProgType_t) ,fp_d) ;
		}
	}
	FCLOSE(fp_c) ;
	if(DDisk){
		FCLOSE(fp_d) ;
	}
}
void Gccyfile(int fileno)
{
	FILE *fp_c, *fp_d ;
	fp_c= FOPEN(HUANG01_C,"rb+") ;
	if(DDisk){
		fp_d=FOPEN(HUANG01_D,"rb+") ;
	}
	long seek_loc= (long)sizeof(ProgType_t)*MAX_PROG_LINE*fileno ;
	fseek(fp_c,seek_loc,SEEK_SET) ;
   	if(DDisk){
       fseek(fp_d ,seek_loc,SEEK_SET) ;
   }
	ini_progline() ;
	for(long l=0 ; l < (long)MAX_PROG_LINE ; l++){
		fwrite(&CurProgBuf ,1,sizeof(ProgType_t) ,fp_c) ;
		if(DDisk){
			fwrite(&CurProgBuf ,1,sizeof(ProgType_t) ,fp_d) ;
		}
	}
	FCLOSE(fp_c) ;
	if(DDisk){
		FCLOSE(fp_d) ;
	}
}
short ReadFileBuf (char *filename ,long off, short size,char *data)
{
	FILE *fh;
	short isok=0;
	int len ,i;

	if((fh=FOPEN(filename,"rb")) != NULL ){
		if( fseek(fh,off,SEEK_SET) ==0){
			if( (len=fread((char *)data,1,size,fh)) != 0 ){
				if(len < size){
					//填入0
					for(i=len ; i < size ; i++){
						*(BYTE *)(data) = 0 ;
					}
				}
				isok = 1;
			}
		}
		FCLOSE(fh);
	}
	if(!isok){
		//填入0
		for(i=0 ; i < size ; i++){
			*(BYTE *)(data) = 0 ;
		}
	}
	return(isok) ;
}

short WriteFileBuf (char *filename ,long off, short size, char *data)
{
	FILE  *fh ;
	short isok=0;  
	int t1 , t2 ;

	if( (fh=FOPEN(filename,"rb+")) != NULL ){
		if( (t1=fseek(fh,off,SEEK_SET)) == 0 ){
      	t1;
			if( (t2=fwrite(data,1,size,fh)) != 0 ){
         	t2;
				isok = 1;
			}
		}
		FCLOSE(fh);
	}
	return(isok) ;
}


short LoadFromFile (long off, WORD size, char *name)
{
	FILE *fh1, *fh_c ;
	short tt, i, isok=0;

	if( (fh1=FOPEN(name,"rb")) != NULL ){
		if( (fh_c =FOPEN(HUANG01_C,"rb+")) != NULL){
			if( fseek(fh_c,off,SEEK_SET) == 0 ){
				for( i=tt=0; i < size/COPY_SIZE; i++ ){
					if( fread(CopyBuf,1,COPY_SIZE,fh1) != 0 ){
						if( fwrite(CopyBuf,1,COPY_SIZE,fh_c) != 0 ){
							continue;
						}
					}
					tt = 1;
					break;
				}
				if( !tt ){
					if( size%COPY_SIZE ){
						if( fread(CopyBuf,1,size%COPY_SIZE,fh1) != 0 ){
							if( fwrite(CopyBuf,1,size%COPY_SIZE,fh_c) != 0 ){
								isok = 1;
							}
						}
					}
					else{
						isok = 1;
					}
				}
			}
			FCLOSE(fh_c);
		}
		FCLOSE(fh1);
	}
	return(isok) ;
}

short SaveToFile (long off, WORD size, char *name)
{
	FILE *fh1, *fh2 ;
	short  tt, i, isok=0;

	if( (fh1=FOPEN(name,"wb")) != NULL ){
		if((fh2=FOPEN(HUANG01_C,"rb")) != NULL ){
			if( fseek(fh2,off,SEEK_SET) == 0 ){
				for( i=tt=0; i < size/COPY_SIZE; i++ ){
					if( fread(CopyBuf,1,COPY_SIZE,fh2) != 0 ){
						if( fwrite(CopyBuf,1,COPY_SIZE,fh1) != 0 ){
							continue;
						}
					}
					tt = 1;
					break;
				}
				if( !tt ){
					if( size%COPY_SIZE ){
						if( fread(CopyBuf,1,size%COPY_SIZE,fh2) != 0 ){
							if( fwrite(CopyBuf,1,size%COPY_SIZE,fh1) != 0 ){
								isok = 1;
							}
						}
					}
					else{
						isok = 1;
					}
				}
			}
			FCLOSE(fh2);
		}
		FCLOSE(fh1);
	}
	return(isok) ;
}
#else
#define SECTOR_SIZE		512
#define DRIVE_NO		1

short LastSector=-1;
char  SectorBuf[SECTOR_SIZE*2];

#if PC_586
#define SEC_IO_INT		0x13
#define SECTOR_NUM		32

short ReadSectors (short drv, short sec, short num, char far *buf){
	unsigned char sec_no, track_no;
	short flg;

	sec_no = (sec%SECTOR_NUM) + 1;
	track_no = sec/SECTOR_NUM + 1;

	_asm{
		cli ;
		pusha ;
		push	ds ;
		push	es ;
		mov		ah, 2 ;
		mov		al, byte ptr num ;
		mov		dh, 0 ;
		mov		dl, byte ptr drv ;
		mov		ch, track_no;
		mov		cl, sec_no;
		les		bx, buf ;
		int		SEC_IO_INT ;
		jc		err ;
		pop		es ;
		pop		ds ;
		popa ;
		mov		flg, 1 ;
		jmp		end1 ;
err:
		pop		es ;
		pop		ds ;
		popa ;
		mov		flg, 0 ;
end1:
		sti ;
	}

	return( flg );
}

short WriteSectors (short drv, short sec, short num, char far *buf){
	unsigned char sec_no, track_no;
	short flg;

	sec_no = (sec%SECTOR_NUM) + 1;
	track_no = sec/SECTOR_NUM + 1;

	_asm{
		cli ;
		pusha ;
		push	ds ;
		push	es ;
		mov		ah, 3 ;
		mov		al, byte ptr num ;
		mov		dh, 0;
		mov		dl, byte ptr drv ;
		mov		ch, track_no;
		mov		cl, sec_no;
		les		bx, buf ;
		int		SEC_IO_INT ;
		jc		err ;
		pop		es ;
		pop		ds ;
		popa ;
		mov		flg, 1 ;
		jmp		end1 ;
err:
		pop		es;
		pop		ds;
		popa;
		mov		flg, 0;
end1:
		sti;
	}

	return( flg );
}
#else
#define SEC_IO_INT		0x83

short ReadSectors (short drv, short sec, short num, char far *buf){
	_asm{
		cli ;
		pusha;
		push	ds;
		push	es;
		mov		ah, 2;
		mov		al, byte ptr num;
		mov		dl, byte ptr drv;
		mov		cx, sec;
		les		bx, buf;
		int		SEC_IO_INT;
		pop		es;
		pop		ds;
		popa;
		sti;
	}

	return( 1 );
}

short WriteSectors (short drv, short sec, short num, char far *buf){
	short flg;

	_asm{
		cli;
		pusha;
		push	ds;
		push	es;
		mov		ah, 3;
		mov		al, byte ptr num;
		mov		dl, byte ptr drv;
		mov		cx, sec;
		les		bx, buf;
		int		SEC_IO_INT;
		jc		err;
		pop		es;
		pop		ds;
		popa;
		mov		flg, 1;
		jmp		end1;
err:
		pop		es;
		pop		ds;
		popa;
		mov		flg, 0;
end1:
		sti;
	}

	return( flg );
}
#endif

void ReadFileBuf (long off, short size){
	short sec, isok=0;

	sec = (short)(off/SECTOR_SIZE);
	if( sec == (short)((off+size-1)/SECTOR_SIZE) ){
		if( sec == LastSector )	isok = 1;
		else					isok = ReadSectors(DRIVE_NO, sec, 1, SectorBuf);
	}
	else{
		if( sec == LastSector )	isok = ReadSectors(DRIVE_NO, sec+1, 1, SectorBuf+SECTOR_SIZE);
		else					isok = ReadSectors(DRIVE_NO, sec, 2, SectorBuf);
	}
	if( isok ){
		memcpy((char *)(DP_TRANS_ADDR+2+8), SectorBuf+(off%SECTOR_SIZE), size);
		LastSector = sec;
	}
	else{
		LastSector = -1;
	}

	*(BYTE *)(DP_TRANS_ADDR+0) = 8+size+1;
	*(BYTE *)(DP_TRANS_ADDR+1) = ++SendCmdID;
	*(BYTE *)(DP_TRANS_ADDR+2) = READ_ACK;
	*(BYTE *)(DP_TRANS_ADDR+3) = (BYTE)isok;
	*(DWORD*)(DP_TRANS_ADDR+4) = off;
	*(WORD *)(DP_TRANS_ADDR+8) = size;
	*(BYTE *)(DP_TRANS_ADDR+2+8+size) = 0;
	SendDPCmd(READ_ACK);
}

void WriteFileBuf (long off, short size, char *data){
	short sec, isok=0;

	sec = (short)(off/SECTOR_SIZE);
	if( sec == (short)((off+size-1)/SECTOR_SIZE) ){
		if( sec == LastSector )	isok = 1;
		else					isok = ReadSectors(DRIVE_NO, sec, 1, SectorBuf);
		if( isok ){
			memcpy(SectorBuf+(off%SECTOR_SIZE), data, size);
			isok = WriteSectors(DRIVE_NO, sec, 1, SectorBuf);
		}
	}
	else{
		if( sec == LastSector )	isok = ReadSectors(DRIVE_NO, sec+1, 1, SectorBuf+SECTOR_SIZE);
		else					isok = ReadSectors(DRIVE_NO, sec, 2, SectorBuf);
		if( isok ){
			memcpy(SectorBuf+(off%SECTOR_SIZE), data, size);
			isok = WriteSectors(DRIVE_NO, sec, 2, SectorBuf);
		}
	}
	if( isok )
		LastSector = sec;
	else
		LastSector = -1;

	*(BYTE *)(DP_TRANS_ADDR+0) = 8+1;
	*(BYTE *)(DP_TRANS_ADDR+1) = ++SendCmdID;
	*(BYTE *)(DP_TRANS_ADDR+2) = WRITE_ACK;
	*(BYTE *)(DP_TRANS_ADDR+3) = (BYTE)isok;
	*(DWORD*)(DP_TRANS_ADDR+4) = off;
	*(WORD *)(DP_TRANS_ADDR+8) = size;
	*(BYTE *)(DP_TRANS_ADDR+10) = 0;
	SendDPCmd(WRITE_ACK);
}

void LoadFromFloppy (long off, short size, short no){
	*(BYTE *)(DP_TRANS_ADDR+0) = 8+1;
	*(BYTE *)(DP_TRANS_ADDR+1) = ++SendCmdID;
	*(BYTE *)(DP_TRANS_ADDR+2) = READ_ACK;
	*(BYTE *)(DP_TRANS_ADDR+3) = 0;
	*(DWORD*)(DP_TRANS_ADDR+4) = off;
	*(WORD *)(DP_TRANS_ADDR+8) = size;
	*(BYTE *)(DP_TRANS_ADDR+2+8) = 0;
	SendDPCmd(READ_ACK);
}

void SaveToFloppy (long off, short size, short no){
	*(BYTE *)(DP_TRANS_ADDR+0) = 8+1;
	*(BYTE *)(DP_TRANS_ADDR+1) = ++SendCmdID;
	*(BYTE *)(DP_TRANS_ADDR+2) = WRITE_ACK;
	*(BYTE *)(DP_TRANS_ADDR+3) = 0;
	*(DWORD*)(DP_TRANS_ADDR+4) = off;
	*(WORD *)(DP_TRANS_ADDR+8) = size;
	*(BYTE *)(DP_TRANS_ADDR+2+8) = 0;
	SendDPCmd(WRITE_ACK);
}
#endif

void PrinterBuf (short len, char *p)
{
	short isok;

	isok = PrnBuf(p, len);

	*(BYTE *)(DP_TRANS_ADDR+0) = 2+1;
	*(BYTE *)(DP_TRANS_ADDR+1) = ++SendCmdID;
	*(BYTE *)(DP_TRANS_ADDR+2) = PRN_ACK;
	*(BYTE *)(DP_TRANS_ADDR+3) = (BYTE)isok;
	*(BYTE *)(DP_TRANS_ADDR+4) = 0;
	SendDPCmd(PRN_ACK);
}

void PrinterChar (char c, short len)
{
	short isok;

	isok = PrnChar(c, len);

	*(BYTE *)(DP_TRANS_ADDR+0) = 2+1;
	*(BYTE *)(DP_TRANS_ADDR+1) = ++SendCmdID;
	*(BYTE *)(DP_TRANS_ADDR+2) = PRN_ACK;
	*(BYTE *)(DP_TRANS_ADDR+3) = (BYTE)isok;
	*(BYTE *)(DP_TRANS_ADDR+4) = 0;
	SendDPCmd(PRN_ACK);
}

void PrinterStr (char *p)
{
	short isok;

	isok = PrnStr(p);

	*(BYTE *)(DP_TRANS_ADDR+0) = 2+1;
	*(BYTE *)(DP_TRANS_ADDR+1) = ++SendCmdID;
	*(BYTE *)(DP_TRANS_ADDR+2) = PRN_ACK;
	*(BYTE *)(DP_TRANS_ADDR+3) = (BYTE)isok;
	*(BYTE *)(DP_TRANS_ADDR+4) = 0;
	SendDPCmd(PRN_ACK);
}

void DispTouchFrame1_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i) ;
	CHK_CHKSUM

	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = TOUCH_TITLE_BCOLOR;

	short lx = TOUCH_LX;
	short ly = TOUCH_LY+i*(ASC_CHAR_H+4);
	DrawCasing(lx, ly, lx+TOUCH_TITLE_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, TOUCH_TITLE_FCOLOR, TOUCH_TITLE_BCOLOR, TouchTitle_crt[idx_language][i]);
	PutIcon(lx+ASC_CHAR_W+2, ly+2, TOUCH_ICON, _GPSET);
	frame.type = 0;



	lx += TOUCH_TITLE_CHARS*ASC_CHAR_W+4;
	DrawCasing(lx, ly, lx+TOUCH_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispTouchFrame_q (void)
{
	for(short  i=0; i < sizeof(TouchTitle_crt[0])/sizeof(TouchTitle_crt[0][0]); i++ ){
		BYTE *dptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE *tptr = dptr ;
		SAVE_VAL(short,i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispTouchFrame1_proc,tptr) ;
	}
}

void DispMissFrame1_proc (void *ptr)
{
	BYTE *dptr = (BYTE *)ptr ;
	GET_VAL(short,i) ;
	CHK_CHKSUM
	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = MISS_TITLE_BCOLOR;

	short lx = MISS_LX;
	short ly = MISS_LY+i*(ASC_CHAR_H+4);
	DrawCasing(lx, ly, lx+MISS_TITLE_CHARS*ASC_CHAR_W+4+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, MISS_TITLE_FCOLOR, MISS_TITLE_BCOLOR, MissTitle[idx_language][i]);
	farfree(ptr) ;
}
void DispMissFrame2_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i) ;
	CHK_CHKSUM
	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = 0;
	frame.main_col = MISS_TITLE_BCOLOR;

	short lx = MISS_LX;
	short ly = MISS_LY+i*(ASC_CHAR_H+4);

	PutIcon(lx+ASC_CHAR_W+2, ly+2, ERROR_ICON, _GPSET);

	lx += MISS_TITLE_CHARS*ASC_CHAR_W+4+4;
	ly = MISS_LY+i*(ASC_CHAR_H+4) ;
	DrawCasing(lx, ly, lx+MISS_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispMissFrame_q (void)
{
	for( short i=0; i < sizeof(MissTitle[0])/sizeof(MissTitle[0][0]); i++ ){
		BYTE *dptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE *tptr = dptr ;
		SAVE_VAL(short ,i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispMissFrame1_proc,tptr) ;

		dptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		tptr=dptr ;
		SAVE_VAL(short ,i) ;
		SAVE_CHKSUM_NO_ALLOC
		FILL_PROC_QUEUE(DispMissFrame2_proc,tptr) ;
	}
}
void DispQuanFrame1_proc (void * ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i) ;
	CHK_CHKSUM

	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = QUAN_TITLE_BCOLOR;

	short lx = QUAN_LX;
	short ly = QUAN_LY+i*(ASC_CHAR_H+4) ;
	DrawCasing(lx, ly, lx+QUAN_TITLE_CHARS*ASC_CHAR_W+4+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, QUAN_TITLE_FCOLOR, QUAN_TITLE_BCOLOR, QuanTitle[idx_language][i]);

	farfree(ptr) ;
}
void DispQuanFrame2_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i) ;
	CHK_CHKSUM
	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = 0;
	frame.main_col = QUAN_TITLE_BCOLOR;

	short lx = QUAN_LX;
	short ly = QUAN_LY+i*(ASC_CHAR_H+4) ;
	PutIcon(lx+ASC_CHAR_W+2, ly+2, QUAN_ICON, _GPSET);


	lx += QUAN_TITLE_CHARS*ASC_CHAR_W+4+4;
	ly = QUAN_LY+i*(ASC_CHAR_H+4);
	DrawCasing(lx, ly, lx+QUAN_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);

	farfree(ptr) ;
}
void DispQuanFrame_q (void)
{
	for( short i=0; i < sizeof(MissTitle[0])/sizeof(QuanTitle[0][0]); i++ ){
		BYTE *dptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE *tptr = dptr ;
		SAVE_VAL(short, i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispQuanFrame1_proc,tptr) ;

		dptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		tptr = dptr ;
		SAVE_VAL(short,i) ;
		SAVE_CHKSUM_NO_ALLOC
		FILL_PROC_QUEUE(DispQuanFrame2_proc,tptr) ;
	}

}
void DispModeFrame_proc (void* dptr)
{
	dptr=dptr ;
	short	lx, ly;
	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col =MODE_TITLE_BCOLOR;

	lx = MODE_LX;
	ly = MODE_LY;
	DrawCasing(lx, ly, lx+MODE_TITLE_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, MODE_TITLE_FCOLOR, MODE_TITLE_BCOLOR, ModeTitle[idx_language][0]);
	PutIcon(lx+ASC_CHAR_W+2, ly+2, MODE_ICON, _GPSET);

	frame.type = 0;

	lx += MODE_TITLE_CHARS*ASC_CHAR_W + 4;
	DrawCasing(lx, ly, lx+MODE_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
}
void DispModeFrame_q (void)
{
	FILL_PROC_QUEUE(DispModeFrame_proc,NULL) ;
}
void DispReturn_proc (void* dptr)
{
	dptr=dptr ;
	short	lx, ly;
	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = 0;
	frame.main_col =MODE_TITLE_BCOLOR;

	lx = MODE_LX;
	ly = STATUS_BAR_LY;
	DrawCasing(lx, ly-2, lx+MODE_TITLE_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-3, &frame);
	PutIcon(lx+ASC_CHAR_W+22, ly, MODE_ICON, _GPSET);
	if(ModyAfNum>=10)	sprintf((char *)pDispBuf,"10");
	else sprintf((char *)pDispBuf,"%d ",ModyAfNum);
	int x=10 ;
	DispStatusBar_q(x,pDispBuf) ;
	
	sprintf((char *)pDispBuf,"%d ",ModyBeNum);
	x=57 ;
	DispStatusBar_q(x,pDispBuf);
	
}

void DispTotalY_proc (void* dptr)//顯示送線量
{
	dptr=dptr ;
	short	lx, ly;
	Frame_t frame;
	
	DefaultButtonStyle(&frame);
	frame.type = 0;
	frame.main_col =MODE_TITLE_BCOLOR;
	ly = STATUS_BAR_LY;
	if(MachineStatus.language == 1||MachineStatus.language == 2)sprintf((char *)pDispBuf,"總送線量:%.2f",totalY/100);
	else sprintf((char *)pDispBuf,"Total  Y:%.2f",totalY/100);
	int x=119 ;
	DispStatusBar_q(x,pDispBuf) ;
	
}
void TotalY(void){
	totalY=0;
	int loop_S=0,loop_E=0,loop_Y=0;
	float loop_YTotal=0;
	for(int line=0 ; line < MAX_PROG_LINE ; line++){
		if(ProgBuf[line].bygcode>0&&ProgBuf[line].bygcode<=6){
			if(ProgBuf[line].bygcode==5){
				loop_S=BcdToBin(3,ProgBuf[line].dval[START_X]);
				loop_E=BcdToBin(3,ProgBuf[line].dval[END_X]);
				loop_Y=BcdToBin(4,ProgBuf[line].dval[AXIS_Y]);
				for(int i=loop_S;i<loop_E;i++){
					if(ProgBuf[i].bysign[AXIS_Y]&0x7f)
						loop_YTotal-=BcdToBin(8,ProgBuf[i].dval[AXIS_Y]);
					else
						loop_YTotal+=BcdToBin(8,ProgBuf[i].dval[AXIS_Y]);
				}
					totalY+=loop_Y*loop_YTotal;
			}
			else{
				if(ProgBuf[line].dval[AXIS_Y]!=PROG_VAL_NULL){
					if(ProgBuf[line].bysign[AXIS_Y]&0x7f)
						totalY-=BcdToBin(8,ProgBuf[line].dval[AXIS_Y]);
					else
						totalY+=BcdToBin(8,ProgBuf[line].dval[AXIS_Y]);
				}
			}
		}
		else if(ProgBuf[line].bygcode==0) break;//送線G8送線變0
	}
}
void DispReutrn_q (void)
{	
	FILL_PROC_QUEUE(DispReturn_proc,NULL) ;
}
void DispTotalY_q (void)
{
	FILL_PROC_QUEUE(DispTotalY_proc,NULL) ;
}
void DispSpeedFrame1_proc (void *dptr)
{
	dptr=dptr ;
	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = SPEED_TITLE_BCOLOR;

	short lx = SPEED_LX;
	short ly = SPEED_LY;
	DrawCasing(lx, ly, lx+SPEED_TITLE_CHARS*ASC_CHAR_W+4+4-1, ly+ASC_CHAR_H+4-1, &frame);
	if(MachineStatus.WorkMode==0){
		PrintStringLine_fmt(lx+2, ly+2, SPEED_TITLE_FCOLOR, SPEED_TITLE_BCOLOR, SpeedTitle[idx_language][0]);
	}
	else{
		PrintStringLine_fmt(lx+2, ly+2, SPEED_TITLE_FCOLOR, SPEED_TITLE_BCOLOR, SpeedTitle1[idx_language][0]);
	}
}
void DispSpeedFrame2_proc (void *dptr)
{
	dptr=dptr ;
	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = 0;
	frame.main_col = SPEED_TITLE_BCOLOR;

	short lx = SPEED_LX;
	short ly = SPEED_LY;
	PutIcon(lx+ASC_CHAR_W+2, ly+2, RPM_ICON, _GPSET);

	lx += SPEED_TITLE_CHARS*ASC_CHAR_W + 4+4;
	DrawCasing(lx, ly, lx+SPEED_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
}
void DispSpeedFrame_q (void)
{
	FILL_PROC_QUEUE(DispSpeedFrame1_proc,NULL) ;
	FILL_PROC_QUEUE(DispSpeedFrame2_proc,NULL) ;
}


void DispFileFrame1_proc (void *dptr)
{
	dptr=dptr ;
	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col =FILE_TITLE_BCOLOR;

	short lx = FILE_LX;
	short ly = FILE_LY;
	DrawCasing(lx, ly, lx+FILE_TITLE_CHARS*ASC_CHAR_W+4+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, FILE_TITLE_FCOLOR, FILE_TITLE_BCOLOR, FileTitle[idx_language][0]);
}
void DispFileCommentFrame1_proc (void *dptr)
{
	dptr=dptr ;
	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col =FILE_TITLE_BCOLOR;

	short lx = FILE_COMMENT_LX;
	short ly = FILE_COMMENT_LY-(ASC_CHAR_H+4);
	DrawCasing(lx, ly, lx+16*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, FILE_TITLE_FCOLOR, FILE_TITLE_BCOLOR, FileCommentTitle[idx_language][0]);
	PutIcon(lx+ASC_CHAR_W+2, ly+2, FILE_ICON, _GPSET);
}
void DispFileCommentFrame2_proc (void *dptr)
{
	dptr=dptr ;
	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col =FILE_TITLE_BCOLOR;

	short lx = FILE_COMMENT_LX;
	short ly = FILE_COMMENT_LY;
	DrawCasing(lx, ly, lx+16*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
}


void DispFileFrame2_proc (void *dptr)
{
	dptr=dptr ;
	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.main_col =FILE_TITLE_BCOLOR;
	frame.type = 0;
	short lx = FILE_LX;
	short ly = FILE_LY;

	PutIcon(lx+ASC_CHAR_W+2, ly+2, FILE_ICON, _GPSET);

	lx += FILE_TITLE_CHARS*ASC_CHAR_W + 4+4;
	DrawCasing(lx, ly, lx+FILE_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
}
void DispFileFrame_q (void)
{
	FILL_PROC_QUEUE(DispFileFrame1_proc,NULL) ;
	FILL_PROC_QUEUE(DispFileFrame2_proc,NULL) ;
	FILL_PROC_QUEUE(DispFileCommentFrame1_proc,NULL) ;
	FILL_PROC_QUEUE(DispFileCommentFrame2_proc,NULL) ;
}

void DispSafeSw (short mode)
{
	short	lx, ly;
	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col =SAFE_TITLE_BCOLOR;

	lx = SAFE_LX+8;
	ly = SAFE_LY;
	DrawCasing(lx, ly, lx+SAFE_TOTAL_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	BYTE *dptr= (BYTE *) farmalloc(3*sizeof(short)+LEN_CHKSUM) ;
	BYTE *tptr= dptr ;
	SAVE_VAL(short, lx) ;
	SAVE_VAL(short, ly) ;
	SAVE_VAL(short, mode) ;
	SAVE_CHKSUM
	FILL_PROC_QUEUE(DispSafeSw1_proc, tptr) ;
}
void DispSafeSw1_proc(void *ptr)
{
	BYTE *dptr= (BYTE *) ptr ;
	GET_VAL(short ,lx) ;
	GET_VAL(short ,ly) ;
	GET_VAL(short , mode) ;
	CHK_CHKSUM
	PrintStringLine_fmt(lx+2, ly+2, SAFE_TITLE_FCOLOR, SAFE_TITLE_BCOLOR, SafeTitle[idx_language][0]);
	PrintStringLine_fmt(lx+2+strlen(SafeTitle[0][0])*ASC_CHAR_W, ly+2, SAFE_TITLE_FCOLOR, SAFE_TITLE_BCOLOR, SafeMode[idx_language][mode]);
	PutIcon(lx+ASC_CHAR_W+2, ly+2, SAFE_ICON, _GPSET);
	farfree(ptr) ;
}

char *(*Title_arr[])[1]= { AxisTitle,PosTitle ,ManTitle ,HandTitle} ;
short Title_fclr[]= {AXIS_TITLE_FCOLOR,POS_TITLE_FCOLOR,MAN_TITLE_FCOLOR,HAND_TITLE_FCOLOR} ;
short Title_bclr[]= {AXIS_TITLE_BCOLOR,POS_TITLE_BCOLOR,MAN_TITLE_BCOLOR,HAND_TITLE_BCOLOR} ;
short Title_icon[]= {TOOL_ICON,POS_ICON,MAN_ICON,HAND_ICON} ;

void DispAxisFrame_q (void)
{
	DispAxisPosManHandFrame (0) ;
}


void DispPosFrame_q (void)
{
	DispAxisPosManHandFrame (1) ;
}


void DispManFrame_q (void)
{
	DispAxisPosManHandFrame (2) ;
}
char *keylock_str[]= { 
	"KEY SWAP" ,
	"按鍵切換" , 
	"KEY SWAP" ,
	"KEY LOCK" ,
	"鍵盤鎖住"  ,
	"CHIUDI  " ,
	 } ;
char *BUZZER_str[]= { 
	"W. LIGHT" ,
	"警示燈  " , 
	"W. LIGHT" ,
	"KEY LOCK" ,
	"鍵盤鎖住"  , 
	"CHIUDI  " ,
	} ;

void DispKeyscrn_q(BYTE idx)
{
	BYTE *dptr= (BYTE *) farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
	BYTE *tptr=dptr ;
	SAVE_VAL(short, idx) ;
	SAVE_CHKSUM
	FILL_PROC_QUEUE(DispKeyscrn_proc,tptr) ;
}
void DispKeyscrn_proc(void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short, idx) ;
	CHK_CHKSUM
	
	
#if 0
	//改成顯示訊息框	
	short lx= 500 ;
	short ly = MISS_LY+(ASC_CHAR_H+4) ;
	short lx2=lx+8*ASC_CHAR_W+4-1 ;
	short ly2=ly+ASC_CHAR_H+4-1 ;
	if(idx !=0){
		Frame_t frame;
		DefaultButtonStyle(&frame);
		frame.type = -1;
		frame.main_col = LIGHTRED_USR ;

		DrawCasing(lx, ly, lx2,ly2 , &frame);
		PrintStringLine_fmt(lx+2, ly+2, LIGHTGRAY_USR, LIGHTRED_USR, keylock_str[(idx-1)*3+idx_language]);
	}
	else{
		bar256(lx,ly , lx2+1,ly2+1,WIN_TEXT_BCOLOR) ;
	}
	farfree(ptr) ;
#else 	
	farfree(ptr) ;
	switch (idx){
		case 2:
		case 1:
			INI_DISP_BUF();
			Fill_pDispBuf(	keylock_str[(idx-1)*3+1], keylock_str[(idx-1)*3+0],keylock_str[(idx-1)*3+2]);
			FILL_DISP_BUF(0);
			DispMsgWin_q(-1, -1, WAR_WIN, DispBuf);
			break;
		case 0:
			ClrMsgWin_q();
			break;
	}	
#endif
}
void DispBUZZER_q(BYTE idx)
{
	BYTE *dptr= (BYTE *) farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
	BYTE *tptr=dptr ;
	SAVE_VAL(short, idx) ;
	SAVE_CHKSUM
	FILL_PROC_QUEUE(DispBUZZER_proc,tptr) ;
}
void DispBUZZER_proc(void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short, idx) ;
	CHK_CHKSUM
	
	
	short lx= 500 ;
	short ly = MISS_LY+(ASC_CHAR_H+4)*2 ;
	short lx2=lx+10*ASC_CHAR_W+4-1 ;
	short ly2=ly+ASC_CHAR_H+4-1 ;
	if(idx !=0){
		Frame_t frame;
		DefaultButtonStyle(&frame);
		frame.type = -1;
		frame.main_col = LIGHTRED_USR ;

		DrawCasing(lx, ly, lx2,ly2 , &frame);
		PrintStringLine_fmt(lx+2, ly+2, LIGHTGRAY_USR, LIGHTRED_USR, BUZZER_str[idx_language]);
	}
	else{
		bar256(lx,ly , lx2+1,ly2+1,WIN_TEXT_BCOLOR) ;
	}
	farfree(ptr) ;
}

void DispHandFrame1_proc(void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short, idx) ;
	CHK_CHKSUM

	Frame_t frame;
	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = Title_bclr[idx] ;

	short lx= AXIS_LX ;
	short ly = AXIS_LY+idx*(ASC_CHAR_H+4) ;
	DrawCasing(lx, ly, lx+HAND_TITLE_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, Title_fclr[idx], Title_bclr[idx], Title_arr[idx][idx_language][0]);
	PutIcon(lx+ASC_CHAR_W+2, ly+2, Title_icon[idx], _GPSET);

	farfree(ptr) ;
}
void DispHandFrame2_proc(void *ptr)
{
	BYTE *dptr = (BYTE *)ptr ;
	GET_VAL(short, idx) ;
	GET_VAL(short, start_i) ;
	GET_VAL(short, end_i) ;
	CHK_CHKSUM

	Frame_t frame;
	DefaultButtonStyle(&frame);
	frame.type = 0;
	frame.main_col = Title_bclr[idx] ;

	short lx= AXIS_LX +AXIS_TITLE_CHARS*ASC_CHAR_W + 4+start_i*(HAND_DATA_CHARS*ASC_CHAR_W + 4) ;
	short ly = AXIS_LY+idx*(ASC_CHAR_H+4) ;
	for(short i=start_i; i < end_i; i++ )
	{
		int incx= HAND_DATA_CHARS*ASC_CHAR_W + 4 ;
		if(MachineStatus.p3701[i]){
			DrawCasing(lx, ly, lx+incx-1, ly+ASC_CHAR_H+4-1, &frame);
		}
		lx += incx;
	}

	farfree(ptr) ;
}
void DispHandFrame_q (void)
{
	DispAxisPosManHandFrame (3) ;
}
void DispAxisPosManHandFrame (short idx)
{
	BYTE *dptr= (BYTE *) farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
	BYTE *tptr=dptr ;
	SAVE_VAL(short, idx) ;
	SAVE_CHKSUM
	FILL_PROC_QUEUE(DispHandFrame1_proc,tptr) ;

	dptr= (BYTE *) farmalloc(3*sizeof(short)+LEN_CHKSUM) ;
	tptr=dptr ;
	SAVE_VAL(short, idx) ;
	SAVE_VAL(short, 0) ;
	SAVE_VAL(short, (SysInfo.AxisNo <=3) ? SysInfo.AxisNo: 3) ;
	SAVE_CHKSUM_NO_ALLOC
	FILL_PROC_QUEUE(DispHandFrame2_proc,tptr) ;
	if(SysInfo.AxisNo > 3){
		dptr= (BYTE *) farmalloc(3*sizeof(short)+LEN_CHKSUM) ;
		tptr= dptr ;
		SAVE_VAL(short, idx) ;
		SAVE_VAL(short, 3) ;
		SAVE_VAL(short, SysInfo.AxisNo) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispHandFrame2_proc,tptr) ;
	}
}

void DispToolBar1_proc(void *ptr)
{
	BYTE *dptr=(BYTE *)ptr ;
	GET_VAL(WinStyle_t , tt)
	CHK_CHKSUM
	DrawTextButton(&tt);
	farfree(ptr) ;
} 
void DispToolBar_q (short idx)
{
	short	i, len;
	WinStyle_t ws;

	DefaultButtonStyle(&(ws.frame));
	ws.style		= W_NORMAL;
	ws.lx			= TOOL_BAR_LX;
	ws.ly			= TOOL_BAR_LY;
	ws.rx			= TOOL_BAR_RX;
	ws.ry			= TOOL_BAR_RY;
	DrawWindow_q(&ws);

	ws.style		= W_TITLE+W_ICON;
	ws.title_fcol	= WIN_TEXT_FCOLOR;
	ws.title_bcol	= BRIGHTWHITE_USR;
	ws.lx			= TOOL_BAR_LX + 4;
	ws.rx			= ws.lx;
	ws.ly			= TOOL_BAR_LY + 4;
	ws.ry			= TOOL_BAR_RY - 4;

	for( len=0, i=0; i < (sizeof(ToolBarTitle[0])/sizeof(ToolBarTitle[0][0])); i++ )
	{
		if( i == idx )	ws.frame.type = 1;
		else			ws.frame.type = 0;

		ws.title	 = ToolBarTitle[idx_language][i];
		ws.icon		 = i;
		ws.lx		+= len;
		ws.rx		 = ws.lx + (len=(strlen(ws.title)+6)*ASC_CHAR_W) - 1;
		
		BYTE *dptr= (BYTE *)farmalloc(1*sizeof(WinStyle_t)+LEN_CHKSUM) ;
		BYTE *tptr= dptr ;
		SAVE_VAL(WinStyle_t, ws) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispToolBar1_proc,tptr) ;

		len			+= 2;
	}
}
void DispEditBox_q (void)
{
	WinStyle_t ws;

	DefaultButtonStyle(&(ws.frame));
	ws.frame.main_col	= EDITBOX_MAIN_BCOLOR;
	ws.frame.type		= 1;
	ws.lx				= EDIT_BOX_LX;
	ws.ly				= EDIT_BOX_LY;
	ws.rx				= EDIT_BOX_RX;
	ws.ry				= EDIT_BOX_RY;

	DrawWindow_q(&ws);
	DrawScrollVBar_q(VSCROLL_LX, VSCROLL_LY, VSCROLL_RX, VSCROLL_RY, 0);
}




void DispAirWindow(void)
{
	DispAirBox_q() ;
	DispAirTitle_q() ;



#if 0
	DispPageAir(0) ;
#endif
}
void DispAirBox_q (void)
{
	WinStyle_t ws;

	DefaultButtonStyle(&(ws.frame));
	ws.frame.main_col	= AIRBOX_MAIN_BCOLOR;
	ws.frame.type		= 1;
	ws.lx				= EDIT_BOX_LX+AIR_BOX_OFF;
	ws.ly				= EDIT_BOX_LY;
	ws.rx				= EDIT_BOX_RX;
	ws.ry				= EDIT_BOX_RY;

	DrawWindow_q(&ws);
	DrawScrollVBar_q(VSCROLL_LX, VSCROLL_LY, VSCROLL_RX, VSCROLL_RY, 0);
}
void SYS_INFO_proc(void *ptr)
{
	BYTE *dptr=(BYTE *)ptr ;
	GET_VAL(WORD,GrayColor) ;
	CHK_CHKSUM
	if( !SysInfo.GrayColor && GrayColor ){
		SysInfo.GrayColor = 1;
		SystemOn();
	}
	HelpCurLine = 0;
	if( idx_language==1 )	HelpTotalLine = sizeof(cHelpTbl)/sizeof(cHelpTbl[0]);
	else					HelpTotalLine = sizeof(eHelpTbl)/sizeof(eHelpTbl[0]);


	farfree(ptr) ;
}
void DISP_LED_proc(void *dptr)
{
	dptr=dptr ;
}
void SCRN_OFF_proc(void *dptr)
{
	dptr=dptr ;
	SystemOff();
	RollOn = 0;
}
void ROLL_OFF_proc(void *dptr)
{
	dptr=dptr ;
	RollOn = 0;
}
void SCRN_ON_proc(void *dptr)
{
	dptr=dptr ;
	SystemOn();
	RollOn = 1;
}
void ROLL_ON_proc(void *dptr)
{
	dptr=dptr ;
	RollOn = 1;
}
void FLASH_COLOR_proc(void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(BYTE,idx) ;
	GET_VAL(COLOR_T,col1) ;
	GET_VAL(COLOR_T,col2) ;
	CHK_CHKSUM
	SetFlash(idx, col1, col2);
	farfree(ptr) ;
}
void DISP_STR2_proc(void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(WORD ,lx) ;
	GET_VAL(WORD ,ly) ;
	GET_VAL(COLOR_T,fcol) ;
	GET_VAL(COLOR_T,bcol) ;
	BYTE *nstr= dptr ;
	GET_STRING_MUST
	BYTE *ostr= dptr ;
	GET_STRING
	CHK_CHKSUM
	
	char buf[10] ;
	int idxbuf=0 ;
	for(int i=0 ; nstr[i]!= 0 ; i++){
		if(nstr[i]== ostr[i]){
			if(idxbuf !=0){
				buf[idxbuf]=0 ;
				PrintStringLine(lx,  ly, fcol, bcol, buf);
				idxbuf=0 ;
			}
		}
		else{
			if(idxbuf==0){
				lx = *(short *)ptr+i*ASC_CHAR_W ;
			}
			EPT_IDX(idxbuf, buf);
			buf[idxbuf++]= nstr[i] ;
		}
	}
	if(idxbuf !=0){
				EPT_IDX(idxbuf, buf);
				buf[idxbuf]=0 ;
				PrintStringLine(lx,  ly, fcol, bcol, buf);
	}
	farfree(ptr) ;
}
void DISP_BIG_DIGIT_proc(void *dptr)
{
	dptr=dptr ;
}
void DispIcon_proc(void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(WORD,lx) ;	 
	GET_VAL(WORD,ly) ;
	GET_VAL(WORD,idx) ;  
	GET_VAL(WORD,op_mode) ; 
	CHK_CHKSUM

	PutIcon(lx, ly, idx , op_mode);
	farfree(ptr) ;
}
void DispSafeSw_proc(void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;

	GET_VAL(BYTE,mode) ;
	CHK_CHKSUM
	DispSafeSw( mode );
	farfree(ptr) ;
}
void DISP_MSG_WIN_proc(void *ptr)
{
	uint8 *dptr= (uint8 *)ptr ;
	GET_VAL(uint16 , x) ;	
	GET_VAL(uint16 ,	y) ;	
	GET_VAL(uint8 , type) ;
	uint8 *str= dptr ;
	GET_STRING
	CHK_CHKSUM

	DispMsgWin(x, y, type, (char *)str);
	free(ptr) ;
}

void DispMsgWin_proc(void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(WORD , x) ;	
	GET_VAL(WORD , y) ;	
	GET_VAL(BYTE , type) ;
	BYTE *str= dptr ;
	GET_STRING
	CHK_CHKSUM

	DispMsgWin(x, y, type, (char *)str);
	farfree(ptr) ;
}
void CLR_MSG_WIN_proc(void *dptr)
{
	dptr= dptr ;
	ClearMessageWin();
}
void ClrMsgWin_proc(void *dptr)
{
	dptr= dptr ;
	ClearMessageWin();
}



void HELP_UP_proc(void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(WORD,step) ;
	CHK_CHKSUM
	
	if( HelpCurLine > 0 ){
		HelpCurLine -= step;
		if( HelpCurLine < 0 )  HelpCurLine = 0;
		DispHelpContent();
	}
	farfree(ptr) ;
}
void HELP_DOWN_proc(void * ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(WORD,step) ;
	CHK_CHKSUM

	if( HelpCurLine < HelpTotalLine-HELP_PAGE_LINE ){
		HelpCurLine += step;
		if( HelpCurLine > HelpTotalLine-HELP_PAGE_LINE )  HelpCurLine = HelpTotalLine-HELP_PAGE_LINE;
		DispHelpContent();
	}
	farfree(ptr) ;
}
void UpdateScrollBar_proc(void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(WORD,percent) ;
	CHK_CHKSUM

	DrawScrollVBar(VSCROLL_LX, VSCROLL_LY, VSCROLL_RX, VSCROLL_RY, percent);
	farfree(ptr) ;
}
void DISP_RUN_WIN_proc(void *dptr)
{
	dptr=dptr ;
	DispRunMessageWin();
}
void DISP_RUN_MSG_proc(void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(DWORD , cur_quan) ;
	GET_VAL(DWORD , set_quan)	;
	CHK_CHKSUM

	DispRunMessage(cur_quan, set_quan);
	farfree(ptr) ;
	
}
void DispTestMsg_proc(void *dptr)
{
	dptr=dptr ;
	struct TIMER Ticks;
	int rpm , rpmd ;
	struct TIMER t1 = ReadTimer() ;
	
	cal_rrpm(t1,Ticks,rpm,rpmd) ;
	INI_DISP_BUF() ;
	Fill_pDispBuf("實際生產速度" ,"Produce Speed");
	sprintf((char *)pDispBuf,"= %03d.%01d", rpm,rpmd);
	int x=450 ;
	DispStatusBar_q(x,DispBuf) ;
}

void CLR_RUN_WIN_proc(void *dptr)
{
	dptr=dptr ;
	ClrRunMessageWin();
}

void Init_pc_common()
{

	//    short chk = SelfTest();

	SetVideoMode();
	InitChFont();
	InitRollData();

	//    InitScrn(chk);
	SystemOn();
	InitImageStack();
	SendCmdID =  0;

	HelpCurLine = 0;
	if( idx_language==1 )	HelpTotalLine = sizeof(cHelpTbl)/sizeof(cHelpTbl[0]);
	else					HelpTotalLine = sizeof(eHelpTbl)/sizeof(eHelpTbl[0]);

#if USE_DOS_FILE
#else
	LastSector = -1;
#endif

	RollOn = 0;
	Reset = 0;
}

void Init_pc()
{
	Init_pc_common() ;
	Init_ints() ;
}






#if 0
static char *WinTitle[][7]={
	{
		"SOL SERVO SYSTEM - EDIT",
		"SOL SERVO SYSTEM - WORK", 
		"SOL SERVO SYSTEM - TEST",
		"SOL SERVO SYSTEM - STEP", 
		"SOL SERVO SYSTEM - MODY", 
		"SOL SERVO SYSTEM - PARA",
		"SOL SERVO SYSTEM - HELP"
	},
	{
		"SOL 京微伺服控制系統 - 編輯", 
		"SOL 京微伺服控制系統 - 生產", 
		"SOL 京微伺服控制系統 - 測試",
		"SOL 京微伺服控制系統 - 單步", 
		"SOL 京微伺服控制系統 - 修改", 
		"SOL 京微伺服控制系統 - 參數",
		"SOL 京微伺服控制系統 - 說明"
	},
	{
		"SOL SERVO SYSTEM - EDIT    ",
		"SOL SERVO SYSTEM - LAVORA  ",
		"SOL SERVO SYSTEM - TEST    ",
		"SOL SERVO SYSTEM - PASSO   ",
		"SOL SERVO SYSTEM - MODIFICA",
		"SOL SERVO SYSTEM - PARAM   ",
		"SOL SERVO SYSTEM - AIUTO   "
	},
	{
		"    伺服控制系統 - 編輯", 
		"    伺服控制系統 - 生產", 
		"    伺服控制系統 - 測試",
		"    伺服控制系統 - 單步", 
		"    伺服控制系統 - 修改", 
		"    伺服控制系統 - 參數",
		"    伺服控制系統 - 說明"
	},	
};
#else
static char *WinTitle[][7]={
	{
		"XINDA SERVO SYSTEM - EDIT",
		"XINDA SERVO SYSTEM - WORK", 
		"XINDA SERVO SYSTEM - TEST",
		"XINDA SERVO SYSTEM - STEP", 
		"XINDA SERVO SYSTEM - MODY", 
		"XINDA SERVO SYSTEM - PARA",
		"XINDA SERVO SYSTEM - HELP"
	},
	{
		"    新達伺服控制系統 - 編輯", 
		"    新達伺服控制系統 - 生產", 
		"    新達伺服控制系統 - 測試",
		"    新達伺服控制系統 - 單步", 
		"    新達伺服控制系統 - 修改", 
		"    新達伺服控制系統 - 參數",
		"    新達伺服控制系統 - 說明"
	},
	{
		"XINDA SERVO SYSTEM - EDIT    ",
		"XINDA SERVO SYSTEM - LAVORA  ",
		"XINDA SERVO SYSTEM - TEST    ",
		"XINDA SERVO SYSTEM - PASSO   ",
		"XINDA SERVO SYSTEM - MODIFICA",
		"XINDA SERVO SYSTEM - PARAM   ",
		"XINDA SERVO SYSTEM - AIUTO   "
	},
	{
		"    伺服控制系統 - 編輯", 
		"    伺服控制系統 - 生產", 
		"    伺服控制系統 - 測試",
		"    伺服控制系統 - 單步", 
		"    伺服控制系統 - 修改", 
		"    伺服控制系統 - 參數",
		"    伺服控制系統 - 說明"
	},	
};
#endif
static char *PassWordTitle[][1]={
	{"PASSWORD "},
	{"密碼輸入 "},
	{"PASSWORD "},
};

static char *ColPara1_01[][3]={
   {"LANGUAGE","TYPE NO.","Y-Encode"/*,"MOT NEAR"*/} ,
   {"語言設定","機器型號","Y-編碼器"/*,"回報信號"*/} , 
   {"LINGUAG ","TIPO    ","Y-Encode"/*,"MOT NEAR"*/} ,
} ;
static char *ColPara1_02[][4]={
   {"SHIELD  ","SENSOR  ","W.LIGHT ","Cut Dist"} ,
   {"安全門  ","安全裝置","警示燈  ","切刀距離"} ,
   {"SICUREZ ","SENSORE ","W.LIGHT ","Cut Dist"} ,
} ;
static char *ColPara1_03[][4]={
   {"Y-REPAIR","Y-DIST  ","Y-GEAR0 ","Y-GEAR1 ",} ,
   {"整定速度","整定距離","Y軸齒比0","Y軸齒比1",} ,
   {"Y-REPAIR","Y-DIST  ","Y-GEAR0 ","Y-GEAR1 ",} ,
} ;
static char *ColPara1_04[][2]={  //   repair_spd ,repair_dst,G2Mode,SPDMode
	{/*"SPEED UP","DIST UP ",*/"RateMode","SPD Mode" },
	{/*"速度補正","距離補正",*/"速率模式","SPD 模式" },
	{/*"COMP.VEL","COMPDIST",*/"RateMode","SPD Mode" },
};
static char *MotorExtPara11[][3]={
	{ "SIM FAST", "MOT   NO", "Switch T"		},  //ManSpeed_PMfun[]
	{ "手動加速", "手動減速", "手動\xA5\x5C能"	} ,	
	{ "SIM FAST", "MOT   NO", "Switch T"		},
};
static char *SPDLinkMode[][1]={
	{ "LinkMode"},  //SPDLinkMode
	{ "聯動模式"},	
	{ "LinkMode"},
};

static char *MotorExtPara12[][3]={
	{ "SIM FAST", "MOT   NO", "Switch T"		},  //RORSpeed_PMfun[]
	{ "翻線加速", "翻線減速", "翻線\xA5\x5C能"	} ,	
	{ "SIM FAST", "MOT   NO", "Switch T"		},
};
static char *MotorExtPara13[][3]={
	{ "SIM FAST", "MOT   NO", "Switch T"		},  //DefSpeed_PMfun[] 
	{ "預設加速", "預設減速", "預設\xA5\x5C能"	} ,	
	{ "SIM FAST", "MOT   NO", "Switch T"		},
};

static char *Company[][2]={
	{"SOL  TECHNOLOGY CO., LTD  Copyrights (c)      All right reserved ", "1F, #74-1, YUN HO ST., TAIPEI"},
	{"京微科技股份有限公司                          著作財產權所有     ", "台北市雲和街 74-1 號 1F      "} ,
	{"SOL  TECHNOLOGY CO., LTD  Copyrights (c)      All right reserved ", "1F, #74-1, YUN HO ST., TAIPEI"},
};

char *MotorSysPara_nopass[][9]={
	{ "  UNIT  ","MOT SPD ","G1  SPD ","ZERO SPD"   ,"  DELAY "," TO POS ","ZRT PreM","Uint Y0 ","Cus Rate"}, 
	{ "  單 位 ","馬達速度","G1  速度","歸零速度"   ,"  延 遲 "," 到定位 ","歸零預走","單位換算","自訂速率"} ,
	{ "  UNITA'","VEL. MOT","VEL.  G1","PUNTO\"0\"" ," RITARDO","RIT. POS","ZRT PreM","Uint Y0 ","Cus Rate"},
};
char *MotorSysPara_Speed_PMfun[][4]={
	{ "SPD Plus","SPDMinus","SPD  Fun","LOW  SPD"},
	{ "各軸加速","各軸減速","加減\xA5\x5C能","最小加減"},
	{ "SPD Plus","SPDMinus","SPD  Fun","LOW  SPD"},
};

char *MotorSysPara_Speed_PMfun2[][4]={
	{ "Item NO.","SET  SPD","SPD Plus","SPDMinus"},
	{ "組    數","速度設定","加    速","減    速"},
	{ "Item NO.","SET  SPD","SPD Plus","SPDMinus"},
} ;

static char *Y0Para[][4]={
   {  "BIOS RST","SCRN SAV", "TIMER   " ,"ROTW Deg"} ,  //bios_rst,ScrnSav,Timer,AHome
   {  "BIOS重置","螢幕保護", "自動關電" ,"翻線角度"} ,
   {  "BIOS RST","SCRN SAV", "TIMER   " ,"ROTAZ\x6  "} ,
} ;
static char *NEARPara[][4]={
   {  /*"X-NEAR  ","X-SPD   ",*/"Pay  Off","USB Disk","SlidLimi","Air  OFF"} ,  //NEAR,X_SPD,PayOff,SlideLimit,Air_Off
   {  /*"x軸預走 ","X軸變速 ",*/"線架加速","USB 磁碟","滑座極限","汽缸解除"} ,
   {  /*"X-NEAR  ","VEL. X  ",*/"Pay  Off","USB Disk","SlidLimi","Air  OFF"} ,  //NEAR,X_SPD,PayOff,SlideLimit
} ;
static char *SPIN_ZRTPara[][4]={
   {  "SPIN ZRT",	"MPG X100",	"WileSTOP",	"WileTIME"/*, " T STOP "*/} ,  //SPIN_ZRT,MPG_X100,WileSTOP,Touch_Stop_Flag,Wire_Time
   {  "捲取歸零",	"手輪X100",	"送線暫停",	"線架時間"/*, "探針停軸"*/} ,
   {  "P. 0 ZRT",	"MPG X100",	"WileSTOP",	"WileTIME"/*, " T STOP" */} ,  //SPIN_ZRT
} ;
static char *WILE_MODEPara[][4]={
   {  "WileMode"/*,"EnterMOD"*/,"WorkMode" , "UsePMfun", "T-TIME　"} ,  //WileMode,CursorMode,WorkMode,UsePMfun,Touch_rate
   {  "線架模式"/*,"輸入模式"*/,"工作模式" , "加減速  ", "探針時間"} ,
   {  "WileMode"/*,"EnterMOD"*/,"WorkMode" , "UsePMfun", "T-TIME　"} ,  //
} ;
static char *PRODPASSPara[][4]={						//CursorPRODPASS,CursorPRODDELAY
   {  "Prod PAS","ProDELAY","X--MINUS","KEY LOCK"} ,				//PRODPASS ,PRODDELAY,XMINUS,KEYLOCK
   {  "生產密碼","生產延遲","X軸反向","鍵盤鎖住"} ,					
   {  "Prod PAS","ProDELAY","X--MINUS","KEY LOCK"} , 
} ;
static char *OilChkPara[][1]={						//CursorOilChk,
   {  "Oil  OFF"} ,				
   {  "油檢解除"},					
   {  "Oil  OFF"} , 
} ;


static char *BIOS_RST[][1]={
   {  "BIOS RST"} ,
   {  "BIOS重置"} ,
   {  "BIOS RST"} , 
} ;



#if TPROGBUF
static BYTE huge tProgBuf[PROG_BUF_LINES][QUEUE_SIZE];
#endif


////////////////////////////////////////////////////////////////////////////////
//
//自動format 起始點
//

void DispMainWindow_q ()
{
	WinStyle_t ws;
	DefaultButtonStyle(&(ws.frame));
	ws.style		= W_NORMAL;
	ws.lx			= MAIN_WIN_LX;
	ws.ly			= MAIN_WIN_LY+300;
	ws.rx			= MAIN_WIN_RX;
	ws.ry			= MAIN_WIN_RY;
	DrawWindow_q(&ws);
}

void DispMainWindow_q (short idx, short only_title)
{
	
	//警示燈控制
	if(idx == 1){
		if(MachineStatus.PayOff ==1){
			WireOnOff(1) ;
		}
		WARN_LIGHT_ON_GREEN
	}
	else{
		if(MachineStatus.PayOff ==1){
			WireOnOff(0) ;
		}
		WARN_LIGHT_OFF_RED
	}
	
	WinStyle_t ws;
	
	DefaultButtonStyle(&(ws.frame));
	ws.style		= W_TITLE+W_ICON+W_MINIMUN+W_CLOSE;
	ws.lx			= MAIN_WIN_LX;
	ws.ly			= MAIN_WIN_LY;
	ws.rx			= MAIN_WIN_RX;
	ws.ry			= MAIN_WIN_RY;
	char buf[100] ;
	
	strcpy(buf,WinTitle[idx_language][idx]) ;


	//2012_1010_新增"小鍵盤"&&"LOGO"切換----------------------------
	uint8 ManuFactory = MachineStatus.MANUFACTORY&0xf;
	if(ManuFactory==SETT)	strcat(buf,"  SETT20") ;
	else{
		if(MachineStatus.Delay!=3){
			strcat(buf,"  CNC") ;
		}
		else{
			strcat(buf,"  XB-") ;
		}
		if(MachineStatus.Type == TYPE_650_850){
			//2012_1010_新增"小鍵盤"&&"LOGO"切換----------------------------
			uint8 ManuFactory = MachineStatus.MANUFACTORY&0xf;
			if(ManuFactory==1)	strcat(buf,"800") ;			
			else{
				 strcat(buf,(TYPE_650_850==0x650)?"650":"850") ;
			}
		}
		else if(MachineStatus.Type == TYPE_635_835||MachineStatus.Type == TYPE_1635_1835){
			strcat(buf,(TYPE_635_835==0x635)?"635":"835") ;
		}
		else if(MachineStatus.Type == 0x630){
			strcat(buf,"630") ;
		}
		else if(MachineStatus.Type == 0x608){
			strcat(buf,"608") ;
		}
		else{
			if(MachineStatus.Delay!=3){
				strcat(buf,(TYPE_620_820==0x620)?"620":"820") ;
			}
			else{
				strcat(buf,"20") ;
			}
		}

		if(CHK_ROTW(AXIS_A)){
			strcat(buf,"W") ;
		}
	}

	strcat(buf,"  ") ;
	strcat(buf,VERSION) ;
	if(ExeMode ==0){
//		strcat(buf,"(測試版)") ;
	}
	if(NewH){ 
	#ifdef HNCNC6 
	strcat(buf,"N6") ;//新主版版本顯示N //版本後面顯示軸數
	#else
	strcat(buf,"N8") ;//新主版版本顯示N
	#endif 			
	}
	
	ws.title		= buf ;
	ws.icon			= idx;
	ws.title_fcol	= WIN_TITLE_FCOLOR;
	ws.title_bcol	= WIN_TITLE_BCOLOR;

	if( only_title )	DrawWindowTitle_q(&ws);
	else				DrawWindow_q(&ws);
	
	if(stBATCHn.flag && !(MachineStatus.op_mode & (PARA_MODE))){
		int32 x;
		char *str[3]={"BATCH   " ,"批量    ","BATCH   "};		
		DispStrLine_q(x=MAIN_WIN_LX+450, MAIN_WIN_LY+6,	 WIN_TEXT_BCOLOR,RED_USR, str[idx_language]);
		x+= (ASC_CHAR_W*5) ;
		char buf[30];
#ifdef Bound_Check
		ept_char ept_buf={&buf[0], &buf[0], &buf[30]}, pBuf=ept_buf ;
#else
        ept_char pBuf=buf ;
#endif
		
		pBuf_value += BcdToStrBuf(7, MachineStatus.BATCHn, pBuf);
		ADD_MINUS_01(pBuf);
		buf[8]='\0';
		DispStrLine_q(x, MAIN_WIN_LY+6,	RED_USR, WIN_TEXT_BCOLOR, buf);
		
	}
}
void DispWindow_q (short all,short idx)
{
	DispMainWindow_q(idx, !all);
	DispToolBar_q(idx);

	if( all ){
		DispTouchFrame_q();
		DispMissFrame_q();
		DispQuanFrame_q();
		DispFileFrame_q();
		DispSpeedFrame_q();
		DispModeFrame_q();
		//if(NewH&&MachineStatus.ScrnSav==0x88)DispReutrn_q();		//顯示返回功能次數 ///返回功能隱藏於螢幕保護設定88分鐘
		if(NewH)DispReutrn_q();		//顯示返回功能次數 ///返回功能隱藏於螢幕保護設定88分鐘
		DispAxisFrame_q();
		DispPosFrame_q();
		DispManFrame_q();
		DispHandFrame_q();
		DispEditBox_q();
	}
}
void DispEditWin_q (short all)
{
	DispWindow_q(all,EDIT_ICON);
}

void DispWorkWin_q (short all)
{
	DispWindow_q(all,WORK_ICON);
}

void DispTestWin_q (short all)
{
	DispWindow_q(all,TEST_ICON);
}

void DispStepWin_q (short all)
{
	DispWindow_q(all,STEP_ICON);
}

void DispModyWin_q (short all)
{
	DispWindow_q(all,MODY_ICON);
}

void DispParaBox_q (void)
{
	WinStyle_t ws;

	DefaultButtonStyle(&(ws.frame));
	ws.frame.type		= -1;
	ws.lx				= PARA_BOX_LX;
	ws.ly				= PARA_BOX_LY;
	ws.rx				= PARA_BOX_RX;
	ws.ry				= PARA_BOX_RY;

	DrawWindow_q(&ws);
}

void DispPasswordFrame_proc(void *dptr)
{
	dptr=dptr ;
	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PASSWORD_LX;
	short ly = PASSWORD_LY;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, PassWordTitle[idx_language][0]);
	frame.type = 0;
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
}
void DispPasswordFrame_q (void)
{
	FILL_PROC_QUEUE(DispPasswordFrame_proc,NULL) ;
}
void DispSPDMotorIDFrame_proc(void *dptr)
{
	dptr=dptr ;
	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PASSWORD_LX;
	short ly = PASSWORD_LY;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, MotorSysPara[idx_language][0]);  //顯示馬達編號
	frame.type = 0;
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
}

void DispSPDMotorIDFrame_q (void)
{
	FILL_PROC_QUEUE(DispSPDMotorIDFrame_proc,NULL) ;
}

void DispParaMotorFrame_com(short idx , char *MotorStr)
{
	Frame_t	frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_MOTOR_LX;
	short ly = PARA_MOTOR_LY+idx*(ASC_CHAR_H+4);
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR,MotorStr );
}
void DispParaMotorFrameh_com(short idx , char *MotorStr)
{
	Frame_t	frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_MOTOR_LX+idx*(PARA_DATA_CHARS*ASC_CHAR_W+4);
	short ly = PARA_MOTOR_LY;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR,MotorStr );
}
void DispParaMotorFrame1_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short ,idx) ;
	CHK_CHKSUM
	DispParaMotorFrame_com(idx ,MotorSysPara[idx_language][idx]) ;   //顯示馬達編號(idx=0)/馬達名稱(idx=1)
	farfree(ptr) ;
}
void DispParaMotorFrame1_pass_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short ,idx) ;
	CHK_CHKSUM
	DispParaMotorFrame_com(idx+2,MotorSysPara_pass[idx_language][idx]) ;
	farfree(ptr) ;
}
void DispParaMotorFrame2_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i) ;
	GET_VAL(short , start_j) ;
	GET_VAL(short , end_j) ;
	CHK_CHKSUM

	Frame_t	frame;

	DefaultButtonStyle(&frame);
	frame.type = 0;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_MOTOR_LX;
	short ly = PARA_MOTOR_LY+start_j*(ASC_CHAR_H+4);

	lx = PARA_MOTOR_LX + PARA_DATA_CHARS*ASC_CHAR_W+4+i*(PARA_DATA_CHARS*ASC_CHAR_W+4);
	for(short  j=start_j; j < end_j; j++ )
	{
		DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
		ly += ASC_CHAR_H+4;
	}
	farfree(ptr) ;
}

#if NOPASS
void DispParaMotorFrame1_Speed_PMfun_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short ,idx) ;
	CHK_CHKSUM
	DispParaMotorFrame_com(idx+2,MotorSysPara_Speed_PMfun[idx_language][idx]) ;
	farfree(ptr) ;
}
void DispParaMotorFrame1h_Speed_PMfun_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short ,idx) ;
	CHK_CHKSUM
	DispParaMotorFrameh_com(idx+2,MotorSysPara_Speed_PMfun[idx_language][idx]) ;
	farfree(ptr) ;
}
void DispParaMotorFrame2h_Speed_PMfun_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short ,idx) ;
	CHK_CHKSUM
	DispParaMotorFrameh_com(idx+0,MotorSysPara_Speed_PMfun2[idx_language][idx]) ;
	farfree(ptr) ;
}
#endif
void DispParaMotorFrame1_nopass_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short ,idx) ;
	CHK_CHKSUM
	DispParaMotorFrame_com(idx+2,MotorSysPara_nopass[idx_language][idx]) ;
	farfree(ptr) ;
}

void DispParaMotorFrame_nopass_q (void)
{
	short len = sizeof(MotorSysPara[0])/sizeof(MotorSysPara[0][0]) ;
	for(short i=0 ; i < len ; i++ ){
		BYTE *dptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE *tptr = dptr ;
		SAVE_VAL(short, i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispParaMotorFrame1_proc,tptr) ;    //顯示馬達編號/馬達名稱
	}
	short len2 = sizeof(MotorSysPara_nopass[0])/sizeof(MotorSysPara_nopass[0][0]) ;
	for(short i=0 ; i < len2 ; i++ ){
		BYTE *dptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE *tptr = dptr ;
		SAVE_VAL(short, i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispParaMotorFrame1_nopass_proc,tptr) ;
	}
	len = len+len2 ;
	for( short i=0; i < SysInfo.AxisNo; i++ ){
		for(short  j=0; j < len; j+=3 ){
			BYTE *dptr = (BYTE *)farmalloc(3*sizeof(short)+LEN_CHKSUM) ;
			BYTE *tptr= dptr ;
			SAVE_VAL(short , i) ;
			SAVE_VAL(short , j) ;
			SAVE_VAL(short , (j+3) > len ? len : j+3) ;
			SAVE_CHKSUM
			FILL_PROC_QUEUE(DispParaMotorFrame2_proc,tptr) ;
		}
	}
}

void DispParaY0Frame1_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i) ;
	CHK_CHKSUM

	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_MOTOR_LX+i*(PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	short ly = PARA_Y0_LY;
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, Y0Para[idx_language][i]);
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispParaY0Frame_q (void)
{
	for(short i=0; i < sizeof(Y0Para[0])/sizeof(Y0Para[0][0]); i++ ){
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE * dptr= tptr ;
		SAVE_VAL(short , i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispParaY0Frame1_proc,tptr) ;
	}
}


void DispParaNEARFrame1_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i) ;
	CHK_CHKSUM

	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_MOTOR_LX+i*(PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	short ly = PARA_NEAR_LY;
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, NEARPara[idx_language][i]);
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispParaNEARFrame_q (void)
{
	for(short i=0; i < sizeof(NEARPara[0])/sizeof(NEARPara[0][0]); i++ ){
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE * dptr= tptr ;
		SAVE_VAL(short , i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispParaNEARFrame1_proc,tptr) ;
	}
}
void DispParaSPIN_ZRTFrame1_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i) ;
	CHK_CHKSUM

	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_MOTOR_LX+i*(PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	short ly = PARA_SPIN_ZRT_LY;
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, SPIN_ZRTPara[idx_language][i]);
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispParaSPIN_ZRTFrame_q (void)
{
	for(short i=0; i < sizeof(SPIN_ZRTPara[0])/sizeof(SPIN_ZRTPara[0][0]); i++ ){
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE * dptr= tptr ;
		SAVE_VAL(short , i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispParaSPIN_ZRTFrame1_proc,tptr) ;
	}
}

void DispParaWILE_MODEFrame1_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i) ;
	CHK_CHKSUM

	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_MOTOR_LX+i*(PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	short ly = PARA_WILE_MODE_LY;
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, WILE_MODEPara[idx_language][i]);
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispParaWILE_MODEFrame_q (void)
{
	for(short i=0; i < sizeof(WILE_MODEPara[0])/sizeof(WILE_MODEPara[0][0]); i++ ){
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE * dptr= tptr ;
		SAVE_VAL(short , i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispParaWILE_MODEFrame1_proc,tptr) ;
	}
}

void DispParaPRODPASSFrame1_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i) ;
	CHK_CHKSUM

	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_MOTOR_LX+i*(PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	short ly = PARA_PRODPASS_LY;
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, PRODPASSPara[idx_language][i]);
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispParaPRODPASSFrame_q (void)
{
	for(short i=0; i < sizeof(PRODPASSPara[0])/sizeof(PRODPASSPara[0][0]); i++ ){
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE * dptr= tptr ;
		SAVE_VAL(short , i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispParaPRODPASSFrame1_proc,tptr) ;
	}
}
void DispParaOilChkFrame1_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i) ;
	CHK_CHKSUM

	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_MOTOR_LX+i*(PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	short ly = PARA_OilChk_LY;
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, OilChkPara[idx_language][i]);
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispParaoOilChkFrame_q (void)
{
	for(short i=0; i < sizeof(OilChkPara[0])/sizeof(OilChkPara[0][0]); i++ ){
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE * dptr= tptr ;
		SAVE_VAL(short , i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispParaOilChkFrame1_proc,tptr) ;
	}
}
void DispParaExt11Frame_proc (void * ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i ) ;
	CHK_CHKSUM
	
	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_EXT11_LX+i*(PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	short ly = PARA_EXT11_LY;
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, MotorExtPara11[idx_language][i]);
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;	
}
void DispParaExt11Frame_q (void)
{
	for(short  i=0; i < sizeof(MotorExtPara11[0])/sizeof(MotorExtPara11[0][0]); i++ ){
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE *dptr=tptr ;
		SAVE_VAL(short, i );
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispParaExt11Frame_proc,tptr) ;
	}
}
void DispSPDLinkMode_proc (void * ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i ) ;
	CHK_CHKSUM
	
	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_SPDLinkMode_LX+i*(PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	short ly = PARA_SPDLinkMode_LY;
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, SPDLinkMode[idx_language][i]);
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;	
}
void DispSPDLinkMode_q (void)
{
	for(short  i=0; i < sizeof(SPDLinkMode[0])/sizeof(SPDLinkMode[0][0]); i++ ){
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE *dptr=tptr ;
		SAVE_VAL(short, i );
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispSPDLinkMode_proc,tptr) ;
	}
}

void DispParaExt12Frame_proc (void * ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i ) ;
	CHK_CHKSUM
	
	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_EXT12_LX+i*(PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	short ly = PARA_EXT12_LY;
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, MotorExtPara12[idx_language][i]);
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispParaExt12Frame_q (void)
{
	for(short  i=0; i < sizeof(MotorExtPara12[0])/sizeof(MotorExtPara12[0][0]); i++ ){
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE *dptr=tptr ;
		SAVE_VAL(short, i );
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispParaExt12Frame_proc,tptr) ;
	}
}
void DispParaExt13Frame_proc (void * ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i ) ;
	CHK_CHKSUM
	
	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_EXT13_LX+i*(PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	short ly = PARA_EXT13_LY;
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, MotorExtPara13[idx_language][i]);
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispParaExt13Frame_q (void)
{
	for(short  i=0; i < sizeof(MotorExtPara13[0])/sizeof(MotorExtPara13[0][0]); i++ ){
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE *dptr=tptr ;
		SAVE_VAL(short, i );
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispParaExt13Frame_proc,tptr) ;
	}
}





void DispParaWin_nopass_q (short all)
{

	DispMainWindow_q(PARA_ICON, !all);
	DispToolBar_q(PARA_ICON);

	if( all )
	{
		DispParaBox_q();
		DispParaMotorFrame_nopass_q();
		DispParaY0Frame_q();
		DispParaNEARFrame_q();
		DispParaSPIN_ZRTFrame_q();
		DispParaWILE_MODEFrame_q();
		DispParaPRODPASSFrame_q();
		DispParaoOilChkFrame_q();
#if 0
		PrintStringLine_fmt_q(PARA_BOX_LX+2+(ASC_CHAR_W*2), PARA_BOX_RY-2-(ASC_CHAR_H+1)*(5-4), MAGENTA_USR, LIGHTGRAY_USR, Company[idx_language][0]);
		if(MachineStatus.SN[0] == '6'){
			DispSN(0) ;
		}
#endif
//		PrintStringLine(PARA_BOX_LX+2+(ASC_CHAR_W*2), PARA_BOX_RY-2-(ASC_CHAR_H+1), CCY_NAME_FCOLOR, CCY_NAME_BCOLOR, "宋昀, 馮義, 1998 製作.");
	}
}




void DispHelpBox_q (void)
{
	WinStyle_t ws;

	DefaultButtonStyle(&(ws.frame));
	ws.frame.main_col	= HELPBOX_MAIN_BCOLOR;
	ws.frame.type		= 1;
	ws.lx				= HELP_BOX_LX;
	ws.ly				= HELP_BOX_LY;
	ws.rx				= HELP_BOX_RX;
	ws.ry				= HELP_BOX_RY;
	DrawWindow_q(&ws);
}

void DispHelpContent_q (void)
{
	char buf[ONE_LINE_CHAR_NO];
	short i, len;

	if( HelpTotalLine <= HELP_PAGE_LINE )
	{
		HelpCurLine = 0;
	}
	else
	{
		if( HelpCurLine+HELP_PAGE_LINE > HelpTotalLine )  HelpCurLine = HelpTotalLine-HELP_PAGE_LINE;
	}

	for( i=0; i < HELP_PAGE_LINE; i++ )
	{
		if( HelpCurLine+i < HelpTotalLine )
		{
			if( idx_language==1 )	strcpy(buf, cHelpTbl[HelpCurLine+i]);
			else					strcpy(buf, eHelpTbl[HelpCurLine+i]);
		}
		else
		{
			buf[0] = 0;
		}

		len = strlen(buf);
		if( len < HELP_PAGE_CHARS )
		{
			memset(buf+len, ' ', HELP_PAGE_CHARS-len);
			
			EPT_IDX(HELP_PAGE_CHARS, buf);
			buf[HELP_PAGE_CHARS] = 0;
		}
		else if( len > HELP_PAGE_CHARS )
		{
			EPT_IDX(HELP_PAGE_CHARS, buf);
			buf[HELP_PAGE_CHARS] = 0;
		}

		DispStrLine_q(HELP_BOX_LX+2, HELP_BOX_LY+2+i*(ASC_CHAR_H+1), HELPBOX_MAIN_FCOLOR, HELPBOX_MAIN_BCOLOR, buf);
	}

}


void DispHelpContent (void)
{
	char buf[ONE_LINE_CHAR_NO];
	short i, len;

	if( HelpTotalLine <= HELP_PAGE_LINE )
	{
		HelpCurLine = 0;
	}
	else
	{
		if( HelpCurLine+HELP_PAGE_LINE > HelpTotalLine )  HelpCurLine = HelpTotalLine-HELP_PAGE_LINE;
	}

	for( i=0; i < HELP_PAGE_LINE; i++ )
	{
		if( HelpCurLine+i < HelpTotalLine )
		{
			if( idx_language==1 )	strcpy(buf, cHelpTbl[HelpCurLine+i]);
			else					strcpy(buf, eHelpTbl[HelpCurLine+i]);
		}
		else
		{
			buf[0] = 0;
		}

		len = strlen(buf);
		if( len < HELP_PAGE_CHARS )
		{
			memset(buf+len, ' ', HELP_PAGE_CHARS-len);
			
			EPT_IDX(HELP_PAGE_CHARS, buf);
			buf[HELP_PAGE_CHARS] = 0;
		}
		else if( len > HELP_PAGE_CHARS )
		{
			EPT_IDX(HELP_PAGE_CHARS, buf);
			buf[HELP_PAGE_CHARS] = 0;
		}

		PrintStringLine(HELP_BOX_LX+2, HELP_BOX_LY+2+i*(ASC_CHAR_H+1), HELPBOX_MAIN_FCOLOR, HELPBOX_MAIN_BCOLOR, buf);
	}

}

void DispHelpWin_q (short all)
{
	DispMainWindow_q(HELP_ICON, !all);
	DispToolBar_q(HELP_ICON);

	if( all )
	{
		DispHelpBox_q();
		DispHelpContent_q();
	}
	DispSN(1) ;
}

void ClearMessageWin (void)
{
	ErrMsg[0]= '\0' ;
	ErrMsg_timeout_flg=false ;
	PopImage(-1, -1);
}
char *StrWORKING[]= {
	"WORKING..." ,
	"生產中..." ,
	"LAVORA..." ,
} ;


void DispRunMessageWin (void)
{
	WinStyle_t ws;
	short lx, ly, rx, ry;

	lx = RUN_MSG_LX;
	ly = RUN_MSG_LY;
	rx = RUN_MSG_LX+RUN_MSG_W-1;
	ry = RUN_MSG_LY+RUN_MSG_H-1-2*ASC_CHAR_H;


	if(SCRN_W==800){
		lx+=160;
		ly+=120;
		rx+=160;
		ry+=120;
	}

	PushImage(lx, ly, rx, ry);

	DefaultButtonStyle(&(ws.frame));
	ws.style		= W_TITLE+W_ICON+W_CLOSE;
	ws.lx			= lx;
	ws.ly			= ly;
	ws.rx			= rx;
	ws.ry			= ry;
	ws.title_fcol	= BRIGHTWHITE_USR;
	ws.title_bcol	= BLUE_USR;
	ws.title		= StrWORKING[idx_language];
	ws.icon			= WORK_ICON;
	DrawWindow(&ws);

	if(FlagRun1){
		DispRunMessage() ;
	}

	t0= ReadTimer() ;

}

void DispRunMessage (unsigned long curquan, unsigned long setquan)
{
	char	buf[30];
	short	lx, ly, rx, ry;
	short	p, year=0, month=0, day=0, hour=0, minute=0;
	long long  ticks, m;

	struct TIMER t1 = ReadTimer() ;
	long long  dif =  ELAAPSED_CNT(t0,t1) ;
	ticks= dif*182UL/(10UL*TIMER0_HZ) ; //  1193UL*182UL/10000UL
	if(ticks<=0){
		ticks=100 ;
	}
	t0=t1 ;

	if( setquan == 0 )  setquan = 1;
	if( curquan > setquan ) curquan = setquan;

	lx = RUN_MSG_LX+ASC_CHAR_W*2;
	ly = RUN_MSG_LY+ASC_CHAR_H*2;
	rx = RUN_MSG_LX+RUN_MSG_W-1-ASC_CHAR_W*2;
	ry = RUN_MSG_LY+ASC_CHAR_H*3;

	if(SCRN_W==800){
		lx+=160;
		ly+=120;
		rx+=160;
		ry+=120;
	}

	p = (short)((curquan*100)/setquan);
	DrawHLightBar(lx, ly, rx, ry, p);
	PrintString((lx+rx-4*ASC_CHAR_W)/2, ly, BLACK_USR, NULL_COLOR, "%3d%%", p);

	m   = (ticks*10*1000)/(182*60);




#if 1
	int rpmd= (short)(m==0?0:((1000L*10/m)%10));
	int rpm = (short)(m==0?0:1000L/m);
	if(NewH){
		if(dif!=dif%10000)
			dif=dif-(dif%1000);
		rpmd= (short)(m==0?0:((60*1000*10*10)/dif)%10);
		rpm = (short)(m==0?0:(60*1000*10)/dif);
	}
	INI_DISP_BUF() ;
	Fill_pDispBuf( "實際生產速度 ",
                        "Produce Speed");
	sprintf((char *)pDispBuf_value,"= %03d.%01d", rpm,rpmd);
	PrintStringLine_fmt(lx, ry+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, (char *)DispBuf);
#else
	rpm = (short)(m==0?0:1000L/m);
	PrintStringLine(lx, ry+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, "RPM = %03d", rpm);
#endif






	m = (ticks*100)/182L;
	m = (m*(setquan-curquan))/(10*60L) + 1;

	year = (short)(m/(365L*30*24*60));
	m -= year*(365L*30*24*60);
	month = (short)(m/(30L*24*60));
	m -= month*(30L*24*60);
	day = (short)(m/(24L*60));
	m -= day*(24L*60);
	hour = (short)(m/60L);
	m -= hour*60L;
	minute = (short)m;

	p = 0;
	if( year	|| p ) p += sprintf(buf+p, "%04dy", year);
	if( month	|| p ) p += sprintf(buf+p, "%02dm", month);
	if( day		|| p ) p += sprintf(buf+p, "%02dd", day);
	if( hour	|| p ) p += sprintf(buf+p, "%02dh", hour);
	if( minute	|| p ) p += sprintf(buf+p, "%02dm", minute);

	if( idx_language==1 )	p += sprintf(buf+p, "%s", " 完成....");
	else					p += sprintf(buf+p, "%s", " Finish..");
	PrintStringLine_fmt(lx, ry+1*ASC_CHAR_H+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, buf);
}
void DispRunMessage ()
{
	short	lx,  ry;
	lx = RUN_MSG_LX+ASC_CHAR_W*2;
	ry = RUN_MSG_LY+ASC_CHAR_H*3;

	if(SCRN_W==800){
		lx+=160;
		ry+=120;
	}

	INI_DISP_BUF() ;
	Fill_pDispBuf(	"生產一條彈簧後,自動停機",
                	"after produce one spring");
	FILL_DISP_BUF(0) ;
	PrintStringLine_fmt(lx, ry+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, (char *)DispBuf);


	if(idx_language !=1){
		INI_DISP_BUF() ;
	 	Fill_pDispBuf(",then stop") ;
		FILL_DISP_BUF(0) ;
		PrintStringLine_fmt(lx, ry+ASC_CHAR_H*1+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, (char *)DispBuf);
	}
	 	
}

void ClrRunMessageWin (void)
{
	ClearMessageWin() ;
}

#if TPROGBUF

void GetProgLine (short idx, char *buf)
{
	strcpy((char *)tProgBuf[idx], buf);
}

void DispProg (short s_idx, short m_idx, short h)
{
	short i;

	for( i=0; i < h; i++ )
	{
		if( i == m_idx )
			PrintColorStringLine(EDIT_BOX_LX2, EDIT_BOX_LY+2+(ASC_CHAR_H+1)+i*(ASC_CHAR_H+1), CUR_PROG_FCOLOR, CUR_PROG_BCOLOR, (char *)tProgBuf[s_idx+i]);
		else
			PrintColorStringLine(EDIT_BOX_LX2, EDIT_BOX_LY+2+(ASC_CHAR_H+1)+i*(ASC_CHAR_H+1), EDITBOX_MAIN_FCOLOR, EDITBOX_MAIN_BCOLOR, (char *)tProgBuf[s_idx+i]);
	}
}
void DispProgLine_test (short y, short disp_line, bool mode)
{
		if( mode )
			PrintColorStringLine(EDIT_BOX_LX2, EDIT_BOX_LY+2+(ASC_CHAR_H+1)+y*(ASC_CHAR_H+1), CUR_PROG_FCOLOR, CUR_PROG_BCOLOR, (char *)tProgBuf[disp_line]);
		else
			PrintColorStringLine(EDIT_BOX_LX2, EDIT_BOX_LY+2+(ASC_CHAR_H+1)+y*(ASC_CHAR_H+1), EDITBOX_MAIN_FCOLOR, EDITBOX_MAIN_BCOLOR, (char *)tProgBuf[disp_line]);
}
#endif



void InitScrn (short chk)
{
	switch(chk)
	{
	case 1:
		PrintStringLine_fmt(0, 0, BRIGHTWHITE_USR, BLACK_USR, "PCB1 Test Error !");
		break;
	case 2:
		PrintStringLine_fmt(0, 0, BRIGHTWHITE_USR, BLACK_USR, "PCB2 Test Error !");
		break;
	default:
		PrintStringLine_fmt(0, 0, BRIGHTWHITE_USR, BLACK_USR, "Waiting...");
		break;
	}
}

short SelfTest (void)
{
	short i;
	BYTE far *p;

	p = (BYTE far *)(DP_TRANS_ADDR);
	for(i=0; i < 3*1024; i++){
		*p++ = 0x55;
	}
	p = (BYTE far *)(DP_TRANS_ADDR);
	for(i=0; i < 3*1024; i++){
		if(*p++ != 0x55)  return(2);
	}

	p = (BYTE far *)(DP_RECEIVE_ADDR);
	{
		for(i=0; i < 3*1024; i++){
			if(*p++ != 0xAA) return(1);
		}
	}

	return(0);
}

//各軸加減速--------------------------------------------------------------------------------------------------
void DispParaSPDPlus_q(void)
{
	short lx = PARA_MOTOR_LX + PARA_DATA_CHARS*ASC_CHAR_W+4;
	short ly = PARA_MOTOR_LY+(ASC_CHAR_H+4)*2;
	for(short i=0; i < MachineStatus.axis_no; i++ ){
		INI_DISP_BUF();
		pDispBuf_value += BcdToStrBuf(3, MachineStatus.WORD_SPDPlus[i], pDispBuf);
		FILL_DISP_BUF(0);
		DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
		lx += PARA_DATA_CHARS*ASC_CHAR_W+4;
	}
}
void DispParaSPDMinus_q(void)
{
	short lx = PARA_MOTOR_LX + PARA_DATA_CHARS*ASC_CHAR_W+4;
	short ly = PARA_MOTOR_LY+(ASC_CHAR_H+4)*3;
	for(short i=0; i < MachineStatus.axis_no; i++ ){
		INI_DISP_BUF();
		pDispBuf_value += BcdToStrBuf(3, MachineStatus.WORD_SPDMinus[i], pDispBuf);
		FILL_DISP_BUF(0);
		DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
		lx += PARA_DATA_CHARS*ASC_CHAR_W+4;
	}
}
void DispParaSPDFun_q(void)
{
	short lx = PARA_MOTOR_LX + PARA_DATA_CHARS*ASC_CHAR_W+4;
	short ly = PARA_MOTOR_LY+(ASC_CHAR_H+4)*4;
	for(short i=0; i < MachineStatus.axis_no; i++ ){
		INI_DISP_BUF();
		pDispBuf_value += BcdToStrBuf(3, MachineStatus.WORD_SPDFun[i], pDispBuf);
		FILL_DISP_BUF(0);
		DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
		lx += PARA_DATA_CHARS*ASC_CHAR_W+4;
	}
}
void DispParaLOWSPD_q(void)
{
	short lx = PARA_MOTOR_LX + PARA_DATA_CHARS*ASC_CHAR_W+4;
	short ly = PARA_MOTOR_LY+(ASC_CHAR_H+4)*5;
	for(short i=0; i < MachineStatus.axis_no; i++ ){
		INI_DISP_BUF();
		pDispBuf_value += BcdToStrBuf(3, MachineStatus.WORD_LOWSPD[i], pDispBuf);
		FILL_DISP_BUF(0);
		DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
		lx += PARA_DATA_CHARS*ASC_CHAR_W+4;
	}
}
void DispParaSpeed_PMfun_q (void)
{
	DispParaSPDPlus_q();
	DispParaSPDMinus_q();
	DispParaSPDFun_q();
	DispParaLOWSPD_q();
}
void DispParaField_Speed_PMfun_q(void)
{
	//顯示馬達編號及註解
	short lx = PASSWORD_LX-(ASC_CHAR_W*15);
	short ly = PASSWORD_LY;
	INI_DISP_BUF();
	if(MachineStatus.SPDMotorID >= SysInfo.AxisNo ){ 
		Fill_pDispBuf(StrDef_PMFn[idx_language][0]);		
	}
	else{
		Fill_pDispBuf(AxisName[idx_language][MachineStatus.SPDMotorID]);
	}	
	Fill_pDispBuf(StrDef_PMFn[idx_language][1]);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, RED_USR, WIN_TEXT_BCOLOR, DispBuf);
	
	lx = PASSWORD_LX+PARA_DATA_CHARS*ASC_CHAR_W+4;
	ly = PASSWORD_LY;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1, MachineStatus.SPDMotorID, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	
	
	
	
	if(MachineStatus.SPDMotorID >= SysInfo.AxisNo ){
		DispParaSpeed_PMfun_q();
		DispParaExt11_q() ;
		DispParaExtSPDLinkMode_q();
	}
	else{
		short ly = PARA_MOTOR_LY+(ASC_CHAR_H+4)*1;
		for(short i=0; i < ItemNo_bTblSETSPD; i++ ){
			short lx = PARA_MOTOR_LX + PARA_DATA_CHARS*ASC_CHAR_W+4;
			
			INI_DISP_BUF();
			pDispBuf_value += BcdToStrBuf(4, MachineStatus.TblSETSPD[i], pDispBuf);
			FILL_DISP_BUF(0);
			DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
			lx += PARA_DATA_CHARS*ASC_CHAR_W+4;
			
			
			INI_DISP_BUF();
			pDispBuf_value += BcdToStrBuf(3, MachineStatus.TblSPDPlus[i], pDispBuf);
			FILL_DISP_BUF(0);
			DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
			lx += PARA_DATA_CHARS*ASC_CHAR_W+4;


			INI_DISP_BUF();
			pDispBuf_value += BcdToStrBuf(3, MachineStatus.TblSPDMinus[i], pDispBuf);
			FILL_DISP_BUF(0);
			DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
			lx += PARA_DATA_CHARS*ASC_CHAR_W+4;


			INI_DISP_BUF();
			pDispBuf_value += BcdToStrBuf(3, MachineStatus.TblSPDFun[i], pDispBuf);
			FILL_DISP_BUF(0);
			DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
			lx += PARA_DATA_CHARS*ASC_CHAR_W+4;
			
			
			
			ly +=(ASC_CHAR_H+4) ;

		}
	}
}

void DispParaMotorFrame_Speed_PMfun_q (void)
{
	if(MachineStatus.SPDMotorID >= SysInfo.AxisNo ){
		short len = sizeof(MotorSysPara[0])/sizeof(MotorSysPara[0][0]) ;
		for(short i=0 ; i < len ; i++ ){
			BYTE *dptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
			BYTE *tptr = dptr ;
			SAVE_VAL(short, i) ;
			SAVE_CHKSUM
			FILL_PROC_QUEUE(DispParaMotorFrame1_proc,tptr) ;   //顯示馬達編號/馬達名稱
		}
		short len2 = sizeof(MotorSysPara_Speed_PMfun[0])/sizeof(MotorSysPara_Speed_PMfun[0][0]) ;  
		for(short i=0 ; i < len2 ; i++ ){
			BYTE *dptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
			BYTE *tptr = dptr ;
			SAVE_VAL(short, i) ;
			SAVE_CHKSUM
			FILL_PROC_QUEUE(DispParaMotorFrame1_Speed_PMfun_proc,tptr) ;  //顯示各軸加速/各軸減速/加減功能/加減比率
		}
		len = len+len2 ;
		for( short i=0; i < SysInfo.AxisNo; i++ ){
			for(short  j=0; j < len; j+=3 ){
				BYTE *dptr = (BYTE *)farmalloc(3*sizeof(short)+LEN_CHKSUM) ;
				BYTE *tptr= dptr ;
				SAVE_VAL(short , i) ;
				SAVE_VAL(short , j) ;
				SAVE_VAL(short , (j+3) > len ? len : j+3) ;
				SAVE_CHKSUM
				FILL_PROC_QUEUE(DispParaMotorFrame2_proc,tptr) ;  //顯示框框
			}
		} 
		short	ly;
  		
		short lx = PARA_MOTOR_LX + PARA_DATA_CHARS*ASC_CHAR_W+4;
		for( short i=0; i < MachineStatus.axis_no; i++ ){
			ly = PARA_MOTOR_LY;
			INI_DISP_BUF();
			pDispBuf_value += BinToStrBuf(1, i, pDispBuf);
			FILL_DISP_BUF(0);
			DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
  		
			ly += ASC_CHAR_H+4;
			DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, (AxisName[idx_language][i]));
			
			lx += PARA_DATA_CHARS*ASC_CHAR_W+4;
		}
  		
		DispParaExt11Frame_q();
		DispSPDLinkMode_q();
	}
	else{
		short len = sizeof(MotorSysPara_Speed_PMfun2[0])/sizeof(MotorSysPara_Speed_PMfun2[0][0]) ;  
		for(short i=0 ; i < len ; i++ ){
			BYTE *dptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
			BYTE *tptr = dptr ;
			SAVE_VAL(short, i) ;
			SAVE_CHKSUM
			FILL_PROC_QUEUE(DispParaMotorFrame2h_Speed_PMfun_proc,tptr) ;  //顯示組數及速度設定/加速/減速
		}
//		short len2 = sizeof(MotorSysPara_Speed_PMfun[0])/sizeof(MotorSysPara_Speed_PMfun[0][0]) ;  
		{   short i=2 ;
			BYTE *dptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
			BYTE *tptr = dptr ;
			SAVE_VAL(short, i) ;
			SAVE_CHKSUM
			FILL_PROC_QUEUE(DispParaMotorFrame1h_Speed_PMfun_proc,tptr) ;  //顯示加減功能
		}
		len=10+1 ;
		for( short i=-1; i < 4; i++ ){
			for(short  j=1; j < (len); j+=3 ){
				BYTE *dptr = (BYTE *)farmalloc(3*sizeof(short)+LEN_CHKSUM) ;
				BYTE *tptr= dptr ;
				SAVE_VAL(short , i) ;
				SAVE_VAL(short , j) ;
				SAVE_VAL(short , (j+3) > len ? len : j+3) ;
				SAVE_CHKSUM
				FILL_PROC_QUEUE(DispParaMotorFrame2_proc,tptr) ;  //顯示框框
			}
		} 
		short	ly=PARA_MOTOR_LY+ASC_CHAR_H+4;
  		
		short lx = PARA_MOTOR_LX;
		for( short i=0; i < 10; i++ ){
			INI_DISP_BUF();
			short j=i+1 ;
			pDispBuf_value += BinToStrBuf(2, j, pDispBuf);
			FILL_DISP_BUF(0);
			DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
			
			ly += ASC_CHAR_H+4;
		}
	}
}
void DispParaWin_Speed_PMfun_q (short all)
{

	DispMainWindow_q(PARA_ICON, !all);
	DispToolBar_q(PARA_ICON);

	if( all )
	{
		DispParaBox_q();
		DispSPDMotorIDFrame_q ();
		DispParaMotorFrame_Speed_PMfun_q();
		//PrintStringLine_fmt_q(PARA_BOX_LX+2+(ASC_CHAR_W*2), PARA_BOX_RY-2-(ASC_CHAR_H+1)*(5-4), MAGENTA_USR, LIGHTGRAY_USR, Company[idx_language][0]);
		if(MachineStatus.SN[0] == '6'){
			DispSN(0) ;
		}
	}
}
void DispPara_Speed_PMfun_q(void)
{
	DispParaWin_Speed_PMfun_q(1);
	DispParaField_Speed_PMfun_q();
}
//--------------------------------------------------------------------------------------------------------------
//PARA1
void DispParaMotorFrame_q (void)
{
	short len = sizeof(MotorSysPara[0])/sizeof(MotorSysPara[0][0]) ;
	for(short i=0 ; i < len ; i++ ){
		BYTE *dptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE *tptr = dptr ;
		SAVE_VAL(short, i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispParaMotorFrame1_proc,tptr) ;
	}
	
	short len2 = sizeof(MotorSysPara_pass[0])/sizeof(MotorSysPara_pass[0][0]) ;
	for(short i=0 ; i < len2 ; i++ ){
		BYTE *dptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE *tptr = dptr ;
		SAVE_VAL(short, i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispParaMotorFrame1_pass_proc,tptr) ;
	}
	len = len+len2 ;

	for( short i=0; i < SysInfo.AxisNo; i++ ){
		for(short  j=0; j < len; j+=3 ){
			BYTE *dptr = (BYTE *)farmalloc(3*sizeof(short)+LEN_CHKSUM) ;
			BYTE *tptr= dptr ;
			SAVE_VAL(short , i) ;
			SAVE_VAL(short , j) ;
			SAVE_VAL(short , (j+3) > len ? len : j+3) ;
			SAVE_CHKSUM
			FILL_PROC_QUEUE(DispParaMotorFrame2_proc,tptr) ;
		}
	}
}
void DispColPara1_01Frame_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i) ;
	CHK_CHKSUM

	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_MOTOR_LX+i*(PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	short ly = PARA_LINE12_LY;
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, ColPara1_01[idx_language][i]);
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispColPara1_01Frame_q (void)
{
	for(short i=0; i < sizeof(ColPara1_01[0])/sizeof(ColPara1_01[0][0]); i++ ){
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE * dptr= tptr ;
		SAVE_VAL(short , i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispColPara1_01Frame_proc,tptr) ;
	}
}
void DispColPara1_02Frame_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short, i) ;
	CHK_CHKSUM

	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_MOTOR_LX+i*(PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	short ly = PARA_LINE13_LY;
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, ColPara1_02[idx_language][i]);
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispColPara1_02Frame_q (void)
{
	for( short i=0; i < sizeof(ColPara1_02[0])/sizeof(ColPara1_02[0][0]); i++ ){
		BYTE *dptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE *tptr=dptr ;
		SAVE_VAL(short, i );
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispColPara1_02Frame_proc,tptr) ;
	}
}
void DispColPara1_03Frame_proc (void* ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short ,i) ;
	CHK_CHKSUM

	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_MOTOR_LX+i*(PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	short ly = PARA_LINE14_LY;
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, ColPara1_03[idx_language][i]);
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispColPara1_03Frame_q (void)
{
	for(short  i=0; i < sizeof(ColPara1_03[0])/sizeof(ColPara1_03[0][0]); i++ ){
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE *dptr=tptr ;
		SAVE_VAL(short , i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispColPara1_03Frame_proc,tptr) ;
	}
}
void DispColPara1_04Frame_proc (void * ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i ) ;
	CHK_CHKSUM
	
	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_MOTOR_LX+i*(PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	short ly = PARA_LINE14_LY;//PARA_LINE15_LY;
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, ColPara1_04[idx_language][i]);
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispColPara1_04Frame_q (void)
{
	for(short  i=0; i < sizeof(ColPara1_04[0])/sizeof(ColPara1_04[0][0]); i++ ){
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE *dptr=tptr ;
		SAVE_VAL(short, i );
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispColPara1_04Frame_proc,tptr) ;
	}
}
void DispParaWin_q (short all)
{
	DispMainWindow_q(PARA_ICON, !all);
	DispToolBar_q(PARA_ICON);

	if( all )
	{
		DispParaBox_q();
		DispPasswordFrame_q();
		DispParaMotorFrame_q();
		
		DispColPara1_01Frame_q(); //12
		DispColPara1_02Frame_q(); //13
		//DispColPara1_03Frame_q(); //14
		DispColPara1_04Frame_q();	//15
		
#if 0		
		PrintStringLine_fmt_q(PARA_BOX_LX+2+(ASC_CHAR_W*2), PARA_BOX_RY-2-(ASC_CHAR_H+1)*(5-4), MAGENTA_USR, LIGHTGRAY_USR, Company[idx_language][0]);
		if(MachineStatus.SN[0] == '6'){
			DispSN(0) ;
		}
#endif
	}
}

