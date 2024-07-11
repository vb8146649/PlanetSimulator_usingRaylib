#include <raylib.h>
#include <raymath.h>
#define RAYGUI_IMPLEMENTATION
#define RLIGHTS_IMPLEMENTATION
#include "planet.h"

int main(){

    int windowHeight=700,windowWidth=700;
    InitWindow(windowWidth,windowHeight,"Planet_Simulator");
    Planet planet;
    Camera camera = { 0 };
    camera.position = (Vector3){ 20.0f, 20.0f, 20.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);
    while(!WindowShouldClose()){
        UpdateCamera(&camera,CAMERA_THIRD_PERSON);        
        planet.Update();
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode3D(camera);
        planet.Draw();
        EndMode3D();
        planet.Gui();
        EndDrawing();
    }
    CloseWindow();
}