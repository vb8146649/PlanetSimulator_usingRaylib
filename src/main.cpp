#include <raylib.h>
#include <raymath.h>
#define RAYGUI_IMPLEMENTATION
#define RLIGHTS_IMPLEMENTATION
#include <raylib/examples/models/rlights.h>
#include "planet.h"
#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif
int main(){
    SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)

    int windowHeight=700,windowWidth=700;
    InitWindow(windowWidth,windowHeight,"Planet_Simulator");
    Planet planet;
    // while(planet.mesh.meshCount==0){
    //     planet.Update();
    // }
    Camera camera = { 0 };
    camera.position = (Vector3){ 20.0f, 20.0f, 20.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Shader shader = LoadShader(TextFormat("raylib/examples/shaders/resources/shaders/glsl%i/lighting.vs", GLSL_VERSION),TextFormat("raylib/examples/shaders/resources/shaders/glsl%i/lighting.fs", GLSL_VERSION));
    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
    // int ambientLoc = GetShaderLocation(shader, "ambient");
    // SetShaderValue(shader, ambientLoc, (float[4]){ 0.1f, 0.1f, 0.1f, 1.0f }, SHADER_UNIFORM_VEC4);
    //light
    Light light = { 0 };
    light=CreateLight(LIGHT_POINT, (Vector3){ 20, 20, 0 }, Vector3Zero(), YELLOW, shader);
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        UpdateCamera(&camera,CAMERA_THIRD_PERSON);
        float cameraPos[3] = { camera.position.x, camera.position.y, camera.position.z };
        SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
        
        
        planet.Update();
        BeginDrawing();
        ClearBackground(GREEN);
        BeginMode3D(camera);
        BeginShaderMode(shader);
        // DrawPlane(Vector3Zero(), (Vector2) { 10.0, 10.0 }, WHITE);
        planet.Draw();
        EndShaderMode();
        EndMode3D();
        planet.Gui();
        EndDrawing();
    }
    UnloadShader(shader);
    CloseWindow();
}