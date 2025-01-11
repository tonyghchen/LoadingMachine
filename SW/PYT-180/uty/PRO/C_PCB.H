#define LOOP_TIMES      100000L
#define TIMER0_HZ      10000

#if (SAVE_AXIS_CMD ==1)	//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
#define FILL_AXIS_CMD(addr,val)											\
		wDosMem(addr,(uint8)(val)) ;				 					\
		axis_cmd.SaveBuf(addr,val,0,0,ReadTimer2()) ;
#else	//************************************************
#define FILL_AXIS_CMD(addr,val)											\
		wDosMem(addr,(uint8)(val)) ;
#endif	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#define FILL_AXIS_CMD_24(base,ref)										\
			FILL_AXIS_CMD((base+DATA51_L) ,(uint8) (ref&0xff));			\
			FILL_AXIS_CMD((base+DATA51_M) ,	(uint8)((ref>>8)&0xff));	\
			FILL_AXIS_CMD((base+DATA51_H) ,	(uint8)((ref>>16)&0xff));


// AIRINPROG    1:原來air設定穿插在程式中, 0:獨立畫面
//#define AIRINPROG    0

//只有一種可以設定為1
//  M68K_51			代表控制器為:M68K軸卡控制器:8051
//	M68K_3701_3702	代表控制器為:M68K軸卡控制器:3701/3702
//  PC_51_ARM		代表控制器為:PC  軸卡控制器:8051/ARM
#define M68K_51 		0
#define M68K_3701_3702	0
#define PC_51_ARM		1



//2012_0613_ETP_Bound_Check------------------------------------------

#ifdef Bound_Check
#define SIZE(buf) (sizeof(buf)/sizeof(buf[0]))

#define EPT(type)								\
typedef struct EPT_##type{						\
	type *value ;								\
	type *low_bound ;							\
	type *high_bound ;							\
}ept_##type ;
#else
#define EPT(type)								\
typedef type *  ept_##type ;
#endif

EPT(bool);
EPT(char);
EPT(short);
EPT(long);
EPT(int);
//	

#ifdef Bound_Check
#define EPT_IDX(Now_idx, Max_idx)		\
	if	( (((int32)(Now_idx+1))<=0)							||(((int32)Now_idx)	>=	((int32)(SIZE(Max_idx))))){	\
		Sprintf("bound err --> Now_idx(%d) >= Max_idx(%d)-->%s:%s() %d",Now_idx,SIZE(Max_idx),__FILE__,__FUNCTION__,__LINE__);	\
		char buf[100];																												\
		sprintf(buf,"bound err --> Now_idx(%d) >= Max_idx(%d)-->%s:%s() %d",Now_idx,SIZE(Max_idx),__FILE__,__FUNCTION__,__LINE__);	\
		save_record(buf);																											\
	}



#define EPT_BC(a,b)													\
	if((((unsigned char*)(a)) < ((unsigned char *)b.low_bound))||(((unsigned char *)(a))>=((unsigned char*)b.high_bound))){				\
		Sprintf("bound error %x (%x,%x)---->%s:%s() %d",(a),b.low_bound,b.high_bound,__FILE__,__FUNCTION__,__LINE__) ;		\
	}
#else
#define EPT_IDX(Now_idx, Max_idx)
#define EPT_BC(a,b)
#endif

/*	例
 	int a[100] ;
 	ept_int ept_a={&a[0],&a[0],&a[100]} ;
 	ept_int p = ept_a ;
 	int i ;						<==陣列目前idx
 	
 	for(i=0 ; i <100 ; i++){
 		if(i==50){i+=100;}		<==錯誤句插入，超出a[]陣列範圍
 		EPT_BC(p.value+i,p) ;
        *(p.value+i) = i ;
 	}	
*/
//2012_0613_ETP_Bound_Check------------------------------------------


// PC mode -----include N(ew)620/S(mall)620 
#define N620			1
#define S620			0



#define DP_PART_PC1		0
#define DEBUG			0
#define CCY_CHECK		0
#define TOUCH_PRI		1
#define NEW_3701		1
#define SAVE_LENCHK_XMS			0

#define BNY(B7,B6,B5,B4,B3,B2,B1,B0)	((unsigned char)(((((((B7*2+B6)*2+B5)*2+B4)*2+B3)*2+B2)*2+B1)*2+B0))
#define MASK_BIT7						BNY(1,0,0,0,0,0,0,0)
#define MASK_BIT6						BNY(0,1,0,0,0,0,0,0)
#define MASK_BIT5						BNY(0,0,1,0,0,0,0,0)
#define MASK_BIT4						BNY(0,0,0,1,0,0,0,0)
#define MASK_BIT3						BNY(0,0,0,0,1,0,0,0)
#define MASK_BIT2						BNY(0,0,0,0,0,1,0,0)
#define MASK_BIT1						BNY(0,0,0,0,0,0,1,0)
#define MASK_BIT0						BNY(0,0,0,0,0,0,0,1)
#define BYTE							unsigned char
#define WORD							unsigned short
#define DWORD							unsigned long
#define SBYTE							char
#define SWORD							short
#define SDWORD							long
#define TIMEROUT						long long
#define malloc   			malloc	
typedef unsigned char   uint8  ;
typedef unsigned short 	uint16	;
typedef unsigned long  	uint32	;
typedef char            int8	;
typedef short			int16	;
typedef long			int32 ;	
typedef short  			SCRN_XY ;	
typedef char * 			Cptr ;	


