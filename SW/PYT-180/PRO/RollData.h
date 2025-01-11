
#include "象虎.D"
struct ROLLDATA  RollDataSETT=
{
	{
	y00506 ,y01506,y02506,y03506,y04506,y05506,y06506,y07506,y08506,y09506,
	y10506,y11506,y12506,y13506,y14506,y15506,y16506,y17506} ,
{
#include "象虎.P"
}
} ;


#include "江南.D"
struct ROLLDATA  RollDataRSOUTH=
{
	{
	y00550 ,y01550,y02550,y03550,y04550,y05550,y06550,y07550,y08550,y09550
	} ,
{
#include "江南.P"
}
} ;


#include "開創.D"
struct ROLLDATA  RollDataKNCNC=
{
	{
	y00208 ,y01208,y02208,y03208,y04208,y05208,y06208,y07208,y08208,y09208,y08208,y07208,y06208,y05208,
	y04208,y03208,y02208,y01208} ,
{
#include "開創.p"
}
} ;

#include "星火.D"
struct ROLLDATA  RollDataSFNCNC=
{
	{
	y00SFNCNC ,	y01SFNCNC,	y02SFNCNC ,	y03SFNCNC ,	y04SFNCNC ,	y05SFNCNC ,	y06SFNCNC ,	y07SFNCNC ,	y08SFNCNC ,	y09SFNCNC ,
																									y08SFNCNC ,
																						y07SFNCNC ,
																			y06SFNCNC,
												  				y05SFNCNC ,
													y04SFNCNC ,
										y03SFNCNC ,
							y02SFNCNC ,
			  	y01SFNCNC } ,
{
#include "星火.P"
}
} ;

#include "建岭.D"
struct ROLLDATA  RollDataJLNCNC=
{
	{
	y00JLNCNC ,	y01JLNCNC,	y02JLNCNC ,	y03JLNCNC ,	y04JLNCNC ,	y05JLNCNC ,	y06JLNCNC ,	y07JLNCNC ,	y08JLNCNC ,	y09JLNCNC ,
																									y08JLNCNC ,
																						y07JLNCNC ,
																			y06JLNCNC,
												  				y05JLNCNC ,
													y04JLNCNC ,
										y03JLNCNC ,
							y02JLNCNC ,
			  	y01JLNCNC } ,
{
#include "建岭.P"
}
} ;

#if NEWLOGO
#include "新達.R"
struct ROLLDATA  RollDataHNCNC=
{
	{
	y00 ,y01,y02,y03,y04,y05,y06,y07,y08,y09,y10,y11} ,
{
#include "新達.P"
}
} ;
#else
#include "新達.D"
struct ROLLDATA  RollDataHNCNC=
{
	{
	y00 ,y01,y02,y03,y04,y05,y06} ,
{
#include "新達.P"
}
} ;
#endif





struct ROLLDATA *RollData=&RollDataHNCNC ;


