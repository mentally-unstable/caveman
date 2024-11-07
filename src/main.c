// hello
// #include "state.h"
#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

#define RES 50
#define SEC_PER_TICK (0.05) // 0.001 = millisecond

#define YLIM 50
#define XLIM 200

#define MY_ORANGE (Color) {255,79,0,255}

int width = 1000, height = 800;
const int glvl = 30;
Vector2 cursor, man;
float coffx, coffy;

typedef struct {
    Vector2 pos;
    Vector2 origin;

    float angle;
    float ux, uy;
    int thrown;

    clock_t when;
    float delta;

    float flight;
} Rock;

void handle_event(void);
Vector2 rock_pos(Rock *r);
void update_rock(int i);

#define MAXROCKS 10
Rock rocks[MAXROCKS];
int rockc;

int main(void) {
    man = (Vector2) {0, height-glvl};
    InitWindow(width, height, "Dyn Taflu Roc TestSim");

    while (!WindowShouldClose()) {
        handle_event();

        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangleV(man, (Vector2) {10,20}, BLUE);
        for (int i = 0; i <= rockc; i++)
            update_rock(i);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void handle_event(void) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        cursor = GetMousePosition();
        coffx = cursor.x-man.x;
        coffy = man.y-cursor.y;

        rockc++;

        if (rockc >= MAXROCKS) {
            rockc = 0;
        }

        rocks[rockc] = (Rock) {
            .origin = man,
            .thrown = 1,
            .when = clock(),
            .ux = coffx,
            .uy = coffy,

            .delta = 0,
            .flight = 0
        };
    }

    if (IsKeyDown(KEY_A)) {
        man.x-=1;
    }

    if (IsKeyDown(KEY_D)) {
        man.x+=1;
    }
}

void update_rock(int i) {
    if (rocks[i].thrown && rocks[i].delta <= rocks[i].flight)
    {
        rocks[i].delta = (clock() - rocks[i].when)/(CLOCKS_PER_SEC*SEC_PER_TICK);
        rocks[i].pos = rock_pos(&rocks[i]);
        DrawCircleV(rocks[i].pos, 5, MY_ORANGE);
    }
    else if (rocks[i].delta > rocks[i].flight) {
        rocks[i].thrown = 0;
        rocks[i].delta = 0;
    }
}


/*
   dx = Vx * cos(theta) * t;
   dy = Vy * sin(theta) * t - (a * pow(t, 2)/2);
   dy = t * ((Vy * sin(theta)) - (a * t * 0.5));
   */
Vector2 rock_pos(Rock *r) {
    if (r->uy < 0) return r->origin;

    // angle elevation to cursor
    r->angle = atan(r->uy/r->ux);

    if (r->ux < 0) r->angle = (3.14) + r->angle;
    if (r->ux == 0) return r->origin;

    float ux = sqrt((r->ux * 9.8) / (sin(2 * r->angle)));
    float uy = sqrt(2 * 9.8 * r->uy);
    if (ux > XLIM) ux = XLIM;
    if (ux < -XLIM) ux = -XLIM;
    if (uy > YLIM) uy = YLIM;
    float v = sqrt((ux*ux) + (uy*uy));

    float x, y;
    x = v * cos(r->angle) * r->delta;

    float a = (v * sin(r->angle));
    float b = (9.8 * r->delta)/2;
    y = r->delta * (a-b);

    // other calculations
    float vy = v * sin(r->angle);
    // range = ((v * v) * sin((2 * r->angle)))/9.8;
    r->flight = (2 * vy)/9.8;
    // max = (vy*vy)/(2 * 9.8);

    return (Vector2) {r->origin.x+x, r->origin.y-y};
}
