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
	//�Ǹ�
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(6, MachineStatus.NSN, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//�ҰʱK�X
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
	//�K�X-1
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
	//�K�X-2
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
	//�K�X-3
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
	//�K�X-4
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
	//�K�X-5
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
	//�t�Τ��
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(8, MachineStatus.SystemDate, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//�t�ήɶ�
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
	//�]�w���
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(4, MachineStatus.SetSystemDate[0], pDispBuf);
	pDispBuf_value += BcdToStrBuf(2, MachineStatus.SetSystemDate[1], pDispBuf);
	pDispBuf_value += BcdToStrBuf(2, MachineStatus.SetSystemDate[2], pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//�]�w�ɶ�
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
	//�}�Ҷb��
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1, MachineStatus.AxisNo, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
}

void DispPara2_q(void)
{
	DispParaWin2_q();
	DispParaField2_q();
	DispContextHintFrame_q();  //�Ŧ⩳��
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
	short ly = PARA_LINE15_LY; //��
	frame.type = -1;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	PrintStringLine_fmt(lx+2, ly+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, ColPara2_05[idx_language][i]);//��
	lx += PARA_DATA_CHARS*ASC_CHAR_W+4;

	frame.type = 0;
	DrawCasing(lx, ly, lx+PARA_DATA_CHARS*ASC_CHAR_W+4-1, ly+ASC_CHAR_H+4-1, &frame);
	farfree(ptr) ;
}
void DispColPara2_05Frame_q (void)
{
	for(short i=0; i < sizeof(ColPara2_05[0])/sizeof(ColPara2_05[0][0]); i++ ){//��
		BYTE *tptr = (BYTE *)farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
		BYTE * dptr= tptr ;
		SAVE_VAL(short , i) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispColPara2_05_proc,tptr) ;//��
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
		Fill_pDispBuf("�g��", "cyc." ,"cyc.");
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
	//T1��Z��
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(6, MachineStatus.TDecDisA[0], pDispBuf);
	ADD_DOT_UNIT(AXIS_Y);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//T2��Z��
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(6, MachineStatus.TDecDisA[1], pDispBuf);
	ADD_DOT_UNIT(AXIS_Y);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//T3��Z��
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(6, MachineStatus.TDecDisA[2], pDispBuf);
	ADD_DOT_UNIT(AXIS_Y);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//T4��Z��
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
	//����t��
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(2, MachineStatus.man_gain, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//�e�u����
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
	//��@�Ͳ�
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1, MachineStatus.ONE, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//��Ͳ��q
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1, MachineStatus.dec_dist, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//���ե�
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1,MachineStatus.ROTQ_MDY , pDispBuf);
	FILL_DISP_BUF('-') ;
	Fill_pDispBuf (StrONOFF[idx_language][MachineStatus.ROTQ_MDY]);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//�����ե�
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
	//��q
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(7, MachineStatus.BATCHn, pDispBuf);
	ADD_MINUS_01(pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//����FAST
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1, MachineStatus.SimFast, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//X-�s�X��
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1, MachineStatus.X_Encoder, pDispBuf);
	FILL_DISP_BUF('-') ;
	Fill_pDispBuf (StrX_Encoder[idx_language][MachineStatus.X_Encoder]);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//���F����
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
	//�o�ʲ�T
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(2, MachineStatus.SwitchT, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//���w����
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
	DispMotorNo_q(0); //���F�s��
	DispMotorName_q(1); //���F�W��
	DispMotorGrads_q(2); //���F���
	DispnMotorType_q(3); //���F���A
	DispMotFunc_q(4); //���F�\��
	DispHomeSeq_q(5); //���I����
	DispParaZrtMode_q(6); //���I�Ҧ�
	DispParaZRTSET_q(7); //�s�]���I
	DispZrtCorr_q(8); //���I����
	DispParaMAX_q(9); //�̤j����
	DispParaMIN_q(10); //�̤p����
	DispParaMotorNEAR_q(11) ;//�^���H��
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
//5215�ӧO�Ѽ�:
void DispColPara1_01_q (void)
{
	short	lx, ly;
	lx = PARA_MOTOR_LX + PARA_DATA_CHARS*ASC_CHAR_W+4;
	ly = PARA_LINE12_LY;
	//�y���]�w
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1, MachineStatus.language, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//��������
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(3, MachineStatus.Type, pDispBuf);
	FILL_DISP_BUF(' ') ;
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);		
	//Y-�s�X��
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1, MachineStatus.Y_Encoder, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//�^���H��
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
	//�w����
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1, MachineStatus.safety_door, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//�w���˸m
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(2,MachineStatus.bysafe_plugin , pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//ĵ�a�˸m
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1, MachineStatus.BUZZER, pDispBuf);
	FILL_DISP_BUF('-') ;
	Fill_pDispBuf (StrONOFF[idx_language][MachineStatus.BUZZER]);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//���M�Z��
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
	//��w�t��
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(5, MachineStatus.repair_y, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//��w�Z��
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(2, MachineStatus.dist_y, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//Y�b����0
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(6, MachineStatus.gear_y[0], pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//Y�b����1
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
	//�t�׸ɥ�
	//INI_DISP_BUF();
	//pDispBuf_value += BcdToStrBuf(2, MachineStatus.repair_spd, pDispBuf);
	//FILL_DISP_BUF(0);
	//DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//�Z���ɥ�
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	INI_DISP_BUF();
	pDispBuf_value += BcdToStrBuf(1, MachineStatus.SPDMode, pDispBuf);
	FILL_DISP_BUF(0);
	DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//INI_DISP_BUF();
	//pDispBuf_value += BcdToStrBuf(2, MachineStatus.repair_dst, pDispBuf);
	//FILL_DISP_BUF(0);
	//DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
	//G2  �Ҧ�
	lx += (PARA_DATA_CHARS*ASC_CHAR_W+4)*2;
	
	//SPD �Ҧ�
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
	"[���F���]:���c�B��@��ɪ���ưѦҭ�,��������өw.",
	"[MOT GRID]:",
	//01************************************************************************************************************************************	
	"[���F���A]:�̰��F�t�P�]�w,�j�������p:0-�T�v,1-�w�t ���F.",
	"[MOT TYPE]:",										
	//02************************************************************************************************************************************
	"[���F\xa5\x5c��]:0-�Y��,1-�e��,2-���,3-½�u,4-����,5-���M,6-����,7-�Ʈy,8-½�u(�׾�,�ݰt�X�Ѽ�:Y-�s�X��), 9-�騤, 10-����.",
	"[MOT FUNC]:0-CAM,1-FEED,2-ROTQ,3-ROTW,4-SPIN,5-CUT,6-HOOK,7-SLIDE, 8-ROTW(repair with \"Y-Encode\"), 9-ANGLE 10-STM.",		
	//03************************************************************************************************************************************
	"[���I����]:����^���I���B���V�Υ��ᶶ��,+��ܥ��V�^���I,-��ܤϦV�^���I;�Ʀr�p�����^���I,�Ʀr�@�˪��P�ɦ^���I.",
	"[HOME SEQ]:",
	//04************************************************************************************************************************************
	"[���I�Ҧ�]:0-����,1-����,2-�ߧY,3-��u;�Ҧ��]�w�P���F���u�覡����, �ԲӤ��e�аѦһ�����.",
	"[ZRT MODE]:0-DIRECT, 1-INDIRT, 2-IMMED, 3-ROTW",
	//05************************************************************************************************************************************
	"[�s�]���I]:�^���I��A��������ƭ�,+/-��ܰ�������V.",
	"[ZRT SET]:",
	//06************************************************************************************************************************************
	"[���I����]:�A�Ω���I�Ҧ���1-����,2-�ߧY;���IIO�H������.",
	"[ZRT CORR]:",
	//07************************************************************************************************************************************
	"[�̤j����]:�U�b������V�ಾ�ʪ��̤j�Z��,�s��{���Τ�ʮ��ˬd.",
	"[AXIS MAX]:",
	//08************************************************************************************************************************************
	"[�̤p����]:�U�b���t��V�ಾ�ʪ��̤j�Z��,�s��{���Τ�ʮ��ˬd.",
	"[AXIS min]:",


	
	//09************************************************************************************************************************************
	"[�y���]�w]:0-�^��,1-�c�餤��,2-²�餤��,3-�q�j�Q��.",
	"[LANGUAGE]:",
	//10************************************************************************************************************************************
	"[��������]:�̫Ȥ���������]�w.",
	"[TYPE NO.]:",
	//11************************************************************************************************************************************
	"[Y-�s�X��]:",
	"[Y-Encode]:",
	//12************************************************************************************************************************************
	"[�^���H��]:�ѼƳ]�w000��:���F�u�����|�^�����~;�]�w255��:���F�u���� ���|�^�����~.�ԲӤ��e�аѦһ�����.",
	"[MOT NEAR]:",	
	//13************************************************************************************************************************************
	"[�w����]:���[�˦w������,�i��ܶ}��\xa5\x5c��;0-����,1-�}��.",
	"[SHIELD]:",
	//14************************************************************************************************************************************
	"[�w���˸m]:�]�w�w���˸m���}�һP�F�ӫ�;00-����,01-�}��(���F��),�Ʀr �V�j�V���F��.",
	"[SENSOR]:",
	//15************************************************************************************************************************************
	"[ĵ�ܿO]:���x�o�Ϳ��~�T����,�H���O�{�{�@��ĵ��;0-����,1-�}��,IO��X�I��(BZ).�ȾA�Ω�n��v3.52�H�᪩��.",
	"[W.LIGHT]:",
	//16************************************************************************************************************************************
	"[���M�Z��]:���A���M�T�w�Ӧ^�����ʶZ��,�̤j�ȳ]��15000��,�ק惡�Ѽ� �t�η|�۰ʱN[���M�Z��]��J���M�b[�̤j����],��@�n�鷥���]�w.",
	"[Cut Dist]:",	
	//17************************************************************************************************************************************
	"[�t�v�Ҧ�]:0-�W�t�v(���q��X�b�O���Ͳ��t�v,��L�b�i��W�L�Ͳ��t�v)   1-���t�v(�U�b�����W�L�Ͳ��t�v)   2-�ۭq(�ۭq�U�b�Ͳ��t�v)",
	"[RateMode]:",	
	//18************************************************************************************************************************************
	"[SPD �Ҧ�]:0-SPD�i��J2���;1-SPD�i��J3���,�̧C��N��p���I�᪺�Ʀr",
	"[SPD Mode]:",
	//19************************************************************************************************************************************
	"[Y�b����0]:�Y�e�u�b����D�U���������w�]��,�ݤ�ʿ�J.",
	"[Y-GEAR0]:",
	//20************************************************************************************************************************************
	"[Y�b����1]:�Y�e�u�b����D�U���������w�]��,�ݤ�ʿ�J.",
	"[Y-GEAR1]:",	
	//21************************************************************************************************************************************
	"[�t�׸ɥ�]:",
	"[SPEED UP]:",
	//22************************************************************************************************************************************
	"[�Z���ɥ�]:",
	"[DIST UP ]:",
	//23************************************************************************************************************************************
	"[��w�t��]:�e�u�b��w\xa5\x5c��,��ȶV�j��w�t�׶V�C.�ȾA�Ω�PCB3���O2014�~�H�᪩��.",
	"[Y-REPAIR]:",
	//24************************************************************************************************************************************
	"[�^���H��]:�ѼƳ]�w0��:���F�u�����|�^�����~;�]�w1��:���F�u�������| �^�����~.�ԲӤ��e�аѦһ�����",
	"[NOT NEAR]:",
	//25************************************************************************************************************************************
	"[��w�Z��]:�e�u�b��w\xa5\x5c��,��ȶV�j�V���}�l��w,�̤j�]��64��.�ȾA�� ��PCB3���O2014�~�H�᪩��.",
	"[Y-DIST]:",
};
//para2
string ContextHintStr2[] = {		
	//00************************************************************************************************************************************	
	"[���I��m]:�ѱK�X��J5217,�]�w����Ȱ��F���I��m.",
	"[ZRT  POS]:",										
	//01************************************************************************************************************************************
	"[���I���]:�ѱK�X��J5217,�]�w����Ȱ��F���I���.",
	"[ZRT  CYE]:",		
	//02************************************************************************************************************************************
	"[������0]:�w�]��1000,����Ȱ��F������.",
	"[GEAR 0]:",
	//03************************************************************************************************************************************
	"[������1]:�w�]��1000,����Ȱ��F������.",
	"[GEAR 1]:",
	//04************************************************************************************************************************************
	"[���P���l]:�w�]��1000,�վ��X�ʾ��^�«H�����P��.",
	"[ENCR0]:",
	//05************************************************************************************************************************************
	"[���P����]:�w�]��1000,�վ��X�ʾ��^�«H�����P��.",
	"[ENCR1]:",
	//06************************************************************************************************************************************
	"[A/B�ϦV]:�]�w�X�ʾ��^�«H���O�_�ϦV.0-���ϦV,1-�ϦV.",
	"[A/B Dir]:",
	//07************************************************************************************************************************************
	"[���I�H��]:�w�]��1-High,���F�L�w��Sensor�Φ��~��Encoder��,�Y[���I�Ҧ�]��0-����,[���I�H��]�ݵ����p�վ�.(�P�X�ʾ��]�w����),[NEW]2-���Ѧ�",
	"[Sensor]:",
	//08************************************************************************************************************************************
	"[�w���ˬd]:�ϥΨ�w��\xa5\x5c���(�`�ΰѼ�[��w��]�]�w1,�άO�{���������r),�]�w�X�Ӷg���ɶ��ˬd�@��(�@�Ӷg��=100us),���U�b���F���p�վ�",
	"[ChkToPos]:",	
	//09************************************************************************************************************************************
	"[T1��Z��]:",
	"[T1DecDis]:",
	//10************************************************************************************************************************************
	"[T2��Z��]:",
	"[T2DecDis]:",
	//11************************************************************************************************************************************
	"[T3��Z��]:",
	"[T3DecDis]:",
	//12************************************************************************************************************************************
	"[T4��Z��]:",
	"[T4DecDis]:",	
	//13************************************************************************************************************************************
	"[����t��]:",
	"[HAND SPD]:",
	//14************************************************************************************************************************************
	"[�e�u����]:",
	"[Wire Gap]:",
	//15************************************************************************************************************************************
	"[LINE]:",
	"[LINE]:",
	//16************************************************************************************************************************************
	"[LOGO]:",
	"[LOGO]:",	
	//17************************************************************************************************************************************
	"[��@�Ͳ�]:",
	"[ONE]:",
	//18************************************************************************************************************************************
	"[��Ͳ��q]:",
	"[LOCK PNO]:",
	//19************************************************************************************************************************************
	"[���ե�]:",
	"[ROTQ MDY]:",
	//20************************************************************************************************************************************
	"[�����ե�]:",
	"[SPIN MDY]:",
	//21************************************************************************************************************************************
	"[��q]:",
	"[BATCH]:",
	//22************************************************************************************************************************************
	"[����FAST]:",
	"[SIM FAST]:",
	//23************************************************************************************************************************************
	"[X-�s�X��]:",
	"[X-Encode]:",
	//24************************************************************************************************************************************
	"[���F����]:",
	"[MOT   NO]:",
	//25************************************************************************************************************************************
	"[�o�ʲ� T]:",
	"[Switch T]:",
	//26************************************************************************************************************************************
	"[���w����]:",
	"[T  Delay]:",
};

//para3
string ContextHintStr3[] = {		
	//00************************************************************************************************************************************	
	"[�}�Ҷb��]:�w�]0,2�b�H�U���Ѧ�.�n��i�ۥѳ]�w�}�Ҷb��,�W�L�H�u��pin���D.",
	"[Axis No ]:",										
};
//para4
string ContextHintStr4[] = {		
	//00************************************************************************************************************************************	
	"[ �� ��  ]:�����ߤ@6��Ʀr�{�Ҹ��X,�Фŭ��Ƴ]�w,�קK�ѱK�K�X�ۦP.��J������,����V����,�ҰʱK�X\xa5\x5c��.",
	"[Ser No. ]:",
	//01************************************************************************************************************************************	
	"[�ҰʱK�X]:�p���ҰʱK�X\xa5\x5c��,�бN�ƭȳ]�w�b1-�}��,0��������\xa5\x5c��.",
	"[ Pass Wd]:",
	//02************************************************************************************************************************************	
	"[YYYYMMDD]:��J�w��t�Τ��,�]�w�ƭȬ������i�B�檺����.            �Ҧp:��J20160123,�����Y�i�ϥΨ�2016�~01��23��e.",
	"[YYYYMMDD]:",
	//03************************************************************************************************************************************	
	"[ �K �X-1]:���K�X���ѱ���q������,�L����J.",
	"[PassWd-1]:",
	//04************************************************************************************************************************************	
	"[YYYYMMDD]:�ĤG�չw��t�Τ��,�i�������ϥ�.�Y[�K �X-1]���,��J    [�K �X-2]������,�w��t�Τ���̧ǻ��W�Y�i,�̦�����.",
	"[YYYYMMDD]:",
	//05************************************************************************************************************************************	
	"[ �K �X-2]:���K�X���ѱ���q������,�L����J.",
	"[PassWd-2]:",
	//06************************************************************************************************************************************	
	"[YYYYMMDD]:�ĤT�չw��t�Τ��.",
	"[YYYYMMDD]:",
	//07************************************************************************************************************************************	
	"[ �K �X-3]:���K�X���ѱ���q������,�L����J.",
	"[PassWd-3]:",
	//08************************************************************************************************************************************	
	"[YYYYMMDD]:�ĥ|�չw��t�Τ��.",
	"[YYYYMMDD]:",
	//09************************************************************************************************************************************	
	"[ �K �X-4]:���K�X���ѱ���q������,�L����J.",
	"[PassWd-4]:",	
	//10************************************************************************************************************************************	
	"[YYYYMMDD]:�Ĥ��չw��t�Τ��.�Y�w�]�w�����Цb������[�O����]���� �����K�X.",
	"[YYYYMMDD]:",
	//11************************************************************************************************************************************	
	"[ �K �X-5]:���K�X���ѱ���q������,�L����J.",
	"[PassWd-5]:",
	//12************************************************************************************************************************************	
	"[�t�Τ��]:���BIOS���,�Y���ȻP���Ѥ������,�Ф�ʳ]�w,������ ��[�O����]��sBIOS���.",
	"[Sys Date]:",
	//13************************************************************************************************************************************	
	"[�t�ήɶ�]:���BIOS�ɶ�,�Y���ȻP�ثe�ɶ�����,�Ф�ʳ]�w,������ ��[�O����]��sBIOS�ɶ�.",
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