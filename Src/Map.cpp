#include "Map.h"

#include "Dependencies/TerGen.h"
#include "Entity.h"
#include "Globals.h"

#include "Chaos.h"
#include "./UI/Models.h"

#include "../Dependencies/GGUI.h"

#include <cmath>
#include <numeric>
#include <array>
#include <float.h>

using namespace TerGen; 

namespace MAP{

    inline unordered_map<IVector3, Tile, IVector3> Tiles;
    TerGen::Generator* Elevation_Generator;
    TerGen::Generator* Humidity_Generator;
    TerGen::Generator* Temperature_Generator;
    TerGen::Generator* Particle_Generator;

    GGUI::RGB TINT_MAP[UCHAR_MAX * UCHAR_MAX * UCHAR_MAX] = {};

    GGUI::RGB BIOME_MAP[UCHAR_MAX * UCHAR_MAX * UCHAR_MAX] = {};

    double Sigmoid(double x)
    {
        return 1.0 / (1.0 + std::exp(-x));
    }

    vector<Tile*> Get_Chunk_Content(IVector3 position){
        // check if the chunk exists
        if (Tiles.find(position) != Tiles.end())
            return Tiles[position].Content;

        // generate new chunk now that we know that the queried chunk doesn't exists
        Tile* Current_Chunk = new Tile({{}, position});
    
        for (int Y = 0; Y < GLOBALS::CHUNK_HEIGHT; Y++){
            for (int X = 0; X < GLOBALS::CHUNK_WIDTH; X++){
                // get the tile from the generator
                Tile* Current_Tile = new Tile({{(float)X, (float)Y, 0}, position});

                // global positions
                int Global_Y = Y + position.Y * GLOBALS::CHUNK_HEIGHT;
                int Global_X = X + position.X * GLOBALS::CHUNK_WIDTH;

                // get the elevation from the generator
                float Elevation = TerGen::Warp_Noise({Global_X, Global_Y}, Elevation_Generator);
                
                // get the humidity from the generator
                float Humidity = TerGen::Warp_Noise({Global_X, Global_Y}, Humidity_Generator);

                // get the temperature from the generator
                float Temperature = TerGen::Warp_Noise({Global_X, Global_Y}, Temperature_Generator);

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

                Current_Tile->Effect = Generate_Particle(Elevation, Humidity, Temperature, Current_Tile->Position);

                // add the tile to the chunk
                Current_Chunk->Content.push_back(Current_Tile);
            }
        }

        // add the chunk to the map
        Tiles[position] = *Current_Chunk;

        return Current_Chunk->Content;
    }

    FVector3 Get_Relative_Position_To_Camera(Location position){
        int Tile_Width = 1;
        int Tile_Height = 1;

        int Tile_Position_Y = position.HIGH.Y * Tile_Height;
        int Tile_Position_X = position.HIGH.X * Tile_Width;

        int Chunk_Position_Y = position.CHUNK.Y * GLOBALS::CHUNK_HEIGHT * Tile_Height;
        int Chunk_Position_X = position.CHUNK.X * GLOBALS::CHUNK_WIDTH * Tile_Width;

        int Camera_Position_Y = GLOBALS::CAMERA.CHUNK.Y * GLOBALS::CHUNK_HEIGHT + GLOBALS::CAMERA.HIGH.Y * Tile_Height;
        int Camera_Position_X = GLOBALS::CAMERA.CHUNK.X * GLOBALS::CHUNK_WIDTH + GLOBALS::CAMERA.HIGH.X * Tile_Width;

        float Relative_Y = Tile_Position_Y + Chunk_Position_Y - Camera_Position_Y;
        float Relative_X = Tile_Position_X + Chunk_Position_X - Camera_Position_X;

        return FVector3{Relative_X, Relative_Y, 0.f};
    }

