#include "clouds.h"

Clouds::Clouds(const char *filename, int start, int end, bool reverse)
{
    changeRadius= radius=6.0;
    changeRings= rings=25;
    changeSlices= slices=25;
    rotationSpeed=0.0;
    lastTimeUpdate=0.0;
    iterationPos=start;
    this->start=start;
    this->end=end;
    this->reverse=reverse;
    direction=1;
    this->filename=filename;
    hide=false;
    rotation=0;
    model=LoadModelFromMesh(GenMeshSphere(radius,(int)rings,(int)slices));
}

void Clouds::Update(){
    if(abs(changeRadius-radius)>=0.1 || abs(changeRings-rings)>=0.1||abs(changeSlices-slices)>=0.1){
        model=LoadModelFromMesh(GenMeshSphere(radius,(int)rings,(int)slices));
        changeRadius=radius;
        changeRings=rings;
        changeSlices=slices;
    }
    if(GetTime()-lastTimeUpdate>=0.1){
        if(iterationPos<start || iterationPos>end){
            if(reverse==true){
                direction=-direction;
            }
            iterationPos+=direction;
        }
        char fileNumber[64];
        std::sprintf(fileNumber, "%d.png", iterationPos); // Assuming files are named clouds_00.png, clouds_01.png, etc.
        image=LoadImage((filename+fileNumber).c_str());
        ImageRotateCCW(&image);
        ImageFlipVertical(&image);
        model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture=LoadTextureFromImage(image);
        iterationPos+=direction;
        lastTimeUpdate=GetTime();
        // std::cout<<filename<<std::endl;
        model.transform= MatrixMultiply(MatrixRotateZ(rotation), MatrixTranslate(0,0,0));
        rotation+=rotationSpeed;
    }
}

void Clouds::Draw(){
    DrawModel(model,{0,0,0},1.0,WHITE);
}

void Clouds::CloudTexture()
{
    
}

void Clouds::RandomCloudMapGenerator()
{
}

void Clouds::Gui()
{
    GuiLabel((Rectangle){275, 30, 150, 20}, "Cloud Controls:");
    GuiSliderBar((Rectangle){275, 70, 100, 20}, "Radius", NULL, &radius, 5,10);
    GuiSliderBar((Rectangle){275, 90, 100, 20}, "Slices", NULL, &slices, 10, 100);
    GuiSliderBar((Rectangle){275, 110, 100, 20}, "Rings", NULL, &rings, 10, 100);
    GuiSliderBar((Rectangle){275, 130, 100, 20}, "Rotation", NULL, &rotationSpeed, 0.0, 0.5);
    GuiCheckBox((Rectangle){275,150,20,20},"Hide",&hide);
}