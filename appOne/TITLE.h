#pragma once
#include "SCENE.h"
class TITLE :
    public SCENE
{
public:
    TITLE(class GAME* game) : SCENE(game) {}
    void init();
    void draw();
    void nextScene();

};