    Tile::Tile(Location position) : Effect(position){
        Position = position;
        ID = 0;
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

    Tile* Get_Tile(Location location){
        location.Update_Chunk_Location();

        unsigned int Internal_Index = location.HIGH.Y * GLOBALS::CHUNK_HEIGHT + location.HIGH.X;

        vector<Tile*> childs = Get_Chunk_Content(location.CHUNK);

        if (Internal_Index >= childs.size())
            return nullptr;

        return childs[Internal_Index];
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
            AMP * 10,
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
            PERS * 0.55,
            SED,
            FMB_OCT,
            WARP_OCT
        );

        Particle_Generator = new TerGen::Generator(
            FREQ * 10,
            AMP,
            LAC,
            PERS,
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

    void Make_Map(){
        // generate for the few chunks up ahead.
        for (auto pos : CHAOS::Get_Surrounding_Positions(GLOBALS::CAMERA.CHUNK, 5)){
            vector<Tile*> tmp = Get_Chunk_Content(pos);

            // check if the chunk generation failed.
            if (tmp.size() == 0)
                GGUI::Report("Chunk generation failed!");
        }
    }

    Particle Generate_Particle(float Elevation, float Humidity, float Temperature, Location position, Particle* Previous){
        // generate a triangle of vectors each pointing to each point in the triangle, then multiply each vector by the corresponding values.
        // After multiplying each value with their corresponding vector, we add the vector together, the resulting vector will represent the particle type we need.
        std::array<FVector3, 3> Base_Vectors = Get_Equilateral_Vectors();
        
        // Now multiply each vector length by the value
        Base_Vectors[0] = Base_Vectors[0] * Elevation;
        Base_Vectors[1] = Base_Vectors[1] * Humidity;
        Base_Vectors[2] = Base_Vectors[2] * Temperature;

        // now add the vectors to construct the final vector.
        FVector3 Sum = std::accumulate(Base_Vectors.begin(), Base_Vectors.end(), FVector3{0, 0, 0});

        // now we can check that which Base_Vector is closest to the Sum
        float Min_Distance = FLT_MAX;
        int Closest_Vector_Index = -1;
        for (int i = 0; i < 3; ++i) {
            float distance = (Sum - Base_Vectors[i]).Length();
            if (distance < Min_Distance) {
                Min_Distance = distance;
                Closest_Vector_Index = i;
            }
        }

        Particle Result;

        if (Previous){
            Result.Transfer_Particle_Calculations(Previous);
        }
        else{
            Result = Particle(position);
        }

        if (Closest_Vector_Index == 1){
            Result.Set_Texture("WAVE");
            Result.Tick = [&](Location location){
                Tile* Starting_Tile = Get_Tile(location);

                // cold down the current tile
                Starting_Tile->Temperature = Sigmoid(Starting_Tile->Temperature * (1 - Starting_Tile->Humidity));

                float Lowest_Elevation = Starting_Tile->Elevation;
                Location Lowest_Location;

                // check if the surrounding locations have lower elevation, if so then spread water there.
                for (auto neighboring_positions : CHAOS::Get_Surrounding_Positions({location.HIGH.X, location.HIGH.Y, location.HIGH.Z}, 1)){
                    if (neighboring_positions.X < 0 || neighboring_positions.Y < 0)
                        continue;

                    // transform the IVector into a FVector
                    Location tmp_position({
                        neighboring_positions.X,
                        neighboring_positions.Y,
                        neighboring_positions.Z
                    }, 
                        location.CHUNK
                    );

                    Tile* Current_Tile = Get_Tile(tmp_position);

                    if (Current_Tile->Elevation < Lowest_Elevation){
                        Lowest_Elevation = Current_Tile->Elevation;
                        Lowest_Location = tmp_position;
                    }
                }

                // Now that we know the lowest location the water can flow into it.
                if (Lowest_Elevation < Starting_Tile->Elevation){
                    // move the water to the lowest location
                    Tile* Lowest_Tile = Get_Tile(Lowest_Location);

                    // calculate the flow which occurs from the difference between the elevations
                    float Water_Flow = Lowest_Elevation / Starting_Tile->Elevation;

                    // move the water to the lowest location
                    Lowest_Tile->Humidity = Sigmoid(Lowest_Tile->Humidity + Water_Flow * Starting_Tile->Humidity);

                    // remove the water from the current tile
                    Starting_Tile->Humidity = Sigmoid(Starting_Tile->Humidity - Water_Flow * Starting_Tile->Humidity * 0.1);

                    // now calculate dynamic erosion.
                    Starting_Tile->Elevation = Sigmoid(Starting_Tile->Elevation * Water_Flow);
                }
            };
        }
        else if (Closest_Vector_Index == 2){
            Result.Set_Texture("FIRE");
            Result.Tick = [&](Location location){
                Tile* Starting_Tile = Get_Tile(location);

                bool Can_Be_Sustained = false;

                // Fire feeds itself from the green color, so as long as there is green in the current tile the fire can spread.
                if (
                    // Check if the grounds isn't dried up from nutrients.
                    Starting_Tile->Humidity > 0.05 && Starting_Tile->Humidity < 0.5 &&

                    // Check if the temperature isn't too cold
                    Starting_Tile->Temperature >= 0.7    
                ){
                    Can_Be_Sustained = true;
                }

                if (!Can_Be_Sustained){
                    Result.Life_Span *= 0.5;
                }
                else{
                    Starting_Tile->Humidity = Sigmoid(Starting_Tile->Humidity * (1 - Starting_Tile->Temperature));
                    Starting_Tile->Temperature = Sigmoid(Starting_Tile->Temperature * (Starting_Tile->Temperature + 1));

                    // check if the surrounding locations have lower elevation, if so then spread water there.
                    for (auto neighboring_positions : CHAOS::Get_Surrounding_Positions({location.HIGH.X, location.HIGH.Y, location.HIGH.Z}, 1)){
                        if (neighboring_positions.X < 0 || neighboring_positions.Y < 0)
                            continue;

                        // transform the IVector into a FVector
                        Location tmp_position({
                            neighboring_positions.X,
                            neighboring_positions.Y,
                            neighboring_positions.Z
                        }, 
                            location.CHUNK
                        );

                        Tile* Current_Tile = Get_Tile(tmp_position);

                        // Heat the surrounding tiles 
                        Current_Tile->Temperature = Sigmoid(Current_Tile->Temperature * (Starting_Tile->Temperature + 1));
                        // Dry surrounding tiles.
                        Current_Tile->Humidity = Sigmoid(Current_Tile->Humidity * (1 - Starting_Tile->Temperature));
                    }
                }
            };
        }

        return Result;
    }

    // Inits everything related to TerGen and saves
    void Init(){
        Init_TerGen();
        Init_Tint_Map();
        Init_Biome_Map();

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

    constexpr void Init_Tint_Map(){
        // Order of accessors: Width/X = Humidity, Height/Y = Elevation, Depth/Z = Temperature

        // MAPPINGS:
        /*
        
            Temperature Gradient, where Temperature 0 = RGB(0, 0, 0) and Temperature 255 = RGB(255, 255, 255)
            This means a plane at X&Y plane, {0-255, 0-255, 0} is black and {0-255, 0-255, 255} is white.
        
            Humidity Gradient, where Humidity 0 = RGB(0, 255, 255) and Humidity 255 = RGB(0, 0, 255)
            This means a plane at Y&Z plane, {0, 0-255, 0-255} is yellow and {255, 0-255, 0-255} is blue.

        */

        for (unsigned char Temperature = 0; Temperature < UCHAR_MAX; Temperature++){
            for (unsigned char Elevation = 0; Elevation < UCHAR_MAX; Elevation++){
                for (unsigned char Humidity = 0; Humidity < UCHAR_MAX; Humidity++){
                    GGUI::RGB Current_Tint;

                    // Apply the Temperature Tint.
                    // Since the temperature is already the gradient from 0-255 we dont need to calculate anything.
                    GGUI::RGB Temperature_Tint = {Temperature, Temperature, Temperature};
                    Apply_Tint(Current_Tint, Temperature_Tint, GLOBALS::Tint_Alpha);

                    // Apply the Humidity Tint.
                    // We need to lerp between the yellow and blue colors.
                    GGUI::RGB Humidity_Tint = Lerp({255, 255, 0}, {0, 0, 255}, Humidity);
                    Apply_Tint(Current_Tint, Humidity_Tint, GLOBALS::Tint_Alpha);

                    Apply_Tint(TINT_MAP[Temperature * UCHAR_MAX * UCHAR_MAX + Elevation * UCHAR_MAX + Humidity], Current_Tint, GLOBALS::Tint_Alpha);
                }
            }
        }

    }

    constexpr void Init_Biome_Map(){

        // Biome ideas:
        /*
        


            Create a vertical tree of branching blue, where the higher the elevation goes, the thinner the branches get.
            This inturn creates a instance, where higher places are less probable to have water in them (blue).
            And more deeper parts are more likely to have water (blue)
            The tree is vertical the Elevation is the Y axis.
            The above will be achieved by a carver system, with a pathfinder in the actual tile map and not in the BIOME_MAPPING.

        */

    }
    
    const std::array<FVector3, 3> Get_Equilateral_Vectors(){
        const int Chape_Corner_Count = 3;
        float Difference = 2 * GLOBALS::PI / Chape_Corner_Count;
        
        std::array<FVector3, 3> Result = {};

        Result[0] = FVector3(0, 1, 0);

        Result[1] = {
            cos(Difference) * Result[0].X - sin(Difference) * Result[0].Y,
            sin(Difference) * Result[0].X + cos(Difference) * Result[0].Y,
            0
        };

        Result[2] = {
            cos(-Difference) * Result[0].X - sin(-Difference) * Result[0].Y,
            sin(-Difference) * Result[0].X + cos(-Difference) * Result[0].Y,
            0
        };

        return Result;
    }

}