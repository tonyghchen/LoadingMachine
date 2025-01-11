//#include <stdarg.h>
#include "utyc_2.cpp"

uint32 x_Sprintf ;
COLOR_T fclr_Sprintf = AIRBOX_MAIN_FCOLOR ;
COLOR_T bclr_Sprintf  = AIRBOX_MAIN_BCOLOR ;
void Sprintf_Clr()
{
	fclr_Sprintf = AIRBOX_MAIN_FCOLOR ;
	bclr_Sprintf  = AIRBOX_MAIN_BCOLOR ;
}
void Sprintf_Clr(COLOR_T   fclr )
{
	fclr_Sprintf=fclr ;	
}
void Sprintf_Clr(COLOR_T   fclr , COLOR_T bclr)
{
	fclr_Sprintf=fclr ;
	bclr_Sprintf=bclr ;
	
}
