#include <iostream>

#include "Src/Entity.h"
#include "Src/Globals.h"
#include "Src/Map.h"

#include "UI/Render.h"

using namespace std;

int main(){
    GLOBALS::Init_Globals();

    MAP::Init();

    Init_Render();

    Render_Tick();

    _sleep(INT32_MAX);
    return 0;    
}

