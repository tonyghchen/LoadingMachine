
#ifdef Bound_Check
uint16 StrCpy (ept_char dst, Cptr src)
{
	uint8 ch;
	uint16 len;

	for( len=0; (ch=*src++)!=0 ; len++ )  {
		EPT_BC(dst.value,dst) ;
		*dst.value++ = ch;
	}

	return( len );
}
uint8 BinToStrBuf (uint8 digit, uint32 val, ept_char buf)
{
	uint8 i;

	for( i=0; i < digit; i++ ){
 		EPT_BC(&buf.value[digit-i-1],buf) ;
        		
		(buf.value[digit-i-1]) = (uint8)(val%10) + '0';
		val /= 10;
	}

	return( i );
}
uint8 BcdToStrBuf (uint8 digit, uint32 val, ept_char buf)
{
	uint8 i, k;

	for( i=0; i < digit; i++ ){
		k = (uint8)(val&0xf);
		EPT_BC(&buf.value[digit-i-1],buf) ;
		
		buf.value[digit-i-1] = k + (k<=9?'0':'A'-10);
		val >>= 4;
	}

	return( i );
}
#endif

//將src所指向的字串(不包含字串結尾'\0')抄到dst所指向的記憶空間
//傳回值:字串的長度(不包含字串結尾'\0')
uint16 StrCpy (Cptr dst, Cptr src)
{
	uint8 ch;
	uint16 len;

	for( len=0; (ch=*src++)!=0 ; len++ )  *dst++ = ch;

	return( len );
}

//計算str所指向的字串長度
uint16 StrLen (Cptr str)
{
	uint16 len;

	for( len=0; *str++; len++ );

	return( len );
}
// 將val轉換成digit個十進制數字,存到buf所指
// 數字後沒有補NULL
// 傳回值:digit
uint8 BinToStrBuf (uint8 digit, uint32 val, Cptr buf)
{
	uint8 i;

	for( i=0; i < digit; i++ ){
		buf[digit-i-1] = (uint8)(val%10) + '0';
		val /= 10;
	}

	return( i );
}

// 將val轉換成digit個十六進制數字,存到buf所指
// 數字後沒有補NULL
// 傳回值:digit
uint8 BcdToStrBuf (uint8 digit, uint32 val, Cptr buf)
{
	uint8 i, k;

	for( i=0; i < digit; i++ ){
		k = (uint8)(val&0xf);
		buf[digit-i-1] = k + (k<=9?'0':'A'-10);
		val >>= 4;
	}

	return( i );
}

uint8 BcdToStrBuf (uint8 digit, uint32 val, Cptr buf,uint8 *sign,int dotpos)
{
	uint8 i, k;

	for( i=0; i < digit; i++ ){
		k = (uint8)(val&0xf);
		buf[digit-i-1] = k + (k<=9?'0':'A'-10);
		val >>= 4;
	}
	for(i=0 ; i < digit-dotpos-1 ; i++){
		if(buf[i]== '0'){
			buf[i]=' ' ;
		}
		else{
		     break ;
		}
	}
	if((sign) && isMINUS_SIGN(*sign)){
		if(((i-1)>=0 )&& ((i-1) <= digit-1)){
			buf[i-1]='-' ;
		}
	}
	return( digit );
}
//將BCD編碼(w),位數(nibble)轉換成binary code 傳回

uint32 BcdToBin (short nibble, uint32 w)
{
	short i;
	uint32 result;

	char t[8] ;
	for( i=0 ;i < nibble; i++ ){
		t[nibble-1-i] = (char )w&0xf;
		w >>= 4 ;
	}
	for( i=0, result=0; i < nibble; i++ ){
		result *= 10;
		result += t[i];
	}
	return( result );
}
uint16 BcdToBin (short nibble, uint16 w)
{
	short i;
	uint16 result;
	
	if(nibble >=4)nibble=4 ;
	char t[4] ;
	for( i=0 ;i < nibble; i++ ){
		t[nibble-1-i] = w&0xf;
		w >>= 4 ;
	}
	for( i=0, result=0; i < nibble; i++ ){
		result *= 10;
		result += t[i];
	}
	return( result );
}
uint8 BcdToBin (short nibble, uint8 w)
{
	if(nibble >=2)nibble=2  ;
	switch(nibble){
	case 1:
		return(w) ;
	case 2:
		return((w>> 4)*10+ (w & 0xf)) ;
	default:
		return(0) ;
	}
}
uint32 dBinToBcd(short nibble,int32 w,uint8 &bcdsign)
{
	bcdsign = PLUS_SIGN ;
	if(w < 0){
		bcdsign=MINUS_SIGN ;
		w = -w ;
	}
	return(dBinToBcd(nibble,(uint32)w)) ;
}

