#include <raylib.h>
#include <raymath.h>
#define RLIGHTS_IMPLEMENTATION
#define RAYGUI_IMPLEMENTATION

#include "planet.h"
#include <string.h>

int main(){
    int windowHeight=700,windowWidth=700;
    InitWindow(windowWidth,windowHeight,"Planet_Simulator");


    //filenames
    std::string topographymap="src/earth/topography(1).png",
                texturemap="src/earth/texture.png",
                cloudmaploc="src/GFSR/",
                seasonsmaploc="static_images/monthly/earth/resized-images/";

    //planet
    Planet planet(topographymap,texturemap,cloudmaploc,seasonsmaploc);


    
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
        planet.season.Update(planet.mesh);
        planet.clouds.Update();
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode3D(camera);
        if(!planet.hide){
            planet.Draw();
        }
        if(!planet.clouds.hide){
            planet.clouds.Draw();
        }

        EndMode3D();
        planet.Gui();
        planet.clouds.Gui();
        planet.season.Gui();
        EndDrawing();
    }
    CloseWindow();
}