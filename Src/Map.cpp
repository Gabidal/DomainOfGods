#include "Map.h"

#include "Dependencies/TerGen.h"
#include "Entity.h"
#include "Globals.h"

#include "Chaos.h"
#include "../UI/Render.h"


using namespace TerGen; 

namespace MAP{

    inline unordered_map<IVector3, Tile, IVector3> Tiles;
    inline TerGen::Generator* Terrain_Generator;

    vector<Tile*> Get_Chunk_Content(IVector3 position){
        return Tiles[position].Content;
    }

    Tile::Tile(Location position){
        Position = position;
        ID = 0;
    }

    int Normalize_Tile_Elevation(float Y) {
        int Normalized_Y = (abs(Y) * (int)RENDER::Tile_Textures.size());

        int Offset_Y = (Normalized_Y % (int)RENDER::Tile_Textures.size());

        return Offset_Y;
    }

    vector<Tile*> Get_Surrounding_Content(IVector3 position){
        vector<Tile*> Result;
        
        for (auto chunk_position : CHAOS::Get_Surrounding_Positions(position)){
            vector<Tile*> tmp = Get_Chunk_Content(chunk_position);

            Result.insert(Result.end(), tmp.begin(), tmp.end());
        }

        return Result;
    }

    vector<Tile*> Get_Surrounding_Content(IVector3 position, int Distance){
        vector<Tile*> Result;
        
        for (auto chunk_position : CHAOS::Get_Surrounding_Positions(position, Distance)){
            vector<Tile*> tmp = Get_Chunk_Content(chunk_position);

            Result.insert(Result.end(), tmp.begin(), tmp.end());
        }

        return Result;
    }

    void Init_TerGen(){
        Terrain_Generator = new TerGen::Generator();
    }

    void Save_Map([[maybe_unused]] string file){

        
    }

    bool Load_Map([[maybe_unused]] string file){

        return false;

    }

    void Make_Map(){
        // generate for the few chunks up ahead.
        for (auto pos : CHAOS::Get_Surrounding_Positions(GLOBALS::CAMERA, 5)){
            Tile* Current_Chunk = new Tile({{}, pos});

            for (int Y = 0; Y < GLOBALS::CHUNK_HEIGHT; Y++){
                for (int X = 0; X < GLOBALS::CHUNK_WIDTH; X++){
                    // get the tile from the generator
                    Tile* Current_Tile = new Tile({{(float)X, (float)Y, 0}, pos});

                    // global positions
                    int Global_Y = Y + pos.Y * GLOBALS::CHUNK_HEIGHT;
                    int Global_X = X + pos.X * GLOBALS::CHUNK_WIDTH;

                    // get the elevation from the generator
                    float Elevation = TerGen::Warp_Noise({Global_X, Global_Y}, Terrain_Generator);

                    // get the texture from the generator
                    int Texture = Normalize_Tile_Elevation(Elevation);

                    // set the texture
                    Current_Tile->ID = Texture;

                    // add the tile to the chunk
                    Current_Chunk->Content.push_back(Current_Tile);
                }
            }

            // add the chunk to the map
            Tiles[pos] = *Current_Chunk;
        }
    }

    // Inits everything related to TerGen and saves
    void Init(){
        Init_TerGen();

        // if there is no previus run made, make a new world
        if (!Load_Map("Default.sv")){

            Make_Map();
            Save_Map("Default.sv");
        }
    }

}