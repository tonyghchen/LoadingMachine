void PrintfInport(int x,int y , uint32 state ,char *str)
{
	if(state){
//		PrintStringLine_q(x,y,BROWN_USR , BLACK_USR,str) ;
	}
	else{
//		PrintStringLine_q(x,y,RED_USR , YELLOW_USR,str) ;
	}
}
void DispInport(void)
{
	if(flag_DispInport){
		static int cnnt =0 ;
		cnnt++ ;
		if(cnnt == 500){
			cnnt=0 ;
			int y=600-ASC_CHAR_H*5 ;
			int x=10 ;
			uint16 lb=rDosMem(pc_base+EXTINL);
			uint16 mb=rDosMem(pc_base+EXTINM) ; 
			uint16 lw=(mb << 8)+lb ;
            static uint16 wInport=0x55;
			if(lw != wInport){
				wInport=lw ;
				for(int i=0 ; i < 12 ; i++){
					char buf[20] ;
					sprintf(buf,"%02d",i+1) ;
//					PrintStringLine_q(x,y,(lw&0x1)?RED_USR:YELLOW_USR , (lw&0x1)?YELLOW_USR:RED_USR,buf) ;
					lw >>= 1 ;
					x += ASC_CHAR_W*3 ;
				}
			}
		}
	}
	if(flag_DispInport){
		static int cnnt =0 ;
		cnnt++ ;
		if(cnnt == 500){
			cnnt=0 ;
			int y=516-ASC_CHAR_H*5 ;
			int x=10 ;
			uint32 lb=PORT_CN1;
			uint32 mb=PORT_INM ; 
			uint32 hb=PORT_INH ;
			uint32 l=(hb << 16)+(mb << 8)+lb ;
			static uint32 lInport ;
			if(l != lInport){
				lInport=l ;
				PrintfInport(x,y,l&0x1,"oil") ;
				x += ASC_CHAR_W*4 ;
				PrintfInport(x,y,l&0x2,"ESTOP") ;
				x += ASC_CHAR_W*6 ;
				PrintfInport(x,y,l&0x4,"DOOR") ;
				x += ASC_CHAR_W*5 ;
				PrintfInport(x,y,l&0x8,"T3") ;
				x += ASC_CHAR_W*3 ;
				PrintfInport(x,y,l&0x10,"T4") ;
				x += ASC_CHAR_W*4 ;
				PrintfInport(x,y,l&0x20,"WIRE") ;
				x += ASC_CHAR_W*5 ;
				PrintfInport(x,y,l&0x40,"T1") ;
				x += ASC_CHAR_W*3 ;
				PrintfInport(x,y,l&0x80,"T2") ;
				x += ASC_CHAR_W*3 ;
				PrintfInport(x,y,l&0x100,"W") ;
				x += ASC_CHAR_W*3 ;
				PrintfInport(x,y,l&0x200,"A+") ;
				x += ASC_CHAR_W*3 ;
				PrintfInport(x,y,l&0x400,"A-") ;
				y -=20;
			    x=10 ;
				PrintfInport(x,y,l&0x800,"KEY") ;
				x += ASC_CHAR_W*4 ;
				PrintfInport(x,y,l&0x1000,"Y+") ;
				x += ASC_CHAR_W*6 ;
				PrintfInport(x,y,l&0x2000,"Y-") ;
				x += ASC_CHAR_W*5 ;
				PrintfInport(x,y,l&0x4000,"SW") ;
				x += ASC_CHAR_W*3 ;
				PrintfInport(x,y,l&0x8000,"UV1") ;
				x += ASC_CHAR_W*4 ;
				PrintfInport(x,y,l&0x10000,"POFF") ;
				x += ASC_CHAR_W*5 ;
				PrintfInport(x,y,l&0x20000,"B") ;
				x += ASC_CHAR_W*3 ;
				PrintfInport(x,y,l&0x40000,"A") ;
				x += ASC_CHAR_W*3 ;
				PrintfInport(x,y,l&0x80000,"C") ;
				x += ASC_CHAR_W*3 ;
				PrintfInport(x,y,l&0x100000,"Z") ;
				x += ASC_CHAR_W*3 ;
				PrintfInport(x,y,l&0x200000,"D") ;
			}
#ifdef DISP_HOME			
			LOG_AXIS laxis;
			static bool lhome[16]={1,1,1,1,0,0,0,0} ;
			bool home[16] ;
		
			for(laxis.idx=0 ; laxis.idx < 16 ; laxis.idx++){
				PHY_AXIS phy_axis=log2phyaxis(laxis) ;			
				home[laxis.idx]=GetMotorZrt(phy_axis) ;
			}
			bool same=true ;
			for(laxis.idx=0 ; laxis.idx < 16 ; laxis.idx++){
				if(home[laxis.idx] != lhome[laxis.idx]){
					same=false ;
				}
			}
			if(!same){
				int y=556-ASC_CHAR_H*5 ;
				int x=10 ;
				PrintfInport(x,y,home[0],"SH1") ;
				x += ASC_CHAR_W*5 ;
				PrintfInport(x,y,home[1],"SH2") ;
				x += ASC_CHAR_W*5 ;
				PrintfInport(x,y,home[2],"SH3") ;
				x += ASC_CHAR_W*5 ;
				PrintfInport(x,y,home[3],"SH4") ;
				x += ASC_CHAR_W*5 ;
				PrintfInport(x,y,home[4],"SH5") ;
				x += ASC_CHAR_W*5 ;
				PrintfInport(x,y,home[5],"SH6") ;
				x += ASC_CHAR_W*5 ;
				PrintfInport(x,y,home[6],"SH7") ;
				x += ASC_CHAR_W*5 ;
				PrintfInport(x,y,home[7],"SH8") ;
				x += ASC_CHAR_W*5 ;
				PrintfInport(x,y,home[8],"SH9") ;
				x += ASC_CHAR_W*5 ;
				PrintfInport(x,y,home[9],"SHA") ;
				x += ASC_CHAR_W*5 ;
				PrintfInport(x,y,home[10],"SHB") ;
				x += ASC_CHAR_W*5 ;
				PrintfInport(x,y,home[11],"SHC") ;
				x += ASC_CHAR_W*5 ;
				PrintfInport(x,y,home[12],"SHD") ;
				x += ASC_CHAR_W*5 ;
				PrintfInport(x,y,home[13],"SHE") ;
				x += ASC_CHAR_W*5 ;
				PrintfInport(x,y,home[14],"SHF") ;
				x += ASC_CHAR_W*5 ;
				PrintfInport(x,y,home[15],"SHG") ;
				x += ASC_CHAR_W*5 ;
				
				for(laxis.idx=0 ; laxis.idx < 16 ; laxis.idx++){
					lhome[laxis.idx] = home[laxis.idx]; 
				}
			}	
#endif
		}
	}
}
