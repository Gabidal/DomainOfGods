#include "Render.h"
#include "../Dependencies/raylib.h"
#include "../Src/Entity.h"

// Get the terrain from MAP.h
#include "../Src/Map.h"
#include "../Src/Globals.h"

// Get the Entities from Chaos.h
#include "../Src/Chaos.h"

#include <unordered_map>

using namespace std;

namespace RENDER{
    unordered_map<int, Texture2D> Tile_Textures;

    void Init(){
        // Do some environment vibe cheks.

        InitWindow(GLOBALS::WINDOW_HEIGHT, GLOBALS::WINDOW_WIDTH, "Domain Of Gods");

        Tile_Textures = {
            {0, LoadTexture("Img/Grass.png")},       // Normal grass
            {1, LoadTexture("Img/Wet_Grass.png")},   // Wet grass
            {2, LoadTexture("Img/Swamp_Grass.png")}  // Swamp grass
        };

        GLOBALS::CAMERA.Y = GLOBALS::CHUNK_HEIGHT / 2;
        GLOBALS::CAMERA.X = GLOBALS::CHUNK_WIDTH / 2;
    }

    void Close(){
        // end all

        CloseWindow();
    }

    void Update_Frame(){
        if (WindowShouldClose()){
            Close();
            return;
        }

        BeginDrawing(); 
        ClearBackground(BLACK);

        // First draw the background with tilesseses-
        for (auto* tile : MAP::Get_Surrounding_Content(GLOBALS::CAMERA, 5)){
            int Tile_Width = Tile_Textures[tile->ID].width;
            int Tile_Height = Tile_Textures[tile->ID].height;

            int Tile_Position_Y = tile->Position.HIGH.Y * Tile_Height;
            int Tile_Position_X = tile->Position.HIGH.X * Tile_Width;

            int Chunk_Position_Y = tile->Position.CHUNK.Y * GLOBALS::CHUNK_HEIGHT * Tile_Height;
            int Chunk_Position_X = tile->Position.CHUNK.X * GLOBALS::CHUNK_WIDTH * Tile_Width;

            int Camera_Position_Y = GLOBALS::CAMERA.Y * GLOBALS::CHUNK_HEIGHT * Tile_Height;
            int Camera_Position_X = GLOBALS::CAMERA.X * GLOBALS::CHUNK_WIDTH * Tile_Width;

            int Relative_Y = Tile_Position_Y + Chunk_Position_Y - Camera_Position_Y;
            int Relative_X = Tile_Position_X + Chunk_Position_X - Camera_Position_X;

            DrawTexture(Tile_Textures[tile->ID], Relative_X, Relative_Y, WHITE);
        }

        EndDrawing();
    }
}