EPT(int8);	EPT(int16);		EPT(int32);
EPT(uint8);	EPT(uint16);	EPT(uint32);

EPT(SBYTE);	EPT(SWORD);		EPT(SDWORD);
EPT(BYTE);	EPT(WORD);		EPT(DWORD);
					
#define GET_VAL(type , name) 						\
				type name = *(type *)dptr ;			\
				dptr += (sizeof(type)) ;
#define GET_VAL_ONLY(type , name)					\
				name = *(type *)dptr ;				\
				dptr += (sizeof(type)) ;
				
#define SAVE_VAL(type , name)						\
				*(type *)dptr = name ;				\
				dptr += (sizeof(type)) ;
#define SAVE_STRING(str,len)						\
			memcpy(dptr,str,len) ;					\
			*(dptr+len)=0 ;								\
			dptr+=(len+1) ;
#define GET_STRING_MUST								\
			while(*dptr++ != '\0') ;				
			
			
#if DEBUG_PARAMETER 				
#define LEN_CHKSUM 1
#define SAVE_CHKSUM         						\
				BYTE chksum=0 ; 			        \
				BYTE *chksum_ptr=(BYTE *) tptr ;    \
				while(chksum_ptr < dptr){           \
					chksum += *chksum_ptr++ ;       \
				}                                   \
				*(BYTE *)dptr = chksum ;				
#define SAVE_CHKSUM_NO_ALLOC   						\
				chksum=0 ; 			       			\
				chksum_ptr=(BYTE *) tptr ;   		\
				while(chksum_ptr < dptr){           \
					chksum += *chksum_ptr++ ;       \
				}                                   \
				*(BYTE *)dptr = chksum ;				
#define CHK_CHKSUM         							\
				BYTE chksum=0 ;                     \
				BYTE *chksum_ptr= (BYTE *)ptr ;     \
				while(chksum_ptr < dptr){           \
					chksum += *chksum_ptr++ ;       \
				}                                   \
				if((*(BYTE *)dptr) != chksum){	    \
					chksum_err() ;					\
				}			
#define CHK_CHKSUM_NO_ALLOC         				\
				chksum=0 ;                     		\
				chksum_ptr= (BYTE *)ptr ;     		\
				while(chksum_ptr < dptr){           \
					chksum += *chksum_ptr++ ;       \
				}                                   \
				if((*(BYTE *)dptr) != chksum){	    \
					chksum_err() ;					\
				}			
#define GET_STRING		GET_STRING_MUST
#else
#define LEN_CHKSUM 0
#define SAVE_CHKSUM
#define SAVE_CHKSUM_NO_ALLOC
#define CHK_CHKSUM
#define CHK_CHKSUM_NO_ALLOC
#define GET_STRING
#endif




#define PLUS_MOVE		0
#define MINUS_MOVE		1
#define PLUS_MINUS		2
#define MINUS_PLUS      3
#define OFF_MOVE		30




#define MAX_RESEND_CNT     5
#define QUEUE_NO				40
#define QUEUE_SIZE				400
EXTERN ept_char pDispBuf;

#ifdef Bound_Check
#define pDispBuf_value 			pDispBuf.value
#define SetAirBuf_value 		SetAirBuf.value
#define ref_value				ref.value
#define lpos_value				lpos.value
#define dw_value     			dw.value
#define buf_value     			buf.value
#define pBuf_value     			pBuf.value
#define flag_ZABC_value     	flag_ZABC.value
#define pbuffer_value     		pbuffer.value
#else
#define pDispBuf_value 			pDispBuf
#define SetAirBuf_value 			SetAirBuf
#define ref_value      			ref
#define lpos_value     			lpos
#define dw_value     			dw
#define buf_value     			buf
#define pBuf_value     			pBuf
#define flag_ZABC_value     	flag_ZABC
#define pbuffer_value	     	pbuffer
#endif

EXTERN char DispBuf[QUEUE_SIZE];

#ifdef Bound_Check
EXTERN ept_char ept_DispBuf
#ifdef GLOBAL
={
	&DispBuf[0],&DispBuf[0],&DispBuf[QUEUE_SIZE]
} 
#endif
;
#else
#define ept_DispBuf    DispBuf 
#endif

EXTERN bool ChkOverFlow[MAX_AXIS] ;
#define idx_language   (MachineStatus.language?(MachineStatus.language==3? 2:1):0)
#define CHINESE ((MachineStatus.language==1)||(MachineStatus.language==2))
#define ENGLISH (MachineStatus.language==0) 
#define ITALY	(MachineStatus.language==3)


struct PHY_AXIS{
	BYTE idx ;
} ;
struct LOG_AXIS{
	BYTE idx ;
} ;
