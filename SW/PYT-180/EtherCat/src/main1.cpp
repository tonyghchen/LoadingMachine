/******************************************************************************
 *  File    :   main1.cpp
 *  Version :   1.00
 *  Date    :   2022/06/07
 *  Author  :   chan-fa
 *
 *
 *
 * @copyright (C) 2022.
 *
 ******************************************************************************/
#include <stdint.h>
#include "..\src\test.h" 
#include "app_config.h"
#include "NuMicro.h"
#include "EtherCatInterface.h"
#include "platform.h"
#include "ec.h"

#define DEBUG_RUN_COUNTS    5000
#define DEBUG_STOP_COUNTS   3000
#define MAXSPEED   10000			

uint32_t gu32AccDecTable[500];

extern "C" {
int kbhit(void);
}



uint32_t differential_cnt(uint8_t axis) 
{
	  uint32_t ActualLoc  ;
		EtherCatGetActualPos(axis, &ActualLoc);									
		if(gstProcessState.u32Pos[axis] >= ActualLoc){
				return(gstProcessState.u32Pos[axis]-ActualLoc);
		}
		else{
				return(ActualLoc-gstProcessState.u32Pos[axis]);
		}
}
void MotionDirectionToggle()
{
     gstProcessState.u8ReserveRotation = gstProcessState.u8ReserveRotation ? 0 : 1;   
}


int setNextPosition(uint32_t ppr, int nPos, int u8ClockWise) 
{
    int dfAccStep = (ppr/1000);

    int nNextPos ;
        
    if (u8ClockWise){   
        nNextPos = dfAccStep;
    }
    else{
        nNextPos = -dfAccStep;
    }
    
    return (nNextPos);
}
void ClrTouch()
{
		//清除clear touch 訊號
		FPGA_WRITE8(0xc12,0x00) ; //'0'disable & clear interrupt
		switch(gstProcessState.touch){
			case 1:
			case 5:
				ClrTouchAir(1) ;
				FPGA_WRITE8(0xf8,0) ;  //T1發生時不停軸
				break ;
			case 2:
			case 6:
				ClrTouchAir(2) ;
				FPGA_WRITE8(0xf9,0) ;  //T2發生時不停軸
				break ;
			case 3:
			case 7:
				ClrTouchAir(3) ;
				FPGA_WRITE8(0xfa,0) ;  //T3發生時不停軸
				break ;
			case 4:
			case 8:
				ClrTouchAir(4) ;
				FPGA_WRITE8(0xfb,0) ;  //T4發生時不停軸
				break ;
		}		
		FPGA_WRITE8(0xf2,0) ;   //清除Driver Clear		
}


bool CheckTouchProbeStatus(uint16_t u16ProbeState)
{
    uint32_t u32FAxisVendorId = gstProcessState.u32Vid[FAxis];
    bool     bTouchProbePositionStore = false;
    
    // 三洋馬達(0x1b9)
    // 安川馬達(0x539)
    if(u32FAxisVendorId == 0x01b9 || u32FAxisVendorId == 0x539){
        if((u16ProbeState&0x700)== 0x300){
            bTouchProbePositionStore = true;
        }
    }
    return (bTouchProbePositionStore);
}


uint16_t getTouchProbeFunction(void)
{
    uint16_t u16FunctionCode = 0x1313;
    uint32_t u32FAxisVendorId = gstProcessState.u32Vid[FAxis];
    
    // 三洋馬達(0x1b9)
    // 安川馬達(0x539)    
    if(u32FAxisVendorId == 0x01b9){
        u16FunctionCode = 0x1313;
    }
    else if (u32FAxisVendorId == 0x539){
        u16FunctionCode = 0x1300;        
    }
    return (u16FunctionCode);
}


	uint8_t HWPower[3]={2,8,20};

/*
 * Desc
 *      callback function before PDO transmit 
 *      PDO交換前將呼叫此函數.
 * Param
 *      slaveIndex:
 *      pVid:
 *      pPid:
 * Return
 *      ECM_DEVICE_NONE : No error
 *      ECM_DEVICE_XXX: Error occur
 * */
