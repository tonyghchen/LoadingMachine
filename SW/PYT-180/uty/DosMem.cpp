// DOS MEM no protection mode function  v1.00

static uint8 *base ;
void new_base(uint8* tbase)
{
	base=tbase ;
}
void wDosMem(uint8 *addr , uint8 data1)
{
	*(addr)= data1;
}
void wDosMem(uint8 *addr , uint16 data1)
{
	*((uint16 *)addr)= data1;
}
void wDosMem_base(unsigned off , uint8 data1)
{
	*(base+off)= data1;
}
void wDosMem_pc_base(unsigned off , uint8 data1)
{
	*(pc_base+off)= data1;
}
uint8 rDosMem(uint8 *addr)
{
	return(*(addr)) ;
}
uint8 rDosMem_base(unsigned off)
{
	return(*(base+off)) ;
}
uint8 rDosMem_pc_base(unsigned off)
{
	return(*(pc_base+off)) ;
}
void OUTB2ARM(BYTE *addr , BYTE val)
{
	*addr= val ;
}
void OUTL2ARM(BYTE *addr , unsigned long val)
{
	*(unsigned long *)addr=val ;
}
