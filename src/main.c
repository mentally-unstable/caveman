// hello
#include "state.h"
#include "raylib.h"
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

void handle_event(void);
Vector2 rock_pos(float t);

#define WIDTH 1200
#define MAXDOTS (WIDTH)
#define HEIGHT 800
#define SEC_PER_TICK (0.01) // 0.001 = millisecond

#define YLIM 100

Vector2 pos;
Vector2 origin = (Vector2) {0, HEIGHT-20};

clock_t start;
float elapsed = 0;

int thrown = 0;
float flight = 0;
float range = 0;

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Dyn Taflu Roc TestSim");

    while (!WindowShouldClose()) {
        handle_event();

        BeginDrawing();
        ClearBackground(BLACK);

        DrawLineV(origin, (Vector2) {pos.x, pos.y}, GREEN);
        DrawRectangleV(origin, (Vector2) {10,20}, BLUE);

        if (thrown && elapsed <= flight) {
            elapsed = (clock() - start)/(CLOCKS_PER_SEC*SEC_PER_TICK);
            DrawCircleV(rock_pos(elapsed), 5, RED);
            Vector2 final = rock_pos(flight);
            DrawLineV(
                    (Vector2) {final.x, 0},
                    (Vector2) {final.x, HEIGHT},
                    BLUE
            );

            DrawLineV(
                    (Vector2) {range, 0},
                    (Vector2) {range, HEIGHT},
                    RAYWHITE
            );
        }
        else {
            elapsed = 0;
            thrown = 0;
            flight = 0;
            range = 0;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void handle_event(void) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        pos = GetMousePosition();
        start = clock();
        thrown = 1;
    }

    if (IsKeyDown(KEY_A)) {
        origin.x-=2;
    }

    if (IsKeyDown(KEY_D)) {
        origin.x+=2;
    }
}

/*
   dx = Vx * cos(theta) * t;
   dy = Vy * sin(theta) * t - (a * pow(t, 2)/2);
   */
Vector2 rock_pos(float t) {
    // angle elevation to cursor
    float ox = pos.x-origin.x;
    float oy = origin.y-pos.y;
    float theta = atan(oy/ox);

    float ux = ox/6;
    float uy = oy*2;

    if (uy > YLIM) uy = YLIM;

    float x, y;
    x = ux * cos(theta) * t;

    float a = (uy * sin(theta) * t);
    float b = (9.81 * (pow(t, 2)))/2;
    y = a-b;

    float v = sqrt( (pow(ux, 2) + pow(uy, 2)) );
    flight = (2 * v * sin(theta))/9.81;
    range = (v * v * sin(2*theta))/9.81;

    return (Vector2) {origin.x+x, origin.y-y};
}
