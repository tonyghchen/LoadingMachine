#include "header.h"

void ini_loopchk(bool val)
{
	for(int axis =0 ; axis < MAX_AXIS ; axis++){
		 loopchk[axis]=val ;
	}
}
/*
int phys_mem_left()
{
	_go32_dpmi_meminfo info ;
	_go32_dpmi_get_free_memory_information(&info) ;
	if(info.available_physical_pages != -1){
		return (info.available_physical_pages*4096) ;
	}
	return(info.available_memory) ;
}

void Fill_REPAIR_Y()
{
	if (USE_REPAIRY){
		uint16 cnt = (uint16)BcdToBin(5,MachineStatus.repair_y);
		cvtbuf.word[0] = cnt;
		wDosMem(pc_base+0x1f8,(uint8)cvtbuf.bytes[0]) ;
		wDosMem(pc_base+0x1fc,(uint8)cvtbuf.bytes[1]) ;      
	}
}


void cal_wiregap()
{
	uint8  temp_y_scale = MachineStatus.y_scale;	
	uint8  temp_unit	= MachineStatus.Unit[AXIS_Y];
	uint16 temp_manval  = MachineStatus.manval[AXIS_Y];
	uint16 gridcnt = 0;
	MachineStatus.y_scale = 0;
	MachineStatus.Unit[AXIS_Y] = UNIT_GRID;
	MachineStatus.manval[AXIS_Y] = 0x01;
	
	WORD ly,ny;
	ly=ny=(WORD)(dReadAbsPos(AXIS_Y));
	while (ly == ny){
		ly = ny;
		KeyPLUSY();mDelay(300);
		ny = (WORD)(dReadAbsPos(AXIS_Y));
		gridcnt++;
		if (gridcnt >100)break; 
	}
	gridcnt = 0;
	ly = ny;	
	while (ly == ny){
		ly = ny;
		KeyMinusY();mDelay(300);
		ny = (WORD)(dReadAbsPos(AXIS_Y));
		gridcnt++;
		if (gridcnt >100)break; 
	}
	
	MachineStatus.y_scale 		 = temp_y_scale;
	MachineStatus.Unit[AXIS_Y]   = temp_unit;
	MachineStatus.manval[AXIS_Y] = temp_manval;
	MachineStatus.WireGap        = (WORD)dBinToBcd(4,gridcnt-1);
	
	open_config("rb+") ;
	save_wiregap() ;
	close_config() ;
	ShowCursor();
}
*/
void Fill_BreakCnt(int brk)
{
	cvtbuf.dword = brk;
	wDosMem(pc_base+0x1e0,(uint8)cvtbuf.bytes[0]) ;
	wDosMem(pc_base+0x1e4,(uint8)cvtbuf.bytes[1]) ;
	wDosMem(pc_base+0x1e8,(uint8)cvtbuf.bytes[2]) ;
	wDosMem(pc_base+0x1ec,(uint8)cvtbuf.bytes[3]) ;
}
void Cvtmotor_grads()
{
// 	for(int i=0 ; i < MAX_AXIS ; i++){
// 		MachineStatus.bmotor_grads[i]=BMOTORGRID(i);
// 	}
}
/*
void mdy_PM_6xxY()
{
	int idx =0 ;
	if(MachineStatus.Type ==TYPE_635_835||MachineStatus.Type == TYPE_1635_1835){
		idx=1 ;
	}
	else if(MachineStatus.Type ==TYPE_620_820){
		idx=2 ;
	}
	int offbSPDFun=MachineStatus.bSPDFun[AXIS_Y]-oPM_6xxY[idx].bSPDFun[0] ;
	int offbSPDPlus=MachineStatus.bSPDPlus[AXIS_Y]-oPM_6xxY[idx].bSPDPlus[0] ;
	int offbSPDMinus=MachineStatus.bSPDMinus[AXIS_Y]-oPM_6xxY[idx].bSPDMinus[0] ;
	for(int i=0 ; i < 6 ; i++){
		PM_6xxY.rpm[i]=oPM_6xxY[idx].rpm[i] ;
		if((oPM_6xxY[idx].bSPDFun[i] !=0)&&((oPM_6xxY[idx].bSPDFun[i]+offbSPDFun)> 0)){
			PM_6xxY.bSPDFun[i]=oPM_6xxY[idx].bSPDFun[i]+offbSPDFun ;
		}
		else{
			PM_6xxY.bSPDFun[i]=0 ;
		}
		
		if((oPM_6xxY[idx].bSPDPlus[i] !=0)&&((oPM_6xxY[idx].bSPDPlus[i]+offbSPDPlus)> 0)){
			PM_6xxY.bSPDPlus[i]=oPM_6xxY[idx].bSPDPlus[i]+offbSPDPlus ;
		}
		else{
			PM_6xxY.bSPDPlus[i]=0 ;
		}	
		if((oPM_6xxY[idx].bSPDMinus[i] !=0)&&((oPM_6xxY[idx].bSPDMinus[i]+offbSPDMinus)> 0)){
			PM_6xxY.bSPDMinus[i]=oPM_6xxY[idx].bSPDMinus[i]+offbSPDMinus ;
		}
		else{
			PM_6xxY.bSPDMinus[i]=0 ;
		}
	}
}
void MdySpeed_PMfun(ActTbl_t HUGE *a_tbl ,WORD	idx,uint8 Speed_P,uint8 Speed_M,uint8 Speed_fun)
{
	if(MachineStatus.ManSpeed_PMfun[2] !=0){
		if(Speed_P > a_tbl[idx].mov){
			a_tbl[idx].mov=Speed_P ;
		}
		if(Speed_M > a_tbl[idx].ref){
			a_tbl[idx].ref=Speed_M ;
		}
		if(Speed_fun > a_tbl[idx].sdchk_pos){
			a_tbl[idx].sdchk_pos=Speed_fun ;
		}
	}
}
*/
//----------------------------------------------------------------------------------------------------------------

