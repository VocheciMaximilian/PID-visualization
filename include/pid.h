#ifndef PID_H
#define PID_H
#include<stdbool.h>
#include "config.h"
#include "common.h"

typedef struct PID{
  float kp, ki, kd;
  float integral;
  float previousError;
  bool hasPrevious;
  
  float outputMin, outputMax;
  float integralMin, integralMax;
} PID;
/*****************************
Function: PID_Init
Parameters: PID *pid is the object we intialize
Objective: Initialize the pid struct fields with the default values from config.h
Observation:
*****************************/
void PID_Init(PID *pid);
/*****************************
Function: PID_Reset
Parameters: PID *pid) is the object we reset
Objective: Reset the PID integral, has previous and previous error to their default values from config.h
Observation:
*****************************/
void PID_Reset(PID *pid);
/*****************************
Function: PID_Update
Parameters:
  -PID *pid, is the object we update
  -float error, is the error calculated for our PID
  -float dt, is the time period that passed since the last update
Objective: Calculate the p, derivative and integral in order to get our correction.
Observation:
*****************************/
float PID_Update(PID *pid, float error, float dt);
/*****************************
Function: PID_ModifyParams
Parameters:
  -PID *pid, is the object we modify
  -float kp, 
  -loat ki, 
  -float kd
Objective: Modify the parameters for the pid.
Observation: This is used to tune the PID and see how the system reacts to different parameter values in order to optimize the car following the line.
*****************************/
void PID_ModifyParams(PID *pid, float kp, float ki, float kd);
/*****************************
Function: PID_ModifyOutLims
Parameters: 
  -ID *pid, is the object we modify,
  -float outputMin, 
  -float outputMax)
Objective: Modify the interval of accepted output values.
Observation: The interval is closed at both ends, [outputMin, outputMax].
*****************************/
void PID_ModifyOutLims(PID *pid, float outputMin, float outputMax);
/*****************************
Function: PID_ModifyIntLims
Parameters: 
  -ID *pid, is the object we modify,
  -float integralMin, 
  -float integralMax)
Objective: Modify the interval of accepted integral values.
Observation: The interval is closed at both ends, [integralMin, integralMax]. 
*****************************/
void PID_ModifyIntLims(PID *pid, float integralMin, float
 integralMax);
/*****************************
Function: PID_ResetModify
Parameters: PID *pid, is the object we reset
Objective: Reset the values of all parameter to their default values from config.
Observation: This is a wrapper fucntion over PID_init(), i wrote it like this so its easier to read.
*****************************/
void PID_ResetModify(PID *pid);
/*****************************
Function: PID_CurrentError
Parameters: 
  -float setPoint,
  -float measured
Objective: Calculate the current error for updating our PID.
Observation: This could have been just an inline operation but i wrote it like this so its easier to read.
*****************************/
float PID_CurrentError(float setPoint, float measured);

#endif
