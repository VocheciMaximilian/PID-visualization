#ifndef PURE_PURSUIT_H
#define PURE_PURSUIT_H

#include "car.h"
#include "track.h"
#include "raylib.h"
#include <stdbool.h>
#include "config.h"
#include "common.h"
#include <math.h>

typedef struct
{
    float lookAheadDistance;

    int closestIndex;
    int targetIndex;

    Vector2 targetPoint;
    bool hasTarget;
} PurePursuit;

/*****************************
Function: PurePursuit_Init
Parameters:
    - PurePursuit *pp: controller object to initialize
Objective:
    Initialize the pure pursuit controller with default values.
Observation:
    The controller starts with no valid target point.
*****************************/
void PurePursuit_Init(PurePursuit *pp);

/*****************************
Function: PurePursuit_Reset
Parameters:
    - PurePursuit *pp: controller object to reset
Objective:
    Reset the runtime state of the controller.
Observation:
    Keeps the configured look-ahead distance unchanged.
*****************************/
void PurePursuit_Reset(PurePursuit *pp);

/*****************************
Function: PurePursuit_SetLookAhead
Parameters:
    - PurePursuit *pp: controller object to modify
    - float lookAheadDistance: desired look-ahead distance
Objective:
    Modify the controller look-ahead distance.
Observation:
    The value is clamped to a small positive minimum.
*****************************/
void PurePursuit_SetLookAhead(PurePursuit *pp, float lookAheadDistance);

/*****************************
Function: PurePursuit_UpdateTarget
Parameters:
    - PurePursuit *pp: controller object to update
    - const Car *car: current car state
    - const Track *track: track centerline to follow
Objective:
    Find the closest path point and select a look-ahead target point
    on the centerline.
Observation:
    The target point is chosen by walking forward along the track
    centerline until the accumulated distance reaches the configured
    look-ahead distance.
*****************************/
void PurePursuit_UpdateTarget(PurePursuit *pp, const Car *car, const Track *track);

/*****************************
Function: PurePursuit_GetSteeringInput
Parameters:
    - PurePursuit *pp: controller object
    - const Car *car: current car state
    - const Track *track: track centerline to follow
Objective:
    Compute a steering command using the pure pursuit method.
Observation:
    This function does not modify the car directly. It only returns
    a steering input that can be passed into Car_Update().
*****************************/
float PurePursuit_GetSteeringInput(PurePursuit *pp, const Car *car, const Track *track);

/*****************************
Function: PurePursuit_DrawDebug
Parameters:
    - const PurePursuit *pp: controller object to visualize
Objective:
    Draw debug information for the controller.
Observation:
    A blue point marks the active follow target.
*****************************/
void PurePursuit_DrawDebug(const PurePursuit *pp);

#endif