#ifndef CAR_H
#define CAR_H

#include "motor.h"
#include "steering.h"

typedef struct{
  Motor motor;
  Steering steering;
  float wheelBase;
  float wheelRadius;
} Car;

void Car_Init(Car *car);
void Car_Reset(Car *car);
void Car_Update(Car *car, float throttle, float steeringInput, float dt);
void Car_ModifySpecs(Car *car, float wheelBase, float wheelRadius);
void Car_ResetModify(Car*car);
#endif