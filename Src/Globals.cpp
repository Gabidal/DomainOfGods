#include "Globals.h"

#include <iostream>

using namespace std;

namespace GLOBALS{
    TerGen::Generator* Value_Noise = nullptr;

    int MIN_POWER = 1;
    int MAX_POWER = 10;

    void Init_Globals(){
        srand(time(NULL));

        Value_Noise = new TerGen::Generator();
    }

    bool DEBUG = true;

    int UPDATE_DISTANCE_X = 100;
    int UPDATE_DISTANCE_Y = 100;

    int RENDER_DISTANCE_X = 100;
    int RENDER_DISTANCE_Y = 100;

    int WORLD_WIDTH = 100;
    int WORLD_HEIGHT = 100;

    float ENTITY_DENSITY = 0.1f;

    int CHUNK_WIDTH = 100;
    int CHUNK_HEIGHT = 100;
    int CHUNK_DEPTH = 100;

    float CAMERA_X = WORLD_WIDTH / 2;
    float CAMERA_Y = WORLD_HEIGHT / 2;
}

