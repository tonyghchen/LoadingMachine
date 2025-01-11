#include "header.h"

enum 
{
	START_STATUS,	aa_LENGTH,	aa_STATUS,	bb_STATUS,	cc_STATUS,
};
static uint8 ERP_STATE=START_STATUS;


//have_idx,使否要改變ERP_idx
uint32 ByteToBin(int Start_Byte, int num, bool have_idx)
{
	uint32 ch=0;
	for(int i=0; i<num; i++){
		if(i=0){
			ch=ERP_regist[Start_Byte+i];
		}
		else{
			ch=(ch<<8)+ERP_regist[Start_Byte+i];
		}
	}
	if(have_idx){ERP_idx+=num;}	
	return ch;
}

void BinToERP_regitst(int len, uint32 val)
{
	for(int i=0; i<len; i++){
		EPT_IDX(ERP_idx, ERP_regist);
		ERP_regist[ERP_idx++]=	(val>>(24-8*i))&0xff;
	}
}
uint8 chk_ERPsum(int Start_Byte, int len, chksum)
{
	uint16 sum=0;
	for(int i=Start_Byte; i<len; i++){
		sum+=ERP_regist[i];
	}
	if(sum==chksum){
		return (0x0);
	}
	else{return (0xff);}
}

void ERP_aa_cmd()
{
	uint16 Lot_no=0, Part_id=0, Checksum=0;		//生產批號,	料號, checksum;
	uint32 Plan_qty=0;							//設定生產量
	uint16 File_NO=0,	Progline=0;				//檔號, 行數	
	ERP_idx=0;	//初始化ERP_idx
	
	Lot_no=(uint16)ByteToBin(ERP_idx,2,true);
	Part_id=(uint16)ByteToBin(ERP_idx,2,true);
	Plan_qty=ByteToBin(ERP_idx,3,true);
	Checksum=ByteToBin(aa_length-2,2,true);
	
	//讀取program
	File_NO=ByteToBin(ERP_idx,2,true);				//檔號
	Progline=(aa_length-(ERP_idx+2))%58;			//計算行數
	
	for(int line=0; line<Progline; line++){
		
		EPT_IDX(line, ProgBuf);
		ProgBuf[line].bygcode=(BYTE)ByteToBin(ERP_idx,1,true);	//G_code
		ProgBuf[line].byth=(BYTE)ByteToBin(ERP_idx,1,true);		//th
		ProgBuf[line].bytd=(BYTE)ByteToBin(ERP_idx,1,true);		//td
		ProgBuf[line].byair=(BYTE)ByteToBin(ERP_idx,1,true);	//air
		
		//seq
		for(int i=0; i<MAX_PROG_AXIS; i++){
			
			EPT_IDX(line, ProgBuf);
			EPT_IDX(i, ProgBuf[0].byseq);
			ProgBuf[line].byseq[i]=(BYTE)ByteToBin(ERP_idx,1,true);
		}
		
		//sign
		for(int i=0; i<(MAX_PROG_AXIS+1); i++){
			
			EPT_IDX(line, ProgBuf);
			EPT_IDX(i, ProgBuf[0].bysign);			
			ProgBuf[line].bysign[i]=(BYTE)ByteToBin(ERP_idx,1,true);
		}
		
		//align_byte
		EPT_IDX(line, ProgBuf);
		ProgBuf[line].align_byte=(BYTE)ByteToBin(ERP_idx,1,true);
		
		//dval
		for(int i=0; i<(MAX_PROG_AXIS+1+2); i++){
			
			EPT_IDX(line, ProgBuf);
			EPT_IDX(i, ProgBuf[0].dval);	
			ProgBuf[line].dval[i]=ByteToBin(ERP_idx,4,true);
		}		


		EPT_IDX(line, ProgBuf);
		EPT_IDX(i, ProgBuf[0].wspd);
		EPT_IDX(i, ProgBuf[0].wjmp);
		ProgBuf[line].wspd=(WORD)ByteToBin(ERP_idx,2,true);		//spd
		ProgBuf[line].wjmp=(WORD)ByteToBin(ERP_idx,2,true);		//jmp
	}
	
	wr_rs232(chk_ERPsum(0, aa_length, Checksum));				//回傳正確or錯誤	
}

