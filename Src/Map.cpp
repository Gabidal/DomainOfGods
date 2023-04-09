#include "Map.h"

#include "Dependencies/TerGen.h"
#include "Entity.h"
#include "Globals.h"

using namespace TerGen; 

namespace MAP{

    inline vector<class Entity*> Entities;

    // We get the ground map from TerGen.

    void Init(){
        Entities.resize(GLOBALS::UPDATE_DISTANCE_X * GLOBALS::UPDATE_DISTANCE_Y);

        for (int y = 0; y < GLOBALS::WORLD_HEIGHT; y++){
            for (int x = 0; x < GLOBALS::WORLD_WIDTH; x++){
                bool Spawn_Entity = rand() % 100 < GLOBALS::ENTITY_DENSITY * 100;

                if (Spawn_Entity)
                    Entities[x + y * GLOBALS::WORLD_WIDTH] = new Entity({{x, y, 0}, {0, 0, 0}});
            }
        }
    }

    void Init_TerGen(){

    }

    void Save_Map(){

        
    }

    void Load_Map(string file){



    }
}