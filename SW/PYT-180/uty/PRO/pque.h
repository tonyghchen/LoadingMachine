#define DrawButtonx_proc_GET(DrawButtonx_proc,x1,y1,x2,y2,col1,DrawButton_colx)		\
void DrawButtonx_proc(void *ptr)													\
{                                                   								\
	BYTE *dptr= (BYTE *)ptr ;                       								\
	GET_VAL(short , x1) ;                           								\
	GET_VAL(short , y1) ;                           								\
	GET_VAL(short , x2) ;                           								\
	GET_VAL(short , y2) ;                           								\
	GET_VAL(short , col1) ;                         								\
	CHK_CHKSUM                                      								\
	DrawButton_colx(x1,y1,x2,y2,col1) ;             								\
	farfree(ptr) ;                                  								\
}

#define	DrawButtonx_proc_SAVE(x1, y1, x2, y2, col1,DrawButtonx_proc) 	\
	{																	\
		MALLOC(5*sizeof(short)+LEN_CHKSUM) ;         					\
		SAVE_VAL(short , x1) ;                                          \
		SAVE_VAL(short , y1) ;                                          \
		SAVE_VAL(short , x2) ;                                          \
		SAVE_VAL(short , y2) ;                                          \
		SAVE_VAL(short , col1) ;                                        \
		SAVE_CHKSUM                                                     \
		FILL_PROC_QUEUE(DrawButtonx_proc,tptr) ;						\
	}

void DrawButton1_proc(void *ptr);
void DrawButton2_proc(void *ptr) ;
void DrawButton3_proc(void *ptr) ;
void DrawButton4_proc(void *ptr) ;

#define DrawButtonxx_proc_GET(DrawButtonxx_proc, x1, y1, x2, y2, col1, col2,DrawButton_col1,DrawButton_col2) ;  \
void DrawButtonxx_proc(void *ptr)                                       \
{                                                                       \
	BYTE *dptr= (BYTE *)ptr ;                                           \
	GET_VAL(short , x1) ;                                               \
	GET_VAL(short , y1) ;                                               \
	GET_VAL(short , x2) ;                                               \
	GET_VAL(short , y2) ;                                               \
	GET_VAL(short , col1) ;                                             \
	GET_VAL(short , col2) ;                                             \
	CHK_CHKSUM                                                          \
	DrawButton_col1(x1,y1,x2,y2,col1) ;                                 \
	DrawButton_col2(x1,y1,x2,y2,col2) ;                                 \
	farfree(ptr) ;                                                      \
}


void DrawButton12_proc(void *ptr) ;

#define DrawButtonxx_proc_SAVE( x1, y1, x2, y2, col1, col2,DrawButtonxx_proc) \
	{																	\
		MALLOC(6*sizeof(short)+LEN_CHKSUM) ;         					\
		SAVE_VAL(short , x1) ;                                          \
		SAVE_VAL(short , y1) ;                                          \
		SAVE_VAL(short , x2) ;                                          \
		SAVE_VAL(short , y2) ;                                          \
		SAVE_VAL(short , col1) ;                                        \
		SAVE_VAL(short , col2) ;                                        \
		SAVE_CHKSUM                                                     \
		FILL_PROC_QUEUE(DrawButtonxx_proc,tptr) ;                       \
	}

void DrawButton34_proc(void *ptr) ;
void DrawButton1234_proc(void *ptr) ;
#define DrawButton1234_proc_GET											\
void DrawButton1234_proc(void *ptr)                                     \
{                                                                       \
	BYTE *dptr= (BYTE *)ptr ;                                           \
	GET_VAL(short , x1);                                                \
	GET_VAL(short , y1);                                                \
	GET_VAL(short , x2);                                                \
	GET_VAL(short , y2);                                                \
	GET_VAL(short , col1) ;                                             \
	GET_VAL(short , col2) ;                                             \
	GET_VAL(short , col3) ;                                             \
	GET_VAL(short , col4) ;                                             \
	CHK_CHKSUM                                                          \
	DrawButton_col1(x1,y1,x2,y2,col1) ;                                 \
	DrawButton_col2(x1,y1,x2,y2,col2) ;                                 \
	DrawButton_col3(x1,y1,x2,y2,col3) ;                                 \
	DrawButton_col4(x1,y1,x2,y2,col4) ;                                 \
	farfree(ptr) ;                                                      \
}

#define DrawButton1234_proc_SAVE										\
	{                                                                   \
		MALLOC(8*sizeof(short)+LEN_CHKSUM) ;         					\
		SAVE_VAL(short , x1);                                           \
		SAVE_VAL(short , y1);                                           \
		SAVE_VAL(short , x2);                                           \
		SAVE_VAL(short , y2);                                           \
		SAVE_VAL(short , col1) ;                                        \
		SAVE_VAL(short , col2) ;                                        \
		SAVE_VAL(short , col3) ;                                        \
		SAVE_VAL(short , col4) ;                                        \
		SAVE_CHKSUM                                                     \
		FILL_PROC_QUEUE(DrawButton1234_proc,tptr) ;                     \
	}
