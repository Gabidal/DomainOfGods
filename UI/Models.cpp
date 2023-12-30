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
            "≈",         // WAVE-3
            "≋",         // WAVE-4
            "≌",         // WAVE-5

            // BEACH
            " ",         // SAND
            ".",         // SAND-2
            ":",         // SAND-3
            ";",         // SAND-4
            "°",         // SAND-5
            "•",         // SAND-6
            "⁰",         // SAND-7
            "⁴",         // SAND-8

            // PLAINS
            " ",         // GRASS
            ",",         // GRASS-2
            "\'",        // GRASS-3
            "\"",         // GRASS-4
            "`",         // GRASS-5
            "¨",         // GRASS-6
            
            // HILLS
            " ",         // HILL
            " ",         // HILL-2
            " ",         // HILL-3
            "^",         // HILL-4
            "V",         // HILL-5
            "<",         // HILL-6
            ">",         // HILL-7
            "∧",         // HILL-8
            "∠",         // HILL-10
            "∟",         // HILL-11
            
            // MOUNTAINS
            " ",         // MOUNTAIN
            "m",         // MOUNTAIN-2
            "w",         // MOUNTAIN-3
            "M",         // MOUNTAIN-4
            "W",         // MOUNTAIN-5
            "∩",         // MOUNTAIN-6
            "∴",         // MOUNTAIN-8
            "∵",         // MOUNTAIN-9
            
            // SNOW
            " ",         // SNOW
            "*",         // SNOW-2
            "+",         // SNOW-3
            "⁂",         // SNOW-5
            "⁑",         // SNOW-7
            "⁕",         // SNOW-8
        }},

    };

}

int Normalize_Float_To_Model_Index(float Elevation, MODEL_TYPE type){
    int Normalized_Elevation = (abs(Elevation) * (int)Models[type].size());

    int Offset_Y = (Normalized_Elevation % (int)Models[type].size());

    return Offset_Y;
}

GGUI::Sprite Render_Tile(MAP::Tile* t){
    GGUI::Sprite Result;

    Result.Texture.Set_Text(Models[MODEL_TYPE::TILE][t->ID]);

    Result.Background_Color.B = (int)(t->Humidity * 255) % 255;
    Result.Background_Color.G = (int)(t->Temperature * 255) % 255;
    Result.Background_Color.R = (int)(t->Humidity * t->Temperature * 255) % 255;

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
