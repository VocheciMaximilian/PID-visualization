#include "car.h"

void Car_Init(Car *car){
    if (!car) return;

    Motor_Init(&car->motor);
    Steering_Init(&car->steering);

    car->wheelBase = CAR_DEFAULT_WHEELBASE;
    car->wheelRadius = CAR_DEFAULT_WHEELRADIUS;

    car->x = CAR_DEFAULT_X;
    car->y = CAR_DEFAULT_Y;
    car->heading = CAR_DEFAULT_HEADING;
}

void Car_Reset(Car *car){
    if (!car) return;

    Motor_Reset(&car->motor);
    Steering_Reset(&car->steering);

    car->x = CAR_DEFAULT_X;
    car->y = CAR_DEFAULT_Y;
    car->heading = CAR_DEFAULT_HEADING;
}

void Car_Update(Car *car, float throttle, float steeringInput, float dt){
    if (!car || dt <= 0.0f) return;

    Motor_Update(&car->motor, throttle, dt);
    Steering_Update(&car->steering, steeringInput, dt);

    float speed = Motor_GetAvgSpeed(car->motor.leftSpeed, car->motor.rightSpeed);

    float steerAngle = car->steering.angle;
    float yawRate = 0.0f;

    if (fabsf(car->wheelBase) > CAR_MIN_WHEELBASE)
    {
        yawRate = (speed / car->wheelBase) * tanf(steerAngle);
    }

    car->heading += yawRate * dt;
    car->x += speed * cosf(car->heading) * dt;
    car->y += speed * sinf(car->heading) * dt;
}

void Car_ModifySpecs(Car *car, float wheelBase, float wheelRadius){
    if (!car) return;

    car->wheelBase = (wheelBase > CAR_MIN_WHEELBASE) ? wheelBase : CAR_MIN_WHEELBASE;
    car->wheelRadius = (wheelRadius > CAR_MIN_WHEELRADIUS) ? wheelRadius : CAR_MIN_WHEELRADIUS;
}
void Car_ResetModify(Car *car){
    Car_Init(car);
}
void Car_SetPose(Car *car, float x, float y, float heading){
    if (!car) return;

    car->x = x;
    car->y = y;
    car->heading = heading;
}
float Car_GetSpeed(const Car *car){
    if (!car) return 0.0f;

    return Motor_GetAvgSpeed(car->motor.leftSpeed, car->motor.rightSpeed);
}
void DrawCar(const Car *car, float bodyLength, float bodyWidth, Color bodyColor){
    if (!car) return;

    Rectangle rect = { car->x - bodyLength * 0.5f, car->y - bodyWidth * 0.5f, bodyLength, bodyWidth};

    Vector2 origin = { bodyLength * 0.5f, bodyWidth * 0.5f };
    float angleDeg = car->heading * RAD2DEG;

    DrawRectanglePro(rect, origin, angleDeg, bodyColor);

    Vector2 start = { car->x, car->y };
    Vector2 end = { car->x + cosf(car->heading) * (bodyLength * 0.7f), car->y + sinf(car->heading) * (bodyLength * 0.7f)};

    DrawLineEx(start, end, 2.0f, RED);
}