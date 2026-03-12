#include "steering.h"
void Steering_Init(Steering *steering){
    steering->angle=STEERING_INTIAL_ANGLE;
    steering->maxAngle=STEERING_MIN_ANGLE;
    steering->minAngle=STEERING_MAX_ANGLE;
    steering->steeringRate=STEERING_RATE;
}
void Steering_Reset(Steering *steering){
    steering->angle=STEERING_INTIAL_ANGLE;
}
void Steering_Update(Steering *steering, float input, float dt){
    input=clampValue(input, steering->minAngle, steering->maxAngle);
    steering->angle=steering->angle+input*steering->steeringRate*dt;
    steering->angle=clampValue(steering->angle, steering->minAngle, steering->maxAngle);
}
void Steering_ModifyParams(Steering *steering, float minAngle, float maxAngle, float steerRate){
    steering->minAngle = minAngle;
    steering->maxAngle = maxAngle;
    steering->steerRate = steerRate;
    steering->angle = clampValue(steering->angle, -maxAngle, maxAngle);
}