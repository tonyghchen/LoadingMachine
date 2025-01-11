

#if CHK_MAN_MOV
void ChkManMov() ;
#endif


#if NEW_INDEX
void IndexFileMody (void) ;
void KeyIndex (void) ;
void DispIndexWindow_q() ;
void DispIndexWindow() ;
#endif

#if FILE_ACCESS
FILE *Fopen(char *filename , char *md) ;
void Fclose(FILE *fp) ;
bool check_file_access(void) ;
#endif


#if GAP_MDY
void YGAP_MDY(DWORD &mov, BYTE dir) ;
void AGAP_MDY(BYTE axis,BYTE dir);
void AMDYY(DWORD &mov,BYTE dir) ;
#endif





#if (COMPILER == DJ_COMPILER)
void rectangle_q( short lx, short ly , short rx, short ry,COLOR_T color,short width) ;
#else
void rectangle_q( short lx, short ly , short rx, short ry);
#endif


