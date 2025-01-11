/******************************************************************************
 *  File    :   device_table.cpp
 *  Version :   1.01
 *  Date    :   2023/08/04
 *  Author  :   chan-fa
 *
 *
 *
 * @copyright (C) 2022-2024.
 * -------------------------------------------------------------------------
 *  Modification History :
 * -------------------------------------------------------------------------
 *  Version | Mdy Date : | Descriptions
 *          | mm/dd/yyyy |
 *  V1.0.1  | 08/04/2023 | First release
 *  V1.1.0  | 07/05/2024 | 增加台灣安川電機馬達, PID=0x6038000
 *                         第一次Initial()可正確進入，再次Initial()將失敗，因此再次Initial()需要重開機
 *  V1.1.1  | 07/23/2024 | 增加panasonic, VID=0x066f, PID=0x60380008
 * -------------------------------------------------------------------------
 ******************************************************************************/

 
 
const ST_SLAVE_OBJECT_INFO_T beckoff_ek1100_pdo [] =
{
    {ECM_DEVICE_COUPLER, 0x00000000},   // Coupler       
    {ECM_DEVICE_NONE,    0x00000000}      // End   
};


const ST_SLAVE_OBJECT_INFO_T beckoff_el1889_pdo [] =
{
    { ECM_DEVICE_DIN,    0x0010},  // DInput, 16Bits
    { ECM_DEVICE_NONE,   0x0000}   // End
};


const ST_SLAVE_OBJECT_INFO_T beckoff_el2889_pdo [] =
{
    { ECM_DEVICE_DOUT,   0x0010},  // Doutput, 16Bits
    { ECM_DEVICE_NONE,   0x0000}   // End    
};


const ST_SLAVE_OBJECT_INFO_T beckoff_el3062_pdo [] =
{
    { ECM_DEVICE_AIN,        0x0020},  // AInput, 32Bits
    { ECM_DEVICE_AIN,        0x0020},  // AInput, 32Bits            
    { ECM_DEVICE_NONE,       0x0000}   // End
};

const ST_SLAVE_OBJECT_INFO_T nextw_es16i16o_pdo [] =
{
    { ECM_DEVICE_DOUT,   	0x0010},  // Doutput, 16Bits	
    { ECM_DEVICE_DIN,  	 	0x0010},  // DInput, 16Bits
    { ECM_DEVICE_NONE,       0x0000}   // End
};


const ST_SLAVE_OBJECT_INFO_T servo_pdo_common [] =
{
    //  RxPDO:output Data
    // 0x1C12:rxPDO mapping assign, 0x1600:   PDO mapping.
    { (ECM_DEVICE_AC_SERVO_OUT ),
        0x1C121600  },
    
    // 0x6040, 16-bits, Control word.
    { (ECM_DEVICE_AC_SERVO_OUT | ECM_RXPOD_REG_CTLWORD),
        0x60400010  }, 
				
	  // 0x60B8, 16-bits, Touch probe mode.    
    { (ECM_DEVICE_AC_SERVO_OUT | ECM_RXPDO_REG_TOUCH_PROBE_MODE),
      0x60B80010  },  


    // 0x607A, 32-bits, Target position.    
    { (ECM_DEVICE_AC_SERVO_OUT | ECM_RXPDO_REG_TARGET_POS),
      0x607A0020  }, 
	  



    //  TxPDO:input Data
    // 0x1C13:TxPDO mapping assign, 0x1A00:    PDO mapping.    
    { ECM_DEVICE_AC_SERVO_IN,
      0x1C131A00  },

    // 0x6041 16-bits, status word.         
    { (ECM_DEVICE_AC_SERVO_IN | ECM_TXPDO_REG_STATUSWORD),
      0x60410010  },

    // 0x6064 32-bits, Position actual value. 
    { (ECM_DEVICE_AC_SERVO_IN | ECM_TXPDO_REG_ACTUAL_POS),
      0x60640020  },
			
    // 0x6077,16-bits, Torque actual value
    { (ECM_DEVICE_AC_SERVO_IN | ECM_TXPDO_REG_ACTUAL_TORQUE),
      0x60770010  }, 
    // 0x603F,16-bits, Error Code   
    { (ECM_DEVICE_AC_SERVO_IN | ECM_TXPDO_REG_ERROR_CODE),
      0x603F0010  },
    // 0x60B9 16-bits, Touch probe status. 
    { (ECM_DEVICE_AC_SERVO_IN | ECM_TXPDO_REG_TOUCH_PROBE_STATE),
      0x60B90010  },	
				
    // 0x60BC 32-bits, Touch probe pos2 positive edge position stored. 
    { (ECM_DEVICE_AC_SERVO_IN | ECM_TXPDO_REG_TOUCH_PROBE_2_POSITIVE_EDGE),
      0x60BC0020  },
    // 0x60F4 32-bits, 实际位置偏差(实际跟随误差值). 
    { (ECM_DEVICE_AC_SERVO_IN | ECM_TXPDO_REG_FOLLOWING_ERROR_ACTUAL_VALUE),
      0x60F40020  },	 			

    { ECM_DEVICE_NONE,       
      0x00000000  }   // End  
};



