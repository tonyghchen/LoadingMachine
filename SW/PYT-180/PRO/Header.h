#include 	"c_header.h"

#include "NuMicro.h"

	
			
#define RUN_MSG_LY	(365+2*ASC_CHAR_H)
#define END_X_LIMIT    (BcdToBin(MOTOR_GRADS_BCD, MachineStatus.motor_grads[AXIS_X])-10)
#define RUN_UPDATE_LINE1																			\
			if(	MachineStatus.op_mode != RUN_MODE ){                                                \
				if(	!MachineStatus.prog_mody ){                                                     \
					DISPCURPROGLIST                                                                 \
				}                                                                                   \
			}                                                                                       \
			break;

#define RUN_SET_TOUCH1\
	RUN_SET_TOUCH2\
  st_extencoder.first= true ;

  
#define STOPX   	0x1 
#define STOPY    	0x2
#define STOPZ   	0x4
#define STOPA  		0x8
#define STOPB		0x10
#define STOPC  		0x20
#define STOPD     	0x40
#define STOPE 		0x80  
#define TOUCH_STOP(touchno,stopaxis)								\
	wDosMem(pc_base+0xf8+(touchno-1),(uint8)stopaxis) ;
#define DISABLE_TOUCH_STOP(touchno)									\
	wDosMem(pc_base+0xf8+(touchno-1),(uint8)0x00) ;
#define ENABLE_TOUCH_INT(touchno) 									\
	wDosMem(pc_base+0xc12,BITmask[7-(touchno-1)]) ;
#define DISABLE_TOUCH_INT											\
wDosMem(pc_base+0xc12,(uint8)0x00) ;
