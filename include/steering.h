#ifndef STEERING_H
#define STEERING_H
typedef struct{
  float angle;
  float maxAngle;
  float steerRate;
} Steering;

void Steering_Init(Steering *steering);
void Steering_Reset(Steering *steering);
void Steering_Update(Steering *steering, float input, float dt);
void Steering_ModifyParams(Steering *steering, float angle, float maxAngle, float steerRate);

#endif