#include "Globals.h"
#include "Entity.h"

#include <iostream>

using namespace std;

namespace GLOBALS{
    TerGen::Generator* Value_Noise = nullptr;

    void Init_Globals(){
        srand(time(NULL));

        Value_Noise = new TerGen::Generator();
    }

    bool DEBUG = true;

    const int UPDATE_DISTANCE_WIDTH = 100;
    const int UPDATE_DISTANCE_HEIGHT = 100;

    const int RENDER_DISTANCE_WIDTH = 100;
    const int RENDER_DISTANCE_HEIGHT = 100;

    const float ENTITY_DENSITY = 0.1f;
    constexpr float MAX_LUCK_PERCENTAGE = 0.75f;

    const int CHUNK_WIDTH = 10;
    const int CHUNK_HEIGHT = 10;
    const int CHUNK_DEPTH = 10;

    // Center as {0, 0}
    IVector3 CAMERA = {0, 0, 0};

    const int WINDOW_WIDTH = 1080;
    const int WINDOW_HEIGHT = 1920;


}

