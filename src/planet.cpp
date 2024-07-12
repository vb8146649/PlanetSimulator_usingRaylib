#include "planet.h"
Planet::Planet(std::string topographymap, std::string texturemap, std::string cloudmaploc, std::string seasonsmaploc)
{
    // topography
    topography = LoadImage(topographymap.c_str());
    ImageRotateCCW(&topography);
    ImageFlipVertical(&topography);
    lastUpdateTime = 0.0;
    frame = 1;

    // texture
    textureImage = LoadImage(texturemap.c_str());
    ImageRotateCCW(&textureImage);
    ImageFlipVertical(&textureImage);
    texture = LoadTextureFromImage(textureImage);

    // Cloud
    clouds = Clouds(cloudmaploc.c_str(),1,79,true);
    season = Seasons(seasonsmaploc.c_str(),1,12,true);

    // initialization
    heightScale = 1;
    initialHeight = 0;
    radius = 5;
    resolution = 25;
    heightMapLoaded = false;
    mapLoaded = false;
    position = {0, 0, 0};
    changeResolution = resolution;
    changeHeightScale = heightScale;
    changexOffset = planet3D.xOffset;
    isTopoColor = false;
    hide=false;
    // shader
    shader = LoadShader("raylib/examples/shaders/resources/shaders/glsl100/base.vs", "raylib/examples/shaders/resources/shaders/glsl100/base.fs");
}

void Planet::Draw()
{
    if (mesh.meshCount != 0)
    {
        DrawModel(mesh, position, 1.0f, WHITE);
    }
    DrawLine3D((Vector3){-10.0f, 0.0f, 0.0f}, (Vector3){10.0f, 0.0f, 0.0f}, RED);   // X-axis (red)
    DrawLine3D((Vector3){0.0f, -10.0f, 0.0f}, (Vector3){0.0f, 10.0f, 0.0f}, GREEN); // Y-axis (green)
    DrawLine3D((Vector3){0.0f, 0.0f, -10.0f}, (Vector3){0.0f, 0.0f, 10.0f}, BLUE);  // Z-axis (blue)
}

void Planet::Gui()
{
    GuiLabel((Rectangle){100, 30, 150, 20}, "Planet Controls:");
    GuiSliderBar((Rectangle){100, 70, 100, 20}, "Resolution", NULL, &resolution, 20, 250);
    GuiSliderBar((Rectangle){100, 90, 100, 20}, "Height Scale", NULL, &heightScale, 0.0f, 10.0f);
    GuiSliderBar((Rectangle){100, 110, 100, 20}, "InitialHeight Scale", NULL, &initialHeight, 0.0f, 4.0f);
    GuiSliderBar((Rectangle){100, 130, 100, 20}, "Radius", NULL, &radius, 5.0f, 10.0f);
    if (GuiCheckBox((Rectangle){100, 160, 20, 20}, "isTopoColor", &isTopoColor))
    {
        heightMapLoaded = false;
        mapLoaded = false;
    };
    (GuiCheckBox((Rectangle){100, 190, 20, 20},"Hide",&hide));
    if (GuiButton((Rectangle){60, 600, 70, 20}, "Save"))
    {
        Save();
    }
    if (GuiButton((Rectangle){600, 600, 70, 20}, "Load"))
    {
        LoadMesh();
    }
}

void Planet::Update()
{
    if (!(topography.data == NULL) && heightMapLoaded == false)
    {
        heightMap = LoadHeightMap();
        heightMapLoaded = true;
    }
    if (mapLoaded == false && heightMap.size() != 0)
    {
        mapLoaded = true;
    }
    if (GetTime() - lastUpdateTime >= 0.5)
    {
        if (((abs(changeResolution - resolution) >= 0.01 || abs(changeHeightScale - heightScale) >= 0.01) || (mesh.meshCount == 0) || abs(changeRadius - radius) >= 0.01 || abs(changeInitialHeight - initialHeight) >= 0.01) && mapLoaded == true)
        {
            mesh = LoadModelFromMesh(planet3D.GenerateDisplacedSphere(radius, (int)resolution, (int)resolution, heightMap, topography.width, topography.height, heightScale, initialHeight));
            // mesh=LoadModel("src/displaced_sphere.obj");
            if (texture.id != 0 && season.hide)
            {
                mesh.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
            }
            if (shader.id != 0)
            {
                mesh.materials[0].shader = shader;
            }

            changeResolution = resolution;
            changeHeightScale = heightScale;
            changeRadius = radius;
            changeInitialHeight = initialHeight;
        }
        lastUpdateTime = GetTime();
    }
}

void Planet::HandleInputs()
{
    if (IsKeyPressed(KEY_UP))
    {
    }
    else if (IsKeyPressed(KEY_DOWN))
    {
    }
    else if (IsKeyPressed(KEY_RIGHT))
    {
    }
    else if (IsKeyPressed(KEY_LEFT))
    {
    }
}

std::vector<float> Planet::LoadHeightMap()
{
    Color *pixels = LoadImageColors(topography);
    std::vector<float> heightMap(topography.width * topography.height);
    if (isTopoColor)
    {
        for (int i = 0; i < topography.width * topography.height; i++)
        {
            Vector3 hsv = ColorToHSV(pixels[i]);
            heightMap[i] = hsv.x / 240.0f;
        }
    }
    else
    {
        for (int i = 0; i < topography.width * topography.height; i++)
        {
            heightMap[i] = pixels[i].r / 255.0f;
        }
    }
    UnloadImageColors(pixels);
    return heightMap;
}

void Planet::Save()
{
    ExportMesh(mesh.meshes[0], "src/planet.obj");
}

void Planet::LoadMesh()
{
}
