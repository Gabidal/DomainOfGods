#include <iostream>

#include "Src/Entity.h"
#include "Src/Globals.h"
#include "Src/Map.h"
#include "Src/Chaos.h"

#include "./Dependencies/GGUI.h"
#include "./UI/GGUI_Render.h"
#include "./UI/Models.h"

#include <thread>
#include <atomic>

using namespace std;

atomic_bool Stop_Stream = false;
atomic_bool Stream_Is_Active = false;

int main(){    
    GGUI::GGUI([=](){
        GLOBALS::Init_Globals();

        Init_Models();

        Init_Menu_Screen();
        Init_Campaign();

        CHAOS::Init();
        MAP::Init();


        thread Entity_Stream = thread([=](){
            while(true){
                std::this_thread::sleep_for(std::chrono::milliseconds((int)GLOBALS::TICK_LENGTH));

                if (Current_Page != PAGE_VIEW::CAMPAIGN || (Stop_Stream || Stream_Is_Active))
                    continue;

                CHAOS::Tick();
            }
        });

        thread Physics_Stream = thread([=](){
            while(true){
                std::this_thread::sleep_for(std::chrono::milliseconds((int)GLOBALS::TICK_LENGTH));

                if (Current_Page != PAGE_VIEW::CAMPAIGN || Stop_Stream)
                    continue;

                Stream_Is_Active = true;

                CHAOS::Apply_Physics();

                Stream_Is_Active = false;
            }
        });

        Entity_Stream.detach();
        Physics_Stream.detach();
    });
    
    Entity* Player = new Entity({{(float)0, (float)0, 1}, {0, 0, 0}}, ENTITY_TYPE::ENTITY);

    CHAOS::Entity_Chunks[IVector3()] = {Player};

    GLOBALS::Focus = Player;

    while (true){}

    return 0;    
}

