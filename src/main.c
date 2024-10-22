// hello
#include "state.h"
#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <time.h>

void handle_event(void);
void draw_dots(void);
void generate_dots(void);

#define MAXDOTS 500
#define WIDTH 1000
#define HEIGHT 800

Vector2 pos;
Vector2 origin = (Vector2) {0, HEIGHT};
Vector2 dot_array[MAXDOTS];
int dotc;
time_t start;

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Dyn Taflu Roc TestSim");
    // SetWindowOpacity(0.9);

    while (!WindowShouldClose()) {
        pos = GetMousePosition();

        handle_event();

        BeginDrawing();
        ClearBackground(BLACK);

        DrawLineV(origin, (Vector2) {pos.x, pos.y}, GREEN);
        draw_dots();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void handle_event(void) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        generate_dots();
    }
}

/*
   dx = Vx * cos(theta) * t;
   dy = Vy * sin(theta) * t - (a * pow(t, 2)/2);
   */
void generate_dots(void) {
    // angle elevation to cursor
    float theta = atan((pos.y/pos.x));
    // float theta = 1;
    float u = 100;
    float v = 0.2;

    float x=0.0, y;
    for (int i = 0; i < MAXDOTS; i++) {
        x++;
        int a = (u * v * sin(theta) * cos(theta) * x);
        int b = (9.81 * (pow((v * cos(theta) * x), 2)/2));
        y = a-b;

        dot_array[i] = (Vector2) {origin.x+x, origin.y-y};
    }
}

void draw_dots(void) {
    for (int i = 0; i < MAXDOTS; i++) {
        DrawPixelV(dot_array[i], RED);
    }
}
