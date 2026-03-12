#include "track.h"

static bool Track_CanAddControlPoint(const Track *track, Vector2 p);
static void Track_AddControlPoint(Track *track, Vector2 p);
static Vector2 Track_GetCenterLinePointCatMullRom(const Track *track, int segmentIndex, float t);

void Track_Init(Track *track){
    track->controlCount = TRACK_DEFAULT_CONTROL_COUNT;
    track->centerLineCount = TRACK_DEFAULT_CENTERLINE_COUNT;

    track->minPointSpacing = TRACK_DEFAULT_MIN_POINT_SPACING;
    track->samplesPerSegment = TRACK_DEFAULT_SAMPLES_PER_SEGMENT;
    track->drawThickness = TRACK_DEFAULT_DRAW_THICKNESS;

    track->finalized = TRACK_FINALIZED;
}
void Track_Reset(Track *track){
    track->controlCount = TRACK_DEFAULT_CONTROL_COUNT;
    track->centerLineCount = TRACK_DEFAULT_CENTERLINE_COUNT;
    track->finalized = TRACK_FINALIZED;
}
void Track_HandleInput(Track *track){
    Vector2 mouse=GetMousePosition();

    if(IsKeyPressed(KEY_R)){
        Track_Reset(track);
        return;
    }
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !track->finalized){
        if(Track_CanAddControlPoint(track, mouse)){
            Track_AddControlPoint(track, mouse);
            Track_RebuildCenterLine(track);
        }
    }
    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && !track->finalized){
        if(track->controlCount>0){
            track->controlCount--;
            Track_RebuildCenterLine(track);
        }
    }
    if(IsKeyPressed(KEY_ENTER)){
        track->finalized=(track->controlCount>=4);
    }
}
bool Track_IsReady(const Track *track){
    return track->centerLineCount>=2;
}

static bool Track_CanAddControlPoint(const Track *track, Vector2 p){
    if(track->controlCount==0) return true;

    Vector2 last=track->controlPoints[track->controlCount-1];
    float dist=Vector2Distance(last, p);
    return dist>=track->minPointSpacing;
}
static void Track_AddControlPoint(Track *track, Vector2 p){
    if(track->controlCount>=TRACK_MAX_CONTROL_POINTS) return;
    track->controlPoints[track->controlCount++]=p;
}
static Vector2 Track_GetCenterLinePointCatMullRom(const Track *track, int segmentIndex, float t) {
    Vector2 p0=track->controlPoints[segmentIndex];
    Vector2 p1=track->controlPoints[segmentIndex+1];
    Vector2 p2=track->controlPoints[segmentIndex+2];
    Vector2 p3=track->controlPoints[segmentIndex+3];

    return GetSplinePointCatmullRom(p0, p1, p2, p3, t);
}
void Track_RebuildCenterLine(Track *track){
    track->centerLineCount=TRACK_DEFAULT_CENTERLINE_COUNT;
    if(track->controlCount<TRACK_SPLINE_WINDOW) return;

    int maxSegmentStart=track->controlCount-TRACK_SPLINE_WINDOW;
    for(int i=0; i<=maxSegmentStart; i++){
        for(int s=0; s<track->samplesPerSegment; s++){
            float t=(float)s/(float)track->samplesPerSegment;

            track->centerLine[track->centerLineCount++]=Track_GetCenterLinePointCatMullRom(track, i, t);
        }
    }
    track->centerLine[track->centerLineCount++]=track->controlPoints[track->controlCount-TRACK_LAST_SPLINE_POINT_OFFSET];
}
void Track_Draw(const Track *track){
    if(track->centerLineCount>=TRACK_SPLINE_WINDOW){
        DrawSplineCatmullRom(track->centerLine, track->centerLineCount, track->drawThickness, BLACK);
    } else if(track->controlCount>=TRACK_LAST_SPLINE_POINT_OFFSET){
        DrawLineStrip(track->controlPoints, track->controlCount, DARKGRAY);
    }
}
void Track_DrawDebug(const Track *track) {
    for (int i = 0; i < track->controlCount; i++) {
        DrawCircleV(track->controlPoints[i], 4.0f, RED);

        if (i > 0) {
            DrawLineV(track->controlPoints[i - 1], track->controlPoints[i], LIGHTGRAY);
        }
    }

    DrawText("LMB drag: draw", 20, 20, 20, DARKGRAY);
    DrawText("RMB: undo last point", 20, 45, 20, DARKGRAY);
    DrawText("C: clear", 20, 70, 20, DARKGRAY);
    DrawText("ENTER: finalize", 20, 95, 20, DARKGRAY);

    DrawText(TextFormat("control points: %d", track->controlCount), 20, 130, 20, MAROON);
    DrawText(TextFormat("centerline points: %d", track->centerLineCount), 20, 155, 20, MAROON);
    DrawText(track->finalized ? "finalized: yes" : "finalized: no", 20, 180, 20, MAROON);
}