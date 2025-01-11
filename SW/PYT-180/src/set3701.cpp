#include "header.h"





//#define TRACE_set3701cmd
#ifdef TRACE_set3701cmd
	struct SET3701CMD set3701cmd[NOSET3701CMD] ;
	int idx_set3701cmd ;
	struct ERR  Err;
#endif

void init_set3701cmd()
{
#ifdef TRACE_set3701cmd
	idx_set3701cmd=0 ;
#endif
}

#include "disperr.cpp"
void Set3701 (uint8 axis, uint8 dir, int32 ref, int32	mov	,int32 rmov,bool run,int32 ymov,int idms)
{
// //重新改寫
// 	if(mov ==0 && !run)return ;
// 	if(NewH){
// 		if(mov !=0){
// 			ChkOverFlow[axis]=true ;  //檢查"伺 服 失 敗"
// 			chk_unconnector= true ;		//檢查"馬 達 線 掉 了"
// 			enable_chk_unconnector[axis]= true ;
// 			if(mov > 0){
// 				DDATbl[axis].dir=dir ;		
// 				DDATbl[axis].movval=mov ;
// 			}
// 			else{
// 				DDATbl[axis].dir=isPLUS_SIGN(dir)?MINUS_SIGN:PLUS_SIGN ;		
// 				DDATbl[axis].movval=-mov ;
// 			}
// 			
// 			if(NewH && axis==AXIS_Y && !chk_run_touch){
// 					TouchWire+=DDATbl[axis].movval;
// 				//Sprintf("%d %d",TouchWire,DDATbl[axis].movval);
// 				//Sprintf("%d",TouchWire);
// 			}
// 			DDATbl[axis].new_accval=0;
// 			//to3701ms=0;
// 			DDATbl[axis].curms=0 ;
// 			DDATbl[axis].lmovval=0 ;
// 			DDATbl[axis].totalms=ref ;
// 			DDATbl[axis].idms =idms ;
// 			if(axis==AXIS_X)DDATbl[axis].idms=0; //x軸idms填0
// 			DDATbl[axis].avgms=DDATbl[axis].totalms-DDATbl[axis].idms ;
// 			DDATbl[axis].curval=0 ;
// 			DDATbl[axis].accval=0 ;
// 			DDATbl[axis].remainingval=0  ;
// 			Mov3701Val[axis] = 0;
// 			Set3701Val[axis] =	isPLUS_SIGN(dir)? rmov : -(SDWORD)rmov;
// 			Abs3701Pos[axis] = dReadAbsPos(axis);
// 			}
// 		if(run){
// 			int  cnt =0 ;
// 			for(BYTE axis =0 ; axis <  MachineStatus.axis_no ; axis++){ 
// 				if(DDATbl[axis].totalms !=0){
// 					cnt++ ;
// 				}
// 			}
// 			//DISABLE() ;
// 			cnt_Set3701 =cnt ;
// 			curRatio=100 ;
// 			//ENABLE() ;
// 		}
// 	}

}

