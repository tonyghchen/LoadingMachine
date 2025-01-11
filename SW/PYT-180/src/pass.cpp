uint8  check_Pass_Tbl[10][7]={{3,7,6,0,6,5,4},
							  {2,2,3,4,5,5,3},
							  {5,7,9,1,4,2,8},
							  {7,4,2,2,7,9,2},
							  {3,9,1,4,3,3,1},
							  {6,2,7,9,1,7,7},
							  {4,3,2,1,8,7,0},
							  {8,2,4,9,2,1,1},
							  {9,4,3,5,7,5,3},
							  {0,2,1,4,3,7,6}};
void load_PassYear()
{
	LOAD_FIELD2(FLOC_PassYear,PassYear) ;
}
void save_PassYear()
{
	SAVE_FIELD2(FLOC_PassYear,PassYear) ;
}
void load_PassMon()
{
	LOAD_FIELD2(FLOC_PassMon,PassMon) ;
}
void save_PassMon()
{
	SAVE_FIELD2(FLOC_PassMon,PassMon) ;
}
void load_PassDay()
{
	LOAD_FIELD2(FLOC_PassDay,PassDay) ;
}
void save_PassDay()
{
	SAVE_FIELD2(FLOC_PassDay,PassDay) ;
}
void UpdatePassDate()
{
		uint32 t1= rdYYYYMMDD() ;
		uint32 t2 =(MachineStatus.PassYear << 16)+ (MachineStatus.PassMon << 8)+MachineStatus.PassDay ;
		if(t1 != t2){
			MachineStatus.PassYear= (t1 >> 16)& 0xff ;
			MachineStatus.PassMon = (t1 >> 8 )& 0xff ;
			MachineStatus.PassDay = (t1      )& 0xff ;
			open_config("rb+") ;
			save_PassYear() ;
			save_PassMon() ;
			save_PassDay() ;
			close_config() ;			
		}
}
void SetNewPassDate()
{
	open_config("rb+") ;
	load_EnPassWd() ;
	load_PassYear() ;
	load_PassMon() ;
	load_PassDay() ;
	close_config() ;
	if(MachineStatus.EnPassWd){
		struct date today ;
		getdate(&today) ;
		CUR_RUNDAYS=((today.da_year%100) << 16)+ (today.da_mon << 8)+today.da_day;
		uint8 PassYear = (MachineStatus.PassYear>> 4)*10+(MachineStatus.PassYear&0xf); //BCD轉bin
		uint8 PassMon = (MachineStatus.PassMon>> 4)*10+(MachineStatus.PassMon&0xf); //BCD轉bin
		uint8 PassDay = (MachineStatus.PassDay>> 4)*10+(MachineStatus.PassDay&0xf); //BCD轉bin
		
		SET_RUNDAYS=((PassYear) << 16)+ (PassMon << 8)+PassDay ;
		if((today.da_year < 2000) || (CUR_RUNDAYS < SET_RUNDAYS)){
			//重新設定時間為設定時間
			today.da_year= PassYear+2000 ;
			today.da_mon= PassMon ;
			today.da_day=PassDay ;
			setdate(&today) ;
		}
	}
}		
void chkRUNDAYS_Over(void)
{
	if((MachineStatus.EnPassWd) && (CUR_RUNDAYS > SET_RUNDAYS)){
		RUNDAYS_Over=true ;
		SoftReset();
	}
}

