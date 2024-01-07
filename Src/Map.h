#ifndef _MAP_H_
#define _MAP_H_

#include "Entity.h"

#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

namespace GGUI{
    class RGB;
}

namespace MAP{

    class Tile{
    public:
        // Chunk coordination if an single tile represents a whole chunk.
        // HIGH coordination for detailed chunk mapping inside other tiles. 
        Location Position;

        int ID = 0;
        float Elevation = 0.0f;
        float Humidity = 0.0f;
        float Temperature = 0.0f;

        vector<Tile*> Content;

        Tile() = default;
        Tile(Location position);
    };

    extern unordered_map<IVector3, Tile, IVector3> Tiles;

    extern void Init_TerGen();

    extern void Init();

    extern void Save_Map();
    extern bool Load_Map(string file);

    extern vector<Tile*> Get_Surrounding_Content(IVector3 position, int Distance = 1);

    extern FVector3 Get_Relative_Position_To_Camera(Location position);

    extern GGUI::RGB Get_Tint(float Elevation, float Humidity, float Temperature);

    extern constexpr void Init_Tint_Map();

    // Linear interpolation function
    template<typename T>
    constexpr T lerp(T a, T b, T t) {
        // Clamp t between a and b
        return a + t * (b - a);
    }
}

#endif