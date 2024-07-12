#include "seasons.h"

Seasons::Seasons(const char *filename, int start, int end, bool reverse)
{
    this->filename = filename;
    this->start = start;
    this->end = end;
    this->reverse = reverse;
    hide = false;
    lastTimeUpdate = 0.0;
    direction = 1;
    iterationPos=start;
}

void Seasons::Update(Model &model)
{
    if (!hide)
    {
        if (GetTime() - lastTimeUpdate >= 0.3)
        {
            if (iterationPos < start || iterationPos > end)
            {
                if (reverse == true)
                {
                    direction = -direction;
                }else{
                    iterationPos%=(end-start);
                    iterationPos+=start;
                }
                iterationPos += direction;
            }
            char fileNumber[64];
            std::sprintf(fileNumber, "%d.png", iterationPos); // Assuming files are named clouds_00.png, clouds_01.png, etc.
            image = LoadImage((filename + fileNumber).c_str());
            ImageRotateCCW(&image);
            if(model.meshCount!=0){
                model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = LoadTextureFromImage(image);
            }
            iterationPos += direction;
            lastTimeUpdate = GetTime();
        }
    }
}

void Seasons::Gui()
{
    GuiLabel((Rectangle){475, 30, 150, 20}, "Seasons Controls:");
    GuiCheckBox((Rectangle){475, 60, 20, 20}, "Hide", &hide);
}
