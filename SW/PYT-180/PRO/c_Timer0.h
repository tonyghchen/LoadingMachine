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
void sDelay(unsigned int sec); //����sec ��
void dDelay(unsigned int ds); //����ds�ӤQ�����@ ��
void hDelay(unsigned int hs); //����hs�Ӧʤ����@ ��
void mDelay(unsigned int ms); //����ms�Ӥd�����@ ��
void tickDelay(unsigned int ms);
void init_interval_time() ;
float interval_time() ;
bool IsTimeUp(struct TIMER h);
// ���1��
struct TIMER minTimerSet(unsigned int d);
// ���1��
struct TIMER sTimerSet(unsigned int d);
// ���0.01��
struct TIMER hTimerSet(unsigned int h);
// ���0.1��
struct TIMER dTimerSet(unsigned int d);
// ���0.001��
struct TIMER mTimerSet(unsigned long m);
float ELAAPSED_MS(struct TIMER t0,struct TIMER t1);
long  long ELAAPSED_CNT(struct TIMER t0,struct TIMER t1);
void mDelay_s(int ms) ;
