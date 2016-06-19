# Dorji

Can create object with En and Set pin or whit Set pin only

DRF7020Dx(int DRF_EN_Pin,int DRF_SET_Pin);

DRF7020Dx(int DRF_SET_Pin);

After create object must set Dorji whith this method:
int Setup(char DR_IN,long Freq_Khz,char Power_Out,char DR_FSK,char Parity,String Security_Str);

#DR_IN:

  define DR_IN_1_2    '0'
  
  define DR_IN_2_4    '1'
  
  define DR_IN_4_8    '2'
  
  define DR_IN_9_6    '3'
  
  define DR_IN_19_2   '4'
  
  define DR_IN_38_4   '5'
  
  define DR_IN_57_6   '6'

#Freq_Khz:

  418000-455000 KHz -->	default 433920

#Power_Out:

  define POUT_Min     '0'
  
  define POUT_1       '1'
  
  define POUT_2       '2'
  
  define POUT_3       '3'
  
  define POUT_4       '4'
  
  define POUT_5       '5'
  
  define POUT_6       '6'
  
  define POUT_7       '7'
  
  define POUT_8       '8'
  
  define POUT_Max     '9'
  

#DR_FSK:

  define DR_FSK_2400  '1'
  
  define DR_FSK_4800  '2'
  
  define DR_FSK_9600  '3'
  
  define DR_FSK_19200 '4'

#Parity:  

  define No_Parity    '0'
  
  define Even_Parity  '1'
  
  define Odd_Parity   '2'
  
#Security_Str:

  Is a header security string



