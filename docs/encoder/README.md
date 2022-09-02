#Энкодер

Модель: 6mm 5V 10bit CAN

Тип выхода: боковой выход.

Максимальная Механическая скорость: 1000 об/мин

10 бит = 1024P/R (об/мин)

Размеры: 

<p align="center">
<img src="picture/encod_razmer.png" width=700/>
</p>

/*
 *  @brief  Initializes the encoder and starts another thread to read characteristics from it.
 *
 *  @note   Set encoder angular velocity sampling time (20 milliseconds).
 *  @note   Sets the zero position of the encoder.
 */
void absoluteEncoderInit(void);

/*
 *  @brief  Stops can if it's enabled.
 *
 *  @note   Not verified.
 */
msg_t absoluteEncoderUninit(void);


/*
 *  @brief  Returns rotation speed in rpm.
 *
 *  @param[out]  encoder.Speed  Encoder rotation speed in rpm.
 */
float getAbsoluteEncoderRotationalSpeed(void);

/*
 *  @brief  Returns number of turns from the starting position.
 *
 *  @param[out]  encoder.NumberOfTurns  Number of turns  can be both positive
 *                                      and negative.
 *
 */
int32_t getAbsoluteEncoderNumberOfTurns(void);

/*
 *  @brief  Returns the rotation angle of the encoder in degrees within one turn.
 *
 *  @param[out]  encoder.Angle  The rotation angle can be in the range from 0 to 360 degrees.
 */
float getAbsoluteEncoderAngleOfRotation(void);

/*
 *  @brief  Returns the rotation angle of the encoder in degrees.
 *
 *  @param[out]  encoder.Angle  The rotation angle can be greater or less than 0 degrees.
 */
int32_t getAbsoluteEncoderMultiTurnAngleOfRotation(void);

/*
 *  @brief  Returns all characteristics from the encoder.
 *
 *  @param[out]  encoder  Pointer to a structure where all characteristics are stored.
 *
 *  @note   Characteristics: rotation speed, number of turns, angle of rotation, multi-turn angle of rotation.
 */
absoluteEncoderParam* getAbsoluteEncoderStruct(void);

Команда позволяет вернуть скорость в оборотах в минуту, учитывая направление, угол поворота в градусах в диаозоне от 0 до 360 градусов,

угол в градусах, который не обнулсется после 360, количество оборотов, а также все эти данные собранные в единую структуру.

[Энкодер](https://aliexpress.ru/item/4001309275150.html?gatewayAdapt=glo2rus&sku_id=10000015687603201&spm=a2g0s.12269583.0.0.609b1e84TvdLx1)