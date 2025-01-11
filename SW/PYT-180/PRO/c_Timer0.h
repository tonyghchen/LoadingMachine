#define NOCNT_1MS		(TIMER0_HZ/1000)
#define NOCNT_1HS		(TIMER0_HZ/100)
#define NOCNT_1DS		(TIMER0_HZ/10)
#define NOCNT_1S		TIMER0_HZ
struct TIMER{
	long long timer ;
} ;
void InitializeTimer() ;
void RestoreTimer() ;
struct TIMER ReadTimer() ;
void sDelay(unsigned int sec); //延遲sec 秒
void dDelay(unsigned int ds); //延遲ds個十分之一 秒
void hDelay(unsigned int hs); //延遲hs個百分之一 秒
void mDelay(unsigned int ms); //延遲ms個千分之一 秒
void tickDelay(unsigned int ms);
void init_interval_time() ;
float interval_time() ;
bool IsTimeUp(struct TIMER h);
// 單位1分
struct TIMER minTimerSet(unsigned int d);
// 單位1秒
struct TIMER sTimerSet(unsigned int d);
// 單位0.01秒
struct TIMER hTimerSet(unsigned int h);
// 單位0.1秒
struct TIMER dTimerSet(unsigned int d);
// 單位0.001秒
struct TIMER mTimerSet(unsigned long m);
float ELAAPSED_MS(struct TIMER t0,struct TIMER t1);
long  long ELAAPSED_CNT(struct TIMER t0,struct TIMER t1);
void mDelay_s(int ms) ;