uint32_t accval[20]={0,0,0,0,0,0,0,0,0,0} ;
uint32_t printcnt =0 ,printcnt1=0;
uint32_t  Pos[20],lPos[20],entcnt[20] ;
uint16_t lp;
uint32_t lPos2 ;
uint32_t lu32Pos ;
uint32_t tt11 ;
uint16_t lProbeState ;
void UserProcessPDO (void)
{
#if 1
	      cnt_UserProcessPDO++ ;
				static bool first=true ;
				if(first){
					first=false ;
					for(int DrvIdx=0 ;DrvIdx < gstProcessState.u8DriverCnt; DrvIdx++){ 
						EtherCatSetCtrlWord(DrvIdx, 0xF);
						EtherCatGetActualPos(DrvIdx, &gstProcessState.u32Pos[DrvIdx]);
					}
					tt11=cnt_UserProcessPDO+5000 ;
				}
				
// 				uint32_t ttpos1,ttpos2 ;
// 				for(int i=3 ; i< 5 ;i++){
// 					EtherCatGetTargetPos(i,&ttpos1) ;				
// 					EtherCatGetActualPos(i,&ttpos2) ;
// 					RTT("Target Pos =%x ,Actual Pos=%x",ttpos1,ttpos2) ;				
// 					ttpos2+=100 ;
// 					EtherCatSetTargetPos(i,ttpos2) ;
//         }					
				



				
				if(flgSetTouchProbeMode){
					//設定Touch Probe 功能
					RTT("flgSetTouchProbeMode FAxis=%d",FAxis) ;
					flgSetTouchProbeMode=false ;
                    //
                    uint16_t u16TouchProbeFunctionCode = getTouchProbeFunction();
					EtherCatSetTouchProbeMode(FAxis,u16TouchProbeFunctionCode) ;
				}
			
				
				
				
		
#ifdef RTT_TRACE_LOC
				uint32_t  ActualLoc ,FollowingErrorActualValue;
				if(TraceLoc.flg){
					  if(TraceLoc.axis!=100){
							EtherCatGetActualPos(TraceLoc.axis-1, &ActualLoc);
//						EtherCatGetFollowingErrorActualValue(TraceLoc.axis-1,&FollowingErrorActualValue);
//							RTT("%d ,%u,%u, %d ,%d , %d ",TraceLoc.lenBuf,ActualLoc,gstProcessState.u32Pos[TraceLoc.axis-1],(TraceLoc.lenBuf==0?0:gstProcessState.u32Pos[TraceLoc.axis-1]-TraceLoc.ltar),gstProcessState.u32Pos[TraceLoc.axis-1]-ActualLoc,FollowingErrorActualValue) ;
// 							RTT("%d ,%u,%u, %d , %d  ",TraceLoc.lenBuf,ActualLoc,gstProcessState.u32Pos[TraceLoc.axis-1],(TraceLoc.lenBuf==0?0:gstProcessState.u32Pos[TraceLoc.axis-1]-TraceLoc.ltar),gstProcessState.u32Pos[TraceLoc.axis-1]-ActualLoc) ;
// 							SRAM_WRITE32(TraceLocActual+TraceLoc.lenBuf*4,ActualLoc) ;
// 							SRAM_WRITE32(TraceLocTarget+TraceLoc.lenBuf*4,gstProcessState.u32Pos[TraceLoc.axis-1]) ;
// 							SEGGER_SYSVIEW_Update_SampleData(uint32_t u32TargetPos, uint32_t u32ActualPos) ;
							TraceLoc.lenBuf++;
							if(ActualLoc==gstProcessState.u32Pos[TraceLoc.axis-1]){
								TraceLoc.cnt++ ;
								if(TraceLoc.cnt ==5){
									RTT("-------------------------------------------------------------------------------") ;
									TraceLoc.flg=false ;
									TraceLoc.axis=100 ;
								}
							}
							else{
								TraceLoc.cnt=0 ;
							}
							if(TraceLoc.ltar ==gstProcessState.u32Pos[TraceLoc.axis-1]){
								TraceLoc.cnt1++ ;
								if(TraceLoc.cnt1==100){
// 									TraceLoc.flg=false ;
// 									TraceLoc.axis=100 ;
									RTT("--------------------------------------------------------------------------") ;
								}
							}
							else{
								TraceLoc.cnt1=0 ;
							}
							TraceLoc.lact=ActualLoc ;
							TraceLoc.ltar=gstProcessState.u32Pos[TraceLoc.axis-1] ;
						}
				}
#endif				
				
				
											
				if(flgRePower){
					for(int DrvIdx=0 ;DrvIdx < gstProcessState.u8DriverCnt; DrvIdx++){ 
						EtherCatGetActualPos(DrvIdx, &gstProcessState.u32Pos[DrvIdx]);
						EtherCatSetTargetPos(DrvIdx, gstProcessState.u32Pos[DrvIdx]);								
					}
					flgRePower= false ;
					
				}
				
				
				
				
				for(int DrvIdx=0 ;DrvIdx < gstProcessState.u8DriverCnt; DrvIdx++){ 
						EtherCatGetStatusWord(DrvIdx,&gstProcessState.StatusWord[DrvIdx]) ;
// 					  if(gstProcessState.StatusWord[DrvIdx] != lStatusWord[DrvIdx]){
// 							RTT("DrvIdx=%d statusWord %x->%x",DrvIdx,lStatusWord[DrvIdx], gstProcessState.StatusWord[DrvIdx]) ;
// 							if((lstatus[DrvIdx]==0x640) && (gstProcessState.StatusWord[DrvIdx]==0x650)){
// 									//大電關閉又重起
// 								  flgRstart[DrvIdx]=true ;
// 							}							}
// 							lStatusWord[DrvIdx]=gstProcessState.StatusWord[DrvIdx] ;
// 						}
// 				}
// 				for(int DrvIdx=0 ;DrvIdx < gstProcessState.u8DriverCnt; DrvIdx++){
// 					    if(!flgRstart[DrvIdx]){
// 								break ;
				}
				
				
				
				
				
				
				//山洋(SANYO DENKI)馬達----encoder換電池---¬ Encoder Clear
				int DrvIdx=AxisResetEncoderClr ;
				if(flgEncoderClr==0){
				}
				else if((flgEncoderClr>=1)&& (flgEncoderClr<=115)){
					RTT("flgEncoderClr=%d status word=%x",flgEncoderClr,gstProcessState.StatusWord[DrvIdx]) ;
					if(flgEncoderClr==1){
						EtherCatSetCtrlWord(DrvIdx, 0x1000);
					}
					flgEncoderClr++ ;
				}
				else{
					RTT("End Encoder clr") ;
					EtherCatSetCtrlWord(DrvIdx, 0x0000);
					flgEncoderClr=0 ;
					flgReset=1 ;
				}

				
				
				
				// reset 驅動器
				if(((gstProcessState.StatusWord[DrvIdx]&0x27)!=0x27) &(flgReset !=0)){
					RTT("cnt_UserProcessPDO =%d flgReset=%d status word =%x",cnt_UserProcessPDO,flgReset,gstProcessState.StatusWord[DrvIdx]) ;
				}
				if(flgReset==0){
				}
				else if(flgReset==1){
						//reset initial 
						EtherCatGetActualPos(DrvIdx, &gstProcessState.u32Pos[DrvIdx]);
						EtherCatSetTargetPos(DrvIdx, gstProcessState.u32Pos[DrvIdx]);			
					
						RTT("Reset=0ControlWORD=%x",0x00) ;
						EtherCatGetActualPos(DrvIdx, &gstProcessState.u32Pos[DrvIdx]);
						EtherCatSetTargetPos(DrvIdx, gstProcessState.u32Pos[DrvIdx]);								
            RTT("Driver=%d status word =%x",DrvIdx,gstProcessState.StatusWord[DrvIdx]) ;							
						EtherCatSetCtrlWord(DrvIdx, 0x00);
					  flgReset++ ;
				}
				else if(flgReset == 2){
						// Reset Off
						RTT("Rest=1 ControlWORD=%x",0x80) ;
            RTT("Driver=%d status word =%x",DrvIdx,gstProcessState.StatusWord[DrvIdx]) ;							
						EtherCatSetCtrlWord(DrvIdx, 0x80);
					  flgReset++ ;
				}
				else if(flgReset == 3){
						if((gstProcessState.StatusWord[DrvIdx]&0x4f)== 0x40){
							RTT(" switch ON disable ");
							RTT("ControlWORD=%x",0x06) ;
							RTT("Driver=%d status word =%x",DrvIdx,gstProcessState.StatusWord[DrvIdx]) ;							
							EtherCatSetCtrlWord(DrvIdx, 0x06);
							flgReset++ ;
						}
				}
				else if(flgReset == 4){
					if((gstProcessState.StatusWord[DrvIdx]&0x2f)==0x21){
					  RTT(" Ready to switch ON");
						RTT("Reset=0 ControlWORD=%x",0x0f) ;
            RTT("Driver=%d status word =%x",DrvIdx,gstProcessState.StatusWord[DrvIdx]) ;							
					  EtherCatSetCtrlWord(DrvIdx, 0x0F);
						flgReset++ ;
					}
				}
				else if(flgReset == 5){
					if((gstProcessState.StatusWord[DrvIdx]&0x2f)==0x27){
						RTT(" operation enable & servo ON ");
            RTT("Driver=%d status word =%x",DrvIdx,gstProcessState.StatusWord[DrvIdx]) ;							
						flgReset=0 ;
					}
				}
				
				
				
#if (defined(TEST_MANMOV_KEY) || defined(TEST_MANMOV_UART))
				
				
//手動
				if(MAN_MOV.DrvIdx !=0xff){
					MAN_MOV.ms++ ;
					uint8_t MS_END=((MAN_MOV.state == STATE_INC_MANMOV)|| (MAN_MOV.state== STATE_DEC_MANMOV))? INCMS_MANMOV:MS_MANMOV ;
					uint32_t tacc=(uint64_t)MAN_MOV.step*MAN_MOV.ms/ MS_END ;
					uint32_t mov = tacc-MAN_MOV.acc;
					
					uint32_t tfrwacc=(uint64_t)MAN_MOV.frwstep*MAN_MOV.ms/ MS_END ;
					uint32_t frwmov = tfrwacc-MAN_MOV.frwacc;
					
					
					if(MAN_MOV.state == STATE_INC_MANMOV){
						 uint32_t tmov=mov*MAN_MOV.ms/MS_END ;
						 MAN_MOV.buf[MAN_MOV.ms-1]=mov-tmov ;
						 mov=tmov ;
						
						
						 tmov=frwmov*MAN_MOV.ms/MS_END ;
						 MAN_MOV.frwbuf[MAN_MOV.ms-1]=frwmov-tmov ;
						 frwmov=tmov ;

					}
					else if(MAN_MOV.state == STATE_DEC_MANMOV){
						mov=MAN_MOV.buf[MAN_MOV.ms-1] ;
						frwmov=MAN_MOV.frwbuf[MAN_MOV.ms-1] ;
					}
					MAN_MOV.acc=tacc ;
					MAN_MOV.frwacc=tfrwacc ;
				RTT("frwmov==%d MAN_MOV.frwacc=%d MAN_MOV.frwdir=%d MAN_MOV.frwstep=%d",frwmov,MAN_MOV.frwacc,MAN_MOV.frwdir,MAN_MOV.frwstep) 
					
					lu32Pos=gstProcessState.u32Pos[MAN_MOV.DrvIdx] ;
					if(MAN_MOV.dir ==0){
						gstProcessState.u32Pos[MAN_MOV.DrvIdx] +=mov ;
						if(lu32Pos > gstProcessState.u32Pos[MAN_MOV.DrvIdx]){
							gstProcessState.flgOverUnder[MAN_MOV.DrvIdx]=1 ;
							gstProcessState.flgOverUnders=true ;
						}
					}
					else{
						gstProcessState.u32Pos[MAN_MOV.DrvIdx] -=mov ;
						if(lu32Pos < gstProcessState.u32Pos[MAN_MOV.DrvIdx]){
							gstProcessState.flgOverUnder[MAN_MOV.DrvIdx]=2 ;
							gstProcessState.flgOverUnders=true ;
						}	
					}
					if(frwmov !=0){
						//lu32Pos=gstProcessState.u32Pos[FAxis] ;
						if(MAN_MOV.frwdir ==0){
							//gstProcessState.u32Pos[FAxis] +=frwmov ;
						}
						else{
							//gstProcessState.u32Pos[FAxis] -=frwmov ;
						}
					}
					uint32_t cPos ;
					EtherCatGetActualPos(MAN_MOV.DrvIdx, &cPos);
					EtherCatSetTargetPos(MAN_MOV.DrvIdx, gstProcessState.u32Pos[MAN_MOV.DrvIdx]); 
					//EtherCatSetTargetPos(FAxis, gstProcessState.u32Pos[FAxis]); 
 					RTT("Axis %d: TPos:%d, APos=%d, m:%d",MAN_MOV.DrvIdx, gstProcessState.u32Pos[MAN_MOV.DrvIdx], cPos, mov);
					if(MAN_MOV.ms == MS_END){
						MAN_MOV.ms=0 ;
						MAN_MOV.acc=0 ;
						MAN_MOV.frwacc=0 ;
						switch(MAN_MOV.state){
							case STATE_INC_MANMOV:
						  case STATE_SAME_MANMOV:
								//是否連按?
							  bool flgcont=false ;
							  while(UART_Complete()){
									if(CmdBufTbl[ridx_CmdBufTbl].cmd!=defUART_wManualUpDown_0xc0){
										RTT("no continue... cmd%x",CmdBufTbl[ridx_CmdBufTbl].cmd) ;
										UART_Update_ridx_CmdBufTbl() ;
										continue ;
									}	
									uint8_t idx =0 ;
									uint8_t DrvIdx=CmdBufTbl[ridx_CmdBufTbl].buf[idx++] ;
									uint8_t dir=CmdBufTbl[ridx_CmdBufTbl].buf[idx++] ;
									if(((DrvIdx-1)== MAN_MOV.DrvIdx)&& (dir == MAN_MOV.dir)){
										  gstProcessState.contMAN_DrvIdx=DrvIdx;
											MAN_MOV.frwstep=*(uint32_t *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
											MAN_MOV.frwdir= MAN_MOV.dir ;
											if(MAN_MOV.frwstep& BIT31){
												MAN_MOV.frwstep = -(int)MAN_MOV.frwstep ;
												MAN_MOV.frwdir=(MAN_MOV.frwdir==0)?1:0 ;
											}
											idx+=4 ;
											MAN_MOV.step=*(uint32_t *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
											idx+=4 ;
											gstProcessState.contMAN_lstep=MAN_MOV.lstep=*((uint32_t *)&(CmdBufTbl[ridx_CmdBufTbl].buf[idx]) );
											gstProcessState.flgcontMAN=true ;
										  RTT("Continue.........................r%d",ridx_CmdBufTbl) ;
											UART_Update_ridx_CmdBufTbl() ;
										  MAN_MOV.state=STATE_SAME_MANMOV ;
										  flgcont=true ;
									}
									break ;
								}
								if(!flgcont){
									MAN_MOV.state=STATE_DEC_MANMOV ;
								}
							  break ;
						  case STATE_DEC_MANMOV:
								RTT("Complete......................................................................") ;
								MAN_MOV.DrvIdx=0xff ;
								break ;
						}
					}
				}
				
				
				
				
				
				
//回原點或虛擬原點				
				if(flgMoveStep){
					if(gstProcessState.CurrentState==AITestState){  //AI 區塊測試
							gstProcessState.speed=10 ;
					}
					else{
						if(gstProcessState.VRAUTOHOME== EC_VRHOME_MODE){
							gstProcessState.speed = gstProcessState.adc;
						}
						else{
							gstProcessState.speed=100 ;
						}
					}
					int org_remind=gstProcessState.remind ;
					if(gstProcessState.remind !=0){
						//計算剩下的是否夠
						if(gstProcessState.remind >=gstProcessState.speed){
							uint8_t tt=gstProcessState.remind-gstProcessState.speed ;
							for(int i=0 ; i < NoMoveStep;i++){
								if(MoveStep[i].axis!=0){
									MoveStep[i].mov=(MoveStep[i].curstep*gstProcessState.remind)/100-(MoveStep[i].curstep*tt)/100 ;
									if(MoveStep[i].frwstep !=0){
										MoveStep[i].frwmov=(MoveStep[i].frwcurstep*gstProcessState.remind)/100-(MoveStep[i].frwcurstep*tt)/100 ;
									}
								}
							}
							gstProcessState.remind=tt ;
							gstProcessState.speed=0 ;
						}
						else{
							for(int i=0 ; i < NoMoveStep;i++){
									MoveStep[i].mov=(MoveStep[i].curstep*gstProcessState.remind)/100 ;
								  if(MoveStep[i].frwstep !=0){
										MoveStep[i].frwmov=(MoveStep[i].frwcurstep*gstProcessState.remind)/100 ;
									}
							}
							gstProcessState.speed=gstProcessState.speed- gstProcessState.remind;
							gstProcessState.remind=0 ;
						}
					}
					else{
						for(int i=0 ; i < NoMoveStep;i++){
								MoveStep[i].mov=0 ;
								MoveStep[i].frwmov=0 ;							  
						}
					}
					bool flgcnt=false ;
					if(gstProcessState.speed!=0){
						  flgcnt=true;
							if(org_remind!=0){
								for(int i=0 ; i < NoMoveStep;i++){
									if((MoveStep[i].lastms)){
										flgcnt=false ;
										break ;
									}
								}
							}
					}
					
					
					if(flgcnt){
						bool  ok=true ;
						msMoveStep++ ;
						gstProcessState.remind=100 ;
						uint8_t tt = gstProcessState.remind-gstProcessState.speed ;
						for(int i=0 ;i < NoMoveStep;i++){
							//計算目前ms的格數
							if(MoveStep[i].ms >= msMoveStep){
								ok=false ;
								uint8_t axis=MoveStep[i].axis-1 ;
								uint32_t curms=(msMoveStep) ;
								uint32_t rectms = (MoveStep[i].ms - MoveStep[i].idms) ;
								uint32_t mov ;
								uint32_t frwmov ;
								if(MoveStep[i].ms >=curms){
									MoveStep[i].lastms=(MoveStep[i].ms==curms)?true:false ;
// 									if(curms== 1){
// 											gstProcessState.curstep[axis]=0 ;
// 											gstProcessState.step[axis]=MoveStep[i].step;
// 											gstProcessState.src_pos[axis]=MoveStep[i].src_pos ;
// 											gstProcessState.dst_pos[axis]=MoveStep[i].dst_pos;
// 											gstProcessState.src_u32Pos[axis]=gstProcessState.u32Pos[axis] ;
// 											gstProcessState.flgDisplays=gstProcessState.flgDisplay[axis]=true ;
// 									}
									if(rectms  >= curms ){
										uint32_t tacc=(uint64_t)MoveStep[i].step*curms/rectms ;
										mov = tacc-MoveStep[i].acc;
										MoveStep[i].acc=tacc ;
										if(MoveStep[i].idms>=curms){
											//加速度
											uint32_t mov1=curms*mov/MoveStep[i].idms ;
											SRAM_WRITE32(IdmsBuf+((MoveStep[i].axis-1)*MAX_IDMS_BUF+curms-1)*4,mov-mov1);
//  											RTT("curms=%d ,MoveStep[i].mov=%d , mov=%d mov1=%d ,MoveStep[i].idms=%d ",curms,MoveStep[i].mov,mov,mov1,MoveStep[i].idms);
											mov=mov1 ;
										}
										else{
											//定速
// 											RTT("------axis=%d mov=%d",MoveStep[i].axis,mov) ;
										}
									}
									else{
										//減速度
										mov=SRAM_READ32(IdmsBuf+((MoveStep[i].axis-1)*MAX_IDMS_BUF+(curms-rectms)-1)*4) ;
									}
// 									RTT("------axis=%d mov=%d",MoveStep[i].axis,mov) ;
									MoveStep[i].curstep=mov ;
									MoveStep[i].mov+=(MoveStep[i].curstep*gstProcessState.remind)/100-MoveStep[i].curstep*tt/100 ;
									if(MoveStep[i].frwstep!=0){
										// 補線值必須和翻線值做比例式的計算
										uint32_t frwmov1,frwmov ;
										frwmov1 = (uint64_t)MoveStep[i].curstepAcc*MoveStep[i].frwstep/MoveStep[i].step;
										MoveStep[i].curstepAcc +=MoveStep[i].curstep  ;
										frwmov =(uint64_t)MoveStep[i].curstepAcc*MoveStep[i].frwstep/MoveStep[i].step ;
										MoveStep[i].frwcurstep=frwmov-frwmov1;
										RTT("MoveStep[i].frwcurstep=%dMoveStep[i].curstep=%d,MoveStep[i].curstepAcc=%d,frwmov1=%d,frwmov=%d",MoveStep[i].frwcurstep,MoveStep[i].curstep,MoveStep[i].curstepAcc,frwmov1,frwmov) ;
										MoveStep[i].frwmov+=(MoveStep[i].frwcurstep*gstProcessState.remind)/100-MoveStep[i].frwcurstep*tt/100 ;
									}
								}
								else{
										MoveStep[i].axis=0 ;
								}
							}
						  else{
								MoveStep[i].mov=0 ;
								MoveStep[i].curstep=0 ;
							}
						}
						gstProcessState.remind=tt ;
						if(ok){
								gstProcessState.flgreadyStopMachine=true ;
						}
					}
					//執行各軸的格數
					for(int i=0 ; i < NoMoveStep ;i++){
						if((MoveStep[i].axis!=0)&& (MoveStep[i].mov !=0)){
							  uint8_t axis=MoveStep[i].axis-1 ;
								lu32Pos=gstProcessState.u32Pos[axis] ;
								if(MoveStep[i].dir ==0){
									gstProcessState.u32Pos[axis] +=MoveStep[i].mov ;
									if(lu32Pos > gstProcessState.u32Pos[axis]){
										gstProcessState.flgOverUnder[axis]=1 ;
										gstProcessState.flgOverUnders=true ;
									}
								}
								else{
// 									RTT("----BBB   %u ,%u",gstProcessState.u32Pos[axis],MoveStep[i].mov ) ;
								  gstProcessState.u32Pos[axis] -=MoveStep[i].mov ;
// 									RTT("----AAA   %u ,%u",gstProcessState.u32Pos[axis],MoveStep[i].mov ) ;
									if(lu32Pos < gstProcessState.u32Pos[axis]){
										gstProcessState.flgOverUnder[axis]=2 ;
										gstProcessState.flgOverUnders=true ;
									}
								}
								gstProcessState.curstep[axis] +=MoveStep[i].mov ;
								gstProcessState.flgDisplays=gstProcessState.flgDisplay[axis] =true ;
								uint32_t cPos ;
								EtherCatGetActualPos(axis, &cPos);
								EtherCatSetTargetPos(axis, gstProcessState.u32Pos[axis]);
//   							RTT("%d %d, %u ,%u",msMoveStep,axis,gstProcessState.u32Pos[axis],MoveStep[i].mov) ;
								if(MoveStep[i].frwstep !=0){
									axis= FAxis ;
									RTT("--------------FAxis=%d",FAxis) ;
									lu32Pos=gstProcessState.u32Pos[axis] ;
									if(MoveStep[i].frwdir ==0){
										gstProcessState.u32Pos[axis] +=MoveStep[i].frwmov ;
									}
									else{
										gstProcessState.u32Pos[axis] -=MoveStep[i].frwmov ;
									}
									uint32_t cPos ;
									EtherCatGetActualPos(axis, &cPos);
									EtherCatSetTargetPos(axis, gstProcessState.u32Pos[axis]);
// 									RTT("%d %d, %u %d  MoveStep[i].frwstep=%d",msMoveStep,axis,gstProcessState.u32Pos[axis],MoveStep[i].frwmov,MoveStep[i].frwstep) ;
								}
							}
						}
						if(gstProcessState.flgreadyStopMachine && gstProcessState.remind==0){
							gstProcessState.flgreadyStopMachine=false ;
							flgMoveStep=false ;
							flgDispZero = true ;
						}
				}
				



				
				
//				
//當全速執行(Full Speed RUN)和測試時從此處開始做
//				
//				
				
				if(flgActionTable){
					bool ok=true ;
					if(noWaitMotor){
						for(int i=0 ; i < noWaitMotor ;i++){
							uint32_t diff = differential_cnt(WaitMotor[i].axis) ;
							if(diff > WaitMotor[i].near){
								uint8_t axis=WaitMotor[i].axis ;
								RTT("wait axis=%d  %d  %d ........... ",axis,gstProcessState.u32Pos[axis],diff) ;
								ok=false ;
								break ;
							}
						}
					}
					if(!ok){
					}
					else{
						noWaitMotor=0 ;
						bool UpdatemsMoveStep=false ;
						if(gstProcessState.RUNTEST== EC_TEST_MODE){
							gstProcessState.speed = gstProcessState.adc;
							if(gstProcessState.adc==0){
								//是否啟動手輪
								if(MPG.ON !=0){
									MPG.ON-- ;
									if(MPG.ON==0){
										flgDisplayADC0=true ;
									}
									if(gstProcessState.HandWheelPower >2){
										gstProcessState.HandWheelPower=0 ;
									}
									gstProcessState.speed=HWPower[gstProcessState.HandWheelPower] ;
								}
							}
						}
						else{
							gstProcessState.speed=100 ;
						}
						if(gstProcessState.flagSPD_CHANGE){
							gstProcessState.speed=gstProcessState.SPD_CHANGE ;
						}
						else{
							gstProcessState.speed=gstProcessState.speed*gstProcessState.SPD ; //0~10000
						}
						
// 						RTT("gstProcessState.speed=%d gstProcessState.remind=%dgstProcessState.SPD=%d",gstProcessState.speed,gstProcessState.remind,gstProcessState.SPD) ;
						//依據remind&speed 決定是否需要進入下一個ms
						int org_remind=gstProcessState.remind ;
						int org_speed=gstProcessState.speed ;
						

						
						//由目前ms剩下的和目前速度計算出此次各軸馬達的移動值(此段程式只針對測試才有作用)
						if(gstProcessState.remind !=0){
							//計算剩下的是否夠gstProcessState.speed
							if(gstProcessState.remind >=gstProcessState.speed){
								//剩下的符合目前的速度
								uint16_t tt=gstProcessState.remind-gstProcessState.speed ;
								for(int i=0 ; i < NoMoveStep;i++){
									if(MoveStep[i].axis!=0){ 
										if(MoveStep[i].Start_ms == (in_Repeat?RepeatmsMoveStep:msMoveStep)){  //目前ms等於起始ms,該軸馬達不動
											MoveStep[i].mov=0 ;
											MoveStep[i].frwmov=0 ;
										}
										else{
											MoveStep[i].mov=((uint64_t)MoveStep[i].curstep*gstProcessState.remind)/MAXSPEED-((uint64_t)MoveStep[i].curstep*tt)/MAXSPEED ;
											if(MoveStep[i].frwstep !=0){
												MoveStep[i].frwmov=((uint64_t)MoveStep[i].frwcurstep*gstProcessState.remind)/MAXSPEED-((uint64_t)MoveStep[i].frwcurstep*tt)/MAXSPEED ;
											}
										}
									}
								}
								gstProcessState.remind=tt ;
								gstProcessState.speed=0 ;
							}
							else{
								for(int i=0 ; i < NoMoveStep;i++){
									if(MoveStep[i].axis!=0){
										if(MoveStep[i].Start_ms == (in_Repeat?RepeatmsMoveStep:msMoveStep)){ //目前ms等於起始ms,該軸馬達不動
											MoveStep[i].mov=0 ;
											MoveStep[i].frwmov=0 ;
										}
										else{
											MoveStep[i].mov=((uint64_t)MoveStep[i].curstep*gstProcessState.remind)/MAXSPEED ;
											if(MoveStep[i].frwstep !=0){
												MoveStep[i].frwmov=((uint64_t)MoveStep[i].frwcurstep*gstProcessState.remind)/MAXSPEED ;
											}
										}
									}
								}
								gstProcessState.speed=gstProcessState.speed- gstProcessState.remind;
								gstProcessState.remind=0 ;
							}
						}
						else{
							for(int i=0 ; i < NoMoveStep;i++){
								if(MoveStep[i].axis!=0){
									MoveStep[i].mov=0 ;
									MoveStep[i].frwmov=0 ;
								}
							}
						}
						
						//決定要不要進到下一個ms
						bool flgNextms=false ;
						if(gstProcessState.speed!=0){
								flgNextms=true;
								if(org_remind!=0){
									for(int i=0 ; i < NoMoveStep;i++){
										if((MoveStep[i].axis!=0)&& (MoveStep[i].lastms)){
											flgNextms=false ;
											break ;
										}
									}
								}
						}
						
						
						
						if(flgNextms){
							UpdatemsMoveStep=true ;
							msMoveStep++ ;
							if((NoRepeat >0)&& (idx_Repeat < NoRepeat)){
								if(msMoveStep == Repeat[idx_Repeat].Start_ms){
									in_Repeat=true ;
									Repeat[idx_Repeat].curCNT=0 ;
								}
								if(in_Repeat){
									if(msMoveStep ==Repeat[idx_Repeat].Last_ms){
										in_Repeat=false ;
										idx_Repeat++ ;
									}
								}
							}
							if(in_Repeat){
								RepeatmsMoveStep=((msMoveStep-Repeat[idx_Repeat].Start_ms)%Repeat[idx_Repeat].Len_ms)+Repeat[idx_Repeat].Start_ms;
							}
							//檢查TouchAir
							for(int i=0 ;i< 8 ;i++){
								if(TouchAir[i].used==1){
                                    uint16_t u16EndMs = TouchAir[i].Start_ms+TouchAir[i].ms;
									if(u16EndMs == (in_Repeat?RepeatmsMoveStep: msMoveStep)){
										RTT("close TouchAir") ;
										//結束TouchAir
										if(i == gstProcessState.TouchAir_touch_idx){
											//總結touch 成功與否
											RTT("Close touch") ;
											ClrTouch() ;
                                            //探針失敗時, 將設定gstProcessState.touch_yvalue=0
											gstProcessState.touch_yvalue=0 ;
											gstProcessState.CurrFailQty++ ;
											gstProcessState.flgDisplay_touch=true ;
											//TouchFail_JumpActionTable(u16EndMs);
										}
										if(TouchAir[i].air !=0){
											//關閉air
											ClrAir(TouchAir[i].air) ;
											RTT("ClrAir =%d",TouchAir[i].air) ;
										}
										TouchAir[i].used=0;
								}
							}
							}

							gstProcessState.flgCurrProductTime=true ;
							bool ok=true ;
							gstProcessState.remind=MAXSPEED ;
							uint16_t tt =0;
							if (gstProcessState.flgreadyStopMachine == false){
									tt = gstProcessState.remind-gstProcessState.speed ;
							}
							for(int i=0 ; i < NoMoveStep ;i++){
								if(MoveStep[i].axis!=0){
									//計算目前ms的馬達格數
									uint8_t axis=MoveStep[i].axis-1 ;
									uint32_t curms =msMoveStep-MoveStep[i].Start_ms;
									if(curms> MoveStep[i].ms){
										curms=MoveStep[i].ms;
										if(MoveStep[i].lastms){
											curms++ ;
										}
									}
									if(in_Repeat){
										if(RepeatmsMoveStep >= MoveStep[i].Start_ms){
											curms =RepeatmsMoveStep-MoveStep[i].Start_ms;
										}
										else{
											curms=MoveStep[i].ms;
											if(MoveStep[i].lastms){
												curms++ ;
											}
										}
									}
									uint32_t rectms = (MoveStep[i].ms - MoveStep[i].idms) ;
									uint32_t mov ;
									uint32_t frwmov ;
									if(MoveStep[i].ms >=curms){
										MoveStep[i].lastms=(MoveStep[i].ms==curms)?true:false ;
										if(curms== 1){
												gstProcessState.curstep[axis]=0 ;
												gstProcessState.step[axis]=MoveStep[i].step;
												gstProcessState.src_pos[axis]=MoveStep[i].src_pos ;
												gstProcessState.dst_pos[axis]=MoveStep[i].dst_pos;
												gstProcessState.src_u32Pos[axis]=gstProcessState.u32Pos[axis] ;
												gstProcessState.flgDisplays=gstProcessState.flgDisplay[axis]=true ;
												if((gstProcessState.TouchAir_touch_idx !=8) && axis== FAxis){ //是否為送線軸
													// 設定探針送線起始值
													gstProcessState.touch_y_dst_pos=gstProcessState.dst_pos[axis];
													gstProcessState.touch_y_step=gstProcessState.step[axis];
													gstProcessState.touch_y_u32Pos=gstProcessState.u32Pos[axis];										  
												}  
										}
										
										
										if(rectms  >= curms ){
											//目前的ms落在加速度或定速度區間
											uint32_t tacc ;
											tacc=(uint64_t)MoveStep[i].step*curms/rectms ;
											mov = tacc-MoveStep[i].acc;
											MoveStep[i].acc=tacc ;
											if(MoveStep[i].idms>=curms){
												//加速度
												uint32_t mov1  ;
												mov1=curms*mov/MoveStep[i].idms ;
                                                uint32_t u32Offset = (curms-1);
												gu32AccDecTable[u32Offset] =mov-mov1; //儲存第(curms-1)個減速於記憶體buffer
                                                //RTT("Acc : curms=%d, move=%d, offset=%08X", curms, mov-mov1, u32Offset);
												mov=mov1 ;
											}
											else{
												//定速
											}
										}
										else{
										//目前的ms落在減速度區間
                                            uint32_t u32Offset = ((curms-rectms)-1);
											mov=gu32AccDecTable[u32Offset] ;
                                            //RTT("Dec : curms=%d, move=%d, offset=%08X", curms, mov, u32Offset);
										}
										RTT("------axis=%d mov=%d",MoveStep[i].axis,mov) ;
										MoveStep[i].curstep=mov ;
										MoveStep[i].mov+=(((uint64_t)MoveStep[i].curstep*gstProcessState.remind)/MAXSPEED-(uint64_t)MoveStep[i].curstep*tt/MAXSPEED) ;
										if(MoveStep[i].frwstep !=0){
											// 補線值必須和翻線值做比例式的計算
											uint32_t frwmov1,frwmov ;
											frwmov1 = (uint64_t)MoveStep[i].curstepAcc*MoveStep[i].frwstep/MoveStep[i].step;
											MoveStep[i].curstepAcc +=MoveStep[i].curstep  ;
											frwmov =(uint64_t)MoveStep[i].curstepAcc*MoveStep[i].frwstep/MoveStep[i].step ;
											MoveStep[i].frwcurstep=frwmov-frwmov1;
// 											RTT("MoveStep[i].frwcurstep=%dMoveStep[i].curstep=%d,MoveStep[i].curstepAcc=%d,frwmov1=%d,frwmov=%d",MoveStep[i].frwcurstep,MoveStep[i].curstep,MoveStep[i].curstepAcc,frwmov1,frwmov) ;
											MoveStep[i].frwmov+=(MoveStep[i].frwcurstep*gstProcessState.remind)/MAXSPEED-MoveStep[i].frwcurstep*tt/MAXSPEED ;
										}
									}
									else{
											//此軸運動時間區域已過,故從表中刪除
											MoveStep[i].axis=0 ;
									}
								}
							}
							gstProcessState.remind=tt ;							
						}
						
						
						
						
						//執行各軸的格數
						for(int i=0 ; i < NoMoveStep ;i++){
							if((MoveStep[i].axis!=0)&& (MoveStep[i].mov !=0)){
										uint8_t axis=MoveStep[i].axis-1 ;
										lu32Pos=gstProcessState.u32Pos[axis] ;
										if(MoveStep[i].dir ==0){
											gstProcessState.u32Pos[axis] +=MoveStep[i].mov ;
											if(lu32Pos > gstProcessState.u32Pos[axis]){
												gstProcessState.flgOverUnder[axis]=1 ;
												gstProcessState.flgOverUnders=true ;
											}
										}
										else{
											gstProcessState.u32Pos[axis] -=MoveStep[i].mov ;
											if(lu32Pos < gstProcessState.u32Pos[axis]){
												gstProcessState.flgOverUnder[axis]=2 ;
												gstProcessState.flgOverUnders=true ;
											}
										}
										gstProcessState.curstep[axis] +=MoveStep[i].mov ;
// 										if(gstProcessState.curstep[axis] >gstProcessState.step[axis]){
// 											RTT("Error axis=%d %d  %d",axis ,gstProcessState.curstep[axis],gstProcessState.step[axis]);
// 										}
// 											RTT("axis=%d  mov =%d curStep=%d",axis,MoveStep[i].mov ,gstProcessState.curstep[axis]) ;
										long tt ;
										if(gstProcessState.u32Pos[axis] >= gstProcessState.src_u32Pos[axis]){
											tt=gstProcessState.u32Pos[axis]- gstProcessState.src_u32Pos[axis] ;
										}
										else{
											tt= gstProcessState.src_u32Pos[axis]-gstProcessState.u32Pos[axis] ;
										}
// 										if(tt != gstProcessState.curstep[axis]){
// 											RTT("error %d  %d  = %d %d",tt,gstProcessState.curstep[axis],gstProcessState.u32Pos[axis],gstProcessState.src_u32Pos[axis]) ;
// 										}
										gstProcessState.flgDisplays=gstProcessState.flgDisplay[axis] =true ;
										uint32_t cPos ;
										EtherCatGetActualPos(axis, &cPos);
										EtherCatSetTargetPos(axis, gstProcessState.u32Pos[axis]);
										RTT("-----%d %d, %u,%u,%d,%d,%d,%d",msMoveStep,MoveStep[i].curstep,gstProcessState.u32Pos[MoveStep[i].axis-1],cPos,MoveStep[i].mov ,org_remind,org_speed ,gstProcessState.remind) ;
// 										RTT("%u  %u   %u   %d",msMoveStep,cPos,gstProcessState.u32Pos[axis],gstProcessState.u32Pos[axis]-cPos) ;
										if(MoveStep[i].frwstep !=0){
											uint8_t axis=FAxis ;
											lu32Pos=gstProcessState.u32Pos[axis] ;
											if(MoveStep[i].frwdir ==0){
												gstProcessState.u32Pos[axis] +=MoveStep[i].frwmov ;
											}
											else{
												gstProcessState.u32Pos[axis] -=MoveStep[i].frwmov ;
											}
											uint32_t cPos ;
											EtherCatGetActualPos(axis, &cPos);
											EtherCatSetTargetPos(axis, gstProcessState.u32Pos[axis]);
// 											RTT("-----%d %d, %u  %d",msMoveStep,MoveStep[i].axis,gstProcessState.u32Pos[MoveStep[i].axis-1],MoveStep[i].mov ) ;
										}
							}
						}
						if(gstProcessState.TouchAir_touch_idx !=8){
							uint16_t ProbeState ;
							EtherCatGetTouchProbeState(FAxis,(uint16_t *)&ProbeState) ;
							if(lProbeState != ProbeState){
								RTT("Probe State=%x",ProbeState) ;
								lProbeState= ProbeState ;
							}
							if(gstProcessState.touch_state==0){
									//if((ProbeState&0x700)== 0x300){
                                    if (CheckTouchProbeStatus(ProbeState) == true){
												// touch probe active 
												EtherCatGetTouchProbe2Pos(FAxis,&gstProcessState.ProbePos) ;
												RTT("Touch probe occur %x y_step=%d ,y_src_u32Pos=%x y_dst_pos=%d  ",gstProcessState.ProbePos,gstProcessState.touch_y_step,gstProcessState.touch_y_u32Pos,gstProcessState.touch_y_dst_pos)   ;
												if (gstProcessState.touch_y_step){
														gstProcessState.touch_yvalue=gstProcessState.touch_y_dst_pos*(gstProcessState.ProbePos-gstProcessState.touch_y_u32Pos)/gstProcessState.touch_y_step ;
												}
												else{
														gstProcessState.touch_yvalue = 0;
												}
												RTT("touch value =%d",gstProcessState.touch_yvalue) ;
												gstProcessState.flgDisplay_touch=true ;
												gstProcessState.touch_state=1 ;
										
												ClrTouch() ;
												if(TouchAir[gstProcessState.TouchAir_touch_idx].touch <=4){
													//需停線
													RTT("STOP LINE",gstProcessState.ProbePos) ;
													gstProcessState.u32Pos[FAxis]=gstProcessState.ProbePos;
													EtherCatSetTargetPos(FAxis, gstProcessState.u32Pos[FAxis]);	
													TouchAir[gstProcessState.TouchAir_touch_idx].used=0 ;
													//把送線的MOVE_Step關掉
													
													for(int i=0; i < NoMoveStep ;i++){
														if(MoveStep[i].axis== (FAxis+1)){
															MoveStep[i].axis=0 ;
															MoveStep[i].mov=0 ;
															MoveStep[i].frwmov=0 ;
														}
													}
												}
									}						
							}
						}
						if(!gstProcessState.flgreadyStopMachine){
							if(UpdatemsMoveStep&&(ActionTable[idxActionTable].Start_ms==msMoveStep) && 
								(ActionTable[idxActionTable].ms==0)){
								//執行完ActionTable
								for(int i=0 ; i < NoMoveStep;i++){
									MoveStep[i].axis=0 ;
								}
								
								//更新最後位址,如果有最後角度有超過360度
								for(int i=0; i < MAX_DRIVER;i++){
									gstProcessState.dst_pos[i]=gstProcessState.OrgPos[i] ;
								}
								gstProcessState.CurrProductQty++ ;
								gstProcessState.flgAccF=gstProcessState.flgCurrProductQty=true ;
								gstProcessState.AccF=0 ;
								RTT("gstProcessState.SetProductQty=%d gstProcessState.CurrProductQty=%d",gstProcessState.SetProductQty,gstProcessState.CurrProductQty) ;
								if((gstProcessState.flgStopMachine)||((gstProcessState.SetProductQty!=0)&&(gstProcessState.CurrProductQty>=gstProcessState.SetProductQty))||((gstProcessState.SetFailQty !=0)&&(gstProcessState.CurrFailQty>=gstProcessState.SetFailQty))){
									gstProcessState.flgStopMachine=false ;
									//RTT("flgreadyStopMachine=true, gstProcessState.remind=%d", gstProcessState.remind);
									gstProcessState.flgreadyStopMachine=true ;								
								}
								else{
									gstProcessState.flagSPD_CHANGE = false ;
									idxActionTable=0 ;
									msMoveStep=0 ;
									idx_Repeat=0 ;
									in_Repeat=false ;
								}
							}
							while(UpdatemsMoveStep&&(!gstProcessState.flgreadyStopMachine)&&(idxActionTable < NoActionTable) &&((in_Repeat?RepeatmsMoveStep:msMoveStep) == ActionTable[idxActionTable].Start_ms)){
								if(ActionTable[idxActionTable].actcmd==0){
									for(int i=0 ;i <MAX_AXIS ; i++){
										if(MoveStep[i].axis== 0){
											fillActionTable(i,idxActionTable) ;
											//檢查是否需要WAIT MOTOR(即該軸還沒有到位
											uint32_t  ActualLoc,diff ;
											uint8_t axis=MoveStep[i].axis-1 ;
											if(NearMotor[axis] !=0){
												diff = differential_cnt(axis) ;
												if(diff > NearMotor[axis]){
													//motor還沒走完,必須等待
													RTT("wait axis=%d  %d  %d %d ",axis,gstProcessState.u32Pos[axis],diff,noWaitMotor) ;
													WaitMotor[noWaitMotor].axis=axis ;
													WaitMotor[noWaitMotor++].near=NearMotor[axis] ;
												}
											}
											
											
											if(i >= NoMoveStep){
												NoMoveStep=i+1 ;
											}
											break ;
										}
									}
								}
								else if(ActionTable[idxActionTable].actcmd==1){
										// touch air 
										for(int i=0; i < 8 ;i++){
											if(TouchAir[i].used==0){
												fillActionTable2TouchAir(i,idxActionTable);
												break ;
											}	
										}
								}
								else if(ActionTable[idxActionTable].actcmd==2){
										gstProcessState.SPD_CHANGE=ActionTable[idxActionTable].axis*100 ;
									  gstProcessState.flagSPD_CHANGE=true ;
								}
								idxActionTable++ ;								
								if(in_Repeat){
									if(ActionTable[idxActionTable].Start_ms== Repeat[idx_Repeat].Last_ms){
										Repeat[idx_Repeat].curCNT++ ;
										if(Repeat[idx_Repeat].curCNT!= Repeat[idx_Repeat].CNT){
												idxActionTable=Repeat[idx_Repeat].StartActionTable ;
										}
									}
								}
							}
						}
						else{
							if(gstProcessState.remind==0){
									flgActionTable=false ;
									gstProcessState.flgCompleteActionTable=true ;
							}
						}
					}
				}
				
							
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
#endif
#ifdef TEST_TOUCH_PROBE
				 uint32_t tPos ;
			   EtherCatGetActualPos(0, &tPos);

				EtherCatGetTouchProbeState(0,(uint16_t *)&ProbeState) ;
				EtherCatGetTouchProbe2Pos(0,&Pos2) ;
				if((lp!= ProbeState)|| (Pos2!= lPos2)){
					lPos2=Pos2; lp=ProbeState;
					RTT("interrupt%d---->%x,%x,%x\n",cnt_UserProcessPDO,ProbeState,Pos2,tPos) ;	
          if((lp&0x700)==0x300){
						//清除clear
						FPGA_WRITE8(0xc12,0x00) ; //'0'disable & clear interrupt
            if(touch_no==0){						
							FPGA_WRITE8(0xf8,0) ;  //T1發生時不停軸
						}
						else{
							FPGA_WRITE8(0xf9,0) ;  //T2發生時不停軸
						}
						FPGA_WRITE8(0xf2,0) ;   //清除Driver Clear		
					}
					if((lp&0x700)==0x500){
						touch_complete=true ;
					}
				}
				gstProcessState.u32Pos[0] +=200 ;
				EtherCatSetTargetPos(0, gstProcessState.u32Pos[0]); 
#endif
				
				
#ifdef TEST_SYNC
				if(Sync.run){
					if(Sync.ms < Sync.totalms){
						Sync.ms++  ;
						int step ;
						if(Sync.ms <= Sync.idms){
							//加速
							step=Sync.step*Sync.ms/Sync.idms ;
						}
						else if((Sync.ms > Sync.idms) && (Sync.ms <= (Sync.totalms-Sync.idms))){
							//等速
							step= Sync.step ;
						}
						else{
							// 減速
							step =Sync.step*(Sync.totalms-Sync.ms)/Sync.idms ;
						}
						if(Sync.dir == 0){
							gstProcessState.u32Pos[Sync.axis] +=step ;
						}
						else{
							gstProcessState.u32Pos[Sync.axis] -=step ;
						}
						EtherCatGetActualPos(Sync.axis, &Sync.Pos);
						EtherCatSetTargetPos(Sync.axis, gstProcessState.u32Pos[Sync.axis]); 
						TRACE_MSG("%d,%u,%u",Sync.ms,gstProcessState.u32Pos[Sync.axis],Sync.Pos) ;
					}
					else{
						EtherCatGetActualPos(Sync.axis, &Sync.Pos);
						if(Sync.dir ==0){
							if(Sync.Pos < gstProcessState.u32Pos[Sync.axis]){
								Sync.ms++ ;
								TRACE_MSG("%d,%u,%u",Sync.ms,gstProcessState.u32Pos[Sync.axis],Sync.Pos) ;				  
							}
							else{
								Sync.run=false ;
							}
						}
						else{
							if(Sync.Pos > gstProcessState.u32Pos[Sync.axis]){
								Sync.ms++ ;
								TRACE_MSG("%d,%u,%u",Sync.ms,gstProcessState.u32Pos[Sync.axis],Sync.Pos) ;				  
							}
							else{
								Sync.run=false ;
							}
						}
					}
				}
#endif
				
				
#ifdef TEST_BREAK

        for(int DrvIdx=0 ;DrvIdx < gstProcessState.u8DriverCnt; DrvIdx++){ 
            // config target positon for CSP Mode
						EtherCastSetCtrlWord(DrvIdx, 0xF);
						if((DrvIdx !=1)&& (DrvIdx !=0)){
									gstProcessState.u32Pos[DrvIdx] +=(gstProcessState.u32Vid[DrvIdx]==stDriverTable[0].u32Vid)? stDriverTable[0].u32PPR/1000:((gstProcessState.u32Vid[DrvIdx]==stDriverTable[1].u32Vid)?stDriverTable[1].u32PPR/1000:stDriverTable[2].u32PPR/1000)*(DrvIdx+1) ; //60RPM*DrvIdx+1
						}
						else{
									if(Break.flag&&(Break.axis==DrvIdx)){
										 EtherCatGetActualPos(DrvIdx, &Break.Pos);
										 if(Break.idx ==0){
											    TRACE_MSG("%u,%u",gstProcessState.u32Pos[DrvIdx],Break.Pos)
// 												gstProcessState.u32Pos[DrvIdx]=Break.Pos ;
										 }
										 if(Break.idx != MAX_BREAK){
												TRACE_MSG("%d,%u",Break.idx ,Break.Pos) ;
										 }
										 if(Break.idx < MAX_BREAK){
													Break.idx++ ;
										 }
									}
									else{
										gstProcessState.u32Pos[DrvIdx] +=((DrvIdx ==0)?131:8389);
									}
						}
						EtherCastSetTargetPos(DrvIdx, gstProcessState.u32Pos[DrvIdx]);              
        }
#endif
#ifdef TEST_ORG
    
    if (gstProcessState.u8DOutCnt){
        if (++gstProcessState.u32DCounter > 1000){
            gstProcessState.u32DCounter = 0;

            if (!gstProcessState.u8DOutFlag){
                gstProcessState.pu32DOUTData[0] = 0xAAAAAAAA;
                gstProcessState.u8DOutFlag = 1;
            }
            else{
                gstProcessState.pu32DOUTData[0] = 0x55555555; 
                gstProcessState.u8DOutFlag = 0;
            }       
        }
        EtherCatSetDOutVal(1, gstProcessState.pu32DOUTData[0]); 
    }
    if (gstProcessState.u8DriverCnt){
        ST_DRIVER_PARA_T *pDriverInfo;      
        int DrvIdx, nVel ;
        int nTargetPos;
        
        if (++gstProcessState.u32RunCounter > gstProcessState.u32MatchCounter){
            gstProcessState.u32RunCounter = 0;         
            if (gstProcessState.u8RunMode == 1){
                gstProcessState.u8RunMode = 2;
                gstProcessState.u32MatchCounter = DEBUG_STOP_COUNTS;
            }
            else if (gstProcessState.u8RunMode == 2){
                gstProcessState.u8RunMode = 1;             
                gstProcessState.u32MatchCounter = DEBUG_RUN_COUNTS;
                MotionDirectionToggle();              
            }           
        }   
        if (gstProcessState.u8RunMode == 1){
                
            for(DrvIdx=0; DrvIdx < gstProcessState.u8DriverCnt; DrvIdx++){
                EtherCastSetCtrlWord(DrvIdx, 0xF);
                
                // config target positon for CSP Mode
                pDriverInfo = &gstProcessState.pDriverInfo[DrvIdx];
                EtherCatGetActualPos(DrvIdx, &pDriverInfo->u32Pos);       
                nVel = setNextPosition(pDriverInfo->u32PPR, pDriverInfo->u32InitPos, gstProcessState.u8ReserveRotation);    

                pDriverInfo->u32SumVel += nVel;              

                nTargetPos = pDriverInfo->u32InitPos + pDriverInfo->u32SumVel;
								//TRACE_MSG("%d,%d,%d\n", DrvIdx+1, pDriverInfo->u32Pos, nTargetPos);                                 

                EtherCastSetTargetPos(DrvIdx, nTargetPos);                            
            }
        }
    }
#endif
		
#endif		
}



static int AppEtherCatConfig(void)
{
    ST_DRIVER_PARA_T *pDriverInfo;  
    size_t sizes;
    uint32_t u32Vid, u32Pid;
    int i, nDriver, nMatchCnt;
    
    //initial run parameter.
    //初始化執行參數
    gstProcessState.u8ReserveRotation = 1;     
    gstProcessState.u8RunMode = 1;
    gstProcessState.u32RunCounter =0;   
    gstProcessState.u32MatchCounter = DEBUG_RUN_COUNTS;
    
    //setup DOut information.
    //設定數位輸出相關參數
    gstProcessState.u8DOutCnt = EtherCatGetDOutCnt();
    if (gstProcessState.u8DOutCnt){
        sizes = sizeof(uint32_t)*gstProcessState.u8DOutCnt;
        gstProcessState.pu32DOUTData = (uint32_t*)vZeroMalloc(sizes); 
        if (gstProcessState.pu32DOUTData == NULL){
            return (EC_ERR_MALLOC);
        }       
    }
    
    //setup DIn information.
    //設定數位輸入相關參數
    gstProcessState.u8DInCnt = EtherCatGetDInCnt();
    if (gstProcessState.u8DInCnt){
        sizes = sizeof(uint32_t)*gstProcessState.u8DInCnt;
        gstProcessState.pu32DInData = (uint32_t*)vZeroMalloc(sizes);  
        if (gstProcessState.pu32DInData == NULL){
            return (EC_ERR_MALLOC);
        }               
    }
    
    //setup AIn information.
    //設定類比輸入相關參數
    gstProcessState.u8AInCnt = EtherCatGetAInCnt();
    if (gstProcessState.u8AInCnt){
        sizes = sizeof(uint32_t)*gstProcessState.u8AInCnt;
        gstProcessState.pu32AInData = (uint32_t*)vZeroMalloc(sizes); 
        if (gstProcessState.pu32AInData == NULL){
            return (EC_ERR_MALLOC);
        }           
    }   
    
    //setup driver information.
    //設定馬達相關參數
    gstProcessState.u8DriverCnt = EtherCatMasterGetDriverCnt();
    if (gstProcessState.u8DriverCnt){
        
        sizes = sizeof(ST_DRIVER_PARA_T) * gstProcessState.u8DriverCnt;
        gstProcessState.pDriverInfo = (ST_DRIVER_PARA_T *)vZeroMalloc(sizes);
        if (gstProcessState.pDriverInfo == NULL){
            return (EC_ERR_MALLOC);
        }
        
        //read Actual Position from Driver
        //讀取馬達目前位置
        for (nDriver=0; nDriver < gstProcessState.u8DriverCnt; nDriver++){
            pDriverInfo = &gstProcessState.pDriverInfo[nDriver];
            EtherCatGetActualPos(nDriver, &pDriverInfo->u32InitPos);
            pDriverInfo->u32Pos = pDriverInfo->u32InitPos ; 
        }
    }
    
    //設定馬達的PPR
    sizes = EtherCatGetDevicesCnt();
    nMatchCnt = 0;
    for (nDriver=0; nDriver < sizes; nDriver++){        
        EtherCatGetVidPid(nDriver+1, &u32Vid, &u32Pid);
        
        for(i=0; i < no_stDriverTable; i++){
            if (stDriverTable[i].u32Vid == u32Vid && 
                stDriverTable[i].u32Pid == u32Pid){
                gstProcessState.pDriverInfo[nMatchCnt++].u32PPR = stDriverTable[i].u32PPR;
                break;
            }
        }
    }
    return (EC_ERR_NONE);   
}



static int EtherCatInit (void)
{
    int nret;
    
    nret = EtherCatMasterOpen(APP_SPI_CLOCK, EC_OP_CSP, APP_EC_DC_ACTIVE_CODE, APP_EC_DC_TIME, UserProcessPDO);
	    // user code.
    AppEtherCatConfig();
    if (nret != EC_ERR_NONE){
        return (nret);
    }
    #if 0
    // user code.
    nret = AppEtherCatConfig();
    if (nret != EC_ERR_NONE){
        return (nret);
    }
		#endif
    
    // not modify.
    //EtherCatMasterRunning();   //RUN
    return (EC_ERR_NONE);
}



static int PlatformInit(uint32_t spi_clock)
{
    int irq;

    IRQn_Type HighPriority[] = {PDMA_IRQn, 
#if (APP_USED_PYT_180_DB == 1)  
                                GPA_IRQn
#else                           
                                GPE_IRQn
#endif                          
                               };

#if (APP_USED_PYT_180_DB == 1) 
    // Reset ECM_XF
#if 1                                                    
    MSG_DBG("Reset ECM_XF...\n");      
    GPIO_SetMode(PH, BIT0, GPIO_MODE_OPEN_DRAIN);//GPIO_MODE_OUTPUT);
    PH0 = 1;    
    UserDelay(100); 
    PH0 = 0;
    UserDelay(2000);
    PH0 = 1;                                                                 
    MSG_DBG("Reset ECM_XF done\n"); 
    UserDelay(2000);															 
#endif                                                           
#endif  
    
    //  Hardware platform dependency    
    MSG_DBG("QSPI Clock=%d\n", spi_clock);      

    //config Interrupt grounp & Priority.
        // 7 : no pre-emption priorities, 16 subpriorities
    NVIC_SetPriorityGrouping(7);
    
    //set lowest priority
        // 0: Highest Priority, 15 : Lowest prioirty
    for(irq=0; irq <= 255; irq++){
        NVIC_SetPriority((IRQn_Type)irq, 1);
    }
    
    //set highest priority  
    for(irq=0; irq < ARRAY_LENGTH(HighPriority); irq++){
        NVIC_SetPriority(HighPriority[irq], 0);
    }
    

    return (EC_ERR_NONE);
}



int EtherCatMasterInit (uint32_t spi_clock)
{
    int ret ;

    PlatformInit(spi_clock); 
    
    ret = EtherCatInit();
    if (ret != EC_ERR_NONE){
        //while(1){
        //}
    }
        return (ret);
}
//Ethercat Bus 初始後的process
void test1_EC()
{
        
}

void SEGGER_SYSVIEW_Update_SampleData(uint32_t u16Value)
{
		static uint32_t u32DataValue;
	  static SEGGER_SYSVIEW_DATA_SAMPLE LoadCell;
	
		int i;
	
		u32DataValue = u16Value;
		//
		// Initialize data sample struct.
		LoadCell.ID = 0;
		LoadCell.pValue.pU32 = &u32DataValue;
		//
		// Send event to SystemView.
		//
		SEGGER_SYSVIEW_SampleData(&LoadCell);	
}



extern "C" {

void SEGGER_SYSVIEW_User_SendSystemDesc(void)
{
		SEGGER_SYSVIEW_DATA_REGISTER LoadCell;

		LoadCell.ID = 0;
		LoadCell.sName = "Load Cell";
		LoadCell.DataType = SEGGER_SYSVIEW_TYPE_U32;
		LoadCell.Offset = 0;
		LoadCell.RangeMin = 0;
		LoadCell.RangeMax = 0;
		LoadCell.ScalingFactor = 1;
		LoadCell.sUnit = "g";
		SEGGER_SYSVIEW_RegisterData(&LoadCell);

}
}  // extern "C"
