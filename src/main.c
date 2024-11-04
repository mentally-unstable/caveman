// hello
#include "state.h"
#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

void handle_event(void);
Vector2 rock_pos(float t);

#define RES 50
#define WIDTH 1200
#define HEIGHT 800
#define SEC_PER_TICK (0.1) // 0.001 = millisecond

#define YLIM 50
#define XLIM 300

Vector2 pos;
Vector2 origin = (Vector2) {0, HEIGHT-30};
Vector2 throw_pos;
float ox, oy; // offsets from origin

clock_t start;
float elapsed = 0;

int thrown = 0;
float range = 0;
float flight = 0;
float max = 0;

void draw_grid(void) {
    int x, y;
    for (x = 0; x < WIDTH; x++) {
        for (y = 0; y < HEIGHT; y++) {
            if ((x % RES) == 0)
                DrawPixel(x, y, GRAY);

            if ((y % RES) == 0)
                DrawPixel(x, y, GRAY);
        }
    }
}

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Dyn Taflu Roc TestSim");

    while (!WindowShouldClose()) {
        handle_event();

        BeginDrawing();
        ClearBackground(BLACK);

        draw_grid();
        DrawLineV(origin, (Vector2) {pos.x, pos.y}, GREEN);
        DrawRectangleV(origin, (Vector2) {10,20}, BLUE);

        if (thrown && elapsed <= flight) {
            elapsed = (clock() - start)/(CLOCKS_PER_SEC*SEC_PER_TICK);
            DrawCircleV(rock_pos(elapsed), 5, ORANGE);
            DrawLineV(
                    (Vector2) {throw_pos.x+range, 0},
                    (Vector2) {throw_pos.x+range, HEIGHT},
                    BLUE
            );

            DrawLine(0, HEIGHT-max, WIDTH, HEIGHT-max, RED);
        }
        else {
            elapsed = 0;
            thrown = 0;
            range = 0;
            max = 0;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void handle_event(void) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        pos = GetMousePosition();
        ox = pos.x-origin.x;
        oy = origin.y-pos.y;
        start = clock();
        throw_pos = origin;
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
   dy = t * ((Vy * sin(theta)) - (a * t * 0.5));
   */
Vector2 rock_pos(float t) {
    // angle elevation to cursor
    float theta = atan(oy/ox);

    if (ox < 0) theta = (3.14) + theta;

    float ux = sqrt((ox * 9.81) / (sin(2 * theta)));
    float uy = sqrt(2 * 9.81 * oy);
    if (ux > XLIM) ux = XLIM;
    if (ux < -XLIM) ux = -XLIM;
    if (uy > YLIM) uy = YLIM;
    float v = sqrt((ux*ux) + (uy*uy));

    float x, y;
    x = v * cos(theta) * t;

    float a = (v * sin(theta));
    float b = (9.81 * t)/2;
    y = t * (a-b);

    // other calculations
    float vy = v * sin(theta);
    range = ((v * v) * sin((2 * theta)))/9.81;
    flight = (2 * vy)/9.81;
    max = pow(vy, 2) / (2 * 9.81);

    return (Vector2) {throw_pos.x+x, throw_pos.y-y};
}