uint32 dBinToBcd (short nibble, uint32 w)
{
	short i;
	uint32 result;

	char t[8] ;
	for( i=0; i < nibble; i++ ){
		t[nibble-1-i] = (char)(w%10);
		w /= 10;
	}
	for( i=0, result=0; i < nibble; i++ ){
		result <<= 4 ;
		result |= t[i] ;
	}

	return( result );
}
int32 DWBcdAddBin (uint8 *sign, uint32 *bcdval, int32 binval)
{
	int32 dw, ret;

	dw = (int32) BcdToBin(8, *bcdval,*sign);
	ret = (dw += binval);

	*sign = PLUS_SIGN;
	if( dw < 0 ){
		*sign = MINUS_SIGN;
		dw = -dw;
	}
	*bcdval = dBinToBcd(8, dw);

	return( ret );
}

int16 WBcdAddBin (uint8 *sign, uint16 *bcdval, int16 binval)
{
	int16 dw, ret;

	dw = (int16)BcdToBin(4, *bcdval,*sign);
	ret = (dw += binval);

	*sign = PLUS_SIGN;
	if( dw < 0 ){
		*sign = MINUS_SIGN;
		dw = -dw;
	}
	*bcdval =(uint16) dBinToBcd(4, dw);

	return( ret );
}
int32 BcdToBin_SX(uint32 x)
{
	uint8 *pp= ((uint8 *)&x+3) ;
	*pp &=0x7f ;
	return(BcdToBin(6,x,*pp)) ;
}
uint32 BcdToBin_X(uint32  x)
{
	return(BcdToBin(5,x)) ;
}
uint32 dBinToBcd_X(uint32  x)
{
	return(dBinToBcd(5,x)) ;
}

bool FileExisted(char *filename)
{

}
Cptr SelStr(Cptr ch , Cptr en)
{

}
Cptr SelStr(bool force_eng, Cptr ch , Cptr en)
{

}

uint8 phy2logaxis_idx(BYTE axis)
{
	PHY_AXIS phy={axis};
	LOG_AXIS laxis = phy2logaxis(phy); //???
	return (laxis.idx);
}
LOG_AXIS phy2logaxis(PHY_AXIS phy_axis)
{
// 	LOG_AXIS laxis ;
// 	for(laxis.idx=0 ; laxis.idx < MachineStatus.axis_no ; laxis.idx++){
// 		if(phy_axis.idx== BcdToBin(2,MachineStatus.AxisMap[laxis.idx])){
// 			return(laxis) ;
// 		}
// 	}

// 	LOG_AXIS log={0};
// 	return(log) ;
}
LOG_AXIS phy2logaxis(uint8 card , uint8 localaxis)
{
	PHY_AXIS phy={card*8+localaxis};
	return(phy2logaxis(phy)) ;
}
uint8 phy2localaxis(uint8 &card ,PHY_AXIS phy_axis)
{
	card=phy_axis.idx/8 ;
	return(phy_axis.idx%8) ;
}
uint8 log2phyaxis(uint8 &card,LOG_AXIS laxis)
{
// 	PHY_AXIS phy_axis={BcdToBin(2,MachineStatus.AxisMap[laxis.idx])} ;
// 	return(phy2localaxis(card ,phy_axis)) ;
}
PHY_AXIS log2phyaxis(LOG_AXIS laxis)
{
// 	PHY_AXIS phy_axis={BcdToBin(2,MachineStatus.AxisMap[laxis.idx])} ;
// 	return(phy_axis) ;
}
DWORD dReadAbsPos (PHY_AXIS phy_axis)
{
// 	BYTE bl, bh;
// 	WORD w,w2;
// 	DWORD d1,d2 ;
// 	uint8 card = phy_axis.idx/8 ;
// 	uint8 localaxis= phy_axis.idx%8 ;
// 	bool first_time=true ;
// 	do{
// 		bh=	rDosMem(pc_base+0x120+card*0x400+localaxis*4)	;
// 		bl=	rDosMem(pc_base+0x121+card*0x400+localaxis*4)	;
// 		w  = (((WORD)bh)<<8) + bl;
// 		bh=	rDosMem(pc_base+0x122+card*0x400+localaxis*4)	;
// 		bl=	rDosMem(pc_base+0x123+card*0x400+localaxis*4)	;
// 		w2=	(((WORD)bh)<<8)	+ bl ;
// 		d2 = ((DWORD)w2	<< 16)+w ;
// 		if(first_time){
// 			first_time=false ;
// 		}
// 		else if(d1==d2){
// 			break ;
// 		}
// 		d1=d2 ;
// 	}while(1) ;
// 	LOG_AXIS laxis=phy2logaxis(phy_axis) ;
// 	if(MachineStatus.ABDir[laxis.idx]){ //馬達的AB回授信號要反相
// 		d1=(~d1)+1; //反向	
// 	}
// 	return(	d1 );
}
unsigned STATUS_ADDR(PHY_AXIS phy_axis)                    
{                                                          
	if(axis_type == INTEL8051_AXIS){                       
		return(pc_base+Base3701[phy_axis.idx]+R_CMD_51) ;
	}                                                      
	else{         
		uint8 card ;                                       
		uint8 local_axis= phy2localaxis(card,phy_axis) ;   
		return((pc_base+0xd+0x400*card+(local_axis << 4)));
	}                                                      
} 
unsigned STATUS_ADDR(uint8 phy_axis)                    
{                                                    
	if(axis_type == INTEL8051_AXIS){ 
		return(pc_base+Base3701[phy_axis]+R_CMD_51) ;
	}                                                      
	else{             

		return((pc_base+0xd+(phy_axis << 4)));
	}                                                      
} 

