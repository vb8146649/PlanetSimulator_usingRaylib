#pragma once
#include "raylib.h"
// #include <raygui/src/raygui.h>
#include <src/common.h>
#include "planetmesh.h"
#include <vector>
#include <raymath.h>
#include <fstream>
#include <iostream>
#include "impmeshcodes.h"
#include <string.h>
#include "clouds.h"
#include "seasons.h"

class Planet{
    public:
        Planet(std::string topographymap,std::string texturemap,std::string cloudmaploc,std::string seasonsmaploc);
        void Update();
        void Draw();
        void Gui();
        void HandleInputs();
        Model mesh;
        int frame;
        float lastUpdateTime;
        bool hide;
        Clouds clouds;
        Seasons season;
    private:
        std::vector<float> LoadHeightMap();
        float changeResolution;
        void Save();
        void LoadMesh();
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
        bool isTopoColor;
};