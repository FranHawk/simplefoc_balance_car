#ifndef  __HW_BLDC_H
#define __HW_BLDC_H

#include <Arduino.h>
#include <SimpleFOC.h>

/*电机相关引脚定义*/
#define M0_OUTPUT_1 32
#define M0_OUTPUT_2 33
#define M0_OUTPUT_3 25
#define M0_OUTPUT_ENABLE 22
#define M0_I2C_SDA 23
#define M0_I2C_SCL 5
#define M0_CURRENT_IN_1 39
#define M0_CURRENT_IN_2 36

#define M1_OUTPUT_1 26
#define M1_OUTPUT_2 27
#define M1_OUTPUT_3 14
#define M1_OUTPUT_ENABLE 12
#define M1_I2C_SDA 19
#define M1_I2C_SCL 18
#define M1_CURRENT_IN_1 35
#define M1_CURRENT_IN_2 34

/*极对数*/
#define PP_NUMBER 7

extern BLDCMotor motor_0;
extern BLDCMotor motor_1;
extern TwoWire I2C_1;
void hw_bldc_motor_init();

#endif 