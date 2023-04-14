#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "../Dependencies/TerGen.h"

namespace GLOBALS{

    extern TerGen::Generator* Value_Noise;

    extern void Init_Globals();

    extern bool DEBUG;

    extern const int UPDATE_DISTANCE_WIDTH;
    extern const int UPDATE_DISTANCE_HEIGHT;

    extern const int RENDER_DISTANCE_WIDTH;
    extern const int RENDER_DISTANCE_HEIGHT;

    extern const float ENTITY_DENSITY;
    extern const float MAX_LUCK_PERCENTAGE;

    extern const int CHUNK_WIDTH;
    extern const int CHUNK_HEIGHT;
    extern const int CHUNK_DEPTH;

    extern float CAMERA_X;
    extern float CAMERA_Y;
}

#endif