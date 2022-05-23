#include "hw_bldc.h"

// BLDC motor & driver instance
BLDCMotor motor_0 = BLDCMotor(PP_NUMBER);
BLDCDriver3PWM driver_0 = BLDCDriver3PWM(M0_OUTPUT_1, M0_OUTPUT_2, M0_OUTPUT_3, M0_OUTPUT_ENABLE);

BLDCMotor motor_1 = BLDCMotor(PP_NUMBER);
BLDCDriver3PWM driver_1 = BLDCDriver3PWM(M1_OUTPUT_1, M1_OUTPUT_2, M1_OUTPUT_3, M1_OUTPUT_ENABLE);

// encoder instance
MagneticSensorI2C sensor_0 = MagneticSensorI2C(AS5600_I2C);
TwoWire I2C_0 = TwoWire(1);

MagneticSensorI2C sensor_1 = MagneticSensorI2C(AS5600_I2C);
TwoWire I2C_1 = TwoWire(0);

// inline current sensor instance
// check if your board has R010 (0.01 ohm resistor) or R006 (0.006 mOhm resistor)
// InlineCurrentSense current_sense_0 = InlineCurrentSense(0.01, 20.0, M0_CURRENT_IN_1, M0_CURRENT_IN_2);

// InlineCurrentSense current_sense_1 = InlineCurrentSense(0.01, 20.0, M1_CURRENT_IN_1, M1_CURRENT_IN_2);

void hw_bldc_motor_init()
{
    motor_0.useMonitoring(Serial);
    motor_1.useMonitoring(Serial);

    I2C_0.begin(M0_I2C_SDA, M0_I2C_SCL, 400000);
    sensor_0.init(&I2C_0);
    motor_0.linkSensor(&sensor_0);
    I2C_1.begin(M1_I2C_SDA, M1_I2C_SCL, 400000);
    sensor_1.init(&I2C_1);
    motor_1.linkSensor(&sensor_1);

    // driver config
    // power supply voltage [V]
    driver_0.voltage_power_supply = 12.0;
    driver_0.init();
    driver_1.voltage_power_supply = 12.0;
    driver_1.init();
    
    // link driver
    motor_0.linkDriver(&driver_0);
    motor_1.linkDriver(&driver_1);

    // 电流限制
    motor_0.current_limit = 2;
    motor_1.current_limit = 2;

    // 电压限制
    motor_0.voltage_limit = 12;
    motor_1.voltage_limit = 12;

    motor_0.phase_resistance = 12.4; // 12.5 Ohms
    motor_0.torque_controller = TorqueControlType::voltage;
    motor_1.phase_resistance = 14.0; // 12.5 Ohms
    motor_1.torque_controller = TorqueControlType::voltage;

    // // TorqueControlType::foc_current
    // // 其他模式 TorqueControlType::voltage TorqueControlType::dc_current
    // motor_0.torque_controller = TorqueControlType::foc_current;
    // motor_1.torque_controller = TorqueControlType::foc_current;
    // motor_0.torque_controller = TorqueControlType::dc_current;
    // motor_1.torque_controller = TorqueControlType::dc_current;
    
    // set control loop type to be used
    motor_0.controller = MotionControlType::torque;
    motor_1.controller = MotionControlType::torque;

    // contoller configuration based on the controll type
    // motor_0.PID_current_q.P = 5;
    // motor_0.PID_current_q.I = 1000;
    // motor_0.LPF_current_q.Tf = 0.01;
    // motor_1.PID_current_q.P = 5;
    // motor_1.PID_current_q.I = 1000;
    // motor_1.LPF_current_q.Tf = 0.01;

    // velocity low pass filtering time constant
    motor_0.LPF_velocity.Tf = 0.01;
    motor_1.LPF_velocity.Tf = 0.01;

    // current sense init and linking
    // current_sense_0.init();
    // current_sense_0.gain_b *= -1;
    // //current_sense_0.skip_align = true;
    // motor_0.linkCurrentSense(&current_sense_0);
    // current_sense_1.init();
    // current_sense_1.gain_b *= -1;
    // //current_sense_1.skip_align = true;
    // motor_1.linkCurrentSense(&current_sense_1);

    // initialise motor

    
    motor_0.init();
    motor_1.init();
    
    // align encoder and start FOC
    // motor.initFOC(2.15, Direction::CW);
    motor_0.initFOC(4.53, Direction::CW);
    motor_1.initFOC(3.33, Direction::CCW);

    motor_0.motion_downsample=0;
    motor_1.motion_downsample=0;

    // set the inital target value
    motor_0.target = 0.3;
    motor_1.target = 0.3;
}