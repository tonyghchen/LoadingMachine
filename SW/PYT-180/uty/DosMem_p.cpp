// DOS MEM protection mode function  v1.00

static unsigned base ;
void new_base (unsigned tbase)
{
	base=tbase ;
}
void wDosMem (unsigned addr , uint8 data1)
{
(*((volatile unsigned short *)((addr))) = (data1));
}
void wDosMem (unsigned addr , uint16 data1)
{
(*((volatile unsigned short *)((addr))) = (data1));
}
void wDosMem (unsigned addr , uint32 data1)
{
(*((volatile unsigned short *)((addr))) = (data1));
}
void wDosMem_base (unsigned off , uint8 data1)
{
	//_farpokeb(_dos_ds,base+off,data1);
}
void wDosMem_pc_base (unsigned off , uint8 data1)
{
	//_farpokeb(_dos_ds,pc_base+off,data1);
}
uint8 rDosMem (unsigned addr)
{
	return((*((volatile unsigned short *)((addr))))) ;
}
uint16 rDosMemw (unsigned addr)
{
	return((*((volatile unsigned short *)((addr))))) ;
}
uint32 rDosMeml (unsigned addr)
{
	//return(_farpeekl(_dos_ds,addr)) ;
}
uint8 rDosMem_base (unsigned off)
{
	//return(_farpeekb(_dos_ds,base+off)) ;
}
uint8 rDosMem_pc_base (unsigned off)
{
	//return(_farpeekb(_dos_ds,pc_base+off)) ;
}
void OUTB2ARM (unsigned addr , uint8 val)
{
	//wDosMem(addr,val) ;
}
void OUTL2ARM (unsigned  addr , uint32 val)
{
	//wDosMem(addr,val) ;
}

