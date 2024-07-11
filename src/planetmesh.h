#pragma once
#include "raylib.h"
#include <vector>
#include <cmath>
#include <raymath.h>
#include <iostream>
class PlanetMesh{
    public:
        PlanetMesh();
        float rotatex,rotatey,rotatez;
        float xOffset;
        float yOffset;
        void GenerateDisplacedSphere(float radius, int rings, int slices, const std::vector<float>& heightMap, int mapWidth, int mapHeight, float heightScale,float initialHeight);
    private:

};