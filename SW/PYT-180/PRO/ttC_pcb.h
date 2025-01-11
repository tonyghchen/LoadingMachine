#define LOOP_TIMES      100000L
#define TIMER0_HZ      10000

#if (SAVE_AXIS_CMD ==1)	//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
#define FILL_AXIS_CMD(addr,val)				\
		wDosMem(addr,(uint8)(val)) ;				 		\
		axis_cmd.SaveBuf(addr,val,0,0,ReadTimer2()) ;
#else	//************************************************
#define FILL_AXIS_CMD(addr,val)				\
		wDosMem(addr,(uint8)(val)) ;
#endif	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^



// AIRINPROG    1:原來air設定穿插在程式中, 0:獨立畫面
//#define AIRINPROG    0

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
typedef unsigned char   uint8  ;
typedef unsigned short 	uint16	;
typedef unsigned long  	uint32	;
typedef char            int8	;
typedef short			int16	;
typedef long			int32 ;							
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
			*(dptr+len)=0 ;							\
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
