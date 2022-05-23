#include "hw_mpu6050.h"
#include "hw_bldc.h"

MPU6050 mpu(I2C_1);

void hw_mpu6050_init()
{
    byte status = mpu.begin();
    Serial.print(F("MPU6050 status: "));
    Serial.println(status);
    while (status != 0)
    {
    } // stop everything if could not connect to MPU6050

    Serial.println(F("Calculating offsets, do not move MPU6050"));
    delay(500);
    mpu.calcOffsets(true, false); // gyro and accelero
    Serial.println("Calculating Done!");
}