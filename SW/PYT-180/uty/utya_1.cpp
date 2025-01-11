#ifdef Bound_Check
Cptr SetColorS(COLOR_T fcol,COLOR_T bcol,ept_char  buf)
{
		EPT_BC(&buf.value[0],buf) ;
#ifdef REAL_COLOR		
		EPT_BC(&buf.value[5],buf) ;
#else
		EPT_BC(&buf.value[3],buf) ;
#endif	
	
		buf.value[0]= CHG_PAL ;
#ifdef REAL_COLOR
		buf.value[1]= fcol ;
		buf.value[2]= fcol >>8 ;
		buf.value[3]= bcol ;
		buf.value[4]= bcol>> 8 ;
		buf.value[5]= '\0' ;
		return(&buf.value[5]) ;
#else		
		buf.value[1]= fcol ;
		buf.value[2]= bcol ;
		buf.value[3]= '\0' ;
		return(&buf.value[3]) ;
#endif
}

Cptr SetColorE(ept_char buf)
{
	EPT_BC(buf.value+0,buf) ;
	
	buf.value[0]= CHG_PAL ;
	EPT_BC(buf.value+1,buf) ;
	buf.value[1]='\0' ;
	return(&buf.value[1]) ;
}

Cptr SetColorE(uint8 sign,ept_char buf)
{
	if(sign&0x80){
		return(SetColorE(buf));
	}
	else{
		return(buf.value) ;
	}
}

#endif



unsigned  FindBIOSVendor()
{
	unsigned addr =FindSMBIOSTbl0() ;
	if(addr !=0){
		addr += rDosMem(addr+1) ;
	}
	return(addr) ;
}
unsigned  FindSMBIOSTbl0()
{
	unsigned  addr =0xf0000L ;
   int i ;
	for(i=0 ; i < 0x1000 ;i++){
		if((rDosMem(addr)== 0x5f)&&(rDosMem(addr+1)== 0x53)&&(rDosMem(addr+2)== 0x4d)&&(rDosMem(addr+3)== 0x5f)&&(rDosMem(addr+0x10)== 0x5f)&&(rDosMem(addr+0x11)== 0x44)&&(rDosMem(addr+0x12)== 0x4d)&&(rDosMem(addr+0x13)== 0x49)&&(rDosMem(addr+0x14)== 0x5f))break ;
		addr++ ;
	}
	if(i == 0x1000)return(0) ;
	addr=rDosMeml(addr+0x18) ;  //SMBIOS table 進入點位址
	if(rDosMem(addr)==0)return(addr) ;
	return(0) ;
}
uint8 GetLastKey	(void)
{
	uint16 i,	tidx;

	tidx = KeyBufRIdx;
	for( i=0; i	< 2; i++ ){
		if(	tidx ==	0 )	 tidx =	MAX_KEY_BUF-1;
		else			 tidx--;
	}
	return(	KeyBuf[tidx] );
}

uint8 GetNextKey	(void)
{
	if(	KeyBufRIdx != KeyBufWIdx ){
		return(	KeyBuf[KeyBufRIdx] );
	}
	else{
		return(	0 );
	}
}

uint8 ClrKeyBuf (void)
{
	uint16 i;
	uint8  code ;

		
	for( i=0; (i<MAX_KEY_BUF) && (KeyBufRIdx!=KeyBufWIdx)&&(KeyBuf[KeyBufRIdx]!=0xfe); i++ )  code=GetKey();


	return(code) ;
}

void ResetKeyBuf (uint8 key)
{
//	DISABLE();
	KeyBufRIdx = 0;
	KeyBufWIdx = 1;
	KeyBuf[0]  = key;
//	ENABLE();
}

