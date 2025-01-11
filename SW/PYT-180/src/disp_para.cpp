//#include <string>
//#include <iostream>
//using namespace std;
/*
void DispPara4_q(void)
{
	DispParaWin4_q();
	DispParaField4_q();
	DispContextHintFrame_q();
}
void DispParaWin4_q (void)
{
	DispMainWindow_q(PARA_ICON, 0);
	DispToolBar_q(PARA_ICON);

	DispParaBox_q();
	DispPasswordFrame_q(); 
	DispColPara4_01Frame_q (); 
	DispColPara4_02Frame_q ();
	DispColPara4_03Frame_q ();
	DispColPara4_04Frame_q ();
	DispColPara4_05Frame_q ();
	DispColPara4_06Frame_q ();
	DispColPara4_07_01_Frame_q ();
	DispColPara4_07_02_Frame_q ();
}
void DispColPara4_01Frame_q (void)
{
	for(short i=0; i < sizeof(ColPara4_01[0])/sizeof(ColPara4_01[0][0]); i++ ){
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE * dptr= tptr ;
		SAVE_VAL(short , i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispColPara4_01_proc,tptr) ;
	}
}
void DispColPara4_01_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i) ;
	CHK_CHKSUM

	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_MOTOR_LX+i*(PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	short ly = PARA_LINE00_LY;
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, ColPara4_01[idx_language][i]);
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispColPara4_02Frame_q (void)
{
	for(short i=0; i < sizeof(ColPara4_02[0])/sizeof(ColPara4_02[0][0]); i++ ){
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE * dptr= tptr ;
		SAVE_VAL(short , i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispColPara4_02_proc,tptr) ;
	}
}
void DispColPara4_02_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i) ;
	CHK_CHKSUM

	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_MOTOR_LX+i*(PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	short ly = PARA_LINE01_LY;
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, ColPara4_02[idx_language][i]);
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispColPara4_03Frame_q (void)
{
	for(short i=0; i < sizeof(ColPara4_03[0])/sizeof(ColPara4_03[0][0]); i++ ){
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE * dptr= tptr ;
		SAVE_VAL(short , i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispColPara4_03_proc,tptr) ;
	}
}
void DispColPara4_03_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i) ;
	CHK_CHKSUM

	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_MOTOR_LX+i*(PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	short ly = PARA_LINE02_LY;
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, ColPara4_03[idx_language][i]);
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispColPara4_04Frame_q (void)
{
	for(short i=0; i < sizeof(ColPara4_04[0])/sizeof(ColPara4_04[0][0]); i++ ){
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE * dptr= tptr ;
		SAVE_VAL(short , i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispColPara4_04_proc,tptr) ;
	}
}
void DispColPara4_04_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i) ;
	CHK_CHKSUM

	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_MOTOR_LX+i*(PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	short ly = PARA_LINE03_LY;
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, ColPara4_04[idx_language][i]);
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispColPara4_05Frame_q (void)
{
	for(short i=0; i < sizeof(ColPara4_05[0])/sizeof(ColPara4_05[0][0]); i++ ){
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE * dptr= tptr ;
		SAVE_VAL(short , i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispColPara4_05_proc,tptr) ;
	}
}
void DispColPara4_05_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i) ;
	CHK_CHKSUM

	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_MOTOR_LX+i*(PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	short ly = PARA_LINE04_LY;
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, ColPara4_05[idx_language][i]);
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispColPara4_06Frame_q (void)
{
	for(short i=0; i < sizeof(ColPara4_06[0])/sizeof(ColPara4_06[0][0]); i++ ){
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE * dptr= tptr ;
		SAVE_VAL(short , i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispColPara4_06_proc,tptr) ;
	}
}
void DispColPara4_06_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i) ;
	CHK_CHKSUM

	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_MOTOR_LX+i*(PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	short ly = PARA_LINE05_LY;
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, ColPara4_06[idx_language][i]);
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispColPara4_07_01_Frame_q (void)
{
	for(short i=0; i < sizeof(ColPara4_07_01[0])/sizeof(ColPara4_07_01[0][0]); i++ ){
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE * dptr= tptr ;
		SAVE_VAL(short , i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispColPara4_07_01_proc,tptr) ;
	}
}
void DispColPara4_07_01_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i) ;
	CHK_CHKSUM

	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_MOTOR_LX+i*(PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	short ly = PARA_LINE07_LY;
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, ColPara4_07_01[idx_language][i]);
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispColPara4_07_02_Frame_q (void)
{
	for(short i=0; i < sizeof(ColPara4_07_02[0])/sizeof(ColPara4_07_02[0][0]); i++ ){
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE * dptr= tptr ;
		SAVE_VAL(short , i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispColPara4_07_02_proc,tptr) ;
	}
}
void DispColPara4_07_02_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i) ;
	CHK_CHKSUM

	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_MOTOR_LX+i*(PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	short ly = PARA_LINE08_LY;
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, ColPara4_07_02[idx_language][i]);
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispParaField4_q(void)
{
	DispCurPassword_q();
	DispParaContext4_q();
}
void DispParaContext4_q (void)
{
	DispColPara4_01_q();
	DispColPara4_02_q();
	DispColPara4_03_q();
	DispColPara4_04_q();
	DispColPara4_05_q();
	DispColPara4_06_q();
	DispColPara4_07_01_q();
	DispColPara4_07_02_q();
}
void DispColPara4_01_q (void)
{
	short	lx, ly;
	lx = PARA_MOTOR_LX + PARA_DATA_CHARS*ASC_CHAR_W+4;
	ly = PARA_LINE00_LY;	
	//序號
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(6, MachineStatus.NSN, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//啟動密碼
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1, MachineStatus.EnPassWd, pDispBuf);
	FILL_DISP_BUF('-') ;
	Fill_pDispBuf (StrONOFF[idx_language][MachineStatus.EnPassWd]);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
}
void DispColPara4_02_q (void)
{
	short	lx, ly;
	lx = PARA_MOTOR_LX + PARA_DATA_CHARS*ASC_CHAR_W+4;
	ly = PARA_LINE01_LY;	
	//YYYYMMDD
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(8, MachineStatus.MONTH[0], pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//密碼-1
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(8, MachineStatus.PASS[0], pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
}
void DispColPara4_03_q (void)
{
	short	lx, ly;
	lx = PARA_MOTOR_LX + PARA_DATA_CHARS*ASC_CHAR_W+4;
	ly = PARA_LINE02_LY;	
	//YYYYMMDD
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(8, MachineStatus.MONTH[1], pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//密碼-2
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(8, MachineStatus.PASS[1], pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
}
void DispColPara4_04_q (void)
{
	short	lx, ly;
	lx = PARA_MOTOR_LX + PARA_DATA_CHARS*ASC_CHAR_W+4;
	ly = PARA_LINE03_LY;	
	//YYYYMMDD
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(8, MachineStatus.MONTH[2], pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//密碼-3
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(8, MachineStatus.PASS[2], pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
}
void DispColPara4_05_q (void)
{
	short	lx, ly;
	lx = PARA_MOTOR_LX + PARA_DATA_CHARS*ASC_CHAR_W+4;
	ly = PARA_LINE04_LY;	
	//YYYYMMDD
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(8, MachineStatus.MONTH[3], pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//密碼-4
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(8, MachineStatus.PASS[3], pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
}
void DispColPara4_06_q (void)
{
	short	lx, ly;
	lx = PARA_MOTOR_LX + PARA_DATA_CHARS*ASC_CHAR_W+4;
	ly = PARA_LINE05_LY;	
	//YYYYMMDD
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(8, MachineStatus.MONTH[4], pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//密碼-5
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(8, MachineStatus.PASS[4], pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
}
void DispColPara4_07_01_q (void)
{		
	short	lx, ly;
	lx = PARA_MOTOR_LX + PARA_DATA_CHARS*ASC_CHAR_W+4;
	ly = PARA_LINE07_LY;
	//系統日期
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(8, MachineStatus.SystemDate, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//系統時間
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(2, MachineStatus.SystemTime[0], pDispBuf);
	FILL_DISP_BUF(':') ;
	pDispBuf_value += BcdToStrBuf(2, MachineStatus.SystemTime[1], pDispBuf);
	FILL_DISP_BUF(':') ;
	pDispBuf_value += BcdToStrBuf(2, MachineStatus.SystemTime[2], pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
}                     
void DispColPara4_07_02_q (void)
{ 		
	short	lx, ly;
	lx = PARA_MOTOR_LX + PARA_DATA_CHARS*ASC_CHAR_W+4;
	ly = PARA_LINE08_LY;
	//設定日期
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(4, MachineStatus.SetSystemDate[0], pDispBuf);
	pDispBuf_value += BcdToStrBuf(2, MachineStatus.SetSystemDate[1], pDispBuf);
	pDispBuf_value += BcdToStrBuf(2, MachineStatus.SetSystemDate[2], pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//設定時間
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(2, MachineStatus.SetSystemTime[0], pDispBuf);
	FILL_DISP_BUF(':') ;
	pDispBuf_value += BcdToStrBuf(2, MachineStatus.SetSystemTime[1], pDispBuf);
	FILL_DISP_BUF(':') ;
	pDispBuf_value += BcdToStrBuf(2, MachineStatus.SetSystemTime[2], pDispBuf);	
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
}
void DispPara3_q(void)
{
	DispParaWin3_q();
	DispParaField3_q();
	DispContextHintFrame_q();
}
void DispParaWin3_q (void)
{
	DispMainWindow_q(PARA_ICON, 0);
	DispToolBar_q(PARA_ICON);

	DispParaBox_q();
	DispPasswordFrame_q(); 
	//DispPara3Frame_q();
	DispColPara3_01Frame_q (); 
}
void DispColPara3_01Frame_q (void)
{
	for(short i=0; i < sizeof(ColPara3_01[0])/sizeof(ColPara3_01[0][0]); i++ ){
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE * dptr= tptr ;
		SAVE_VAL(short , i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispColPara3_01_proc,tptr) ;
	}
}
void DispColPara3_01_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i) ;
	CHK_CHKSUM

	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_MOTOR_LX+i*(PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	short ly = PARA_LINE00_LY;
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, ColPara3_01[idx_language][i]);
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}

void DispParaField3_q(void)
{
	DispCurPassword_q();
	DispParaContext3_q();
}
void DispParaContext3_q (void)
{
	//DispMotorNo_q(0);
	//DispMotorName_q(1);	
	DispColPara3_01_q();
}
void DispColPara3_01_q (void)
{
	short	lx, ly;
	lx = PARA_MOTOR_LX + PARA_DATA_CHARS*ASC_CHAR_W+4;
	ly = PARA_LINE00_LY;	
	//開啟軸數
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1, MachineStatus.AxisNo, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
}

void DispPara2_q(void)
{
	DispParaWin2_q();
	DispParaField2_q();
	DispContextHintFrame_q();  //藍色底框
}
void DispParaWin2_q (void)
{
	DispMainWindow_q(PARA_ICON, 0);
	DispToolBar_q(PARA_ICON);

	DispParaBox_q();
	DispPasswordFrame_q(); 
	DispPara2Frame_q(); 
	DispParaTDecFrame_q(); 			//11
	DispColPara2_02Frame_q ();	//12
	DispColPara2_03Frame_q ();	//13
	DispColPara2_04Frame_q ();	//14
	DispColPara2_05Frame_q ();	//15
}
void DispParaTDecFrame_q (void)
{
	for(short i=0; i < sizeof(TDecPara[0])/sizeof(TDecPara[0][0]); i++ ){
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE * dptr= tptr ;
		SAVE_VAL(short , i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispParaTDecFrame1_proc,tptr) ;
	}
}
void DispColPara2_02Frame_q (void)
{
	for(short i=0; i < sizeof(ColPara2_02[0])/sizeof(ColPara2_02[0][0]); i++ ){
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE * dptr= tptr ;
		SAVE_VAL(short , i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispColPara2_02_proc,tptr) ;
	}
}
void DispColPara2_02_proc (void *ptr)
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
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, ColPara2_02[idx_language][i]);
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispColPara2_03_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i) ;
	CHK_CHKSUM

	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_MOTOR_LX+i*(PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	short ly = PARA_LINE13_LY;
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, ColPara2_03[idx_language][i]);
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispColPara2_03Frame_q (void)
{
	for(short i=0; i < sizeof(ColPara2_03[0])/sizeof(ColPara2_03[0][0]); i++ ){
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE * dptr= tptr ;
		SAVE_VAL(short , i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispColPara2_03_proc,tptr) ;
	}
}
void DispColPara2_04_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i) ;
	CHK_CHKSUM

	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_MOTOR_LX+i*(PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	short ly = PARA_LINE14_LY;
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, ColPara2_04[idx_language][i]);
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispColPara2_04Frame_q (void)
{
	for(short i=0; i < sizeof(ColPara2_04[0])/sizeof(ColPara2_04[0][0]); i++ ){
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE * dptr= tptr ;
		SAVE_VAL(short , i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispColPara2_04_proc,tptr) ;
	}
}
void DispColPara2_05_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i) ;
	CHK_CHKSUM

	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_MOTOR_LX+i*(PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	short ly = PARA_LINE15_LY; //改
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, ColPara2_05[idx_language][i]);//改
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispColPara2_05Frame_q (void)
{
	for(short i=0; i < sizeof(ColPara2_05[0])/sizeof(ColPara2_05[0][0]); i++ ){//改
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE * dptr= tptr ;
		SAVE_VAL(short , i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispColPara2_05_proc,tptr) ;//改
	}
}
void DispParaTDecFrame1_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , i) ;
	CHK_CHKSUM

	Frame_t frame;

	DefaultButtonStyle(&frame);
	frame.type = -1;
	frame.main_col = PARA_TITLE_BCOLOR;

	short lx = PARA_MOTOR_LX+i*(PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	short ly = PARA_LINE11_LY;
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, TDecPara[idx_language][i]);
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispMotorPara2_pass_proc (void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short ,idx) ;
	CHK_CHKSUM
	DispParaMotorFrame_com(idx+2,MotorPara2_pass[idx_language][idx]) ;
	farfree(ptr) ;
}
void DispPara2Frame_q (void)
{
	short len = sizeof(MotorSysPara[0])/sizeof(MotorSysPara[0][0]) ;
	for(short i=0 ; i < len ; i++ ){
		BYTE *dptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE *tptr = dptr ;
		SAVE_VAL(short, i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispParaMotorFrame1_proc,tptr) ;
	}
	
	short len2 = sizeof(MotorPara2_pass[0])/sizeof(MotorPara2_pass[0][0]) ;
	for(short i=0 ; i < len2 ; i++ ){
		BYTE *dptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE *tptr = dptr ;
		SAVE_VAL(short, i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispMotorPara2_pass_proc,tptr) ;
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

void DispParaField2_q(void)
{
	DispCurPassword_q();
	DispParaContext2_q();
}

void DispParaContext2_q (void)
{
	DispMotorNo_q(0);
	DispMotorName_q(1);
	DispParaZrtPos_q(2);
	DispParaZrtCye_q(3);
	DispParaGEAR0_q(4);
	DispParaGEAR1_q(5);
	DispParaENCR0_q(6);
	DispParaENCR1_q(7);
	DispParaABDIR_q(8) ;
	DispSensorHighLow_q(9) ;
	DispChkToPos_q(10) ;	
	DispParaTDec_q(); 	 //11
	DispColPara2_02_q(); //12
	DispColPara2_03_q(); //13
	DispColPara2_04_q(); //14
	DispColPara2_05_q(); //15
}

void DispMotorNo_q(int line)
{
	short	ly = PARA_MOTOR_LY+(ASC_CHAR_H+4)*line;
	short lx;	
	for(uint8 axis=0; axis < MachineStatus.axis_no; axis++ ){
		lx = PARA_MOTOR_LX + (PARA_DATA_CHARS*ASC_CHAR_W+4)*(axis+1);	
		INI_DISP_BUF();
		pDispBuf_value += BinToStrBuf(1, axis, pDispBuf);
		FILL_DISP_BUF(0);
		DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);	
	}	
}
void DispMotorName_q(int line)
{
	short	ly = PARA_MOTOR_LY+(ASC_CHAR_H+4)*line;
	short lx;	
	for(uint8 axis=0; axis < MachineStatus.axis_no; axis++ ){
		lx = PARA_MOTOR_LX + (PARA_DATA_CHARS*ASC_CHAR_W+4)*(axis+1);
		DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, (AxisName[idx_language][axis]));	
	}
}
void DispParaZrtPos_q(int line)
{
	short	ly = PARA_MOTOR_LY+(ASC_CHAR_H+4)*line;
	short lx;	
	
	for(uint8 axis=0; axis < MachineStatus.axis_no; axis++ ){
		lx = PARA_MOTOR_LX + (PARA_DATA_CHARS*ASC_CHAR_W+4)*(axis+1);
		INI_DISP_BUF();		
		pDispBuf_value += BcdToStrBuf(8, MachineStatus.ZrtPos[axis], pDispBuf);
		FILL_DISP_BUF(0);
		DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	}
}
void DispParaZrtCye_q(int line)
{
	short	ly = PARA_MOTOR_LY+(ASC_CHAR_H+4)*line;
	short lx;	
	
	for(uint8 axis=0; axis < MachineStatus.axis_no; axis++ ){
		lx = PARA_MOTOR_LX + (PARA_DATA_CHARS*ASC_CHAR_W+4)*(axis+1);
		INI_DISP_BUF();
		if((MachineStatus.ZrtCye_sign[axis] & 0x7f) ==PLUS_SIGN){ 
			FILL_DISP_BUF('+'); 
		}
		else { 
			FILL_DISP_BUF('-'); 
		}
		pDispBuf_value += BcdToStrBuf(5, MachineStatus.ZrtCye[axis], pDispBuf);
		FILL_DISP_BUF(0);
		DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	}
}
void DispParaGEAR0_q(int line)
{
	short	ly = PARA_MOTOR_LY+(ASC_CHAR_H+4)*line;
	short lx;	
	
	for(uint8 axis=0; axis < MachineStatus.axis_no; axis++ ){
		lx = PARA_MOTOR_LX + (PARA_DATA_CHARS*ASC_CHAR_W+4)*(axis+1);
		INI_DISP_BUF();
		pDispBuf_value += BcdToStrBuf(5, MachineStatus.GEAR0[axis], pDispBuf);
		FILL_DISP_BUF(0);
		DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	}
}
void DispParaGEAR1_q(int line)
{
	short	ly = PARA_MOTOR_LY+(ASC_CHAR_H+4)*line;
	short lx;	
	
	for(uint8 axis=0; axis < MachineStatus.axis_no; axis++ ){
		lx = PARA_MOTOR_LX + (PARA_DATA_CHARS*ASC_CHAR_W+4)*(axis+1);
		INI_DISP_BUF();
		pDispBuf_value += BcdToStrBuf(5, MachineStatus.GEAR1[axis], pDispBuf);
		FILL_DISP_BUF(0);
		DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	}
}
void DispParaENCR0_q(int line)
{
	short	ly = PARA_MOTOR_LY+(ASC_CHAR_H+4)*line;
	short lx;	
	
	for(uint8 axis=0; axis < MachineStatus.axis_no; axis++ ){
		lx = PARA_MOTOR_LX + (PARA_DATA_CHARS*ASC_CHAR_W+4)*(axis+1);
		INI_DISP_BUF();
		pDispBuf_value += BcdToStrBuf(4, MachineStatus.ENCR0[axis], pDispBuf);
		FILL_DISP_BUF(0);
		DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	}
}
void DispParaENCR1_q(int line)
{
	short	ly = PARA_MOTOR_LY+(ASC_CHAR_H+4)*line;
	short lx;
	
	for(uint8 axis=0; axis < MachineStatus.axis_no; axis++ ){
		lx = PARA_MOTOR_LX + (PARA_DATA_CHARS*ASC_CHAR_W+4)*(axis+1);
		INI_DISP_BUF();
		pDispBuf_value += BcdToStrBuf(4, MachineStatus.ENCR1[axis], pDispBuf);
		FILL_DISP_BUF(0);
		DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	}
}
void DispParaABDIR_q(int line)
{
	short	ly = PARA_MOTOR_LY+(ASC_CHAR_H+4)*line;
	short lx;
	
	for(uint8 axis=0; axis < MachineStatus.axis_no; axis++ ){
		lx = PARA_MOTOR_LX + (PARA_DATA_CHARS*ASC_CHAR_W+4)*(axis+1);
		INI_DISP_BUF();
		pDispBuf_value += BcdToStrBuf(1, MachineStatus.ABDir[axis], pDispBuf);
		FILL_DISP_BUF(0);
		DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
		lx += PARA_DATA_CHARS*ASC_CHAR_W+4;
	}
}
void DispSensorHighLow_q(int line)
{
	short	ly = PARA_MOTOR_LY+(ASC_CHAR_H+4)*line;
	short lx;
	
	for(uint8 axis=0; axis < MachineStatus.axis_no; axis++ ){
		lx = PARA_MOTOR_LX + (PARA_DATA_CHARS*ASC_CHAR_W+4)*(axis+1);
		INI_DISP_BUF();
		pDispBuf_value += BcdToStrBuf(1, MachineStatus.SensorHighLow[axis], pDispBuf);
		FILL_DISP_BUF('-') ;
		Fill_pDispBuf (StrHighLow[idx_language][MachineStatus.SensorHighLow[axis]]);
		FILL_DISP_BUF(0);
		DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
		lx += PARA_DATA_CHARS*ASC_CHAR_W+4;
	}
}
void DispChkToPos_q(int line)
{
	short	ly = PARA_MOTOR_LY+(ASC_CHAR_H+4)*line;
	short lx;
	
	for(uint8 axis=0; axis < MachineStatus.axis_no; axis++ ){
		lx = PARA_MOTOR_LX + (PARA_DATA_CHARS*ASC_CHAR_W+4)*(axis+1);
		INI_DISP_BUF();
		pDispBuf_value += BcdToStrBuf(4, MachineStatus.ChkToPos[axis], pDispBuf);
		Fill_pDispBuf("週期", "cyc." ,"cyc.");
		FILL_DISP_BUF(0);
		DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
		lx += PARA_DATA_CHARS*ASC_CHAR_W+4;
	}
}
void DispParaTDec_q (void)
{
	short	lx, ly;
	lx = PARA_MOTOR_LX + PARA_DATA_CHARS*ASC_CHAR_W+4;
	ly = PARA_LINE11_LY;
	//T1減距離
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(6, MachineStatus.TDecDisA[0], pDispBuf);
	ADD_DOT_UNIT(AXIS_Y);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//T2減距離
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(6, MachineStatus.TDecDisA[1], pDispBuf);
	ADD_DOT_UNIT(AXIS_Y);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//T3減距離
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(6, MachineStatus.TDecDisA[2], pDispBuf);
	ADD_DOT_UNIT(AXIS_Y);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//T4減距離
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(6, MachineStatus.TDecDisA[3], pDispBuf);
	ADD_DOT_UNIT(AXIS_Y);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
}
void DispColPara2_02_q (void)
{
	short	lx, ly;
	lx = PARA_MOTOR_LX + PARA_DATA_CHARS*ASC_CHAR_W+4;
	ly = PARA_LINE12_LY;	
	//手輪速度
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(2, MachineStatus.man_gain, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//送線間隙
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(4, MachineStatus.WireGap, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//LINE
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(3, MachineStatus.LINE, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf) ;
	//LOGO
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1, MachineStatus.Delay, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);	
}
void DispColPara2_03_q (void)
{
	short	lx, ly;
	lx = PARA_MOTOR_LX + PARA_DATA_CHARS*ASC_CHAR_W+4;
	ly = PARA_LINE13_LY;		
	//單一生產
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1, MachineStatus.ONE, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//鎖生產量
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1, MachineStatus.dec_dist, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//轉芯校正
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1,MachineStatus.ROTQ_MDY , pDispBuf);
	FILL_DISP_BUF('-') ;
	Fill_pDispBuf (StrONOFF[idx_language][MachineStatus.ROTQ_MDY]);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//捲取校正
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1,MachineStatus.SPIN_MDY , pDispBuf);
	FILL_DISP_BUF('-') ;
	Fill_pDispBuf (StrONOFF[idx_language][MachineStatus.SPIN_MDY]);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
}
void DispColPara2_04_q (void)
{
	short	lx, ly;
	lx = PARA_MOTOR_LX + PARA_DATA_CHARS*ASC_CHAR_W+4;
	ly = PARA_LINE14_LY;
	//批量
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(7, MachineStatus.BATCHn, pDispBuf);
	ADD_MINUS_01(pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//模擬FAST
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1, MachineStatus.SimFast, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//X-編碼器
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1, MachineStatus.X_Encoder, pDispBuf);
	FILL_DISP_BUF('-') ;
	Fill_pDispBuf (StrX_Encoder[idx_language][MachineStatus.X_Encoder]);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//馬達型號
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1, MachineStatus.TAIDAMotor, pDispBuf);
	FILL_DISP_BUF('-') ;
	Fill_pDispBuf (StrTAIDAMotor[idx_language][MachineStatus.TAIDAMotor]);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
}
void DispColPara2_05_q (void)
{
	short	lx, ly;
	lx = PARA_MOTOR_LX + PARA_DATA_CHARS*ASC_CHAR_W+4;
	ly = PARA_LINE15_LY;
	//寸動盒T
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(2, MachineStatus.SwitchT, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//探針延遲
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1, MachineStatus.TDelay, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);	
}
//5215********************************************************************************************************
void DispPara_q(void)
{
	DispParaWin_q(1);
	DispParaField_q();
}
void DispParaField_q(void)
{
	DispCurPassword_q();
	//FORCE_PROC_QUEUE ;
	DispParaContext_q(); //printf content
	DispContextHintFrame_q();
	
}

void DispParaContext_q (void)
{
	DispMotorNo_q(0); //馬達編號
	DispMotorName_q(1); //馬達名稱
	DispMotorGrads_q(2); //馬達格數
	DispnMotorType_q(3); //馬達型態
	DispMotFunc_q(4); //馬達功能
	DispHomeSeq_q(5); //原點順序
	DispParaZrtMode_q(6); //原點模式
	DispParaZRTSET_q(7); //新設原點
	DispZrtCorr_q(8); //原點對應
	DispParaMAX_q(9); //最大極限
	DispParaMIN_q(10); //最小極限
	DispParaMotorNEAR_q(11) ;//回報信號
	DispColPara1_01_q();	//12
	DispColPara1_02_q();	//13
	//DispColPara1_03_q();	//14
	DispColPara1_04_q();	//15
}
void DispMotorGrads_q(int line)
{
	short	ly = PARA_MOTOR_LY+(ASC_CHAR_H+4)*line;
	short lx;	
	for(uint8 axis=0; axis < MachineStatus.axis_no; axis++ ){
		lx = PARA_MOTOR_LX + (PARA_DATA_CHARS*ASC_CHAR_W+4)*(axis+1);
		INI_DISP_BUF();
		pDispBuf_value += BcdToStrBuf(MOTOR_GRADS_BCD, MachineStatus.motor_grads[axis], pDispBuf);
		FILL_DISP_BUF(0);
		DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	}
}
void DispnMotorType_q(int line)
{
	short	ly = PARA_MOTOR_LY+(ASC_CHAR_H+4)*line;
	short lx;	
	for(uint8 axis=0; axis < MachineStatus.axis_no; axis++ ){
		lx = PARA_MOTOR_LX + (PARA_DATA_CHARS*ASC_CHAR_W+4)*(axis+1);
		INI_DISP_BUF();
		pDispBuf_value += BcdToStrBuf(1, MachineStatus.nMotorType[axis], pDispBuf);
		//FILL_DISP_BUF('-') ;
		//Fill_pDispBuf(StrnMotorType[idx_language][MachineStatus.nMotorType[axis]]);
		FILL_DISP_BUF(0);
		DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	}
}

void DispMotFunc_q(int line)
{
	short	ly = PARA_MOTOR_LY+(ASC_CHAR_H+4)*line;
	short lx;	
	for(uint8 axis=0; axis < MachineStatus.axis_no; axis++ ){
		lx = PARA_MOTOR_LX + (PARA_DATA_CHARS*ASC_CHAR_W+4)*(axis+1);
		INI_DISP_BUF();
		pDispBuf_value += BcdToStrBuf(2, MachineStatus.MotFunc[axis], pDispBuf);
		FILL_DISP_BUF(0);
		DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	}
}
void DispHomeSeq_q(int line)
{
	short	ly = PARA_MOTOR_LY+(ASC_CHAR_H+4)*line;
	short lx;	
	for(uint8 axis=0; axis < MachineStatus.axis_no; axis++ ){
		lx = PARA_MOTOR_LX + (PARA_DATA_CHARS*ASC_CHAR_W+4)*(axis+1);
		INI_DISP_BUF();
		if((MachineStatus.home_seq_sign[axis]& 0x7f) ==PLUS_SIGN){ 
			FILL_DISP_BUF('+'); 
		}
		else { 
			FILL_DISP_BUF('-'); 
		}
		pDispBuf_value += BcdToStrBuf(1, MachineStatus.home_seq[axis], pDispBuf);
		FILL_DISP_BUF(0);
		DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	}
}
void DispParaZrtMode_q(int line)
{
	short	ly = PARA_MOTOR_LY+(ASC_CHAR_H+4)*line;
	short lx;

	for(uint8 axis=0; axis < MachineStatus.axis_no; axis++ ){
		lx = PARA_MOTOR_LX + (PARA_DATA_CHARS*ASC_CHAR_W+4)*(axis+1);
		INI_DISP_BUF();
		if((CHK_ROTATE_A(axis))  || (axis== AXIS_Y)){
			Fill_pDispBuf("      ") ;
		}
		else{
			pDispBuf_value += BcdToStrBuf(1, MachineStatus.ZrtMode[axis], pDispBuf);
			FILL_DISP_BUF('-') ;
			Fill_pDispBuf(StrZrtMode[idx_language][MachineStatus.ZrtMode[axis]]);
		}
		FILL_DISP_BUF(0);
		DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	}
}
void DispParaZRTSET_q(int line)
{
	short	ly = PARA_MOTOR_LY+(ASC_CHAR_H+4)*line;
	short lx;
	
	for(uint8 axis=0; axis < MachineStatus.axis_no; axis++ ){
		lx = PARA_MOTOR_LX + (PARA_DATA_CHARS*ASC_CHAR_W+4)*(axis+1);
		INI_DISP_BUF();
		if((MachineStatus.ZRTSET_sign[axis] & 0x7f) ==PLUS_SIGN){ 
			FILL_DISP_BUF('+'); 
		}
		else { 
			FILL_DISP_BUF('-'); 
		}
		pDispBuf_value += BcdToStrBuf(5, MachineStatus.ZRTSET[axis], pDispBuf);
		FILL_DISP_BUF(0);
		DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	}
}
void DispZrtCorr_q(int line)
{
	short	ly = PARA_MOTOR_LY+(ASC_CHAR_H+4)*line;
	short lx;
	
	for(uint8 axis=0; axis < MachineStatus.axis_no; axis++ ){
		lx = PARA_MOTOR_LX + (PARA_DATA_CHARS*ASC_CHAR_W+4)*(axis+1);
		INI_DISP_BUF();
		if( (axis== AXIS_Y)){
			Fill_pDispBuf("      ") ;
		}
//#ifdef HNCNC6
//		else if ((axis== AXIS_D)){
//			Fill_pDispBuf("      ") ;
//		}
//#endif
		else{
			pDispBuf_value += BcdToStrBuf(1, MachineStatus.ZrtCorr[axis], pDispBuf);
		}
		FILL_DISP_BUF(0);
		DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	}
}
void DispParaMAX_q(int line)
{
	short	ly = PARA_MOTOR_LY+(ASC_CHAR_H+4)*line;
	short lx;
	
	for(uint8 axis=0; axis < MachineStatus.axis_no; axis++ ){
		lx = PARA_MOTOR_LX + (PARA_DATA_CHARS*ASC_CHAR_W+4)*(axis+1);
		INI_DISP_BUF();
		if((MachineStatus.Max_sign[axis] & 0x7f) ==PLUS_SIGN){ 
			FILL_DISP_BUF('+'); 
		}
		else { 
			FILL_DISP_BUF('-'); 
		}
		pDispBuf_value += BcdToStrBuf(6, MachineStatus.Max[axis], pDispBuf);
		ADD_DOT_UNIT(axis) ;
		FILL_DISP_BUF(0);
		DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	}
}
void DispParaMIN_q(int line)
{
	short	ly = PARA_MOTOR_LY+(ASC_CHAR_H+4)*line;
	short lx;
	
	for(uint8 axis=0; axis < MachineStatus.axis_no; axis++ ){
		lx = PARA_MOTOR_LX + (PARA_DATA_CHARS*ASC_CHAR_W+4)*(axis+1);
		INI_DISP_BUF();
		if((MachineStatus.Min_sign[axis] & 0x7f) ==PLUS_SIGN){ 
			FILL_DISP_BUF('+'); 
		}
		else { 
			FILL_DISP_BUF('-'); 
		}
		pDispBuf_value += BcdToStrBuf(6, MachineStatus.Min[axis], pDispBuf);
		ADD_DOT_UNIT(axis) ;
		FILL_DISP_BUF(0);
		DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	}
}
void DispParaMotorNEAR_q(int line)
{
	short	ly = PARA_MOTOR_LY+(ASC_CHAR_H+4)*line;
	short lx;
	
	for(uint8 axis=0; axis < MachineStatus.axis_no; axis++ ){
		lx = PARA_MOTOR_LX + (PARA_DATA_CHARS*ASC_CHAR_W+4)*(axis+1);
		INI_DISP_BUF();
		FILL_DISP_BUF('0'+MachineStatus.bMotorNEAR[axis]) ;
		FILL_DISP_BUF(0);
		DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	}
}
//5215個別參數:
void DispColPara1_01_q (void)
{
	short	lx, ly;
	lx = PARA_MOTOR_LX + PARA_DATA_CHARS*ASC_CHAR_W+4;
	ly = PARA_LINE12_LY;
	//語言設定
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1, MachineStatus.language, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//機器型號
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(3, MachineStatus.Type, pDispBuf);
	FILL_DISP_BUF(' ') ;
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);		
	//Y-編碼器
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1, MachineStatus.Y_Encoder, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//回報信號
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	//INI_DISP_BUF();
	//pDispBuf_value += BcdToStrBuf(3, MachineStatus.MotorNEAR, pDispBuf);
	//FILL_DISP_BUF(0);
	//DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
}
void DispColPara1_02_q (void)
{
	short	lx, ly;
	lx = PARA_MOTOR_LX + PARA_DATA_CHARS*ASC_CHAR_W+4;
	ly = PARA_LINE13_LY;
	//安全門
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1, MachineStatus.safety_door, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//安全裝置
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(2,MachineStatus.bysafe_plugin , pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//警鈴裝置
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1, MachineStatus.BUZZER, pDispBuf);
	FILL_DISP_BUF('-') ;
	Fill_pDispBuf (StrONOFF[idx_language][MachineStatus.BUZZER]);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//切刀距離
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(6, MachineStatus.CutDist, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
}
void DispColPara1_03_q (void)
{
	short	lx, ly;
	lx = PARA_MOTOR_LX + PARA_DATA_CHARS*ASC_CHAR_W+4;
	ly = PARA_LINE14_LY;
	//整定速度
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(5, MachineStatus.repair_y, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//整定距離
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(2, MachineStatus.dist_y, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//Y軸齒比0
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(6, MachineStatus.gear_y[0], pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//Y軸齒比1
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(6, MachineStatus.gear_y[1], pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
}
void DispColPara1_04_q (void)
{
	short	lx, ly;
	lx = PARA_MOTOR_LX + PARA_DATA_CHARS*ASC_CHAR_W+4;
	ly = PARA_LINE14_LY;//PARA_LINE15_LY
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1, MachineStatus.G2Mode, pDispBuf);
	FILL_DISP_BUF('-') ;
	Fill_pDispBuf(StrG2Mode[idx_language][MachineStatus.G2Mode]);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//速度補正
	//INI_DISP_BUF();
	//pDispBuf_value += BcdToStrBuf(2, MachineStatus.repair_spd, pDispBuf);
	//FILL_DISP_BUF(0);
	//DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//距離補正
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1, MachineStatus.SPDMode, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//INI_DISP_BUF();
	//pDispBuf_value += BcdToStrBuf(2, MachineStatus.repair_dst, pDispBuf);
	//FILL_DISP_BUF(0);
	//DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//G2  模式
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	
	//SPD 模式
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;

}
//5215********************************************************************************************************

void DispContextHintFrame_q (void)
{
	WinStyle_t ws;

	DefaultButtonStyle(&(ws.frame));
	ws.frame.main_col	= BLUE_USR;
	ws.frame.type		= 1;
	ws.lx				= PARA_MOTOR_LX;
#ifndef HNCNC6
	ws.rx				= ws.lx+(PARA_DATA_CHARS*ASC_CHAR_W+4)*9;
	ws.ly				= PARA_LINE21_LY;
	ws.ry				= PARA_LINE23_LY;
#else
	ws.rx				= ws.lx+(PARA_DATA_CHARS*ASC_CHAR_W+4)*8;
	ws.ly				= PARA_LINE16_LY;
	ws.ry				= PARA_LINE18_LY;
#endif


	DrawWindow_q(&ws);
}
*/
/*
//0~67:line1,68~line2
string ContextHintStr[] = {		
	//00************************************************************************************************************************************	
	"[馬達格數]:機構運轉一圈時的格數參考值,視齒輪比而定.",
	"[MOT GRID]:",
	//01************************************************************************************************************************************	
	"[馬達型態]:依馬達廠牌設定,大部分情況:0-三洋,1-安川 馬達.",
	"[MOT TYPE]:",										
	//02************************************************************************************************************************************
	"[馬達\xa5\x5c能]:0-凸輪,1-送料,2-轉芯,3-翻線,4-捲取,5-切刀,6-夾耳,7-滑座,8-翻線(修整,需配合參數:Y-編碼器), 9-折角, 10-平移.",
	"[MOT FUNC]:0-CAM,1-FEED,2-ROTQ,3-ROTW,4-SPIN,5-CUT,6-HOOK,7-SLIDE, 8-ROTW(repair with \"Y-Encode\"), 9-ANGLE 10-STM.",		
	//03************************************************************************************************************************************
	"[原點順序]:執行回原點的運轉方向及先後順序,+表示正向回原點,-表示反向回原點;數字小的先回原點,數字一樣的同時回原點.",
	"[HOME SEQ]:",
	//04************************************************************************************************************************************
	"[原點模式]:0-直接,1-間接,2-立即,3-轉線;模式設定與馬達接線方式有關, 詳細內容請參考說明檔.",
	"[ZRT MODE]:0-DIRECT, 1-INDIRT, 2-IMMED, 3-ROTW",
	//05************************************************************************************************************************************
	"[新設原點]:回原點後再偏移的格數值,+/-表示偏移的方向.",
	"[ZRT SET]:",
	//06************************************************************************************************************************************
	"[原點對應]:適用於原點模式為1-間接,2-立即;原點IO信號對應.",
	"[ZRT CORR]:",
	//07************************************************************************************************************************************
	"[最大極限]:各軸往正方向能移動的最大距離,編輯程式及手動時檢查.",
	"[AXIS MAX]:",
	//08************************************************************************************************************************************
	"[最小極限]:各軸往負方向能移動的最大距離,編輯程式及手動時檢查.",
	"[AXIS min]:",


	
	//09************************************************************************************************************************************
	"[語言設定]:0-英文,1-繁體中文,2-簡體中文,3-義大利文.",
	"[LANGUAGE]:",
	//10************************************************************************************************************************************
	"[機器型號]:依客戶機器型號設定.",
	"[TYPE NO.]:",
	//11************************************************************************************************************************************
	"[Y-編碼器]:",
	"[Y-Encode]:",
	//12************************************************************************************************************************************
	"[回報信號]:參數設定000時:馬達線未接會回報錯誤;設定255時:馬達線未接 不會回報錯誤.詳細內容請參考說明檔.",
	"[MOT NEAR]:",	
	//13************************************************************************************************************************************
	"[安全門]:有加裝安全門時,可選擇開啟\xa5\x5c能;0-關閉,1-開啟.",
	"[SHIELD]:",
	//14************************************************************************************************************************************
	"[安全裝置]:設定安全裝置的開啟與靈敏度;00-關閉,01-開啟(最靈敏),數字 越大越不靈敏.",
	"[SENSOR]:",
	//15************************************************************************************************************************************
	"[警示燈]:機台發生錯誤訊息時,以黃燈閃爍作為警示;0-關閉,1-開啟,IO輸出點為(BZ).僅適用於軟體v3.52以後版本.",
	"[W.LIGHT]:",
	//16************************************************************************************************************************************
	"[切刀距離]:伺服切刀固定來回的移動距離,最大值設限15000格,修改此參數 系統會自動將[切刀距離]填入切刀軸[最大極限],當作軟體極限設定.",
	"[Cut Dist]:",	
	//17************************************************************************************************************************************
	"[速率模式]:0-超速率(儘量使X軸保持生產速率,其他軸可能超過生產速率)   1-均速率(各軸都不超過生產速率)   2-自訂(自訂各軸生產速率)",
	"[RateMode]:",	
	//18************************************************************************************************************************************
	"[SPD 模式]:0-SPD可輸入2位數;1-SPD可輸入3位數,最低位代表小數點後的數字",
	"[SPD Mode]:",
	//19************************************************************************************************************************************
	"[Y軸齒比0]:若送線軸齒比非各機型內部預設值,需手動輸入.",
	"[Y-GEAR0]:",
	//20************************************************************************************************************************************
	"[Y軸齒比1]:若送線軸齒比非各機型內部預設值,需手動輸入.",
	"[Y-GEAR1]:",	
	//21************************************************************************************************************************************
	"[速度補正]:",
	"[SPEED UP]:",
	//22************************************************************************************************************************************
	"[距離補正]:",
	"[DIST UP ]:",
	//23************************************************************************************************************************************
	"[整定速度]:送線軸整定\xa5\x5c能,其值越大整定速度越慢.僅適用於PCB3號板2014年以後版本.",
	"[Y-REPAIR]:",
	//24************************************************************************************************************************************
	"[回報信號]:參數設定0時:馬達線未接會回報錯誤;設定1時:馬達線未接不會 回報錯誤.詳細內容請參考說明檔",
	"[NOT NEAR]:",
	//25************************************************************************************************************************************
	"[整定距離]:送線軸整定\xa5\x5c能,其值越大越早開始整定,最大設限64格.僅適用 於PCB3號板2014年以後版本.",
	"[Y-DIST]:",
};
//para2
string ContextHintStr2[] = {		
	//00************************************************************************************************************************************	
	"[原點位置]:由密碼輸入5217,設定絕對值馬達原點位置.",
	"[ZRT  POS]:",										
	//01************************************************************************************************************************************
	"[原點圈數]:由密碼輸入5217,設定絕對值馬達原點圈數.",
	"[ZRT  CYE]:",		
	//02************************************************************************************************************************************
	"[齒輪比0]:預設為1000,絕對值馬達齒輪比.",
	"[GEAR 0]:",
	//03************************************************************************************************************************************
	"[齒輪比1]:預設為1000,絕對值馬達齒輪比.",
	"[GEAR 1]:",
	//04************************************************************************************************************************************
	"[分周分子]:預設為1000,調整驅動器回授信號分周比.",
	"[ENCR0]:",
	//05************************************************************************************************************************************
	"[分周分母]:預設為1000,調整驅動器回授信號分周比.",
	"[ENCR1]:",
	//06************************************************************************************************************************************
	"[A/B反向]:設定驅動器回授信號是否反向.0-不反向,1-反向.",
	"[A/B Dir]:",
	//07************************************************************************************************************************************
	"[原點信號]:預設為1-High,馬達無安裝Sensor或有外接Encoder時,若[原點模式]為0-直接,[原點信號]需視情況調整.(與驅動器設定相關),[NEW]2-不參考",
	"[Sensor]:",
	//08************************************************************************************************************************************
	"[定位檢查]:使用到定位\xa5\x5c能時(常用參數[到定位]設定1,或是程式有壓紅字),設定幾個週期時間檢查一次(一個週期=100us),視各軸馬達情況調整",
	"[ChkToPos]:",	
	//09************************************************************************************************************************************
	"[T1減距離]:",
	"[T1DecDis]:",
	//10************************************************************************************************************************************
	"[T2減距離]:",
	"[T2DecDis]:",
	//11************************************************************************************************************************************
	"[T3減距離]:",
	"[T3DecDis]:",
	//12************************************************************************************************************************************
	"[T4減距離]:",
	"[T4DecDis]:",	
	//13************************************************************************************************************************************
	"[手輪速度]:",
	"[HAND SPD]:",
	//14************************************************************************************************************************************
	"[送線間隙]:",
	"[Wire Gap]:",
	//15************************************************************************************************************************************
	"[LINE]:",
	"[LINE]:",
	//16************************************************************************************************************************************
	"[LOGO]:",
	"[LOGO]:",	
	//17************************************************************************************************************************************
	"[單一生產]:",
	"[ONE]:",
	//18************************************************************************************************************************************
	"[鎖生產量]:",
	"[LOCK PNO]:",
	//19************************************************************************************************************************************
	"[轉芯校正]:",
	"[ROTQ MDY]:",
	//20************************************************************************************************************************************
	"[捲取校正]:",
	"[SPIN MDY]:",
	//21************************************************************************************************************************************
	"[批量]:",
	"[BATCH]:",
	//22************************************************************************************************************************************
	"[模擬FAST]:",
	"[SIM FAST]:",
	//23************************************************************************************************************************************
	"[X-編碼器]:",
	"[X-Encode]:",
	//24************************************************************************************************************************************
	"[馬達型號]:",
	"[MOT   NO]:",
	//25************************************************************************************************************************************
	"[寸動盒 T]:",
	"[Switch T]:",
	//26************************************************************************************************************************************
	"[探針延遲]:",
	"[T  Delay]:",
};

//para3
string ContextHintStr3[] = {		
	//00************************************************************************************************************************************	
	"[開啟軸數]:預設0,2軸以下不參考.軟體可自由設定開啟軸數,超過以短路pin為主.",
	"[Axis No ]:",										
};
//para4
string ContextHintStr4[] = {		
	//00************************************************************************************************************************************	
	"[ 序 號  ]:機器唯一6位數字認證號碼,請勿重複設定,避免解密密碼相同.輸入完畢後,按方向左鍵,啟動密碼\xa5\x5c能.",
	"[Ser No. ]:",
	//01************************************************************************************************************************************	
	"[啟動密碼]:如欲啟動密碼\xa5\x5c能,請將數值設定在1-開啟,0為關閉此\xa5\x5c能.",
	"[ Pass Wd]:",
	//02************************************************************************************************************************************	
	"[YYYYMMDD]:輸入預鎖系統日期,設定數值為機器可運行的期限.            例如:輸入20160123,機器即可使用到2016年01月23日前.",
	"[YYYYMMDD]:",
	//03************************************************************************************************************************************	
	"[ 密 碼-1]:此密碼欄位由控制器電腦產生,無須輸入.",
	"[PassWd-1]:",
	//04************************************************************************************************************************************	
	"[YYYYMMDD]:第二組預鎖系統日期,可做分期使用.若[密 碼-1]到期,輸入    [密 碼-2]做解鎖,預鎖系統日期依序遞增即可,依此類推.",
	"[YYYYMMDD]:",
	//05************************************************************************************************************************************	
	"[ 密 碼-2]:此密碼欄位由控制器電腦產生,無須輸入.",
	"[PassWd-2]:",
	//06************************************************************************************************************************************	
	"[YYYYMMDD]:第三組預鎖系統日期.",
	"[YYYYMMDD]:",
	//07************************************************************************************************************************************	
	"[ 密 碼-3]:此密碼欄位由控制器電腦產生,無須輸入.",
	"[PassWd-3]:",
	//08************************************************************************************************************************************	
	"[YYYYMMDD]:第四組預鎖系統日期.",
	"[YYYYMMDD]:",
	//09************************************************************************************************************************************	
	"[ 密 碼-4]:此密碼欄位由控制器電腦產生,無須輸入.",
	"[PassWd-4]:",	
	//10************************************************************************************************************************************	
	"[YYYYMMDD]:第五組預鎖系統日期.若已設定完成請在此欄位按[記憶鍵]產生 對應密碼.",
	"[YYYYMMDD]:",
	//11************************************************************************************************************************************	
	"[ 密 碼-5]:此密碼欄位由控制器電腦產生,無須輸入.",
	"[PassWd-5]:",
	//12************************************************************************************************************************************	
	"[系統日期]:控制器BIOS日期,若欄位值與今天日期不符,請手動設定,完成後 按[記憶鍵]更新BIOS日期.",
	"[Sys Date]:",
	//13************************************************************************************************************************************	
	"[系統時間]:控制器BIOS時間,若欄位值與目前時間不符,請手動設定,完成後 按[記憶鍵]更新BIOS時間.",
	"[Sys Time]:",											
};
void DispContextHint_q (WORD cursor_loc)
{
	int str_idx = -1;
	CursorData_t *ptr= *(CurCursor.ptr) ;
	switch(cursor_loc)
	{
		case MOTOR_GRID_CURSOR: 	str_idx =  0; break;
		case PARA1_LINE03_CURSOR:	str_idx =  1; break;
		case PARA1_LINE04_CURSOR:	str_idx =  2; break;
		case HOME_SEQ_CURSOR:			str_idx =  3; break;
		case ZRTMODE_CURSOR:			str_idx =  4; break;
		case ZRTSET_CURSOR:				str_idx =  5; break;
		case ZRTCORR_CURSOR:			str_idx =  6; break;
		case MAX_CURSOR:					str_idx =  7; break;
		case MIN_CURSOR:					str_idx =  8; break;
		case MotorNEAR_CURSOR:				str_idx=24;break ;
		case PARA1_LINE10_CURSOR:
		{ 
			if 			(ptr == &SYS_LANG_CUR)		str_idx =  9;
			else if (ptr == &TYPE_CUR)				str_idx = 10;
			else if (ptr == &Y_ENCODER_CUR)		str_idx = 11;
			else if (ptr == &MOTOR_NEAR_CUR)	str_idx = 12;
		}
			break;
		case PARA1_LINE11_CURSOR:
		{ 			
			if 			(ptr == &SHIELD_CUR)			str_idx = 13;
			else if (ptr == &SYS_FAST_CUR)		str_idx = 14;
			else if (ptr == &BUZZER_CUR)			str_idx = 15;
			else if (ptr == &CutDist_CUR)			str_idx = 16;
		}
		break;
		//case PARA1_LINE12_CURSOR:
		//{ 
		//	if 			(ptr == &REPAIR_Y_CUR)		str_idx = 17;
		//	else if (ptr == &DIST_Y_CUR)			str_idx = 18;
		//	else if (ptr == &GEAR_Y0_CUR)			str_idx = 19;
		//	else if (ptr == &GEAR_Y1_CUR)			str_idx = 20;
		//}
		//break;
		case PARA1_LINE13_CURSOR:
		{ 
			//if 			(ptr == &REPAIR_SPD_CUR)	str_idx = 21;
			//else if (ptr == &REPAIR_DST_CUR)	str_idx = 22;
			if(ptr == &G2Mode_CUR) str_idx=17 ;
			else if(ptr == &SPDMode_CUR) str_idx=18 ;
			
			
		}
		break;
		
		//para2
		case PARA2_LINE01_CURSOR: str_idx=100;break;
		case PARA2_LINE02_CURSOR: str_idx=101;break;
		case PARA2_LINE03_CURSOR: str_idx=102;break;
		case PARA2_LINE04_CURSOR: str_idx=103;break;
		case PARA2_LINE05_CURSOR: str_idx=104;break;
		case PARA2_LINE06_CURSOR: str_idx=105;break;
		case PARA2_LINE07_CURSOR: str_idx=106;break;
		case PARA2_LINE08_CURSOR: str_idx=107;break;
		case PARA2_LINE09_CURSOR: str_idx=108;break;
			
		case PARA2_LINE10_CURSOR: 
		{
			if 			(ptr == &T1DecDis_CUR)	str_idx = 109;
			else if (ptr == &T2DecDis_CUR)	str_idx = 110;
			else if (ptr == &T3DecDis_CUR)	str_idx = 111;
			else if (ptr == &T4DecDis_CUR)	str_idx = 112;
			break;
		}
		case PARA2_LINE11_CURSOR: 
		{
			if 			(ptr == &MAN_GAIN_CUR)	str_idx = 113;
			else if (ptr == &WIRE_GAP_CUR)	str_idx = 114;
			else if (ptr == &LINE_CUR)			str_idx = 115;
			else if (ptr == &DELAY_CUR)			str_idx = 116;
			break;
		}
		case PARA2_LINE12_CURSOR: 
		{
			if 			(ptr == &ONE_CUR)				str_idx = 117;
			else if (ptr == &DEC_DIST_CUR)	str_idx = 118;
			else if (ptr == &ROTQ_MDY_CUR)	str_idx = 119;
			else if (ptr == &SPIN_MDY_CUR)	str_idx = 120;
			break;
		}
		case PARA2_LINE13_CURSOR:
		{
			if 			(ptr == &BATCHn_CUR)		str_idx = 121;
			else if (ptr == &SimFast_CUR)		str_idx = 122;
			else if (ptr == &X_ENCODER_CUR)	str_idx = 123;
			else if (ptr == &TAIDAMotor_CUR)str_idx = 124;
			break;
		}
		case PARA2_LINE14_CURSOR: 
		{
			if 			(ptr == &SwitchT_CUR)		str_idx = 125;
			else if (ptr == &TDelay_CUR)		str_idx = 126;	
			break;
		}
		
		
		//para3
		case PARA3_LINE01_CURSOR: str_idx=200;break;	

		//para4
		case PARA4_LINE01_CURSOR: 
		{
			if 			(ptr == &SN_CUR)					str_idx = 300;
			else if (ptr == &EnPassWd_CUR)		str_idx = 301;
			break;
		}	
		case PARA4_LINE02_CURSOR: 
		{
			if 			(ptr == &MONTH1_CUR)			str_idx = 302;
			else if (ptr == &PASS1_CUR)				str_idx = 303;
			break;
		}
		case PARA4_LINE03_CURSOR: 
		{
			if 			(ptr == &MONTH2_CUR)			str_idx = 304;
			else if (ptr == &PASS2_CUR)				str_idx = 305;
			break;
		}
		case PARA4_LINE04_CURSOR: 
		{
			if 			(ptr == &MONTH3_CUR)			str_idx = 306;
			else if (ptr == &PASS3_CUR)				str_idx = 307;
			break;
		}
		case PARA4_LINE05_CURSOR: 
		{
			if 			(ptr == &MONTH4_CUR)			str_idx = 308;
			else if (ptr == &PASS4_CUR)				str_idx = 309;
			break;
		}	
		case PARA4_LINE06_CURSOR: 
		{
			if 			(ptr == &MONTH5_CUR)			str_idx = 310;
			else if (ptr == &PASS5_CUR)				str_idx = 311;
			break;
		}
		case PARA4_LINE07_CURSOR: 
		{
			if 			(ptr == &SetSystemDateYear_CUR || ptr == &SetSystemDateMonth_CUR || ptr == &SetSystemDateDay_CUR)	str_idx = 312;
			else if (ptr == &SetSystemTimeHour_CUR || ptr == &SetSystemTimeMin_CUR || ptr == &SetSystemTimeSec_CUR)	str_idx = 313;
			break;
		}	
		default:;
	}
	
	if (str_idx != -1){
		char line1[100]={0};
		char line2[100]={0};
		string str;
		if (str_idx<100){
			str  = (CHINESE)?ContextHintStr[str_idx*2]:ContextHintStr[str_idx*2+1];
		}
		else if (str_idx >=100 && str_idx <200){
			str_idx-=100;
			str  = (CHINESE)?ContextHintStr2[str_idx*2]:ContextHintStr2[str_idx*2+1];
		}
		else if (str_idx >=200 && str_idx <300){
			str_idx-=200;
			str  = (CHINESE)?ContextHintStr3[str_idx*2]:ContextHintStr3[str_idx*2+1];
		}
		else if (str_idx >=300){
			str_idx-=300;
			str  = (CHINESE)?ContextHintStr4[str_idx*2]:ContextHintStr4[str_idx*2+1];
		}
		string str1 = (str.length()>67)?str.substr(0,67):str;
		string str2 = (str.length()>67)?str.substr(67,str.length()-67):"";	
		strcpy(line1,str1.c_str());
		strcpy(line2,str2.c_str());
			
		short	lx, ly;
		lx = PARA_MOTOR_LX+2;
#ifndef HNCNC6
		ly = PARA_LINE21_LY;
#else
		ly = PARA_LINE16_LY;
#endif		
		INI_DISP_BUF();	
		DispContextHintFrame_q();
		Fill_pDispBuf(line1); 
		FILL_DISP_BUF(0);
		DispStrLine_q(lx+2, ly+2, BRIGHTWHITE_USR, BLUE_USR, DispBuf);			
		
		if (!str2.empty()){
#ifndef HNCNC6
		ly = PARA_LINE22_LY;
#else
		ly = PARA_LINE17_LY;
#endif
			INI_DISP_BUF();
			Fill_pDispBuf(line2) ;
			FILL_DISP_BUF(0);
			DispStrLine_q(lx+2, ly+2, BRIGHTWHITE_USR, BLUE_USR, DispBuf);
		}
	}
}

*/