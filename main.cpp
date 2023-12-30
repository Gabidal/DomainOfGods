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
                if (Current_Page != PAGE_VIEW::CAMPAIGN || (Stop_Stream || Stream_Is_Active))
                    continue;

                CHAOS::Tick();
                std::this_thread::sleep_for(std::chrono::milliseconds((int)GLOBALS::TICK_LENGTH));
            }
        });

        thread Physics_Stream = thread([=](){
            while(true){
                if (Current_Page != PAGE_VIEW::CAMPAIGN || Stop_Stream)
                    continue;

                Stream_Is_Active = true;

                CHAOS::Apply_Physics();

                Stream_Is_Active = false;
                std::this_thread::sleep_for(std::chrono::milliseconds((int)GLOBALS::TICK_LENGTH));
            }
        });

        Entity_Stream.detach();
        Physics_Stream.detach();
    });

    // while(true){
    //     Stop_Stream = true;
    //     if (Stream_Is_Active)
    //         continue;
    //     RENDER::Update_Frame();
    //     Stop_Stream = false;
    //     std::this_thread::sleep_for(std::chrono::milliseconds((int)GLOBALS::TICK_LENGTH));
    // }
    // RENDER::Close();
    
    while (true){}

    return 0;    
}

