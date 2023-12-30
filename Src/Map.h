#ifndef _MAP_H_
#define _MAP_H_

#include "Entity.h"

#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

namespace MAP{

    class Tile{
    public:
        // Chunk coordination if an single tile represents a whole chunk.
        // HIGH coordination for detailed chunk mapping inside other tiles. 
        Location Position;

        int ID = 0; // Also used as elevation information.
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

    FVector3 Get_Relative_Position_To_Camera(Location position);
}

#endif