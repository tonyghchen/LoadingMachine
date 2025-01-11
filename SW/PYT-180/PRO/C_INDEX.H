#define main_INDEX1											\
	FILE *fp ;                                      \
	long len ;                                      \
	fp=FOPEN(COMMENT_C,"rb") ;                      \
	if(fp != NULL){                                 \
		len= filesize(fp) ;                          \
		FCLOSE(fp) ;                                 \
	}                                               \
	else{                                           \
		len = 800 ;                                  \
	}                                               \
	if((len == 800) || (len == 40000)){             \
		GComment() ;                                 \
	}

#define   GetCursor_INDEX1														\
	case INDEX_CONTENT_CURSOR:                                     \
		DispIndexContent_q(true) ;                                  \
		SendFlashColor_q(0, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR);      \
		break;                                                      \
	case INDEX_FILE_CURSOR:                                        \
		DispIndex_q(Index.loc_x,true) ;                             \
		SendFlashColor_q(0, CUR_PROG_FCOLOR, CUR_PROG_BCOLOR);      \
		break;


#define NextCursor_INDEX														\
	if(CursorLoc == INDEX_CONTENT_CURSOR){                         \
		if(Index.x == 24){                                          \
			if(Index.y != 15){                                       \
				Index.x=0 ;                                           \
				Index.y++ ;                                           \
			}                                                        \
		}                                                           \
		else{                                                       \
			Index.x++ ;                                              \
		}                                                           \
		DispIndexContent_q(true) ;                                  \
	}                                                              \
	else

#define PrevCursor_INDEX														\
	if(CursorLoc == INDEX_CONTENT_CURSOR){                         \
		if(Index.x == 0){                                           \
			if(Index.y != 0){                                        \
				Index.x=24 ;                                          \
				Index.y-- ;                                           \
			}                                                        \
		}                                                           \
		else{                                                       \
			Index.x-- ;                                              \
		}                                                           \
		DispIndexContent_q(true) ;                                  \
	}                                                              \
	else


#define KeyPgUp_INDEX														\
	case INDEX_FILE_CURSOR:                                              	\
		KeyPgUp_INDEX_FILE_CURSOR()	;										\
		break ;

#define  KeyPgDown_INDEX														\
	case INDEX_FILE_CURSOR:                                                 	\
		KeyPgDown_INDEX_FILE_CURSOR()	;										\
		break ;


#define KeyUp_INDEX													\
	case INDEX_FILE_CURSOR:                               \
		if(Index.loc_x >0){                                \
			DispIndex_q(Index.loc_x--,false) ;              \
			DispIndex_q(Index.loc_x  ,true) ;               \
		}                                                  \
		else{                                              \
			if(Index.start_x > 0){                          \
				Index.start_x-- ;                            \
				DispIndex_q() ;                              \
				DispIndex_q(Index.loc_x,true) ;              \
			}                                               \
		}                                                  \
		DispIndexContent_q() ;                             \
		break ;                                            \
	case INDEX_CONTENT_CURSOR:                            \
		DispIndexContent_q(false) ;                        \
		if(Index.y != 0){                                  \
			Index.x=0 ;                                     \
			Index.y-- ;                                     \
		}                                                  \
		DispIndexContent_q(true) ;                         \
		break ;


#define KeyDown_INDEX																	\
	case INDEX_FILE_CURSOR:                                              \
		if(Index.loc_x+Index.start_x != MAX_FILE_NO){                     \
			if(Index.loc_x < (PAGE_LINES_INDEX-1)){                        \
				DispIndex_q(Index.loc_x++,false) ;                          \
				DispIndex_q(Index.loc_x  ,true) ;                           \
			}                                                              \
			else{                                                          \
				if((Index.start_x+PAGE_LINES_INDEX) < MAX_FILE_NO){         \
					Index.start_x++ ;                                        \
					DispIndex_q() ;                                          \
					DispIndex_q(Index.loc_x,true) ;                          \
				}                                                           \
			}                                                              \
		}                                                                 \
		DispIndexContent_q() ;                                            \
		break ;                                                           \
	case INDEX_CONTENT_CURSOR:                                           \
		DispIndexContent_q(false) ;                                       \
		if(Index.y != 15){                                                \
			Index.x=0 ;                                                    \
			Index.y++ ;                                                    \
		}                                                                 \
		DispIndexContent_q(true) ;                                        \
		break ;


