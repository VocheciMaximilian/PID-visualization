#ifndef STEERING_H
#define STEERING_H
#include "config.h"
#include "common.h"
typedef struct{
  float angle;
  float minAngle;
  float maxAngle;
  float steerRate;
} Steering;
/*****************************
Function:
Parameters:
Objective:
Observation:
*****************************/
void Steering_Init(Steering *steering);
/*****************************
Function:
Parameters:
Objective:
Observation:
*****************************/
void Steering_Reset(Steering *steering);
/*****************************
Function:
Parameters:
Objective:
Observation:
*****************************/
void Steering_Update(Steering *steering, float input, float dt);
/*****************************
Function:
Parameters:
Objective:
Observation:
*****************************/
void Steering_ModifyParams(Steering *steering, float angle, float maxAngle, float steerRate);

#endif