#pragma once
#include "raylib.h"
#include <raygui/src/raygui.h>
#include "planetmesh.h"
#include <vector>
#include <raymath.h>
#include <fstream>
#include <iostream>
#include "impmeshcodes.h"

class Planet{
    public:
        Planet();
        void Update();
        void Draw();
        void Gui();
        void HandleInputs();
        std::vector<float> LoadHeightMap();
        Model mesh;
    private:
        float changeResolution;
        float changeHeightScale;
        float changexOffset;
        float rotation;
        float resolution;
        float heightScale;
        Image topography;
        Image textureImage;
        Texture2D texture;
        std::vector<float> heightMap;
        PlanetMesh planet3D;
        ImpMeshC impmeshc;
        Vector3 position;
        bool mapLoaded;
        bool heightMapLoaded;
        Shader shader;
        float initialHeight;
        float radius;
        float changeRadius;
        float changeInitialHeight;
};