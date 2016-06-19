/*
  Copyright (c) 2015, Arduino LLC

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  
  by:AliReza.Abdiyan@gmail.com
*/

#ifndef DRF702X_H_
#define DRF702X_H_

#include <Arduino.h>
#include <stdlib.h>
#include <string.h>

#define No_Parity    '0'
#define Even_Parity  '1'
#define Odd_Parity   '2'

#define DR_FSK_2400  '1'
#define DR_FSK_4800  '2'
#define DR_FSK_9600  '3'
#define DR_FSK_19200 '4'

#define POUT_Min     '0'
#define POUT_1       '1'
#define POUT_2       '2'
#define POUT_3       '3'
#define POUT_4       '4'
#define POUT_5       '5'
#define POUT_6       '6'
#define POUT_7       '7'
#define POUT_8       '8'
#define POUT_Max     '9'

#define DR_IN_1_2    '0'
#define DR_IN_2_4    '1'
#define DR_IN_4_8    '2'
#define DR_IN_9_6    '3'
#define DR_IN_19_2   '4'
#define DR_IN_38_4   '5'
#define DR_IN_57_6   '6'

#define DRF_Error     0
#define DRF_Ok        1

class DRF7020Dx
{
	public:
		DRF7020Dx(int DRF_EN_Pin,int DRF_SET_Pin);
		DRF7020Dx(int DRF_SET_Pin);
		int Setup(char DR_IN,long Freq_Khz,char Power_Out,char DR_FSK,char Parity,String Security_Str);
		void Send_WireLessData(char * Data, unsigned char Data_Len);
		int Check_WireLess(char * str);
	private:
		void Enter_to_setting_mode(void);
		void Exit_from_setting_mode(void);	
		void Enable_DRF(void);
		void Disable_DRF(void);
		String Security_Code;
		int Security_Code_Len;
		int EN_Pin;
		int SET_Pin;
		//Freq_KHz(418000-455000 KHz)	
		int DRF_Write_Settings(long Freq_KHz,char DR_FSK,char Power_Out,char DR_IN,char Parity);
		int DRF_Read_Settings(long *Freq_KHz,char *DR_FSK,char *Power_Out,char *DR_IN,char *Parity);
};

#endif /* DRF702X_H_ */