void ERP_bb_cmd()
{
	uint16 Lot_no=0, Part_id=0, Speed=MachineStatus.speed[0], Checksum=0;
	uint32 Qty=(uint32)BcdToBin(6,MachineStatus.cur_quan);
	uint8 Err_code=0;
	ERP_idx=0;	//初始化ERP_idx
	
	
	BinToERP_regitst(2, Lot_no);
	BinToERP_regitst(2, Part_id);
	BinToERP_regitst(3, Qty);
	BinToERP_regitst(2, Speed);
	BinToERP_regitst(1, Err_code);
	
	Checksum= Lot_no+Part_id+Speed+Checksum+Qty+Err_code;
	BinToERP_regitst(2, Checksum);
	
	for(int i=0; i<ERP_idx; i++){
		wr_rs232(ERP_regist[i]);				//上傳"控制器狀態"
	}
}
void ERP_cc_cmd()
{
	uint16 Length=0, Lot_no=0, Part_id=0, Checksum=0,	line=0;
	bool ProgEnd=false;		//寫入"結束"
	ERP_idx=0;				//初始化ERP_idx
	
	//寫入program	
	BinToERP_regitst(2, MachineStatus.file);	//檔號
	
	do{	
		if(ProgBuf[line].bygcode==0){ProgEnd=true;}

		BinToERP_regitst(1, ProgBuf[line].bygcode);
		BinToERP_regitst(1, ProgBuf[line].byth);
		BinToERP_regitst(1, ProgBuf[line].bytd);
		BinToERP_regitst(1, ProgBuf[line].byair);
		
		//seq
		for(int i=0; i<MAX_PROG_AXIS; i++){
			BinToERP_regitst(1, ProgBuf[line].byseq[i]);
		}
		
		//sign
		for(int i=0; i<(MAX_PROG_AXIS+1); i++){
			BinToERP_regitst(1, ProgBuf[line].bysign[i]);
		}
		
		//align_byte
		BinToERP_regitst(1, ProgBuf[line].align_byte);
		
		//dval
		for(int i=0; i<(MAX_PROG_AXIS+1+2); i++){
			BinToERP_regitst(4, ProgBuf[line].dval[i]);
		}
		BinToERP_regitst(2, ProgBuf[line].wspd);		//spd
		BinToERP_regitst(2, ProgBuf[line].wjmp);		//jmp
		
		line++;	
	}while(!ProgEnd);
	
	for(int i=0; i<ERP_idx; i++){
		Checksum+=ERP_regist[i];
	}
	BinToERP_regitst(2, Checksum);		//jmp
}

//目前com1_code寫進ERP陣列Byte數量
int ChkERP()
{
	int no =0 ;
	int tERP_BufRIdx=ERP_BufRIdx ;
	while(tERP_BufRIdx !=ERP_BufWIdx){
		no++ ;
		if((tERP_BufRIdx+1)== MAX_ERP_BUF){
			tERP_BufRIdx=0 ;
		}
		else{
			tERP_BufRIdx++ ;
		}
	}		
	return(no) ;
}

//讀ERP陣列一個Byte
uint8 RdERP()
{
	uint8 ch= ERPBuf[ERP_BufRIdx] ;
	char  buf[10];
	static uint16 x_buf, y_buf;
	uint16 z_buf=ch;
		
	if(ERPB_ufRIdx+1 == MAX_ERP_BUF){
		ERP_BufRIdx=0 ;
	}
	else{
		ERP_BufRIdx++ ;
	}
	return(ch) ;
}


void ERPwork()
{
	int no =ChkTouch();
	
	switch(ERP_STATE){
		case START_STATUS:
			{
				if(no>=2){
					//Header寫入					
					EPT_IDX(0, ERP_regist);
					EPT_IDX(1, ERP_regist);
					ERP_regist[0]=RdERP();
					ERP_regist[1]=RdERP();
					
					//Header讀取
					int Header=ByteToBin(0,2,false);
					if(Header==0x55aa){ERP_STATE=aa_LENGTH;}			//下載ERP內容_長度
					else if(Header==0x55bb){ERP_STATE=bb_STATUS;}		//控制器目前工作狀態
					else if(Header==0x55cc){ERP_STATE=cc_STATUS;}		//上傳給ERP
				}
				elase{break ;}
			}
			break;
		case aa_LENGTH:
			{
				if(no>=2){					
					//長度寫入
					EPT_IDX(0, ERP_regist);
					EPT_IDX(1, ERP_regist);
					ERP_regist[0]=RdERP();
					ERP_regist[1]=RdERP();					
					aa_length=ByteToBin(0,2,false);
				}
				elase{break ;}				
			}
			break;
		case aa_STATUS:		//下載_ERP內容	
			{
				if(no>=aa_length){
					//讀取內容
					for(int i=0; i<aa_length; i++){
						
						EPT_IDX(i, ERP_regist);					
						ERP_regist[i]=RdERP();
					}
					ERP_aa_cmd();
					ERP_STATE=START_STATUS;
				}
				else{break;}
			}
			break;			
		case bb_STATUS:		//上傳_控制器"目前工作狀態"
			{
				ERP_bb_cmd();
				ERP_STATE=START_STATUS;
			}
			break;
		case cc_STATUS:		//上傳_控制器"程式"
			{
				ERP_cc_cmd();
				ERP_STATE=START_STATUS;
			}
			break;				
	}//switch
}





