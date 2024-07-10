#include "planet.h"
Planet::Planet()
{
    resolution=50;
    image=LoadImage("src/topography(1).png");
    texture=LoadTexture("src/texture(1).png");
    heightScale=1;
    heightMapLoaded=false;
    mapLoaded=false;
    rotation=0;
    position={0,0,0};
    // mesh=planet3D.GenerateDisplacedSphere(5,24,24,heightMap,image.width,image.height,heightScale);
    changeResolution=resolution;
    changeHeightScale=heightScale;
}

// Planet::~Planet(){
//     // UnloadImage(image);
//     // UnloadTexture(texture);
//     UnloadMesh(mesh);
// }

void Planet::Update()
{
    if(!(image.data==NULL) && heightMapLoaded==false){
        heightMap=LoadHeightMap();
        heightMapLoaded=true;
    }
    if(mapLoaded==false && heightMap.size()!=0){
        mapLoaded=true;
    }
    if(((abs(changeResolution-resolution)>=0.01 || abs(changeHeightScale-heightScale)>=0.01) && mapLoaded==true) ||  (mesh.meshCount==0 && mapLoaded==true)){
        planet3D.GenerateDisplacedSphere(5.0,(int)resolution,(int)resolution,heightMap,image.width,image.height,heightScale);
        mesh=LoadModel("src/displaced_sphere.obj");
        // mesh.transform = MatrixRotateX(DEG2RAD * 45.0);
        // mesh.transform = MatrixRotateY(DEG2RAD * 45.0);
        if(texture.id!=0){
            mesh.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture=texture;
        }
        changeResolution=resolution;
        changeHeightScale=heightScale;
        std::cout<<resolution<<" "<<heightScale<<std::endl;
    }
}

void Planet::Draw()
{
    if(mesh.meshCount!=0){
        DrawModel(mesh,position,1.0f,WHITE);
    }
    DrawGrid(20,20);
    DrawSphere({15,0,0},2,WHITE);
}

void Planet::Gui()
{
    GuiLabel((Rectangle){ 100, 15, 150, 20 }, "Controls:");
    GuiSliderBar((Rectangle){ 100, 50, 150, 20 }, "Rotation", NULL, &rotation, 0, 10);
    GuiSliderBar((Rectangle){ 100, 70, 150, 20 }, "Resolution", NULL, &resolution, 20, 100);
    GuiSliderBar((Rectangle){ 100, 90, 150, 20 }, "Height Scale", NULL, &heightScale, 0.0f, 10.0f);
    GuiCheckBox((Rectangle){100,120,10,10},"RotateX",&planet3D.rotatex);
    GuiCheckBox((Rectangle){100,140,10,10},"RotateY",&planet3D.rotatey);
    GuiCheckBox((Rectangle){100,160,10,10},"RotateZ",&planet3D.rotatez);
}


void Planet::HandleInputs()
{
}

std::vector<float> Planet::LoadHeightMap()
{
    Color* pixels = LoadImageColors(image);

    std::vector<float> heightMap(image.width * image.height);
    for (int i = 0; i < image.width * image.height; i++) {
        heightMap[i] = pixels[i].r / 255.0f;  // Normalize height to 0.0 - 1.0
    }

    UnloadImageColors(pixels);
    std::ofstream outFile("src/heightmap.txt", std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file for writing: " << "src/heightmap.txt" << std::endl;
        // return;
    }

    // Write the size of the height map
    size_t size = heightMap.size();
    outFile.write(reinterpret_cast<const char*>(&size), sizeof(size_t));

    // Write the height map data
    outFile.write(reinterpret_cast<const char*>(heightMap.data()), size * sizeof(float));

    outFile.close();
    std::cout << "Height map exported successfully to: " << "src/heightmap.txt"<< std::endl;
    return heightMap;
}
