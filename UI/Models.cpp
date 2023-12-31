#include "Models.h"

#include "../Src/Map.h"
#include "../Src/Globals.h"

std::unordered_map<MODEL_TYPE, std::vector<std::string>> Models;

void Init_Models(){
    Models = {

        {MODEL_TYPE::TILE, {
            // SEA and RIVERS
            "@",         // SEA     // Vortex
            " ",         // SEA-2
            " ",         // SEA-3
            "~",         // WAVE
            "~",         // WAVE-2
            // "≈",         // WAVE-3
            // "≋",         // WAVE-4
            // "≌",         // WAVE-5

            // BEACH
            " ",         // SAND
            ".",         // SAND-2
            ":",         // SAND-3
            ";",         // SAND-4
            // "°",         // SAND-5
            // "•",         // SAND-6
            // "⁰",         // SAND-7
            // "⁴",         // SAND-8

            // PLAINS
            " ",         // GRASS
            ",",         // GRASS-2
            "\'",        // GRASS-3
            "\"",         // GRASS-4
            // "`",         // GRASS-5
            // "¨",         // GRASS-6
            
            // HILLS
            " ",         // HILL
            " ",         // HILL-2
            " ",         // HILL-3
            "^",         // HILL-4
            "V",         // HILL-5
            "<",         // HILL-6
            ">",         // HILL-7
            // "∧",         // HILL-8
            // "∠",         // HILL-10
            // "∟",         // HILL-11
            
            // MOUNTAINS
            " ",         // MOUNTAIN
            "m",         // MOUNTAIN-2
            "w",         // MOUNTAIN-3
            "M",         // MOUNTAIN-4
            "W",         // MOUNTAIN-5
            // "∩",         // MOUNTAIN-6
            // "∴",         // MOUNTAIN-8
            // "∵",         // MOUNTAIN-9
            
            // SNOW
            " ",         // SNOW
            "*",         // SNOW-2
            "+",         // SNOW-3
            //"⁂",         // SNOW-5
            // "⁑",         // SNOW-7
            // "⁕",         // SNOW-8
        }},

    };

}

int Normalize_Float_To_Model_Index(float Elevation, MODEL_TYPE type){
    int Normalized_Elevation = (abs(Elevation) * (int)Models[type].size());

    int Offset_Y = (Normalized_Elevation % (int)Models[type].size());

    return Offset_Y;
}

// Linear interpolation function
float lerp(float a, float b, float t) {
    return a + t * (b - a);
}

GGUI::Sprite Render_Tile(MAP::Tile* t) {
    GGUI::Sprite Result;

    Result.Texture.Set_Text(Models[MODEL_TYPE::TILE][t->ID]);

    // Define colors for different biomes
    GGUI::RGB oceanColor = {0, 0, 255};     // Blue for oceans
    GGUI::RGB lushColor = {0, 255, 0};      // Green for lush plains
    GGUI::RGB desertColor = {255, 255, 0};  // Yellow for hot deserts
    GGUI::RGB snowColor = {255, 255, 255};  // White for cold and wet
    GGUI::RGB mountainColor = {128, 128, 128};  // Gray for cold and dry

    // Humidity and temperature values
    float humidity = std::min(t->Humidity, 1.0f);        // Ensure humidity is between 0 and 1
    float temperature = std::min(t->Temperature, 1.0f);  // Ensure temperature is between 0 and 1

    // Adjust sensitivity by multiplying humidity and temperature with a factor
    float sensitivityFactor = 5.0f;  // Adjust this factor to control sensitivity
    humidity *= sensitivityFactor;
    temperature *= sensitivityFactor;

    // Interpolate between colors based on humidity and temperature
    GGUI::RGB interpolatedColor = {
        static_cast<unsigned char>(lerp(oceanColor.R, lushColor.R, humidity) * lerp(snowColor.R, mountainColor.R, temperature)),
        static_cast<unsigned char>(lerp(oceanColor.G, lushColor.G, humidity) * lerp(snowColor.G, mountainColor.G, temperature)),
        static_cast<unsigned char>(lerp(oceanColor.B, lushColor.B, humidity) * lerp(snowColor.B, mountainColor.B, temperature))
    };

    Result.Background_Color = interpolatedColor;

    return Result;
}

void Update_Map(GGUI::Terminal_Canvas* tc){
    int Start_X = GLOBALS::CAMERA.X - tc->Get_Width() / 2;
    int Start_Y = GLOBALS::CAMERA.Y - tc->Get_Height() / 2;

    int End_X = GLOBALS::CAMERA.X + tc->Get_Width() / 2;
    int End_Y = GLOBALS::CAMERA.Y + tc->Get_Height() / 2;

    int Needed_Chunk_Coverage = GGUI::Main->Get_Width() / GLOBALS::CHUNK_WIDTH;

    for (auto* tile : MAP::Get_Surrounding_Content(GLOBALS::CAMERA, Needed_Chunk_Coverage)){
        FVector3 Relative_To_Camera = MAP::Get_Relative_Position_To_Camera(tile->Position);

        // check if the tile fits inside the canvas.
        if (Relative_To_Camera.X < Start_X || Relative_To_Camera.X >= End_X)
            continue;

        if (Relative_To_Camera.Y < Start_Y || Relative_To_Camera.Y >= End_Y)
            continue;

        // make the relative to the camera which is in the middle into relative to the canvas, which would start from the top left corner [0, 0]
        unsigned int Relative_To_Canvas_X = Relative_To_Camera.X - Start_X;
        unsigned int Relative_To_Canvas_Y = Relative_To_Camera.Y - Start_Y;

        // if it does, draw it.
        tc->Set(Relative_To_Canvas_X, Relative_To_Canvas_Y, Render_Tile(tile), false);
    }

    tc->Flush();
}
