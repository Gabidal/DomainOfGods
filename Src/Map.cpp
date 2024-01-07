#include "Map.h"

#include "Dependencies/TerGen.h"
#include "Entity.h"
#include "Globals.h"

#include "Chaos.h"
#include "./UI/Models.h"

#include "../Dependencies/GGUI.h"

#include <cmath>
#include <numeric>

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

        double FREQ = 0.001;
        double AMP = 0.01;
        double LAC = 4.0;
        double PERS = 0.5;
        double SED = 1.0;
        double FMB_OCT = 4.0;
        double WARP_OCT = 2.0;

        Elevation_Generator = new TerGen::Generator(
            FREQ,
            AMP,
            LAC,
            PERS,
            SED,
            FMB_OCT,
            WARP_OCT
        );

        Humidity_Generator = new TerGen::Generator(
            FREQ * 10,
            AMP,
            LAC * 0.1,
            PERS * 0.5,
            SED,
            FMB_OCT,
            WARP_OCT
        );

        Temperature_Generator = new TerGen::Generator(
            FREQ * 10,
            AMP,
            LAC * 0.1,
            PERS * 0.5,
            SED,
            FMB_OCT,
            WARP_OCT
        );
    }

    void Save_Map([[maybe_unused]] string file){

        
    }

    bool Load_Map([[maybe_unused]] string file){

        return false;

    }

    double Sigmoid(double x)
    {
        return 1.0 / (1.0 + std::exp(-x));
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

                    // Make sure the Elevation, Humidity and Temperature are at most, 1, and at least -1. But not clamping with minmax.
                    // Use logaritm to make the values more interesting.
                    Elevation = Sigmoid(Elevation);
                    Humidity = Sigmoid(Humidity);
                    Temperature = Sigmoid(Temperature);

                    Current_Tile->Elevation = Elevation;

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
        Init_Tint_Map();

        // if there is no previus run made, make a new world
        if (!Load_Map("Default.sv")){

            Make_Map();
            Save_Map("Default.sv");
        }
    }

    GGUI::RGB Get_Tint(float Elevation, float Humidity, float Temperature){
        // transform the floats into a unsigned chars, 
        // so we can use them as indexes for the tint map.
        unsigned char Elevation_Index = (unsigned char)(Elevation * UCHAR_MAX);
        unsigned char Humidity_Index = (unsigned char)(Humidity * UCHAR_MAX);
        unsigned char Temperature_Index = (unsigned char)(Temperature * UCHAR_MAX);

        // get the tint from the tint map
        return TINT_MAP[Temperature_Index * UCHAR_MAX * UCHAR_MAX + Elevation_Index * UCHAR_MAX + Humidity_Index];
    }

    constexpr void Apply_Tint(GGUI::RGB& A, GGUI::RGB B, float Alpha){
        A.R = (unsigned char)(A.R * (1 - Alpha) + B.R * Alpha);
        A.G = (unsigned char)(A.G * (1 - Alpha) + B.G * Alpha);
        A.B = (unsigned char)(A.B * (1 - Alpha) + B.B * Alpha);
    }

    constexpr GGUI::RGB Lerp(GGUI::RGB A, GGUI::RGB B, unsigned char Distance){
        GGUI::RGB Result;

        Result.R = MAP::lerp<float>(A.R, B.R, (float)Distance / 255);
        Result.G = MAP::lerp<float>(A.G, B.G, (float)Distance / 255);
        Result.B = MAP::lerp<float>(A.B, B.B, (float)Distance / 255);

        return Result;
    }

    constexpr void Init_Tint_Map(){
        // Order of accessors: Width/X = Humidity, Height/Y = Elevation, Depth/Z = Temperature

        // MAPPINGS:
        /*
        
            Temperature Gradient, where Temperature 0 = RGB(0, 0, 0) and Temperature 255 = RGB(255, 255, 255)
            This means a plane at X&Y plane, {0-255, 0-255, 0} is black and {0-255, 0-255, 255} is white.
        
            Humidity Gradient, where Humidity 0 = RGB(0, 255, 255) and Humidity 255 = RGB(0, 0, 255)
            This means a plane at Y&Z plane, {0, 0-255, 0-255} is yellow and {255, 0-255, 0-255} is blue.

        */

       float Alpha = 0.4;   // Each tint can only contribute 10% to the tint map.

        for (unsigned char Temperature = 0; Temperature < UCHAR_MAX; Temperature++){
            for (unsigned char Elevation = 0; Elevation < UCHAR_MAX; Elevation++){
                for (unsigned char Humidity = 0; Humidity < UCHAR_MAX; Humidity++){
                    GGUI::RGB Current_Tint;

                    // Apply the Temperature Tint.
                    // Since the temperature is already the gradient from 0-255 we dont need to calculate anything.
                    GGUI::RGB Temperature_Tint = {Temperature, Temperature, Temperature};
                    Apply_Tint(Current_Tint, Temperature_Tint, Alpha);

                    // Apply the Humidity Tint.
                    // We need to lerp between the yellow and blue colors.
                    GGUI::RGB Humidity_Tint = Lerp({0, 0, 255}, {0, 255, 255}, Humidity);
                    Apply_Tint(Current_Tint, Humidity_Tint, Alpha);

                    Apply_Tint(TINT_MAP[Temperature * UCHAR_MAX * UCHAR_MAX + Elevation * UCHAR_MAX + Humidity], Current_Tint, Alpha);
                }
            }
        }

    }

}