#define	KeyLeft_INDEX								\
	case INDEX_CONTENT_CURSOR:                \
		DispIndexContent_q(false) ;            \
		PrevCursor();                          \
		break ;

#define  KeyRight_INDEX           				\
	case INDEX_CONTENT_CURSOR:                \
		DispIndexContent_q(false) ;            \
		NextCursor();                          \
		break ;


#define KeyWr_INDEX     														\
	case INDEX_FILE_CURSOR:                                        \
		MachineStatus.file=BinToBcd(4,Index.start_x+Index.loc_x) ;  \
		com_FileMody() ;                                            \
		SoftReset() ;                                               \
		break ;                                                     \
	case INDEX_CONTENT_CURSOR:                                     \
		{                                                           \
			WORD fileno= Index.loc_x+Index.start_x ;                 \
			FILE *fp_c ,*fp_d;                                       \
			fp_c= FOPEN(COMMENT_C,"rb+") ;                           \
			fseek(fp_c , fileno*sizeof(Index.Content),SEEK_SET) ;    \
			fwrite(Index.Content,1,sizeof(Index.Content) ,fp_c) ;    \
			FCLOSE(fp_c) ;                                           \
			if(DDisk){                                               \
				fp_d= FOPEN(COMMENT_D,"rb+") ;                        \
				fseek(fp_d , fileno*sizeof(Index.Content),SEEK_SET) ; \
				fwrite(Index.Content,1,sizeof(Index.Content) ,fp_d) ; \
				FCLOSE(fp_d) ;                                        \
			}                                                        \
		}                                                           \
		break ;		

#define KeyChgCursor_INDEX         											\
	else if(CursorLoc == INDEX_FILE_CURSOR){                       \
		DispIndex_q(Index.loc_x,false) ;                            \
		Index.x=Index.y=0 ;                                         \
		ChgCursorLoc(INDEX_CONTENT_CURSOR) ;                        \
		DispIndexContent_q(true) ;                                  \
	}                                                              \
	else if(CursorLoc == INDEX_CONTENT_CURSOR){                    \
		ChgCursorLoc(INDEX_FILE_CURSOR) ;                           \
		DispIndexContent_q(false) ;                                 \
	}



#define   getkey_INDEX															\
			if(CursorLoc == INDEX_CONTENT_CURSOR){                   \
					if(key == 0xd){                                    \
						KeyDown() ;                                     \
					}                                                  \
					else{                                              \
						Index.Content[Index.y][Index.x]=key ;           \
						KeyRight() ;                                    \
					}                                                  \
				}                                                     \
				else

#define  always_run_INDEX												\
	CursorData_t **ptr;                                            		\
	ptr = (CurCursor.ptr);                                         		\
	CursorData_t *pptr= *ptr ;                                     		\
	if((pptr->var != &MachineStatus.file) && IndexScrn){           		\
		ClrIndexWindow_q() ;												\
	}                                                              		\
	if((pptr->var == &MachineStatus.file) && !IndexScrn){          		\
		DispIndexWindow_q() ;                                         	\
	}


#define  KeySpaceBar_INDEX(ch)												\
	if(CursorLoc == INDEX_CONTENT_CURSOR ){ 								\
		Index.Content[Index.y][Index.x]=ch ;          						\
		KeyRight() ;                                    					\
	}																		\
    else if(CursorLoc == INDEX_FILE_CURSOR){								\
	}																		\
    else      				


#define KeySign_INDEX          												\
	if(CursorLoc == INDEX_CONTENT_CURSOR){                         			\
		BYTE *b ;															\
		b = &Index.Content[Index.y][Index.x];                       		\
		switch_next("+-",b) ;                            					\
		DispIndexContent_q(true) ;                                  		\
	}																		\
	else if(CursorLoc == INDEX_FILE_CURSOR){								\
	}																		\
	else


