#include "DRF702x.h"

DRF7020Dx::DRF7020Dx(int DRF_EN_Pin,int DRF_SET_Pin)
{
	EN_Pin=DRF_EN_Pin;
	SET_Pin=DRF_SET_Pin;
	pinMode(DRF_EN_Pin, OUTPUT);
	pinMode(DRF_SET_Pin, OUTPUT);
}

DRF7020Dx::DRF7020Dx(int DRF_SET_Pin)
{
	SET_Pin=DRF_SET_Pin;
	pinMode(DRF_SET_Pin, OUTPUT);
}

int DRF7020Dx::Setup(char DR_IN,long Freq_Khz,char Power_Out,char DR_FSK,char Parity,String Security_Str)
{
	Exit_from_setting_mode();	
	Enable_DRF();
	
	switch(DR_IN)
	{
		case DR_IN_1_2: Serial.begin(1200);
		break;
		case DR_IN_2_4: Serial.begin(2400);
		break;
		case DR_IN_4_8: Serial.begin(4800);
		break;
		case DR_IN_9_6: Serial.begin(9600);
		break;
		case DR_IN_19_2: Serial.begin(19200);
		break;
		case DR_IN_38_4: Serial.begin(38400);
		break;
		case DR_IN_57_6: Serial.begin(57600);
		break;
		default :return DRF_Error;
	}
	Security_Code=Security_Str;
	Security_Code_Len=Security_Str.length();
	//Freq_KHz(418000-455000 KHz)	default 433920	
	return DRF_Write_Settings(Freq_Khz,DR_FSK,Power_Out,DR_IN,Parity);	
}

void DRF7020Dx::Enter_to_setting_mode(void)
{
	digitalWrite(SET_Pin, LOW);
	delay(2);
}

void DRF7020Dx::Exit_from_setting_mode(void)
{
	digitalWrite(SET_Pin, HIGH);
	delay(10);
}

void DRF7020Dx::Enable_DRF(void)
{
	digitalWrite(EN_Pin, HIGH);
	delay(50);
}

void DRF7020Dx::Disable_DRF(void)
{
	digitalWrite(EN_Pin, LOW);
}

void DRF7020Dx::Send_WireLessData(char * Data, unsigned char Data_Len)
{
	int i;
	unsigned char checkSum=0;
	for(i=0;i<Security_Code_Len;i++)
	{
		Serial.print((char)Security_Code[i]);
		checkSum+=Security_Code[i];
	}
	//Serial.print(Security_Code);
	for (i=0;i<Data_Len;i++)
	{
		Serial.print((char)Data[i]);
		checkSum+=Data[i];
	}
	Serial.print((char)checkSum);
	Serial.flush();
}

int DRF7020Dx::Check_WireLess(char * str)
{
	int i,len;
	len=Serial.available();
	unsigned char checkSum=0;
	if(len>0)
	{
		delay(100);
		len=Serial.available();
		Serial.readBytes(str, len);
		Serial.flush();
		//return len;////////
		for(i=0;i<Security_Code_Len;i++)
		{
			checkSum+=str[i];
			if(str[i]!=Security_Code[i]) 
			{
				return 0;
			}
		}
		if(i==Security_Code_Len)
		{
			for(i=0;i<len-Security_Code_Len;i++)
			{
				str[i]=str[i+Security_Code_Len];
				if(i!=len-Security_Code_Len-1)	checkSum+=str[i];
			}
			str[i]=0;
			if(str[i-1]!=checkSum) return 0;
			str[i-1]=0;
			return (len-Security_Code_Len-1);
		}
	}	
	return 0;
}


int DRF7020Dx::DRF_Write_Settings(long Freq_KHz,char DR_FSK,char Power_Out,char DR_IN,char Parity)
{
	char str[25],str_Resp[25],Resp_Index=5;
	Serial.flush();
	
	str_Resp[0]='P';
	str_Resp[1]='A';
	str_Resp[2]='R';
	str_Resp[3]='A';
	str_Resp[4]=0x20;
	
	ltoa(Freq_KHz,str,10);
	
	Enter_to_setting_mode();
	
	Serial.print('W');
	Serial.print('R');
	Serial.print(' ');
	for (char i=0;i<6;i++)
	{
		Serial.print(str[i]);
		str_Resp[Resp_Index++]=str[i];
	}
	
	Serial.print(' ');	
	str_Resp[Resp_Index++]=0x20;
	
	Serial.print(DR_FSK);  //DRFSK 1=2400,2=4800,3=9600,4=19200 bps
	str_Resp[Resp_Index++]=DR_FSK;
	Serial.print(' ');
	str_Resp[Resp_Index++]=0x20;
	
	Serial.print(Power_Out);  //POUT 0~9 0refers to -1dBm and 9 for 20dBm
	str_Resp[Resp_Index++]=Power_Out;
	Serial.print(' ');
	str_Resp[Resp_Index++]=0x20;
	
	Serial.print(DR_IN);  //DRIN 0=1.2 , 1=2.4 , 2=4.8 , 3=9.6 , 4=19.2 , 5=38.4 , 6=57.6  Kbps
	str_Resp[Resp_Index++]=DR_IN;
	Serial.print(' ');
	str_Resp[Resp_Index++]=0x20;
	
	Serial.print(Parity);  //Parity 0:No 1:Even  2:Odd
	str_Resp[Resp_Index++]=Parity;
	
	Serial.println();
	str_Resp[Resp_Index++]=0x0D;
	str_Resp[Resp_Index++]=0x0A;
	
	str_Resp[Resp_Index]=0x00;
	delay(200);
	
	Exit_from_setting_mode();
	
	delay(100);
	if(Serial.available()>0)
	{
		Serial.readBytes(str, Serial.available());
		Serial.flush();
		if(strstr(str,(const char *)str_Resp)!=NULL) return DRF_Ok;
	}
	
	return DRF_Error;
}

int DRF7020Dx::DRF_Read_Settings(long *Freq_KHz,char *DR_FSK,char *Power_Out,char *DR_IN,char *Parity)
{
	char str[25],str_Resp[25];
	Serial.flush();		
	
	Enter_to_setting_mode();
	
	Serial.print('R');
	Serial.print('D');
	Serial.println();
	
	delay(200);
	
	Exit_from_setting_mode();	
	
	delay(100);
	if(Serial.available()>0)
	{
		Serial.readBytes(str_Resp, Serial.available());
		Serial.flush();
		char * index;
		if(strstr(str_Resp,"PARA")!=NULL) 
		{			
			index=strstr(str_Resp,"PARA");
			index+=5;
			str[0]=*index;
			index++;
			str[1]=*index;
			index++;
			str[2]=*index;
			index++;
			str[3]=*index;
			index++;
			str[4]=*index;
			index++;
			str[5]=*index;
			str[6]=0;
			*Freq_KHz=atol(str);
			
			index+=2;
			*DR_FSK=(*index) - 48;
			
			index+=2;
			*Power_Out=(*index) - 48;
			
			index+=2;
			*DR_IN=(*index) - 48;
			
			index+=2;
			*Parity=(*index) - 48;
			return DRF_Ok;
		}
	}
	return DRF_Error;
}