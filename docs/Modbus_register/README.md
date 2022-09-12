# Регистры Modbus

 Регистры используем для записи или чтения важных данных, уходящих или приходящих от пользователя. Так, модули с датчиками используют аналоговые регистры для хранения измерений, модули с регуляторами используют аналоговые регистры для чтения коэффициентов и для записи регулирующих воздействий.   

 Для чтения аналоговых или дискретных регистров используем define
 
 MB_READ_ANALOG_REG(addr) и MB_READ_DISCRET_REG(addr),
 
 где addr define адреса регистра(см. ниже в таблице)


 Для записи в аналоговый регистр исходя из типа данных используем define:
 
  MB_WRITE_REG_FLOAT(i,addr)
  
  MB_WRITE_REG_INT32(i,addr)
  
  MB_WRITE_REG_INT16(i,addr)
  
  где addr опять же define адреса регистра и val значение

## Аналоговые регистры

|    Имя 				  | Адрес | Тип данных | Модуль  |
|:----------------------------------------------:|:--------:|:--------------:|:-----------:|
| DATA_SPEED			  |  0  	|    int16	| пользователь?		|
| DATA_CURRENT			  |  1	|    int16	| датчик тока		|
| STATUS_CURRENT	 	  |  2	|    int16	| датчик тока		|
| DATA_INC_ENCODER		  |  3	|    float	|инкрементальный энкодер|
| STATUS_INC_ENCODER		  |  5	|    int16	|инкрементальный энкодер|	
|  DATA_ABS_ENCODER_ANGLE	  |  6	|    float	|абсолютный энкодер	|
|  DATA_ABS_ENCODER_ANGLEMULTI	  |  8	|    int32	|абсолютный энкодер	|
|  DATA_ABS_ENCODER_SPEED	  |  10	|    float	|абсолютный энкодер	|
|  DATA_ABS_ENCODER_ROTATE	  |  12	|    int32	|абсолютный энкодер	|
|  STATUS_ABS_ENCODER		  |  14	|    int16	|абсолютный энкодер	|
|  DATA_CONTR_KP	  	                    |  15	|    float	|регулятор		|
|  DATA_CONTR_KI			  |  17	|    float	|регулятор		|
|  DATA_CONTR_KD		  |  19	|    float	|регулятор		|
|  DATA_CONTR_KP_2		  |  21	|    float	|регулятор		|
|  DATA_CONTR_KI_2		  |  23	|    float	|регулятор		|
|  DATA_CONTR_KD_2		  |  25	|    float	|регулятор		|
|  CONTR_USE_SEN		  |  27	|    int16	|регулятор		|

## Дискретные регистры

|    Имя 				  | Адрес |
|:----------------------------------------------:|:--------:|
| SYSTEM_STOP			|  0  	|
| MEASURE			|  1	|
| MOTOR				|  2	|
| FLAG_LOAD_1			|  3	|
|  FLAG_LOAD_2			|  4	|	
|  FLAG_LOAD_3			|  5	|
| FLAG_CURRENT			|  6	|
|  FLAG_ABS_ENCODER			|  7	|	
|  FLAG_INC_ENCODER			|  8	|
|  FLAG_CONTROLLER_1		|  9	|
|  FLAG_CONTROLLER_2		|  10	|
|  FLAG_SPEED			|  11	|
|  FLAG_ANGLE		|  12	| 
|  FLAG_ROTATE  	                  |  13	|
|  FLAG_VOLT  	                  |  14	|