void BCDADD3(uint8 n1[],uint8 n2[],uint8 s[])
{
	int t ,carry=0;
	for(int i=0 ; i < 3 ; i++){
		t= n1[i]+n2[i]+carry ;
		if(t >=10){
			t-=10 ;
			carry=1 ;
		}
		else{
		    carry=0 ;
		}
		s[i] = t ;
	}
}
void BCDSUB3(uint8 n1[],uint8 n2[],uint8 s[])
{
	int t ,borrow=0;
	for(int i=0 ; i < 3 ; i++){
		t= n1[i]-n2[i]-borrow ;
		if(t < 0){
			t+=10 ;
			borrow=1 ;
		}
		else{
		    borrow=0 ;
		}
		s[i] = t ;
	}
}
void BCDMUL3(uint8 n1[])
{
	int t ,carry=0;
	for(int i=0 ; i < 3 ; i++){
		t= n1[i]*3+carry;
		carry = t /10 ;
		n1[i] =t %10 ;
	}
}
void Decry_pass(uint8 base, uint8 p[])
{
	for(int k=0; k<base; k++){
		if((p[(base-1)-k])<(check_Pass_Tbl[p[base]][k])){
			p[(base-1)-k]+=10;
		}
		p[(base-1)-k]-=check_Pass_Tbl[p[base]][k];
	}	
}
void Encry_pass(uint8 base, uint8 p[])
{
	for(int k=0; k<base; k++){
		p[(base-1)-k]+=check_Pass_Tbl[p[base]][k];
		p[(base-1)-k]%=10;
	}	
}
bool cal_YYYYMMDD(uint32 &YYYYMMDD)
{
	
	//將序號分成兩半以BCD相加
	uint8 s[9] ;
	uint8 p[8] ;
	int8 m[8] ;
	uint8 ta[3] ;
	uint32 t= MachineStatus.NSN ;
	uint32 t1= YYYYMMDD ;
	for(int i=0 ; i < 8 ; i++){
		s[i] = (uint8)(t&0xf) ;
		t >>= 4 ;
		p[i]= (uint8)(t1&0xf) ;
		t1 >>=4 ;
	}
	
	Decry_pass(5, p);
	Decry_pass(6, p);
	Decry_pass(7, p);	
	//檢查密碼是否正確(依據p[7],p[6])
	uint16 ManuFactory = MachineStatus.MANUFACTORY&0xff;
	uint8 t6= (p[5]+p[4]+p[3]+p[2]+p[1]+p[0]+ManuFactory)%10 ;
	uint8 t7= (p[5]^p[4]^p[3]^p[2]^p[1]^p[0]^ManuFactory)%10 ;
	if((t6== p[6]) && (t7 == p[7])){  
		BCDADD3(&s[0] , &s[3],&s[6]) ;
		ta[0]= p[1]; ta[1]= p[3]; ta[2]= p[5] ;
		BCDSUB3(&ta[0],&s[6],(uint8 *)&m[0]) ;
		
		uint8 rr;
		rr = (s[5]+s[4]+s[3])%10 ;
		m[3]= p[0]-rr ;
		if(m[3] < 0){
			m[3]+=10 ;
		}
		
		rr = (s[2]+s[1]+s[0])%10 ;
		m[4]= p[2]-rr ;
		if(m[4] < 0){
			m[4]+=10 ;
		}
		
		rr = (p[5]+p[3]+p[1])%10 ;
		m[5]= p[4]-rr ;
		if(m[5] < 0){
			m[5]+=10 ;
		}
		uint8 day = m[0]+m[1]*10 ;
		uint8 mon = m[2]+m[3]*10 ;
		if((day >0) && (day <=31) && (mon > 0) && (mon <=12)){
			YYYYMMDD= 0 ;
			for(int i=0 ; i < 6 ; i++){
				YYYYMMDD <<=4 ;
				YYYYMMDD += m[5-i] ;
			}
			return(true) ;
		}
		else{
			YYYYMMDD=0 ;
			return(false) ;
		}
	} 
	else{
		YYYYMMDD=0 ;
		return(false) ;
	}
}
void cal_pass(void)
{
	//將序號分成兩半以BCD相加
	uint8 s[9] ;
	uint8 p[8] ;
	uint8 m[6] ;
	uint32 t= MachineStatus.NSN ;
	for(int i=0 ; i < 6 ; i++){
		s[i] = (uint8)(t&0xf) ;
		t >>= 4 ;
	}
	for(int i=0 ; i < 12 ; i++){
		BCDADD3(&s[0] , &s[3],&s[6]) ;
		uint32 tw = MachineStatus.MONTH[i] ;
		for(int j=0 ; j <6 ; j++){
			m[j]= (uint8)(tw&0xf) ;
			tw >>=4 ;
		} 
		BCDADD3(&s[6],&m[0],&s[6]) ;
		p[1]= s[6];p[3]= s[7];p[5]=s[8] ;
		
		p[0]= (m[3]+s[5]+s[4]+s[3])%10 ;
		p[2]= (m[4]+s[2]+s[1]+s[0])%10 ;
		p[4]= (m[5]+p[5]+p[3]+p[1])%10 ;		
		uint16 ManuFactory = MachineStatus.MANUFACTORY&0xff;
		p[6]= (p[5]+p[4]+p[3]+p[2]+p[1]+p[0]+ManuFactory)%10 ;
		p[7]= (p[5]^p[4]^p[3]^p[2]^p[1]^p[0]^ManuFactory)%10 ;
		
		Encry_pass(7, p);
		Encry_pass(6, p);
		Encry_pass(5, p);		
		
		MachineStatus.PASS[i]=0 ;
		for(int j=0 ; j < 8 ; j ++){
			MachineStatus.PASS[i] <<= 4 ;
			MachineStatus.PASS[i] += p[7-j] ;
		}
	}
}
void SET_PASS_SCRN()
{
	//顯示密碼
/*
	//para_cursor_y=para_top_y=0 ;
	PasswordBuf = 0;
	InitParameter = 0;
	InitAllProg = 0;
	ChgCursorID(PASS_CURSOR);
	MachineStatus.op_mode = PARA_MODE;
	LogoSw_q(0);
	DispPara_q(7);
	SetCursor(1);
*/
	PARA_PAGE_INDEX = 0;
	PasswordBuf = 0;
	InitParameter = 0;
	InitAllProg = 0;
	ChgCursorLoc(PARA4_LINE01_CURSOR);
	MachineStatus.op_mode = PARA_MODE;
	LogoSw_q(0);
	DispPara4_q() ;
	SetCursor(1);
	DispContextHint_q(CursorLoc);
}
uint32 rdYYYYMMDD()
{
	uint8 yy=rdCMOS(9) ;
	uint8 mm=rdCMOS(8) ;
	uint8 dd=rdCMOS(7) ; 
	return(((uint32)yy << 16)+(mm << 8) + dd) ;
}

