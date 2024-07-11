#pragma once
#include "raylib.h"
#include <vector>
#include <cmath>
#include <raymath.h>
#include <iostream>

class ImpMeshC{
    public:
        ImpMeshC();
        void AdjustUVCoordinates(Mesh &mesh, float xOffset, float yOffset);
        void AdjustTextureCoordinates(Mesh &mesh);
        void RotateTextureCoordinates90(Mesh &mesh);
        void TransposeTextureCoordinates(Mesh &mesh);
        Vector3 RotateX(Vector3 v, float angle);
        Vector3 RotateY(Vector3 v, float angle);
        Vector3 RotateZ(Vector3 v, float angle);

    private:
        int changeRotationX;
        int changeRotationY;
        int changeRotationZ;
};