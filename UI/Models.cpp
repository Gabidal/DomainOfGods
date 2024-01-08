#include "Models.h"

#include "../Src/Map.h"
#include "../Src/Globals.h"
#include "../Src/Chaos.h"

std::unordered_map<std::string, std::vector<Model>> Models;

void Init_Models(){
    Models = {
        {
            "WAVE",
            {
                Model({
                    GGUI::Sprite(GGUI::UTF("~"), GGUI::COLOR::DARK_BLUE),
                    GGUI::Sprite(GGUI::UTF("~"), GGUI::COLOR::LIGHT_BLUE),
                    GGUI::Sprite(GGUI::UTF("~"), GGUI::COLOR::CYAN),
                    GGUI::Sprite(GGUI::UTF("~"), GGUI::COLOR::BLUE),
                }),
            }
        }
    };
}

unsigned char Get_Model_Variation(std::string name){
    int Model_Variation_Count = Models[name].size();

    return rand() % Model_Variation_Count;
}

GGUI::RGB Render_Tile(MAP::Tile* t) {
    return MAP::Get_Tint(t->Elevation, t->Humidity, t->Temperature);
}

GGUI::Sprite Interpolate_Animation_Frame(Model m, unsigned char Animation_Frame){
    int Frame_Count = m.Frames.size();

    const int Frame_Distance = GLOBALS::ANIMATION_FRAME_COUNT / Frame_Count + 1;    // Add 1, because 256 overflows back to zero, and we need detailed distance.

    // now check where the current animation frame lies in between two animation frames.
    int Frame_Below = Animation_Frame / Frame_Distance;
    int Frame_Above = (Frame_Below + 1);

    // now interpolate the foreground color between he two points
    GGUI::RGB foreground = MAP::Lerp(
        m.Frames[Frame_Below].Foreground_Color, 
        m.Frames[Frame_Above % Frame_Count].Foreground_Color, 
        Animation_Frame % Frame_Distance,
        Frame_Distance
    );

    GGUI::Sprite Result;
    Result.Foreground_Color = foreground;
    Result.Texture = m.Frames[Frame_Below].Texture;

    return Result;
}

GGUI::Sprite Render_Entity(Entity* e, unsigned char Animation_Frame){
    GGUI::Sprite Current_Frame = Interpolate_Animation_Frame(Models["WAVE"][0], Animation_Frame);

    return Current_Frame;
}

void Update_Map(GGUI::Terminal_Canvas* tc, unsigned char Animation_Frame){
    int Start_X = GLOBALS::CAMERA.CHUNK.X - tc->Get_Width() / 2;
    int Start_Y = GLOBALS::CAMERA.CHUNK.Y - tc->Get_Height() / 2;

    int End_X = GLOBALS::CAMERA.CHUNK.X + tc->Get_Width() / 2;
    int End_Y = GLOBALS::CAMERA.CHUNK.Y + tc->Get_Height() / 2;

    int Needed_Chunk_Coverage = GGUI::Main->Get_Width() / GLOBALS::CHUNK_WIDTH;

    std::unordered_map<IVector3, GGUI::Sprite, IVector3> Entity_Sprites;

    GLOBALS::CAMERA.Update_Chunk_Location();

    for (auto* entity : CHAOS::Get_Surrounding_Content(GLOBALS::CAMERA.CHUNK, Needed_Chunk_Coverage)){
        FVector3 Relative_To_Camera = MAP::Get_Relative_Position_To_Camera(entity->Get_Position());

        // check if the tile fits inside the canvas.
        if (Relative_To_Camera.X < Start_X || Relative_To_Camera.X >= End_X)
            continue;

        if (Relative_To_Camera.Y < Start_Y || Relative_To_Camera.Y >= End_Y)
            continue;

        // make the relative to the camera which is in the middle into relative to the canvas, which would start from the top left corner [0, 0]
        unsigned int Relative_To_Canvas_X = Relative_To_Camera.X - Start_X;
        unsigned int Relative_To_Canvas_Y = Relative_To_Camera.Y - Start_Y;

        GGUI::Sprite s = Render_Entity(entity, Animation_Frame);

        Entity_Sprites[IVector3(Relative_To_Canvas_X, Relative_To_Canvas_Y, 0)] = s;
    }

    for (auto* tile : MAP::Get_Surrounding_Content(GLOBALS::CAMERA.CHUNK, Needed_Chunk_Coverage)){
        FVector3 Relative_To_Camera = MAP::Get_Relative_Position_To_Camera(tile->Position);

        // check if the tile fits inside the canvas.
        if (Relative_To_Camera.X < Start_X || Relative_To_Camera.X >= End_X)
            continue;

        if (Relative_To_Camera.Y < Start_Y || Relative_To_Camera.Y >= End_Y)
            continue;

        // make the relative to the camera which is in the middle into relative to the canvas, which would start from the top left corner [0, 0]
        unsigned int Relative_To_Canvas_X = Relative_To_Camera.X - Start_X;
        unsigned int Relative_To_Canvas_Y = Relative_To_Camera.Y - Start_Y;

        GGUI::Sprite s;
        s.Background_Color = Render_Tile(tile);

        // check if there is an entity on top of the tile.
        if (Entity_Sprites.find(IVector3(Relative_To_Canvas_X, Relative_To_Canvas_Y, 0)) != Entity_Sprites.end()){
            // if there is, draw the entity first.
            GGUI::Sprite tmp = Entity_Sprites[IVector3(Relative_To_Canvas_X, Relative_To_Canvas_Y, 0)];

            s.Foreground_Color = tmp.Foreground_Color;
            s.Texture = tmp.Texture;
        }

        // if it does, draw it.
        tc->Set(Relative_To_Canvas_X, Relative_To_Canvas_Y, s, false);
    }

    tc->Flush();
}
