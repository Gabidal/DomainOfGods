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
        void* Sprite;

        vector<Tile*> Content;

        Tile() = default;
        Tile(Location position);
    };

    extern vector<Tile> Tiles;

    extern void Init_TerGen();

    extern void Init();

    extern void Save_Map();
    extern void Load_Map(string file);

}

#endif