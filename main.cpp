#include <iostream>

#include "Src/Entity.h"
#include "Src/Globals.h"
#include "Src/Map.h"
#include "Src/Chaos.h"

#include "UI/Render.h"

#include "Dependencies/raylib.h"

using namespace std;

int main(){    
    GLOBALS::Init_Globals();

    RENDER::Init();
    CHAOS::Init();

    MAP::Init();

    while(true){

        RENDER::Update_Frame();
        CHAOS::Tick();

    }

    _sleep(INT32_MAX);
    
    RENDER::Close();
    
    return 0;    
}