const ST_SLAVE_OBJECT_INFO_T servo_pdo_panasonic_minas_a6be [] =
{
    //  RxPDO:output Data
    // 0x1C12:rxPDO mapping assign, 0x1600:   PDO mapping.
    { (ECM_DEVICE_AC_SERVO_OUT ),
       0x1C121600  },
    
    // 0x6040, 16-bits, Control word.
    { (ECM_DEVICE_AC_SERVO_OUT | ECM_RXPOD_REG_CTLWORD),
       0x60400010  }, 

    // 0x6060, 8-bits, Modes of operation.    
    { (ECM_DEVICE_AC_SERVO_OUT),
      0x60600008  }, 

    // 0x607A, 32-bits, Target position.    
    { (ECM_DEVICE_AC_SERVO_OUT | ECM_RXPDO_REG_TARGET_POS),
      0x607A0020  }, 	
	  
    // 0x60B8, 16-bits, Touch probe mode.    
    { (ECM_DEVICE_AC_SERVO_OUT | ECM_RXPDO_REG_TOUCH_PROBE_MODE),
      0x60B80010  },   


    //  TxPDO:input Data
    // 0x1C13:TxPDO mapping assign, 0x1A00:    PDO mapping.    
    { ECM_DEVICE_AC_SERVO_IN,
      0x1C131A00  },
	  
    // 0x603F,16-bits, Error Code   
    { (ECM_DEVICE_AC_SERVO_IN | ECM_TXPDO_REG_ERROR_CODE),
      0x603F0010  }, 	  

    // 0x6041 16-bits, status word.         
    { (ECM_DEVICE_AC_SERVO_IN | ECM_TXPDO_REG_STATUSWORD),
      0x60410010  },
	  
    // 0x6061 8-bits, Modes of operation display.         
    { (ECM_DEVICE_AC_SERVO_IN ),
      0x60610008  },	  

    // 0x6064 32-bits, Position actual value. 
    { (ECM_DEVICE_AC_SERVO_IN | ECM_TXPDO_REG_ACTUAL_POS),
      0x60640020  },
	  
    // 0x60B9 16-bits, Touch probe status. 
    { (ECM_DEVICE_AC_SERVO_IN | ECM_TXPDO_REG_TOUCH_PROBE_STATE),
      0x60B90010  },	

    // 0x60BA 32-bits, Touch probe pos1 pos value. 
    { (ECM_DEVICE_AC_SERVO_IN  | ECM_TXPDO_REG_TOUCH_PROBE_1_POSITIVE_EDGE ),
      0x60BA0020  },

    // 0x60F4 32-bits, Following error actual value. 
    { (ECM_DEVICE_AC_SERVO_IN | ECM_TXPDO_REG_FOLLOWING_ERROR_ACTUAL_VALUE),
      0x60F40020  },	  

    // 0x60FD,32-bits, Digital inputs
    { (ECM_DEVICE_AC_SERVO_IN),
      0x60FD0020  },  
    
    { ECM_DEVICE_NONE,       
      0x00000000  }   // End  
};

const SLAVE_DEVICE_TABLE_T slaves_device_table [] = 
{
    // Beckoff,EK1100, Coupler
    {   // Vid      Pid             //Object Dirtionary
        0x0002,     0x044c2c52,     beckoff_ek1100_pdo
    },

    //Beckoff,EL1889, Digital input : 16 channels
    {   
        0x0002,     0x07613052,     beckoff_el1889_pdo
    },  

        //Beckoff,EL2889, Digital output : 16 channels
    {   
        0x0002,     0x0b493052,     beckoff_el2889_pdo 
    },
    
        // Beckoff,EL3062, Analog input, 2 channels,32 bit
    {   
        0x0002,     0x0bf63052,    beckoff_el3062_pdo
   
    },

        // Delta,ASDA-A2-E CoE Drive
    { 
        0x01dd,     0x10305070,    servo_pdo_common
    },  
	
        // nextw    ES-16I16O                                
    { 
        0x101010,    0x00000001,    nextw_es16i16o_pdo          
    },
	
        // SanyoDenki RS2 EtherCAT                                
    { 
        0x01b9,     0x00000002,    servo_pdo_common          
    },	
	
        // panasonic minas-a6be EtherCAT                                
    { 
        0x066f,     0x60380004,    servo_pdo_panasonic_minas_a6be          
    },
	
        // panasonic minas-a6be EtherCAT                                
    { 
        0x066f,     0x60380008,    servo_pdo_panasonic_minas_a6be          
    },	

        // Yaskawa  SGDXS-7R6AAOA, AC SERVO MOTOR SGMXG-09AUA61A2, EtherCAT                                
    { 
        0x0539,     0x02200901,    servo_pdo_common          
    }  
};