void SoftReset (void)
{	
// 	PauseClock_flg=false;	//2012_1123_暫停旗標---------
// 	flag_run=false ;		
// 	PAUSE_Y=false;		//Gcode送線暫停標記
// //	DISABLE();
// 	nSet8254(CLOSE_SC) ;
// 	
// 	
// 	if(NewH){
// 		CLOCKType=RUN_CLOCK ;
// 		wDosMem(pc_base+DriverClear,(uint8)0xff);
// 		//清除dda  buffer
// 		cnt_Set3701=0 ;
// 		for(uint8 axis=0 ;axis < MachineStatus.axis_no ; axis++){
// 			DDATbl[axis].totalms=0 ;
// 		}
// 		//等待 queue =0 ;
// 		for(uint8 axis=0 ; axis < MachineStatus.axis_no ; axis++){
// 			uint16 qLen ;
// 			do{
// 				qLen =rDosMemw(pc_base+0xf00+axis*2) ;
// 			}
// 			while(qLen !=0) ;
// 		}
// 		
// 		
// 		//RInitImage() ;
// 		//flush_proc_queue() ;
// 		wDosMem(pc_base+DriverClear,(uint8) 0x00);
// 	longjmp(RetBuf,RetVal) ;
// 	}
// 	
}


//2012_03----------------------------------------------------------------------------------------------------------------------------------
bool chkOverLimit(uint8 axis,uint8 dir,uint8 man_hand)
{
// 	if (flag_RRealAxis)return (false);
// 	uint32  dincval;
// 	if( MachineStatus.motor[axis] ){
// 		//dincval = (man_hand==0)? BcdToBin(3, MachineStatus.manval[axis]):BcdToBin(3, MachineStatus.handval[axis]);
// 		dincval = (man_hand==0)? MachineStatus.manval[axis]: MachineStatus.handval[axis];
// 		if( axis==AXIS_Y && MachineStatus.y_scale )  dincval *= 10;
// 		int32 newval= BcdToBin(8,MachineStatus.axis_val[axis] ,MachineStatus.sign[axis]);
// 		int32 tt= (isPLUS_SIGN(dir)?dincval:-(int32)dincval) ; 
// 		newval += tt ;
// 		if(MachineStatus.Unit[axis]== 1){ //角度
// 			while(newval >=3600){
// 				newval-=3600 ; 
// 			}
// 			while(newval <=-3600){
// 				newval +=3600 ;
// 			}
// 		}
// 		int32 min= BcdToBin(8,MachineStatus.Min[axis] ,MachineStatus.Min_sign[axis]) ;
// 		int32 max= BcdToBin(8,MachineStatus.Max[axis] ,MachineStatus.Max_sign[axis]) ;
// 		if(((max != 999999)&&(newval > max)) || ((min != -999999)&&(newval < min))){
// 			/*
// 			if(DisplayOverLimit){
// 				DispMsgWin_q(-1, -1, WAR_WIN, 	"超 過 軟 體 極 限!",
// 											" Over software Limit");
// 				WAIT_NEW_KEY();
// 				ClrMsgWin_q();
// 			}
// 			*/
// 			return(true) ;
// 		}
// 	 	else{
// 	 		return(false) ;
// 	 	}
// 	}
// 	return(true);
}

long cal_rpm(int axis , long tms , long tdist)
{ 
	
// 	long long t2=ms*BMOTORGRID(axis);
// 	long long ms = tms ;
// 	long long dist=tdist;
// 	long long t1= dist*1000*60 ;
// 	long rpm ;
// 	if(t2 !=0){
// 	 	rpm=  (t1*10/t2+5)/10 ;
// 	 }
// 	 else{
// 	 	rpm=0 ;
// 	 }
// 	return(rpm) ;
// }
// long absval(long tt)
// {
// 	if(tt < 0){
// 		tt=-tt ;
// 	}
// 	return(tt) ;
}

