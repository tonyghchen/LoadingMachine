int absMov (int &mov) ;
int find_idms (BYTE axis , int mov , int ms ) ;
void Gen_Tidms (BYTE axis) ;
void GenTmov (BYTE axis , short Tmov[] , uint8 sign , int mov , int ms , int cidms ) ;
void RunManMov () ;
void close_intDDA(void) ;
void setup_intDDA (void) ;
int intDDA () ;
int Deg2Grid (int Deg) ;
void CalNextManMov () ;
void Step_operation(void);
bool chkOverLimit (uint8 axis,uint8 dir,uint8 man_hand,int &newval ,int &mov) ;
void StopDDA(BYTE axis) ;
bool ChkDriverClear(uint8 axis) ;
void SetDriverClear() ;
void SetDriverClear(uint8 axis) ;
void ResetDriverClear() ;
void ResetDriverClear(uint8 axis);
int intHomeTouch() ;
void setup_intHomeTouch();   //IRQ11
int ReadAdc100() ;
uint16 GenRatio() ;
void DispReturn_proc(void);
void DispTotalY_proc(void);
void run_DDA() ;
void TotalY(void);
void DispReutrn_q(void);
void DispTotalY_q (void);
void Ini_Feedback(uint8 axis) ;
void setup_intHomeTouch_NewH() ;
void update_run_DDA() ;
void ReadAxes(uint8 axis) ;
void ReadAxes() ;
void close_intHomeTouch_NewH(void);
void ClrTouch(void);
void SendTouch(uint8 Cmd,int mode,int pos);


