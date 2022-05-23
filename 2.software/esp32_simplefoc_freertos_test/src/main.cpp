#include <Arduino.h>
#include "hw_bldc.h"
#include "hw_mpu6050.h"
#include "hw_neopixel.h"

#define TASK_RUNNING_CORE_0 0
#define TASK_RUNNING_CORE_1 1

#define STATE_STOP 0
#define STATE_RUNNING 1
#define STATE_PICKUP 2

// #define USE_DEBUG
#define USE_BLINKER

float translate_speed;
float rotate_speed;

#ifdef USE_DEBUG
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
#endif

#ifdef USE_BLINKER
// #define BLINKER_PRINT Serial
#define BLINKER_BLE
#include <Blinker.h>

#define JOY_1 "JoyKey"

BlinkerJoystick JOY1(JOY_1);

void joystick1_callback(uint8_t xAxis, uint8_t yAxis)
{
    translate_speed = (128-yAxis)*0.1;
    rotate_speed = (128-xAxis)*0.0005;
}

#endif

uint8_t running_state = STATE_PICKUP;

float acc_Z;
float angle_pitch=50;
float angle_last_pitch;
// float angle_pitch_offset = 11.5;
float angle_pitch_offset = -1;
float angle_target_pitch = 0;
float angle_P = 0.0315;
float angle_D = 0.0015;

float speed_target = 0;
float speed_P = 1.3;
float speed_I = 0.0035;
float speed_I_sum=0;
float speed_error = 0;
float speed_right, speed_left, speed_average;
float motor_output_right;
float motor_output_left;

StaticTask_t task_control_task_buffer;
StackType_t task_control_stack[4096];

StaticTask_t task_motor_move_task_buffer;
StackType_t task_motor_move_stack[4096];

StaticTask_t task_neopixel_task_buffer;
StackType_t task_neopixel_task_stack[8192];

void task_motor_move(void *pvParameters);

void task_control(void *pvParameters);
void task_neopixel(void *pvParameters);

void setup()
{
    //串口初始化
    Serial.begin(1152000);

#ifdef USE_BLINKER
    // 初始化blinker
    #if defined(BLINKER_PRINT)
        BLINKER_DEBUG.stream(BLINKER_PRINT);
    #endif
    Blinker.begin(); 
    JOY1.attach(joystick1_callback);
#endif

#ifdef USE_DEBUG    
    SerialBT.begin("ESP32Balance"); // Bluetooth device name
#endif
    // 电机及相关传感器初始化
    hw_bldc_motor_init();

    hw_mpu6050_init();

    hw_neopixel_init();

    xTaskCreateStaticPinnedToCore(
        task_control, "task_control", 4096, NULL, 2, task_control_stack, &task_control_task_buffer, TASK_RUNNING_CORE_0);

    xTaskCreateStaticPinnedToCore(
        task_motor_move, "task_motor_move", 4096, NULL, 7, task_motor_move_stack, &task_motor_move_task_buffer, TASK_RUNNING_CORE_1);

    xTaskCreateStaticPinnedToCore(
        task_neopixel, "task_neopixel", 4096, NULL, 1, task_neopixel_task_stack, &task_neopixel_task_buffer, TASK_RUNNING_CORE_0);
}

void loop()
{
}

void task_motor_move(void *pvParameters)
{
    while (1)
    {
        // iterative setting FOC phase voltage
        motor_1.loopFOC();
        motor_0.loopFOC();
        // Serial.printf("d:%f,%f\n",motor_1.shaftVelocity(),motor_0.shaftVelocity());
        motor_1.move(motor_output_left);
        motor_0.move(motor_output_right);

        // // iterative function setting the outter loop target
        mpu.update();

        speed_right = motor_0.shaftVelocity();
        speed_left = motor_1.shaftVelocity();
    }
}

void task_control(void *pvParameters)
{
    while (1)
    {
        angle_pitch = mpu.getAngleY();
        // Serial.printf("d:%f\n",angle_pitch);
        acc_Z = mpu.getAccZ();
        if (running_state == STATE_STOP)
        {
            if (abs(angle_pitch - angle_pitch_offset) < 0.5)
            {
                running_state = STATE_RUNNING;
            }
        }
        else if (running_state == STATE_RUNNING)
        {
            speed_average = (speed_right + speed_left) / 2;
            if (abs(angle_pitch - angle_pitch_offset) > 50 )
            {
                speed_I_sum=0;//清空积分系数
                running_state = STATE_PICKUP;
            }
            else
            {
                speed_target = translate_speed;

                speed_error = speed_target - speed_average;

                speed_I_sum+=(speed_error*speed_I);
                if(speed_I_sum>15){
                    speed_I_sum = 15;
                }
                if(speed_I_sum<-15){ 
                    speed_I_sum = -15;
                }
                angle_target_pitch = speed_P * speed_error + speed_I_sum;

                motor_output_left = angle_P * ((angle_pitch - angle_pitch_offset) - angle_target_pitch) + angle_D * mpu.getGyroY()+rotate_speed; //+ angle_D * mpu.getGyroY()
                motor_output_right = angle_P * ((angle_pitch - angle_pitch_offset) - angle_target_pitch) + angle_D * mpu.getGyroY()-rotate_speed;
                angle_last_pitch = angle_pitch;
            }
        }
        else if (running_state == STATE_PICKUP)
        {
            motor_output_left = 0;
            motor_output_right = 0;
            if (speed_right > 3.14 && speed_left < -3.14)
            {
                running_state = STATE_STOP;
            }
        }
        vTaskDelay(1);
    }
}

void task_neopixel(void *pvParameters)
{
    uint32_t neopixel_pattern_previous = 0;
    uint32_t neopixel_pattern_interval = 500;
    uint32_t neopixel_pattern_number = 0;
    while (1)
    {
        // 效果切换
        if((neopixel_count-neopixel_pattern_previous)>neopixel_pattern_interval){
            neopixel_pattern_previous = neopixel_count;
            neopixel_pattern_number++;
            neopixel_state_clear(strip_1_handler);
            neopixel_state_clear(strip_2_handler);
            if(neopixel_pattern_number>4){
                neopixel_pattern_number = 0;
            }
        }

        switch(neopixel_pattern_number){
            case 0:
                neopixel_police_style_2(strip_2_handler,10,5);
                neopixel_police_style_2(strip_1_handler,10,5);
                break;
            case 1:
                neopixel_police_style_1(strip_2_handler,10,5);
                neopixel_police_style_1(strip_1_handler,10,5);
                break;
            case 2:
                neopixel_loop(strip_2_handler, 255, 255, 255, 4, 4);
                neopixel_rainbow(strip_1_handler);
                break;
            case 3:
                neopixel_bounce(strip_1_handler, 0, 255, 0, 2, 3, 0);
                neopixel_fade_in_out(strip_2_handler, 255, 0, 255, 2, 1,25);
                break;
            case 4:
                neopixel_spread_out(strip_2_handler, strip_2_handler.strip.Color(0,255,0), strip_2_handler.strip.Color(0,0,255), 4, 10);
                neopixel_spread_out(strip_1_handler, strip_1_handler.strip.Color(255,0,0), strip_1_handler.strip.Color(255,255,0), 4, 10);
                break;
            default:
                break;
        }
        neopixel_count++;

#ifdef USE_BLINKER
        Blinker.run();
#endif

        vTaskDelay(10);
    }
}