WORD cal_cnt8254(WORD speed, WORD spd)
{
// 	WORD cnt8254 = 0;
// 	if (USE_20SC){//(1),2~20
// 		cnt8254 = (WORD)((spd*MachineStatus.cnt8254*10L)/(speed*10L));
// 		if(cnt8254 > MachineStatus.cnt8254){
// 			cnt8254 = MachineStatus.cnt8254 ;//最大段度:SPD變快的極限
// 		}
// 		else if (cnt8254 < 2){
// 			cnt8254 = 2 ;//最小段度:SPD變慢的極限
// 		}
// 	}
// 	else { //(0),51*0xd~1*0xd
// 		cnt8254 = (WORD)((speed*MachineStatus.cnt8254*10L)/(spd*10L));
// 		WORD tt = (axis_type==ARM_AXIS)?cnt8254:(cnt8254/0xd);
// 		if(tt == 0){
// 			cnt8254 = (axis_type==ARM_AXIS)?1:0xd ;//最大段度:SPD變快的極限
// 		}
// 		else if (tt > 51){
// 			cnt8254 = (axis_type==ARM_AXIS)?51:(51*0xd) ;//最小段度:SPD變慢的極限
// 		}
// 	}
// 	return cnt8254;	
}

//設定Speed Count值,其值愈小速度愈快(但0為停止不動)
//       =0xd-------全速執行
//       =2*0xd-----執行速度減半

//USE_20SC
//       =20----全速執行
//       =1-----不動


void nSet8254 (uint16 cnt)
{
	if (USE_20SC){
		if(	cnt	!= Old54Val	){
			wDosMem_pc_base(0xe5 , cnt);
			Old54Val = cnt;
			
			//static int tt= 0;					
			//char buf[100];
			//sprintf(buf,"%4d cnt=%d   ",tt++,cnt);
			//DispStatusBar_q(buf) ;
		}
	}
	else {
		Set8254 (cnt);
	}
}

/*
void ResetLED (void)
{
	uint8 mag,haxis,qlen;
	mag=rDosMem(pc_base+0xc24) ; 
	if(NewH && KeyLockCHG){
		comm_port=0;
	}

}
*/

void nInitMotorIo (void)
{
// 	Para51[0]= 0xff;
// 	Para51[1] = 0;
// 			wDosMem(pc_base+0x114 ,(uint8)0xFF) ;   // disable home interrupt
// 			wDosMem(pc_base+0x10a ,(uint8)0x00) ; //disable ex home interrupt

// 	nSet8254(MachineStatus.cnt8254);
}

//原點讀到0 ,平時為1
bool GetMotorZrt(uint8 axis)
{
	uint8 status ,mask ;
	if(axis <=7){
			status = rDosMem(pc_base+0xf7) ;
			mask = 1<< axis ;
			return(status&mask) ;
	}
}


void cal_rrpm(struct TIMER t1,struct TIMER &ticks,int &rpm , int &rpmd)
{
	long long m;
	long long static timer0tmp=0;
	long long dif =  ELAAPSED_CNT(t0,t1) ;
	ticks.timer = dif*182UL/(10UL*TIMER0_HZ) ; //  1193UL*182UL/10000UL
	if(ticks.timer <=0){
		ticks.timer =100 ;
	}
	//printf("%lld=%lld-%lld",dif,t1,t0);
	//timer0tmp=TimerTicks2.timer;
	t0=t1 ;
	m   = (ticks.timer*10*1000)/(182*60);
	//生產時間重算
	if(NewH){
		//if(dif!=dif%10000)
		//	dif=dif-(dif%1000);
		rpmd= (short)(m==0?0:((60*1000*10*10)/dif)%10);
		rpm = (short)(m==0?0:(60*1000*10)/dif);
	}
	//printf("dif=%lld__%d__%d\n",dif,(60*1000*10*10)/dif,((60*1000*10*10)/dif)%10);
	//printf("rpmd=%d__rpm=%d\n",rpmd,rpm);
}

/*
void CvtXGRID(void)
{
	XGRID.g2 		= 2;		XGRID_TO_GRID(AXIS_X,XGRID.g2);	
	XGRID.g10 	= 10;		XGRID_TO_GRID(AXIS_X,XGRID.g10);
	XGRID.g3950 = 3950;	XGRID_TO_GRID(AXIS_X,XGRID.g3950);
}
*/
/*
void  ADD_Delay_ms(ActTbl_t HUGE	*a_tbl , WORD &idx , DWORD ms)
{
	a_tbl[idx].cmd			 = SET_DELAY;
	a_tbl[idx].u.Delay	 = ms;	//Delay單位為毫秒
	a_tbl[idx].sdchk_pos = 0;
	a_tbl[idx].next	 		 = 0;
	idx++;		EPT_IDX(idx, ActTbl);
	a_tbl[idx].cmd	 		= WAIT_DELAY;
	a_tbl[idx].next	 		= 0;
	idx++;		EPT_IDX(idx, ActTbl);
}
*/

