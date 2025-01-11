#ifdef GLOBAL
#define EXTERN
#else
#define EXTERN extern
#endif
EXTERN	unsigned int comm_port
#ifdef GLOBAL
= 0
#endif
;
