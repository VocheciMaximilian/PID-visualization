#ifndef TRACK_H
#define TRACK_H

#include "config.h"
#include "raylib.h"

typedef struct{
    Vector2 controlPoints[TRACK_MAX_CONTROL_POINTS];
    int controlCount;

    Vector2 centerLine[TRACK_MAX_CENTERLINE_POINTS];
    int centerLineCount;

    float minPointSpacing;
    int samplesPerSegment;
    float drawThickness;

    bool finalized;
} Track;
/*****************************
Function:
Parameters:
Objective:
Observation:
*****************************/
void Track_init(Track *track);
/*****************************
Function:
Parameters:
Objective:
Observation:
*****************************/
void Track_Reset(Track *track);
/*****************************
Function:
Parameters:
Objective:
Observation:
*****************************/
void Track_HandleInput(Track *track);
/*****************************
Function:
Parameters:
Objective:
Observation:
*****************************/
void Track_RebuildCenterLine(Track *track);
/*****************************
Function:
Parameters:
Objective:
Observation:
*****************************/
void Track_Draw(const Track *track);
/*****************************
Function:
Parameters:
Objective:
Observation:
*****************************/
void Track_DrawDebug(const Track *track);
/*****************************
Function:
Parameters:
Objective:
Observation:
*****************************/
bool Track_IsReady(const Track *track);
#endif