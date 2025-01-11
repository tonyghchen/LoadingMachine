#define HNCNC6

#ifdef HNCNC6 

#define MAX_AXIS						2
#define MAX_AXIS_8						8
#define MAX_PROG_AXIS					6

#define MAX_PROGEX_NUMBER          20

#define	TYPE_620_820	(0x620)
#define	TYPE_635_835	(0x635)
#define	TYPE_650_850	(0x650)
#define	TYPE_1635_1835	(0x1635)

#define SCRN_W  		(640)
#define SCRN_H			(480)

#define SCREEN_MAXX 	(640)
#define SCREEN_MAXY 	(480)

#define SIZE_CONFIG1 	  	103
#define SIZE_CONFIG2 	  	131
#define SIZE_CONFIG3 	  	136
#define SIZE_CONFIG4 	  	144
#define SIZE_CONFIG5 	  	156
#define SIZE_CONFIG6 	  	186
#define SIZE_CONFIG7 	  	188
#define SIZE_CONFIG8 	  	190
#define SIZE_CONFIG9 	  	199
#define SIZE_CONFIG10 	  200
#define SIZE_CONFIG11	  	202
#define SIZE_CONFIG12 	  203
#define SIZE_CONFIG13 	  204
#define SIZE_CONFIG14 	  208
#define SIZE_CONFIG15 	  209
#define SIZE_CONFIG16 	  210
#define SIZE_CONFIG17 	  216
#define SIZE_CONFIG18 	  217
#define SIZE_CONFIG19 	  219
#define SIZE_CONFIG20 	  220
#define SIZE_CONFIG21 	  224
#define SIZE_CONFIG22 	  225
#define SIZE_CONFIG23     229
#define SIZE_CONFIG24     230
#define SIZE_CONFIG25     258
#define SIZE_CONFIG26     262
#define SIZE_CONFIG27     264
#define SIZE_CONFIG28     273
#define SIZE_CONFIG29     279
#define SIZE_CONFIG30     303
#define SIZE_CONFIG31     304
#define SIZE_CONFIG32     334
#define SIZE_CONFIG33     364
#define SIZE_CONFIG34     365
#define SIZE_CONFIG35     375
#define SIZE_CONFIG36     376
#define SIZE_CONFIG37     377
#define SIZE_CONFIG38     380
#define SIZE_CONFIG39     394
#define SIZE_CONFIG40     794
#define SIZE_CONFIG41     795
#define SIZE_CONFIG42     804
#define SIZE_CONFIG43     820
#define SIZE_CONFIG44     834
#define SIZE_CONFIG45     838
#define SIZE_CONFIG46     846
#define SIZE_CONFIG47     848
#define SIZE_CONFIG48     856
#define SIZE_CONFIG49     860
#define SIZE_CONFIG50     861
#define SIZE_CONFIG51     862
#define SIZE_CONFIG52     869

#define PARA_BOX_RY 			(PARA_BOX_LY+(ASC_CHAR_H+1)*24)
#define HELP_BOX_RX 			(HELP_BOX_LX+4 +ASC_CHAR_W*79 -1)
#define HELP_BOX_RY 			(HELP_BOX_LY+4 +(ASC_CHAR_H+1)*21 -1)

#define DISK_IO_LX				331
#define DISK_IO_LY				240

#else

#define MAX_AXIS							30
#define MAX_AXIS_8						8
#define MAX_PROG_AXIS					8

#define	TYPE_620_820	(0x820)
#define	TYPE_635_835	(0x835)
#define	TYPE_650_850	(0x850)
#define	TYPE_1635_1835	(0x1835)

#define SCRN_W  		(800)
#define SCRN_H  		(600)

#define SCREEN_MAXX		(800)
#define SCREEN_MAXY 	(600)

#define SIZE_CONFIG1 	  	127
#define SIZE_CONFIG2 	  	161
#define SIZE_CONFIG3 	  	166
#define SIZE_CONFIG4 	  	174
#define SIZE_CONFIG5 	  	190
#define SIZE_CONFIG6 	  	230
#define SIZE_CONFIG7 	  	233
#define SIZE_CONFIG8 	  	234
#define SIZE_CONFIG9 	  	243
#define SIZE_CONFIG10 	  244
#define SIZE_CONFIG11	 	 	246
#define SIZE_CONFIG12 	  247
#define SIZE_CONFIG13 	  248
#define SIZE_CONFIG14 	  252
#define SIZE_CONFIG15 	  253
#define SIZE_CONFIG16 	  254
#define SIZE_CONFIG17 	  262
#define SIZE_CONFIG18 	  263
#define SIZE_CONFIG19 	  265
#define SIZE_CONFIG20 	  266
#define SIZE_CONFIG21 	  270
#define SIZE_CONFIG22 	  271
#define SIZE_CONFIG23     275
#define SIZE_CONFIG24     276
#define SIZE_CONFIG25	  	785
#define SIZE_CONFIG26     789
#define SIZE_CONFIG27     791
#define SIZE_CONFIG28     800
#define SIZE_CONFIG29     808
#define SIZE_CONFIG30     832
#define SIZE_CONFIG31     833
#define SIZE_CONFIG32     873
#define SIZE_CONFIG33     913
#define SIZE_CONFIG34     914
#define SIZE_CONFIG35     924
#define SIZE_CONFIG36     925
#define SIZE_CONFIG37     926
#define SIZE_CONFIG38     929
#define SIZE_CONFIG39     945
#define SIZE_CONFIG40    1345
#define SIZE_CONFIG41    1346
#define SIZE_CONFIG42    1355
#define SIZE_CONFIG43    1371
#define SIZE_CONFIG44    1387
#define SIZE_CONFIG45    1391
#define SIZE_CONFIG46    1399
#define SIZE_CONFIG47    1401
#define SIZE_CONFIG48    1409
#define SIZE_CONFIG49    1413
#define SIZE_CONFIG50    1414
#define SIZE_CONFIG51    1415
#define SIZE_CONFIG52    1423

#define PARA_BOX_RY 			(PARA_BOX_LY+(ASC_CHAR_H+1)*31)
#define HELP_BOX_RX 			(HELP_BOX_LX+4 +ASC_CHAR_W*99 -1)
#define HELP_BOX_RY 			(HELP_BOX_LY+4 +(ASC_CHAR_H+1)*29 -1)

#define DISK_IO_LX				(331+72)
#define DISK_IO_LY				(240+60)

#endif
