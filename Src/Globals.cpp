#include "Globals.h"

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

    const int CHUNK_WIDTH = 100;
    const int CHUNK_HEIGHT = 100;
    const int CHUNK_DEPTH = 100;

    // Center as {0, 0}
    float CAMERA_X = 0;
    float CAMERA_Y = 0;
}

