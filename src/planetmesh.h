#pragma once
#include "raylib.h"
#include <vector>
#include <cmath>
#include <raymath.h>
#include <iostream>
class PlanetMesh{
    public:
        PlanetMesh();
        Vector3 RotateX(Vector3 v, float angle);
        Vector3 RotateY(Vector3 v, float angle);
        Vector3 RotateZ(Vector3 v, float angle); 
        bool rotatex,rotatey,rotatez;
        void GenerateDisplacedSphere(float radius, int rings, int slices, const std::vector<float>& heightMap, int mapWidth, int mapHeight, float heightScale);
    private:

};