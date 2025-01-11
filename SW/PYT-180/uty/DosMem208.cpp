// DOS MEM protection mode function  v1.00

static unsigned base ;
void new_base(unsigned tbase)
{
	base=tbase ;
}
void wDosMem(unsigned addr , uint8 data1)
{
	_farpokeb(_dos_ds,addr,data1);
}
void wDosMem(unsigned addr , uint16 data1)
{
	_farpokew(_dos_ds,addr,data1);
}
void wDosMem(unsigned addr , uint32 data1)
{
	_farpokel(_dos_ds,addr,data1);
}
void wDosMem_base(unsigned off , uint8 data1)
{
	_farpokeb(_dos_ds,base+off,data1);
}
void wDosMem_pc_base(unsigned off , uint8 data1)
{
	_farpokeb(_dos_ds,pc_base+off,data1);
}
uint8 rDosMem(unsigned addr)
{
	uint8 addr_val = _farpeekb(_dos_ds,addr);
	uint8 Mask=0;

	switch(addr){
		case INL: Mask = MachineStatus.MASK_IO&0xf; 		Mask_IOtest=1; break;
		case INM: Mask = (MachineStatus.MASK_IO>>8)&0xf;	Mask_IOtest=2; break;
		case INH: Mask = (MachineStatus.MASK_IO>>16)&0xf;	Mask_IOtest=3; break;
	}
	Mask_IOtest=4;
	addr_val |= Mask;
	return(addr_val) ;
}
uint16 rDosMemw(unsigned addr)
{
	return(_farpeekw(_dos_ds,addr)) ;
}
uint32 rDosMeml(unsigned addr)
{
	return(_farpeekl(_dos_ds,addr)) ;
}
uint8 rDosMem_base(unsigned off)
{
	return(_farpeekb(_dos_ds,base+off)) ;
}
uint8 rDosMem_pc_base(unsigned off)
{
	return(_farpeekb(_dos_ds,pc_base+off)) ;
}
void OUTB2ARM(unsigned addr , uint8 val)
{
	wDosMem(addr,val) ;
}
void OUTL2ARM(unsigned  addr , uint32 val)
{
	wDosMem(addr,val) ;
}

