#pragma once
#include "raylib.h"
#include <raygui/src/raygui.h>
#include "planetmesh.h"
#include <vector>
#include <raymath.h>
#include <fstream>
#include <iostream>

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
        float rotation;
        float resolution;
        float heightScale;
        Image image;
        Texture2D texture;
        std::vector<float> heightMap;
        PlanetMesh planet3D;
        Vector3 position;
        bool mapLoaded;
        bool heightMapLoaded;
};