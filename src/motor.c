#include "motor.h"

void Motor_Init(Motor *motor){
    motor->minSpeed=MOTOR_MIN_SPEED;
    motor->maxSpeed=MOTOR_MAX_SPEED;
    motor->leftSpeed=MOTOR_INITIAL_LEFT_SPEED;
    motor->rightSpeed=MOTOR_INITIAL_RIGHT_SPEED;
    motor->rpm=MOTOR_INTIAL_RPM;
    motor->accelRate=MOTOR_ACCEL_RATE;
    motor->brakeRate=MOTOR_BRAKE_RATE;
    motor->drag=MOTOR_DRAG;
}
void Motor_Reset(Motor *motor){
    motor->leftSpeed=MOTOR_INITIAL_LEFT_SPEED;
    motor->rightSpeed=MOTOR_INITIAL_RIGHT_SPEED;
    motor->rpm=MOTOR_INTIAL_RPM;
}
void Motor_Update(Motor *motor, float throtle, float dt){
    throtle=clampValue(throtle, MOTOR_INPUT_MIN, MOTOR_INPUT_MAX);
    float speed=Motor_GetAvgSpeed(motor->leftSpeed, motor->rightSpeed);
    float acceleration=(throtle>=MOTOR_INPUT_NEUTRAL)?(throtle*motor->accelRate): (throtle*motor->brakeRate);
    speed=speed+acceleration*dt;

    speed=(throtle==MOTOR_INPUT_NEUTRAL)?(speed-motor->drag*speed*dt): speed;
    speed=clampValue(speed, motor->minSpeed, motor->maxSpeed);

    motor->leftSpeed=speed;
    motor->rightSpeed=speed;
    moto->rpm=speed;
}
void Motor_Modify(Motor *motor, float minSpeed, float, maxSpeed, float accelRate, float brakeRate, float drag){
    motor->minSpeed = minSpeed;
    motor->maxSpeed = maxSpeed;
    motor->accelRate = accelRate;
    motor->brakeRate = brakeRate;
    motor->drag = drag;
}

void Motor_GetAvgSpeed(float left, float right){
    return (left+right)/MOTOR_TWO_WHEELS;
}