uint8 RepeatKey (uint8 ref_key, uint16 repeat_no)
{
	uint16 flag, i, j;

	flag = PRESS_KEY;
	for( j=0; (j<repeat_no)	&& (flag==PRESS_KEY); j++ ){
		for( i=0; i	< 1200;	i++	){
			if(	GetNextKey() ==	ref_key	)  break;
		}
		if(	i == 1200 )	 flag =	RELEASE_KEY;
	}

	if(	flag ==	PRESS_KEY )	 ClrKeyBuf();
//	CHECK_RESET(false);//新620
	return(	flag );
}
void SetLastKey(BYTE key)
{
	WORD i,	tidx;

	tidx = KeyBufRIdx;
	for( i=0; i	< 2; i++ ){
		if(	tidx ==	0 )	 tidx =	MAX_KEY_BUF-1;
		else			 tidx--;
	}
	KeyBuf[tidx] =key;
}

void saveVGA(bool force,char filename[])
{
}
void saveVGA(bool force)
{

}



//設定開始(Start)改變顏色
//
Cptr SetColorS(COLOR_T fcol,COLOR_T bcol,Cptr  buf)
{
		buf[0]= CHG_PAL ;
#ifdef REAL_COLOR
		buf[1]= fcol ;
		buf[2]= fcol >>8 ;
		buf[3]= bcol ;
		buf[4]= bcol>> 8 ;
		buf[5]= '\0' ;
		return(&buf[5]) ;
#else		
		buf[1]= fcol ;
		buf[2]= bcol ;
		buf[3]= '\0' ;
		return(&buf[3]) ;
#endif
}

void SetColorS(uint8 sign)
{	
	if(sign&0x80){
		EPT_BC(pDispBuf.value,pDispBuf) ;
#ifdef Bound_Check			
		pDispBuf.value=SetColorS(RED_USR,LIGHTRED_USR,pDispBuf) ;
#else
		pDispBuf=SetColorS(RED_USR,LIGHTRED_USR,pDispBuf) ;
#endif
	}
}


static 	bool chgclr;
Cptr SetColorS(char seq ,Cptr psign,Cptr buf)
{
	COLOR_T nbclr , nfclr ;
	chgclr=false ;
	nbclr= NULL_BCLR_USR ;
	if((psign != NULL) && (*psign&0x80)){
		nfclr=BLACK_USR ; nbclr=LIGHTRED_USR ;
		chgclr=true ;
	}
	if(seq==1){
		nfclr=SEQ1_USR ;
		chgclr=true ;
	}
	else if(seq==2){
		nfclr=SEQ2_USR ;
		chgclr=true ;
	}
	if(chgclr){
		return(SetColorS(nfclr,nbclr,buf)) ;		
	}	
	else{
		return(buf) ;	
	}
}
Cptr SetColorS(uint8 sign,Cptr buf)
{
	if(sign&0x80){
		return(SetColorS(BLACK_USR,LIGHTRED_USR,buf)) ;
	}
	else{
		return(buf) ;	
	}
}
void SetColorS(char seq)
{
	if(seq==1){
		EPT_BC(pDispBuf.value,pDispBuf) ;
#ifdef Bound_Check		
		pDispBuf.value=SetColorS(SEQ1_USR,NULL_BCLR_USR,pDispBuf) ;
#else
		pDispBuf=SetColorS(SEQ1_USR,NULL_BCLR_USR,pDispBuf) ;
#endif
	}
	else if(seq==2){
		EPT_BC(pDispBuf.value,pDispBuf) ;
#ifdef Bound_Check		
		pDispBuf.value=SetColorS(SEQ2_USR,NULL_BCLR_USR,pDispBuf) ;
#else
		pDispBuf=SetColorS(SEQ2_USR,NULL_BCLR_USR,pDispBuf) ;
#endif		
	}	
}
Cptr SetColorE(Cptr buf)
{
	buf[0]= CHG_PAL ;
	buf[1]='\0' ;
	return(&buf[1]) ;
}

