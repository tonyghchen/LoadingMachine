struct REC_TIME{
	unsigned char  id_start , id_end ;
	unsigned long time_start,time_end;
} ;
class crec_time{
	int	idx ,rec_len; 
	REC_TIME *prec_time ;
	public :
	crec_time(int rec_len) ;
	void StartTimer(unsigned char id) ;
	void StopTimer(unsigned char id) ;
	~crec_time() ;
} ;
EXTERN crec_time rec_time
#ifdef GLOBAL
(200) 
#endif
;
