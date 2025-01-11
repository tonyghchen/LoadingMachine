void rd_AllStatus()
{
	for(uint8 laxis=0 ; laxis < MachineStatus.axis_no ; laxis++){
		PHY_AXIS phy_axis=log2phyaxis((LOG_AXIS){laxis}) ;
		pDispBuf += BcdToStrBuf(2, rDosMem(STATUS_ADDR(phy_axis)) , pDispBuf);
		Fill_pDispBuf("  ");
	}
}
bool chkOverLimit(LOG_AXIS laxis,uint8 dir,uint8 man_hand)
{
	if(chk_zrt_power_on(laxis))return(false) ;
	if(flag_RRealAxis)return(false);
	uint32  dincval;
	PHY_AXIS phy_axis= {MachineStatus.AxisMap[laxis.idx]} ;
	if( MachineStatus.motor[laxis.idx] ){
		dincval = (man_hand==0)? BcdToBin(3, MachineStatus.manval[laxis.idx]):BcdToBin(3, MachineStatus.handval[laxis.idx]);
		if( phy_axis.idx==AXIS_Y && MachineStatus.y_scale )  dincval *= 10;
		if((laxis.idx == MachineStatus.XXScaleSel)&& MachineStatus.XXScale){
			dincval *= 5 ;
			if(dincval > 100){
				dincval=100 ;
			}
		}
		int32 newval= BcdToBin(8,MachineStatus.axis_val[laxis.idx] ,MachineStatus.sign[laxis.idx]);
		TO_GRID(laxis,newval) ;
		//滑座移動時,需確定翻刀轉在合法的位置
		if((MachineStatus.MANUFACTORY==KNCNC)&&(MachineStatus.Type == 0x1220) ||
		   (MachineStatus.MANUFACTORY==HNCNC)&&(MachineStatus.Type == 0x1308)){
			if((newval ==0)&&(laxis.idx < 8)){
				SDWORD pos=BcdToBin(8,MachineStatus.axis_val[AXIS_X11] ,MachineStatus.sign[AXIS_X11]);
				LOG_AXIS laxis_x11={AXIS_X11} ;
				TO_GRID(laxis_x11,pos) ;
				if(!chkatsameregion(pos,pos)){
					DispMsgWin_q(-1, -1, WAR_WIN, "翻刀 不 在 定位,不 能 移 動滑座!",
											" RORC is not on Right Position");
					return(true) ;
				}
			}
		}

		int32 tt= (isPLUS_SIGN(dir)?dincval:-(int32)dincval) ; 
		newval += tt ;
		if(MachineStatus.Unit[laxis.idx]== 1){ //角度
			while(newval >=3600){
				newval-=3600 ; 
			}
			while(newval <=-3600){
				newval +=3600 ;
			}
		}
		SDWORD min,max ;
		if((laxis.idx !=AXIS_X11)|| (MachineStatus.MANUFACTORY==HNCNC	&&	MachineStatus.Type == 0x1320)
								 || (MachineStatus.MANUFACTORY==KNCNC	&&	(MachineStatus.Type == 0x1240	||	MachineStatus.Type == 0x1260))){
			min= BcdToBin(8,MachineStatus.Min[laxis.idx] ,MachineStatus.Min_sign[laxis.idx]) ;
			max= BcdToBin(8,MachineStatus.Max[laxis.idx] ,MachineStatus.Max_sign[laxis.idx]) ;
			if(((max != 99999)&&(newval > max)) || ((min != -99999)&&(newval < min))){ 
				DispMsgWin_q(-1, -1, WAR_WIN, "超 過 軟 體 極 限!",
										" Over software Limit");
				return(true) ;
			}
		 	else{
		 		return(false) ;
		 	}   
		}
		else{
			//針對翻刀移動做檢查
			int32 xval ;
         char i;
			for(i=0 ; i < 8 ; i++){
		 		xval= BcdToBin(8,MachineStatus.axis_val[i] ,MachineStatus.sign[i]);
		 		if(xval !=0)break ;
			}
			if(i < 8){
				int32 scale = BcdToBin(5,MachineStatus.motor_grads[AXIS_X11])/8 ;
				int32 gap10;
#ifdef HNCNC
				gap10=GAP10 ;
#else
				gap10=BcdToBin(8,MachineStatus.Max[AXIS_X11] ,MachineStatus.Max_sign[AXIS_X11]) ; ;
#endif				
				normal10(newval) ;
				for(i=0 ; i < 8 ; i++){
					SDWORD base = scale*i ;
					min = base - gap10 ;
					max = base + gap10 ;
					normal10(max) ;
					normal10(min) ;
					if((newval <=max)&& (newval >=min)){
						return(false) ;
					}
				}
				DispMsgWin_q(-1, -1, WAR_WIN, "超 過 翻 刀 極 限!",
										" Over Rotate Cutter Limit");
				return(true) ;
			}
			else{
				return(false) ;
			}
		}
	}
	return(true);
}