//設定結束(End)改變顏色
//
void SetColorE(uint8 sign)
{
	EPT_BC(pDispBuf.value,pDispBuf) ;
#ifdef Bound_Check		
	pDispBuf.value=SetColorE(sign,pDispBuf);
#else
	pDispBuf=SetColorE(sign,pDispBuf);
#endif
}
void SetColorE(char seq)
{
	EPT_BC(pDispBuf.value,pDispBuf) ;
#ifdef Bound_Check		
	pDispBuf.value=SetColorE(seq,pDispBuf);
#else
	pDispBuf=SetColorE(seq,pDispBuf);
#endif
}
Cptr SetColorE(uint8 sign,Cptr buf)
{
	if(sign&0x80){
		return(SetColorE(buf));
	}
	else{
		return(buf) ;
	}
}

Cptr SetColorE_chgclr(Cptr buf)
{
	if(chgclr){
		return(SetColorE(buf));
	}
	else{
		return(buf) ;
	}
}
Cptr SetColorE(char seq,Cptr buf)
{
	if((seq ==1)||(seq==2)){
		return(SetColorE(buf));
	}
	else{
		return(buf) ;
	}
}
void strcpy_S (Cptr d,Cptr str)
{
	uint16 nof =0 ;

	for( ; *str;  ){
		if(*str == CHG_PAL){
			
			nof++ ;
			if(nof%2){
#ifdef REAL_COLOR
				for(uint8 i=0 ; i < 5 ; i++){
					*d++=*str++ ;
				}
#else				
				for(uint8 i=0 ; i < 3 ; i++){
					*d++=*str++ ;
				}
#endif				
			}
			else{
				*d++=*str++ ;
			}
		}
		else{
			*d++=*str++ ;
		}
	}
	*d++=*str++ ;
}
unsigned int cal_intvect(int no)
{
	if(no <= 7){
		return(no+8) ;
	}
	else{
		return(no-8+0x70) ;
	}
}
void init_com(uint8 no)
{
	//comm_port=no ;	//初始化com
	//ini_baud(0xe3) ;
	//init_rs232() ;
}
void process_config_org(uint8 key_help,uint8 key_wr)
{
}
/*
int open_config_backup(char *mode)
{
	char filename[]= "C:\\configBK.dat" ;
	return(open_config(filename,mode)) ;
}
void save_config_backup(void)
{
		open_config_backup("wb") ;
		save_config_all() ;
}
void load_config_backup(void)
{
		open_config_backup("rb") ;
		load_config_all() ;
}
int open_config_org(char *mode)
{
	char filename[]= "C:\\config.org" ;
	return(open_config(filename,mode)) ;
}
void save_config_org(void)
{
		open_config_org("wb") ;
		save_config_all() ;
}
void load_config_org(void)
{
		open_config_org("rb") ;
		load_config_all() ;
}
int open_config(char *filename , char *mode )
{
	if((fp_config_c=FOPEN(filename,mode)) != NULL){
		if(DDisk && (strcmp(mode ,"rb")!=0)){
			filename[0]= 'D' ;
			fp_config_d= FOPEN(filename,mode) ;
		}
		else{
			fp_config_d= NULL ;
		}
		return(fp_config_c!= NULL) ;
	}
	return(NULL) ;
}
int open_config(char *mode )
{
	char filename[]= "C:\\config.dat" ;
   return(open_config(filename , mode)) ;
}
long filesize_config()
{
	return(filesize(fp_config_c)) ;
}
void close_config(void)
{
	if(fp_config_c !=NULL){
		FCLOSE(fp_config_c) ;
		fp_config_c=NULL ;
	}
	if(DDisk && (fp_config_d != NULL)){
		FCLOSE(fp_config_d) ;
		fp_config_d=NULL ;
	}
}
bool SendToArmCmd(uint8 cmd)
{
	uint32  i;
	bool err ;
	for(i=0	; i< LOOP_TIMES	; i++){
		if(FILL_PC_CMD_CHK_ARM_CMD(cmd)) break ;
	}
	err	= ((i>=LOOP_TIMES)?	true: false);
	for(i=0	; i< LOOP_TIMES	; i++){
		if(FILL_PC_CMD_CHK_ARM_CMD(0)) break ;
	}
	return(err)	;
}
void Fill_pDispBuf(Cptr str)
{
	EPT_BC(pDispBuf.value,pDispBuf) ;
#ifdef Bound_Check	
	pDispBuf.value += StrCpy(pDispBuf, str);
#else
	pDispBuf += StrCpy(pDispBuf, str);
#endif
}
void Fill_pDispBuf(Cptr msg_chinese,Cptr msg_english)
{
	if( CHINESE ){
		EPT_BC(pDispBuf.value,pDispBuf) ;
#ifdef Bound_Check
		pDispBuf.value += StrCpy(pDispBuf, msg_chinese);
#else
		pDispBuf += StrCpy(pDispBuf, msg_chinese);
#endif
	}
	else{
		EPT_BC(pDispBuf.value,pDispBuf) ;
#ifdef Bound_Check		
		pDispBuf.value += StrCpy(pDispBuf, msg_english);
#else
		pDispBuf += StrCpy(pDispBuf, msg_english);
#endif		
	}
}
void Fill_pDispBuf(bool force_eng , Cptr msg_chinese,Cptr msg_english)
{
	if( !force_eng && CHINESE ){
		EPT_BC(pDispBuf.value,pDispBuf) ;
#ifdef Bound_Check			
		pDispBuf.value += StrCpy(pDispBuf, msg_chinese);
#else
		pDispBuf += StrCpy(pDispBuf, msg_chinese);
#endif
	}
	else{
		EPT_BC(pDispBuf.value,pDispBuf) ;
#ifdef Bound_Check			
		pDispBuf.value += StrCpy(pDispBuf, msg_english);
#else
		pDispBuf += StrCpy(pDispBuf, msg_english);
#endif		
	}
}
void Fill_pDispBuf(Cptr msg_chinese,Cptr msg_english,Cptr msg_Italian)
{
	if( ITALY ){
		EPT_BC(pDispBuf.value,pDispBuf) ;
#ifdef Bound_Check			
		pDispBuf.value += StrCpy(pDispBuf, msg_Italian);
#else
		pDispBuf += StrCpy(pDispBuf, msg_Italian);
#endif			
	}
	else if( CHINESE ){
		EPT_BC(pDispBuf.value,pDispBuf) ;
#ifdef Bound_Check			
		pDispBuf.value += StrCpy(pDispBuf, msg_chinese);
#else
		pDispBuf += StrCpy(pDispBuf, msg_chinese);
#endif			
	}
	else{
		EPT_BC(pDispBuf.value,pDispBuf) ;
#ifdef Bound_Check			
		pDispBuf.value += StrCpy(pDispBuf, msg_english);
#else
		pDispBuf += StrCpy(pDispBuf, msg_english);
#endif			
	}
}
void Fill_pDispBuf(bool force_eng,Cptr msg_chinese,Cptr msg_english,Cptr msg_Italian)
{
	if( ITALY&& !force_eng ){
		EPT_BC(pDispBuf.value,pDispBuf) ;
#ifdef Bound_Check		
		pDispBuf.value += StrCpy(pDispBuf, msg_Italian);
#else
		pDispBuf += StrCpy(pDispBuf, msg_Italian);
#endif
	}
	else if( CHINESE&& !force_eng ){
		EPT_BC(pDispBuf.value,pDispBuf) ;
#ifdef Bound_Check		
		pDispBuf.value += StrCpy(pDispBuf, msg_chinese);
#else
		pDispBuf += StrCpy(pDispBuf, msg_chinese);
#endif		
	}
	else{
		EPT_BC(pDispBuf.value,pDispBuf) ;
#ifdef Bound_Check			
		pDispBuf.value += StrCpy(pDispBuf, msg_english);
#else
		pDispBuf += StrCpy(pDispBuf, msg_english);
#endif			
	}
}

*/

