#pragma once

/*
    Raylib example file.
    This is an example main file for a simple  C/C++raylib project.
*/

#include "raylib.h"
#include "raymath.h"


// define a timer
typedef struct
{
    float Lifetime;
}Timer;

// start or restart a timer with a specific lifetime
void StartTimer(Timer* timer, float lifetime)
{
    if (timer != NULL)
        timer->Lifetime = lifetime;
}

// update a timer with the current frame time
void UpdateTimer(Timer* timer)
{
    // subtract this frame from the timer if it's not allready expired
    if (timer != NULL && timer->Lifetime > 0)
        timer->Lifetime -= GetFrameTime();
}

// check if a timer is done.
bool TimerDone(Timer* timer)
{
    if (timer != NULL)
        return timer->Lifetime <= 0;

    return false;
}


    

    


    // a timer for the ball
    Timer ballTimer = { 0 };

   
        // check to see if the user clicked
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            // if they did, move the ball to the current position and restart the timer
            pos = GetMousePosition();
            StartTimer(&ballTimer, ballLife);
        }

        // tick our timer
        UpdateTimer(&ballTimer);

        // if the timer hasn't expired, move the ball
        if (!TimerDone(&ballTimer))
        {
            // move the ball based on the speed and the frame time
            pos = Vector2Add(pos, Vector2Scale(dir, GetFrameTime() * speed));

           
        }

        // drawing
        BeginDrawing();
        ClearBackground(BLACK);

        // draw the ball where it is if the timer is alive
        if (!TimerDone(&ballTimer))
            DrawCircleV(pos, radius, RED);

        EndDrawing();

    // cleanup
    CloseWindow();

