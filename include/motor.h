#ifndef MOTOR_H
#define MOTOR_H

#include "common.h"
typedef struct{
  float maxSpeed;
  float leftSpeed;
  float rightSpeed;
  float rpm;
  float accelRate;
  float brakeRate;
  float drag;
} Motor;
/*****************************
Function: Motor_Init
Parameters: Motor *motor is the object we initialize
Objective: Initialize the motor objects with the default values from config.h.
Observation:
*****************************/
void Motor_Init(Motor *motor);
/*****************************
Function:
Parameters:
Objective:
Observation:
*****************************/
void Motor_Reset(Motor *motor);
/*****************************
Function:
Parameters:
Objective:
Observation:
*****************************/
void Motor_Update(Motor *motor, float throtle, float dt);
/*****************************
Function:
Parameters:
Objective:
Observation:
*****************************/
void Motor_Modify

#endif