bool CHK_OVERFLOW(uint8 phy_axis)
{
// 	if(ChkOverFlow[phy_axis]){
// 		BYTE b=rDosMem(pc_base+0xf4) ;
// 		if(MachineStatus.nMotorType[phy_axis]==0){ //山洋
// 			return(!(b & BITmask[7-phy_axis])) ;
// 		}
// 		else{
// 			return((b & BITmask[7-phy_axis])) ;
// 		}	
// 	}
// 	else{
// 		return(false) ;
// 	}
}

uint8 WaitR_CMD(DOS_ADDR base,uint8	axis, uint8 (*chk_fun)(uint8 ),char *mes,uint32 loop_times, uint8 cmd)
{
	uint8 ret,ret1 ;


#if	(DEBUG_RELEASE == DEBUG)
	bool first_time = true ;
#endif




	bool flag51=false;
	for(uint32 i=0; i < loop_times; i++ ){
		if(((i % 25)==0)){
			FILL_AXIS_CMD(base+W_CMD_51 , cmd) ;
		}
		ret= rDosMem(base+R_CMD_51) ;
		while(1){
			ret1= rDosMem(base+R_CMD_51)	;
			if(ret1	== ret)break ;
			ret= ret1 ;
		}
		//若由位址base+R_CMD_51兩次讀到相同的值===>確定return的值是穩定的
		if(	chk_fun(ret) ){
			flag51=true	;
			break;
		}
		
		
		
#if	(DEBUG_RELEASE == DEBUG)
		if(ret > 0xf)break ;
		if(first_time){
			lret= ret ;
			first_time= false ;
		}
		else{
			if(lret != ret){
				axis_cmd.SaveBuf(base+R_CMD_51,lret,0,i,ReadTimer2()) ;
				lret= ret ;
			}
		}
#endif




	}
	if(!flag51){
		if(!RW3701Err){
		}
//		FillErr() ;
		RW3701Err |= (1	<< axis);
		
		
		
		







	}
	return(ret)	;
}
uint8 chk_ST51_NEAR_OK(uint8 ret)
{
	return(ret == ST51_NEAR_OK)	;
}
uint8 chk_ST51_DATAOK1(uint8 ret)
{
	return(ret == ST51_DATAOK1)	;
}
uint8 chk_ST51_NEAR_OK_RESEND_OVERLAY(uint8 ret)
{
	return(( ret ==	ST51_NEAR_OK ) || (ret	== ST51_RE_SEND	) || (ret == ST51_OVERLAY )||(ret== ST51_RUNNING)) ;
}