#if 0
bool Verify_PRODPASS(uint32 prodpass)
{
	//將序號分成兩半以BCD相加
	uint8 s[9] ;
	uint8 p[6] ;
	uint8 m[3] ;
	uint32 t= MachineStatus.NSN ;
	for(int i=0 ; i < 6 ; i++){
		s[i] = t&0xf ;
		t >>= 4 ;
		p[i]= prodpass&0xf ;
		prodpass >>=4 ;
	}
	s[6]= p[1] ;s[7]= p[3] ; s[8]= p[5] ;
	m[0]= p[0] ; m[1]= p[2] ; m[2]= p[4] ;
	p[0]=p[2]=p[4]=0 ;
	for(int j=0 ;j < 9 ;j++){
		p[4] += s[j] ;
		p[2] |= s[j] ;
		p[0] ^= s[j] ;
    }
    p[0] %=10 ;
    p[2] %=10 ;
    p[4] %=10 ;
	return((m[0] == p[0])&& (m[1] == p[2]) && (m[2] == p[4])) ;
}
#endif

void load_NSN()
{
	LOAD_FIELD2(FLOC_NSN,NSN) ;
}
void save_NSN()
{
	SAVE_FIELD2(FLOC_NSN,NSN) ;
}
void NSNMody (void)
{
	uint32 *d;
	CursorData_t *ptr= *(CurCursor.ptr) ;

	d = (uint32 *)(ptr)->var;
	*d &= 0xffffffl;
	open_config("rb+") ;
	save_NSN() ;
	close_config() ;
}

void load_EnPassWd()
{
	LOAD_FIELD2(FLOC_EnPassWd,EnPassWd) ;
}
void save_EnPassWd()
{
	SAVE_FIELD2(FLOC_EnPassWd,EnPassWd) ;
}
void EnPassWdMody (void)
{
	BYTE *b;
	CursorData_t *ptr= *(CurCursor.ptr) ;

	b = (BYTE *)(ptr)->var;
	if (*b>0x1)*b=0;
	open_config("rb+") ;
	save_EnPassWd() ;
	close_config() ;
	DispColPara4_01_q();
}

