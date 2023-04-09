#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "../Dependencies/TerGen.h"

namespace GLOBALS{

    extern TerGen::Generator* Value_Noise;

    extern void Init_Globals();

    extern int MIN_POWER;
    extern int MAX_POWER;

    extern bool DEBUG;

    extern int UPDATE_DISTANCE_X;
    extern int UPDATE_DISTANCE_Y;

    extern int RENDER_DISTANCE_X;
    extern int RENDER_DISTANCE_Y;

    extern int WORLD_WIDTH;
    extern int WORLD_HEIGHT;

    extern float ENTITY_DENSITY;

    extern int CHUNK_WIDTH;
    extern int CHUNK_HEIGHT;
    extern int CHUNK_DEPTH;

    extern float CAMERA_X;
    extern float CAMERA_Y;
}

#endif