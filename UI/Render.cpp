#include "Render.h"

#include "../Src/Map.h"
#include "../Src/Globals.h"

using namespace GGUI;

void Init_Render(){
    GGUI::GGUI([&](){
        Terminal_Canvas* Map = new Terminal_Canvas(
            GGUI::Main->Get_Width(),
            GGUI::Main->Get_Height(),
            {0, 0}
        );

        Map->Set_Background_Color(GGUI::COLOR::WHITE);

        Main->Add_Child(Map);
    });
}

UTF Render(Entity* e){
    return UTF(
        Entity_Type[e->Get_Type()],
        {
            Rank_Color[e->Get_Rank()],
            Class_Color[e->Get_Class()]
        }
    );
}

void Render_Tick(){
    Terminal_Canvas* Canvas_Handle = GGUI::Main->Get_Elements<Terminal_Canvas>()[0];

    int Start_Y = GLOBALS::CAMERA_Y - (GLOBALS::RENDER_DISTANCE_HEIGHT / 2);
    int Start_X = GLOBALS::CAMERA_X - (GLOBALS::RENDER_DISTANCE_WIDTH / 2);

    int End_Y = GLOBALS::CAMERA_Y + (GLOBALS::RENDER_DISTANCE_HEIGHT / 2);
    int End_X = GLOBALS::CAMERA_X + (GLOBALS::RENDER_DISTANCE_WIDTH / 2);

    for (int y = Start_Y; y < End_Y; y++){
        for (int x = Start_X; x < End_X; x++){
            // Entity* Current_Entity = MAP::Entities[x + y * GLOBALS::RENDER_DISTANCE_WIDTH];

            // if (Current_Entity != nullptr){
            //     if (x < Canvas_Handle->Get_Width() && y < Canvas_Handle->Get_Height())
            //         Canvas_Handle->Set(x, y, Render(Current_Entity), false);
            // }
        }
    }

    Canvas_Handle->Flush();
}
