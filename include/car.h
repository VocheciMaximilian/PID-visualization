#ifndef CAR_H
#define CAR_H

#include "motor.h"
#include "steering.h"
#include "config.h"
#include "raylib.h"
#include <math.h>

typedef struct
{
    Motor motor;
    Steering steering;

    float wheelBase;
    float wheelRadius;

    float x;
    float y;
    float heading;
} Car;

/*****************************
Function: Car_Init
Parameters:
    - Car *car: object to initialize
Objective:
    Initialize the car with default geometry and zeroed pose/state.
Observation:
    This initializes the embedded motor and steering modules too.
*****************************/
void Car_Init(Car *car);
/*****************************
Function: Car_Reset
Parameters:
    - Car *car: object to reset
Objective:
    Reset the dynamic state of the car without changing its specs.
Observation:
    Keeps wheelBase and wheelRadius unchanged.
*****************************/
void Car_Reset(Car *car);
/*****************************
Function: Car_Update
Parameters:
    - Car *car: object to update
    - float throttle: longitudinal command, usually in [-1, 1]
    - float steeringInput: steering command
    - float dt: timestep
Objective:
    Update actuator state and advance the car pose using a simple bicycle model.
Observation:
    No line-following logic is included here on purpose.
*****************************/
void Car_Update(Car *car, float throttle, float steeringInput, float dt);
/*****************************
Function: Car_ModifySpecs
Parameters:
    - Car *car: object to modify
    - float wheelBase: distance between axles
    - float wheelRadius: wheel radius
Objective:
    Modify geometric car parameters.
Observation:
    Values are clamped to reasonable positive minimums.
*****************************/
void Car_ModifySpecs(Car *car, float wheelBase, float wheelRadius);
/*****************************
Function: Car_ResetModify
Parameters:
    - Car *car: object to reset to defaults
Objective:
    Reset car specs and state to defaults.
Observation:
    Wrapper over Car_Init().
*****************************/
void Car_ResetModify(Car *car);
/*****************************
Function: Car_SetPose
Parameters:
    - Car *car: object to modify
    - float x: world x
    - float y: world y
    - float heading: world heading in radians
Objective:
    Explicitly place the car in the world.
*****************************/
void Car_SetPose(Car *car, float x, float y, float heading);
/*****************************
Function: Car_GetSpeed
Parameters:
    - const Car *car: object to inspect
Objective:
    Return the current average longitudinal speed.
*****************************/
float Car_GetSpeed(const Car *car);
/*****************************
Function: DrawCar
Parameters:
    - const Car *car: pointer to the car object to visualize
    - float bodyLength: visual length of the car body in world units
    - float bodyWidth: visual width of the car body in world units
    - Color bodyColor: color used to draw the car body
Objective:
    Render a simple visual representation of the car using raylib.
    The car is drawn as a rotated rectangle centered at the car's
    world position (car->x, car->y).
Observation:
    The rectangle is rotated according to the car heading, which
    represents the orientation of the vehicle in radians.

    A red line is also drawn from the center of the car in the
    direction of the heading. This line acts as a heading indicator
    to help visualize the vehicle orientation while debugging
    steering or control algorithms.

    This function is strictly for visualization and does not affect
    the vehicle physics or simulation state.
*****************************/
void DrawCar(const Car *car, float bodyLength, float bodyWidth, Color bodyColor);
#endif