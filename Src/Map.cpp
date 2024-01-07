#include "Map.h"

#include "Dependencies/TerGen.h"
#include "Entity.h"
#include "Globals.h"

#include "Chaos.h"
#include "./UI/Models.h"

#include "../Dependencies/GGUI.h"

using namespace TerGen; 

namespace MAP{

    inline unordered_map<IVector3, Tile, IVector3> Tiles;
    TerGen::Generator* Elevation_Generator;
    TerGen::Generator* Humidity_Generator;
    TerGen::Generator* Temperature_Generator;

    GGUI::RGB TINT_MAP[UCHAR_MAX * UCHAR_MAX * UCHAR_MAX] = {};

    vector<Tile*> Get_Chunk_Content(IVector3 position){
        return Tiles[position].Content;
    }

    FVector3 Get_Relative_Position_To_Camera(Location position){
        int Tile_Width = 1;
        int Tile_Height = 1;

        int Tile_Position_Y = position.HIGH.Y * Tile_Height;
        int Tile_Position_X = position.HIGH.X * Tile_Width;

        int Chunk_Position_Y = position.CHUNK.Y * GLOBALS::CHUNK_HEIGHT * Tile_Height;
        int Chunk_Position_X = position.CHUNK.X * GLOBALS::CHUNK_WIDTH * Tile_Width;

        int Camera_Position_Y = GLOBALS::CAMERA.Y * GLOBALS::CHUNK_HEIGHT * Tile_Height;
        int Camera_Position_X = GLOBALS::CAMERA.X * GLOBALS::CHUNK_WIDTH * Tile_Width;

        float Relative_Y = Tile_Position_Y + Chunk_Position_Y - Camera_Position_Y;
        float Relative_X = Tile_Position_X + Chunk_Position_X - Camera_Position_X;

        return FVector3{Relative_X, Relative_Y, 0.f};
    }

    Tile::Tile(Location position){
        Position = position;
        ID = 0;
    }

    int Normalize_Tile_Elevation(float Y) {
        return Normalize_Float_To_Model_Index(Y, MODEL_TYPE::TILE);
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
        Elevation_Generator = new TerGen::Generator();
        Humidity_Generator = new TerGen::Generator();
        Temperature_Generator = new TerGen::Generator();
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
                    float Elevation = TerGen::Warp_Noise({Global_X, Global_Y}, Elevation_Generator);
                    
                    // get the humidity from the generator
                    float Humidity = TerGen::Warp_Noise({Global_X, Global_Y}, Humidity_Generator);

                    // get the temperature from the generator
                    float Temperature = TerGen::Warp_Noise({Global_X, Global_Y}, Temperature_Generator);

                    // get the texture from the generator
                    int Texture = Normalize_Tile_Elevation(Elevation);

                    // set the texture
                    Current_Tile->ID = Texture;

                    // set the humidity
                    Current_Tile->Humidity = Humidity;

                    // set the temperature
                    Current_Tile->Temperature = Temperature;

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

    GGUI::RGB Get_Tint(float Elevation, float Humidity, float Temperature){



    }

    constexpr void Init_Tint_Map(){
        // Order of accessors: Width = Humidity, Depth = Temperature, Height = Elevation
        GGUI::RGB Lerp_Seeds[UCHAR_MAX] = {};
        int Current_Lerp_Seed_Index = 0;

        for (unsigned char Humidity = 0; Humidity < UCHAR_MAX; Humidity++){
            for (unsigned char Temperature = 0; Temperature < UCHAR_MAX; Temperature++){
                for (unsigned char Elevation = 0; Elevation < UCHAR_MAX; Elevation++){
                    
                    // When its dry and hot its yellow, elevation wont affect
                    


                    
                }
            }
        }

    }

}