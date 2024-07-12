#pragma once
#include "raylib.h"
#include <iostream>
#include <string.h>
// #include "raygui/src/raygui.h"
#include <src/common.h>
#include <raymath.h>
#include<cmath>

class Clouds{
    public:
        Clouds(const char* filename="",int start=0,int end=0,bool reverse=false);
        void Update();
        void Draw();
        void Gui();
        bool hide;
    private:
        void CloudTexture();
        float rotationSpeed;
        Model model;
        float changeRadius,changeSlices,changeRings;
        void RandomCloudMapGenerator();
        float lastTimeUpdate;
        Image image;
        int iterationPos;
        int direction;
        int end;
        int start;
        bool reverse;
        std::string filename;
        float radius,rings,slices;
        float rotation;
};