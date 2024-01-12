#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "../Dependencies/TerGen.h"

class IVector3;
class Location;

namespace GLOBALS{

    extern TerGen::Generator* Value_Noise;

    extern void Init_Globals();

    extern bool DEBUG;

    extern const int UPDATE_DISTANCE_WIDTH;
    extern const int UPDATE_DISTANCE_HEIGHT;

    extern const int RENDER_DISTANCE_WIDTH;
    extern const int RENDER_DISTANCE_HEIGHT;

    extern const double ENTITY_DENSITY;
    extern const float MAX_LUCK_PERCENTAGE;

    extern const int CHUNK_WIDTH;
    extern const int CHUNK_HEIGHT;
    extern const int CHUNK_DEPTH;

    extern Location CAMERA;
    extern const int WINDOW_WIDTH;
    extern const int WINDOW_HEIGHT;

    extern const float TICK_LENGTH;
    extern const float SECOND;
    extern const float TICK_DELTA;

    extern class Entity* Focus;

    extern const unsigned char ANIMATION_FRAME_COUNT;

    extern float Tint_Alpha;

    extern float Biome_Alpha;

    extern const double PI;
}

#endif