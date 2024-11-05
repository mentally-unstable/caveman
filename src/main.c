// hello
// #include "state.h"
#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

void handle_event(void);
Vector2 rock_pos(float t);

#define RES 50
#define SEC_PER_TICK (0.05) // 0.001 = millisecond

#define YLIM 50
#define XLIM 200

int width = 1000, height = 800;
const int glvl = 30;
Vector2 cursor, man;
float coffx, coffy;

typedef struct {
    float offx, offy;
    Vector2 origin;
    int thrown;
    clock_t when;
    float delta;

    float range;
    float height;
    float time;
} Rock;

#define MAXROCKS 20
Rock rocks[MAXROCKS];
int rockc;

void update_rocks(int i) {
    if (rocks[i].thrown && rocks[i].delta <= rocks[i].flight)
    {
        rocks[i].delta = (clock() - rocks[i].when)/(CLOCKS_PER_SEC*SEC_PER_TICK);
        rocks[i].off = rockoff(rocks[i]) // incomplete
        DrawCircleV(rock_pos(rocks[i].delta), 5, RAYWHITE);

        DrawCircleV((Vector2) {
                    rocks[i].origin.x+rocks[i].range,
                    rocks[i].origin.y
                },
                5, GRAY);

        draw_x((Vector2) {
                    rocks[i].origin.x+(rocks[i].range/2),
                    rocks[i].throw_pos.y-rocks[i].height
                },
                GRAY);
    }
    else if (delta > flight) {
        rocks[i].thrown = 0;
        rocks[i].delta = 0;
        rocks[i].range = 0;
        rocks[i].height = 0;
    }
}



int main(void) {
    man = (Vector2) {0, height-glvl};
    InitWindow(width, height, "Dyn Taflu Roc TestSim");

    while (!WindowShouldClose()) {
        handle_event();

        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangleV(man, (Vector2) {10,20}, BLUE);
        for (int i = 0; i < rockc; i++)
            update_rocks(i);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void handle_event(void) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        pos = GetMousePosition();
        coffx = cursor.x-man.x;
        coffy = man.y-cursor.y;

        rockc++;
        rocks[rockc] = (Rock) {
            .origin = man,
            .thrown = 1,
            .when = clock(),

            .delta = 0,
            .range = 0,
            .height = 0,
            .time = 0
        };
    }

    if (IsKeyDown(KEY_A)) {
        man.x-=1;
    }

    if (IsKeyDown(KEY_D)) {
        man.x+=1;
    }
}

/*
   dx = Vx * cos(theta) * t;
   dy = Vy * sin(theta) * t - (a * pow(t, 2)/2);
   dy = t * ((Vy * sin(theta)) - (a * t * 0.5));
   */
Vector2 rock_pos(Rock *rock) {
    if (coffy < 0) return throw_pos;

    // angle elevation to cursor
    float theta = atan(coffy/coffx);

    if (coffx < 0) theta = (3.14) + theta;
    if (coffx == 0) return ;

    float ux = sqrt((offx * 9.8) / (sin(2 * theta)));
    float uy = sqrt(2 * 9.8 * offy);
    if (ux > XLIM) ux = XLIM;
    if (ux < -XLIM) ux = -XLIM;
    if (uy > YLIM) uy = YLIM;
    float v = sqrt((ux*ux) + (uy*uy));

    float x, y;
    x = v * cos(theta) * t;

    float a = (v * sin(theta));
    float b = (9.8 * t)/2;
    y = t * (a-b);

    // other calculations
    float vy = v * sin(theta);
    range = ((v * v) * sin((2 * theta)))/9.8;
    flight = (2 * vy)/9.8;
    max = (vy*vy)/(2 * 9.8);

    return (Vector2) {throw_pos.x+x, throw_pos.y-y};
}
