#include <iostream>

#include "Src/Entity.h"
#include "Src/Globals.h"
#include "Src/Map.h"
#include "Src/Chaos.h"

#include "UI/Render.h"

#include "Dependencies/raylib.h"

#include <thread>
#include <atomic>

using namespace std;

int main(){    
    GLOBALS::Init_Globals();

    RENDER::Init();
    CHAOS::Init();

    MAP::Init();

    atomic_bool Stop_Stream = false;
    atomic_bool Stream_Is_Active = false;

    thread Entity_Stream = thread([&](){
        while(true){
            if (Stop_Stream || Stream_Is_Active)
                continue;

            CHAOS::Tick();
            std::this_thread::sleep_for(std::chrono::milliseconds((int)GLOBALS::TICK_LENGTH));
        }
    });

    thread Physics_Stream = thread([&](){
        while(true){
            if (Stop_Stream)
                continue;

            Stream_Is_Active = true;

            CHAOS::Apply_Physics();

            Stream_Is_Active = false;
            std::this_thread::sleep_for(std::chrono::milliseconds((int)GLOBALS::TICK_LENGTH));
        }
    });

    while(true){
        Stop_Stream = true;

        if (Stream_Is_Active)
            continue;

        RENDER::Update_Frame();


        Stop_Stream = false;
        std::this_thread::sleep_for(std::chrono::milliseconds((int)GLOBALS::TICK_LENGTH));
    }
    
    RENDER::Close();
    
    return 0;    
}

