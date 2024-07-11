#include "planet.h"
Planet::Planet()
{
    // topography
    topography=LoadImage("src/moonbump2k.png");
    ImageRotateCCW(&topography);
    ImageFlipVertical(&topography);

    // texture
    textureImage=LoadImage("src/moonmap2k.png");
    ImageRotateCCW(&textureImage);
    texture=LoadTextureFromImage(textureImage);
    
    // initialization
    heightScale=1;
    initialHeight=0;
    radius=5;
    resolution=25;
    heightMapLoaded=false;
    mapLoaded=false;
    position={0,0,0};
    changeResolution=resolution;
    changeHeightScale=heightScale;
    changexOffset=planet3D.xOffset;

    // shader
    shader = LoadShader("raylib/examples/shaders/resources/shaders/glsl100/base.vs", "raylib/examples/shaders/resources/shaders/glsl100/base.fs");
}

void Planet::Update()
{
    if(!(topography.data==NULL) && heightMapLoaded==false){
        heightMap=LoadHeightMap();
        heightMapLoaded=true;
    }
    if(mapLoaded==false && heightMap.size()!=0){
        mapLoaded=true;
    }
    if(((abs(changeResolution-resolution)>=0.01 || abs(changeHeightScale-heightScale)>=0.01) ||  (mesh.meshCount==0) ||  abs(changeRadius-radius)>=0.01 || abs(changeInitialHeight-initialHeight)>=0.01) && mapLoaded==true) {
        planet3D.GenerateDisplacedSphere(radius,(int)resolution,(int)resolution,heightMap,topography.width,topography.height,heightScale,initialHeight);
        mesh=LoadModel("src/displaced_sphere.obj");
        if(texture.id!=0){
            mesh.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture=texture;
        }
        if(shader.id!=0){
            mesh.materials[0].shader = shader;
        }
        
        changeResolution=resolution;
        changeHeightScale=heightScale;
        changeRadius=radius;
        changeInitialHeight=initialHeight;
        std::cout<<resolution<<" "<<heightScale<<std::endl;
    }
}

void Planet::Draw()
{
    if(mesh.meshCount!=0){
        DrawModel(mesh,position,1.0f,WHITE);
    }
    DrawLine3D((Vector3){-10.0f, 0.0f, 0.0f}, (Vector3){10.0f, 0.0f, 0.0f}, RED);   // X-axis (red)
    DrawLine3D((Vector3){0.0f, -10.0f, 0.0f}, (Vector3){0.0f, 10.0f, 0.0f}, GREEN); // Y-axis (green)
    DrawLine3D((Vector3){0.0f, 0.0f, -10.0f}, (Vector3){0.0f, 0.0f, 10.0f}, BLUE); // Z-axis (blue)
}

void Planet::Gui()
{
    GuiLabel((Rectangle){ 100, 15, 150, 20 }, "Controls:");
    GuiSliderBar((Rectangle){ 100, 70, 150, 20 }, "Resolution", NULL, &resolution, 20, 250);
    GuiSliderBar((Rectangle){ 100, 90, 150, 20 }, "Height Scale", NULL, &heightScale, 0.0f, 10.0f);
    GuiSliderBar((Rectangle){ 100, 110, 150, 20 }, "InitialHeight Scale", NULL, &initialHeight, 0.0f, 4.0f);
    GuiSliderBar((Rectangle){ 100, 130, 150, 20 }, "Radius", NULL, &radius, 5.0f, 10.0f);
}


void Planet::HandleInputs()
{

}

std::vector<float> Planet::LoadHeightMap()
{
    Color* pixels = LoadImageColors(topography);

    std::vector<float> heightMap(topography.width * topography.height);
    for (int i = 0; i < topography.width * topography.height; i++) {
        heightMap[i] = pixels[i].r / 255.0f;  // Normalize height to 0.0 - 1.0
    }

    UnloadImageColors(pixels);
    std::ofstream outFile("src/heightmap.txt", std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file for writing: " << "src/heightmap.txt" << std::endl;
    }

    size_t size = heightMap.size();
    outFile.write(reinterpret_cast<const char*>(&size), sizeof(size_t));

    outFile.write(reinterpret_cast<const char*>(heightMap.data()), size * sizeof(float));

    outFile.close();
    std::cout << "Height map exported successfully to: " << "src/heightmap.txt"<< std::endl;
    return heightMap;
}
