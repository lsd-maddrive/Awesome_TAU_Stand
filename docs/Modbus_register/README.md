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

|    Имя 				         | Адрес |  Тип данных |       Модуль           | Тип взаимодействия |
|:----------------------------------------------:|:-----:|:-----------:|:----------------------:|:------------------:|
| DATA_CURRENT_SENSOR_CURRENT 	   		 |   0	 |    int16    | датчик тока		|    Read only	     |
| DATA_INC_ENCODER_ROTATIONAL_SPEED		 |   2	 |    float    | инкрементальный энкодер|    Read only	     |
| DATA_ABS_ENCODER_ANGLE_OF_ROTATION		 |   4	 |    float    | абсолютный энкодер	|    Read only	     |
| DATA_ABS_ENCODER_MULTI_TURN_ANGLE_OF_ROTATION  |   6	 |    int32    | абсолютный энкодер	|    Read only	     |
| DATA_ABS_ENCODER_ROTATIONAL_SPEED		 |   8   |    float    | абсолютный энкодер	|    Read only	     |
| DATA_ABS_ENCODER_NUMBER_OF_TURNS		 |   10  |    int32    | абсолютный энкодер	|    Read only	     |
| DATA_CONTR_KP	  	  			 |   12  |    float    | регулятор		|    		     |
| DATA_CONTR_KI		  			 |   14  |    float    | регулятор		|    		     |
| DATA_CONTR_KD		  			 |   16  |    float    | регулятор		|    		     |
| DATA_CONTR_KP_2				 |   18  |    float    | регулятор		|    		     |
| DATA_CONTR_KI_2		  		 |   20  |    float    | регулятор		|    		     |
| DATA_CONTR_KD_2		  		 |   22  |    float    | регулятор		|    		     |
| CONTR_USE_SEN		  			 |   24  |    int16    | регулятор		|    		     |
| DATA_FORCE_PID		  		 |   26  |    float    | регулятор		|    		     |
| DATA_FORCE_KP					 |   28  |    float    | регулятор		|    		     |
| DATA_FORCE_KI					 |   30  |    float    | регулятор		|    		     |
| DATA_FORCE_KD					 |   32  |    float    | регулятор		|    		     |
| DATA_MOTOR_REQUIRED_SPEED			 |   34  |    int16    | двигатель		|    Read/Write	     |
| DATA_MOTOR_CURRENT_SPEED			 |   35  |    int16    | двигатель		|    Read only	     |
| DATA_MOTOR_REQUIRED_VOLTAGE			 |   36  |    int16    | двигатель		|    Read/Write	     |
| DATA_MOTOR_CURRENT_VOLTAGE			 |   37  |    int16    | двигатель		|    Read only	     |

## Дискретные регистры

|    Имя 				  | Адрес |
|:---------------------------------------:|:-----:|
| SYSTEM_STOP				  |   0   |
| MEASURE				  |   1	  |
| MOTOR					  |   2	  |
| FLAG_LOAD_1				  |   3	  |
| FLAG_LOAD_2				  |   4	  |	
| FLAG_LOAD_3				  |   5   |
| FLAG_CURRENT				  |   6   |
| FLAG_ABS_ENCODER			  |   7	  |	
| FLAG_INC_ENCODER			  |   8   |
| FLAG_CONTROLLER_1			  |   9   |
| FLAG_CONTROLLER_2			  |   10  |
| FLAG_SPEED				  |   11  |
| FLAG_ANGLE				  |   12  | 
| FLAG_ROTATE  	                  	  |   13  |
| FLAG_VOLT  	                  	  |   14  |
| STATUS_MOTOR	                  	  |   15  |
| STATUS_CURRENT	                  |   16  |
| STATUS_INC_ENCODER	                  |   17  |
| STATUS_ABS_ENCODER	                  |   18  |

