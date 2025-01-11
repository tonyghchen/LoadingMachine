#include "header.h"
#include "rolldata.h"
unsigned int cur_step =0 ;
struct ST_ROLLDATA{
	uint8 compress ;   //1 : compress 0:real color
	uint8	MAX_STEP;
	unsigned char  idx[30] ;
	unsigned char  dir[30] ; // 0:正常,1:左右對調
} ;

struct ST_ROLLDATA	st_RollData[]={
	{	//HNCNC
#if NEWLOGO
		0,
		15,												//MAX_STEP
		{0,0,0,0, 1, 2, 3, 4,   5, 6, 7, 8, 9,  10, 11},		//idx
		{0,0,0,0, 0, 0, 0, 0,   0, 0, 0, 0, 0,   0, 0},		//dir
#else
		1,
		12,												//MAX_STEP
		{0, 1, 2, 3, 2,   1, 0, 4, 5, 6,   5, 4},		//idx
		{0, 0, 0, 0, 1,   1, 1, 0, 0, 0,   1, 1},		//dir
#endif
	},
	{	//KNCNC
        1,
		18,																	//MAX_STEP
		{0, 1, 2, 3, 4,   5, 6, 7, 8, 9,   10,11,12,13,14,   15,16,17},		//idx
		{0, 0, 0, 0, 0,   0, 0, 0, 0, 0,    0, 0, 0, 0, 0,    0, 0, 0},		//dir
	},
	{	//RSOUTH
        1,
		10,										//MAX_STEP
		{0, 1, 2, 3, 2,  5, 6, 7, 8, 9},		//idx
		{0, 0, 0, 0, 0,  0, 0, 0, 0, 0},		//dir
	},
	{	//SETT
        1,
		18,																	//MAX_STEP
		{0, 1, 2, 3, 4,   5, 6, 7, 8, 9,   10,11,12,13,14,   15,16,17},		//idx
		{0, 0, 0, 0, 0,   0, 0, 0, 0, 0,    0, 0, 0, 0, 0,    0, 0, 0},		//dir
	},	
};

void DispRollData_q (short x, short y, short step)
{
	
	uint8 ManuFactory = MachineStatus.MANUFACTORY&0xf;
	
	if(ManuFactory>JLNCNC){
		ManuFactory=HNCNC;
	}
	else if (ManuFactory>SETT){
		ManuFactory=KNCNC; //開創附屬:星火,建岭 
	}
		
	LOGOCompress =st_RollData[ManuFactory].compress ;	
	int MAX_STEP = st_RollData[ManuFactory].MAX_STEP;
	
	cur_step= (cur_step+step) % MAX_STEP ;
	

	unsigned int idx = st_RollData[ManuFactory].idx[cur_step];
	unsigned int dir = st_RollData[ManuFactory].dir[cur_step];

	unsigned char huge *ptr ;
	//unsigned char *start ;
	unsigned int w , h ,tw;
	ptr = RollData->pcx[idx] ;//依據圖形編號(idx),找出圖形的第一個byte的位址
	w= *(uint16 *)ptr ;
	ptr+= 2 ;
	h = *(uint16 *)ptr ;
	ptr += 2 ;
	unsigned int steph=15 ;  //顯示速度愈快,此值可以改更大
	unsigned int remaindh= h%steph ;
	unsigned int lasth= remaindh ? remaindh : steph ;
	unsigned notimes= h/steph+(remaindh ? 1:0) ;
	for(int i =0 ; i < notimes ;i++){
		BYTE *dptr=  (BYTE *)farmalloc(5*sizeof(short)+sizeof(BYTE *)+LEN_CHKSUM) ;
		BYTE *tptr = dptr ;
		SAVE_VAL(short, x);
		SAVE_VAL(short, y+i*steph) ;
		SAVE_VAL(short, w) ;
		SAVE_VAL(short, (i== (notimes-1))? lasth :steph) ;
		SAVE_VAL(short, dir) ;




		SAVE_VAL(BYTE * , (BYTE *)ptr) ;




		SAVE_CHKSUM
		FILL_PROC_QUEUE(DispRollData1_proc,tptr ) ;
		if(LOGOCompress){	
			for(int j=0 ; j < steph ; j++){
				for(tw=0 ; tw < w ;  ){
					if((*ptr& 0xc0) == 0xc0){
						tw += (*ptr & 0x3f) ;
						ptr++ ;
					}
					else{
						tw ++ ;
					}
					ptr++ ;
				}
			}
		}
		else{
			ptr +=(steph*w*3) ;
		}
	}
}

//2012_1010_新增"小鍵盤"&&"LOGO"切換----------------------------
void  InitChRollData(void)
{
	//切換LOGO
	uint8 ManuFactory = MachineStatus.MANUFACTORY&0xf;
	switch (ManuFactory){
		case KNCNC:		RollData= &RollDataKNCNC;	break;
		case RSOUTH:	RollData= &RollDataRSOUTH;	break;
		case SETT:		RollData= &RollDataSETT;	break;
		case SFNCNC	:	RollData= &RollDataSFNCNC;	break;    //0x17	星火(4)
		case JLNCNC	:	RollData= &RollDataJLNCNC;	break;    //0x21	建岭(5)
		
		case HNCNC:
		default:		RollData= &RollDataHNCNC;	break;	
	}
	//切換鍵盤
#ifdef HNCNC6
	MachineStatus.keyboard_type = (MachineStatus.MANUFACTORY &0x100)?KEY_H:KEY_S;
#else
	MachineStatus.keyboard_type = KEY_H;
#endif
	switch(MachineStatus.keyboard_type){
		case KEY_H:		KeyMapTbl= KeyMapTbl_H ;	break ;	
		case KEY_S:		KeyMapTbl= KeyMapTbl_S ;	break ;	
	}
	open_config("rb+") ;
	save_keyboard_type();
	close_config() ;	
	InitRollData();	
}

