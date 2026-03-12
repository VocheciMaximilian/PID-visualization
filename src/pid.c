#include "pid.h"

void PID_Init(PID *pid){
  pid->kp=PID_KP;
  pid->ki=PID_KI;
  pid->kd=PID_KD;
  
  pid->outputMin=PID_OUTPUT_MIN;
  pid->outputMax=PID_OUTPUT_MAX;
  
  pid->integralMin=PID_INTEGRAL_MIN;
  pid->integralMax=PID_INTEGRAL_MAX;
  
  pid->integral=PID_INTEGRAL;
  pid->hasPrevious=PID_HAS_PREVIOUS;
  pid->previousError=PID_PREVIOUS_ERROR;
}
void PID_Reset(PID *pid){
  pid->integral=PID_INTEGRAL;
  pid->hasPrevious=PID_HAS_PREVIOUS;
  pid->previousError=PID_PREVIOUS_ERROR;
}

float PID_Update(PID *pid, float error, float dt){
  float p=pid->kp*error;
  
  pid->integral=clampValue( pid->integral+(error*dt), pid->integralMin, pid->integralMax ) ;
  float i=pid->ki*pid->integral;
  
  float derivative=(pid->hasPrevious && dt>TIME_STEP)?(error-pid->previousError)/dt : 0.0f;
  float d=pid->kd*derivative;
  
  pid->previousError=error;
  pid->hasPrevious=true;
  
  float out=clampValue( p+i+d, pid->outputMin, pid->outputMax );
  return out;
}
void PID_ModifyParams(PID *pid, float kp, float ki, float kd){
  pid->kp=kp;
  pid->ki=ki;
  pid->kd=kd;
}

void PID_ModifyOutLims(PID *pid, float outputMin, float outputMax){
  pid->outputMin=outputMin;
  pid->outputMax=outputMax;
}

void PID_ModifyIntLims(PID *pid, float integralMin, float
 integralMax){
  pid->integralMin=integralMin;
  pid->integralMax=integralMax;
}
 
void PID_ResetModify(PID *pid){
  PID_Init(pid);
}
float PID_CurrentError(float setPoint, float measured){
  return setPoint-measured;
}
