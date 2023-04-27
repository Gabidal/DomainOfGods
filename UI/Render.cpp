#include "Render.h"
#include "../Dependencies/raylib.h"
#include "../Src/Entity.h"

// Get the terrain from MAP.h
#include "../Src/Map.h"
#include "../Src/Globals.h"

// Get the Entities from Chaos.h
#include "../Src/Chaos.h"

#include <iostream>
#include <unordered_map>

using namespace std;

namespace RENDER{
    unordered_map<int, Texture2D> Tile_Textures;
    unordered_map<SPECIES, Texture2D> Entity_Textures;

    void Init(){
        // Do some environment vibe cheks.

        InitWindow(GLOBALS::WINDOW_HEIGHT, GLOBALS::WINDOW_WIDTH, "Domain Of Gods");

        Tile_Textures = {
            {0, LoadTexture("Img/Tile/Grass.png")},       // Normal grass
            {1, LoadTexture("Img/Tile/Wet_Grass.png")},   // Wet grass
            {2, LoadTexture("Img/Tile/Swamp_Grass.png")}  // Swamp grass
        };

        Entity_Textures = {
            {SPECIES::MECHANITE, LoadTexture("Img/Entity/IceGolemMarkII.png")},
            {SPECIES::HUMAN, LoadTexture("Img/Entity/SandGolemMarkII.png")},
        };

        GLOBALS::CAMERA.Y = GLOBALS::CHUNK_HEIGHT / 2;
        GLOBALS::CAMERA.X = GLOBALS::CHUNK_WIDTH / 2;
    }

    void Close(){
        // end all

        CloseWindow();
    }

    FVector3 Get_Relative_Position_To_Camera(Location position, Texture2D texture){
        int Tile_Width = texture.width;
        int Tile_Height = texture.height;

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

    void Update_Frame(){
        if (WindowShouldClose()){
            Close();
            return;
        }

        BeginDrawing(); 
        ClearBackground(BLACK);

        // First draw the background with tilesseses-
        for (auto* tile : MAP::Get_Surrounding_Content(GLOBALS::CAMERA, 5)){
            FVector3 World_Space = Get_Relative_Position_To_Camera(tile->Position, Tile_Textures[tile->ID]);

            DrawTexture(Tile_Textures[tile->ID], World_Space.X, World_Space.Y, WHITE);
        }

        // now draw the entities
        for (auto* entity : CHAOS::Get_Surrounding_Content(GLOBALS::CAMERA, 5)){
            FVector3 World_Space = Get_Relative_Position_To_Camera(entity->Get_Position(), Entity_Textures[entity->Get_Specie()->Specie]);

            // if (Entity_Textures.find(entity->Get_Specie()->Specie) != Entity_Textures.end())
            //     cout << "ERROR: No Texture for '" + SPECIES_Names[(int)entity->Get_Specie()->Specie] + "' found!" << endl;

            // Use directional mappings.
            DrawTexture(Entity_Textures[entity->Get_Specie()->Specie], World_Space.X, World_Space.Y, WHITE);
        }

        EndDrawing();
    }
}

