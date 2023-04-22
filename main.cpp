#include <iostream>

#include "Src/Entity.h"
#include "Src/Globals.h"
#include "Src/Map.h"

#include "UI/Render.h"

#include "Dependencies/raylib.h"

using namespace std;

int main(){    
    GLOBALS::Init_Globals();

    RENDER::Init();

    MAP::Init();

    RENDER::Update_Frame();

    _sleep(INT32_MAX);
    
    RENDER::Close();
    
    return 0;    
}

