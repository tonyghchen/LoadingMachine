void new_base(uint8* tbase) ;
void wDosMem(uint8 *addr , uint8 data1) ;
void wDosMem(uint8 *addr , uint16 data1) ;
void wDosMem_base(unsigned off , uint8 data1) ;
void wDosMem_pc_base(unsigned off , uint8 data1) ;
uint8 rDosMem(uint8 *addr) ;
uint8 rDosMem_base(unsigned off) ;
uint8 rDosMem_pc_base(unsigned off) ;
void OUTB2ARM(BYTE *addr , BYTE val) ;
void OUTL2ARM(BYTE *addr , unsigned long val) ;
