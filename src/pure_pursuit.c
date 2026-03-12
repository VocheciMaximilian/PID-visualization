#include "pure_pursuit.h"

static float PP_Distance(Vector2 a, Vector2 b)
{
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    return sqrtf(dx * dx + dy * dy);
}

static int PP_FindClosestIndex(const Car *car, const Track *track)
{
    int bestIndex = 0;
    float bestDistSq = 0.0f;

    for (int i = 0; i < track->centerLineCount; i++)
    {
        float dx = track->centerLine[i].x - car->x;
        float dy = track->centerLine[i].y - car->y;
        float distSq = dx * dx + dy * dy;

        if (i == 0 || distSq < bestDistSq)
        {
            bestDistSq = distSq;
            bestIndex = i;
        }
    }

    return bestIndex;
}

void PurePursuit_Init(PurePursuit *pp)
{
    if (!pp) return;

    pp->lookAheadDistance = PURE_PURSUIT_DEFAULT_LOOKAHEAD;
    pp->closestIndex = 0;
    pp->targetIndex = 0;
    pp->targetPoint = (Vector2){ 0.0f, 0.0f };
    pp->hasTarget = false;
}

void PurePursuit_Reset(PurePursuit *pp)
{
    if (!pp) return;

    pp->closestIndex = 0;
    pp->targetIndex = 0;
    pp->targetPoint = (Vector2){ 0.0f, 0.0f };
    pp->hasTarget = false;
}

void PurePursuit_SetLookAhead(PurePursuit *pp, float lookAheadDistance)
{
    if (!pp) return;

    pp->lookAheadDistance = Clamp(
        lookAheadDistance,
        PURE_PURSUIT_MIN_LOOKAHEAD,
        1000000.0f
    );
}

void PurePursuit_UpdateTarget(PurePursuit *pp, const Car *car, const Track *track)
{
    if (!pp || !car || !track)
    {
        if (pp) pp->hasTarget = false;
        return;
    }

    if (track->centerLineCount < 2)
    {
        pp->hasTarget = false;
        return;
    }

    pp->closestIndex = PP_FindClosestIndex(car, track);

    float accumulatedDistance = 0.0f;
    int selectedIndex = pp->closestIndex;

    for (int i = pp->closestIndex; i < track->centerLineCount - 1; i++)
    {
        float segmentLength = PP_Distance(track->centerLine[i], track->centerLine[i + 1]);
        accumulatedDistance += segmentLength;
        selectedIndex = i + 1;

        if (accumulatedDistance >= pp->lookAheadDistance)
        {
            break;
        }
    }

    pp->targetIndex = selectedIndex;
    pp->targetPoint = track->centerLine[selectedIndex];
    pp->hasTarget = true;
}

float PurePursuit_GetSteeringInput(PurePursuit *pp, const Car *car, const Track *track)
{
    if (!pp || !car || !track)
    {
        if (pp) pp->hasTarget = false;
        return 0.0f;
    }

    if (track->centerLineCount < 2)
    {
        pp->hasTarget = false;
        return 0.0f;
    }

    PurePursuit_UpdateTarget(pp, car, track);

    if (!pp->hasTarget)
    {
        return 0.0f;
    }

    float dx = pp->targetPoint.x - car->x;
    float dy = pp->targetPoint.y - car->y;

    float localX =  cosf(car->heading) * dx + sinf(car->heading) * dy;
    float localY = -sinf(car->heading) * dx + cosf(car->heading) * dy;

    float lookAhead = sqrtf(localX * localX + localY * localY);
    if (lookAhead < PURE_PURSUIT_MIN_LOOKAHEAD)
    {
        return 0.0f;
    }

    float alpha = atan2f(localY, localX);
    float desiredSteeringAngle = atan2f(2.0f * car->wheelBase * sinf(alpha), lookAhead);

    float steeringInput = desiredSteeringAngle - car->steering.angle;

    steeringInput = Clamp(
        steeringInput,
        car->steering.minAngle,
        car->steering.maxAngle
    );

    return steeringInput;
}

void PurePursuit_DrawDebug(const PurePursuit *pp)
{
    if (!pp || !pp->hasTarget) return;

    DrawCircleV(pp->targetPoint, 6.0f, BLUE);
    DrawCircleLines(
        (int)pp->targetPoint.x,
        (int)pp->targetPoint.y,
        8.0f,
        DARKBLUE
    );
}