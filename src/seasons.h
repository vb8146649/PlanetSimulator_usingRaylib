#pragma once
#include "raylib.h"
#include "common.h"
#include <iostream>
#include<string.h>
class Seasons{
    public:
        Seasons(const char * filename="",int start=0,int end=0,bool reverse=false);
        void Update(Model &model);
        bool hide;
        std::string filename;
        void Gui();
    private:
        Image image;
        int iterationPos;
        int start;
        int end;
        bool reverse;
        float lastTimeUpdate;
        int direction;
};