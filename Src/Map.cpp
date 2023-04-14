#include "Map.h"

#include "Dependencies/TerGen.h"
#include "Entity.h"
#include "Globals.h"

using namespace TerGen; 

namespace MAP{

    inline vector<Tile> Tiles;

    Tile::Tile(Location position){



    }

    void Init_TerGen(){

    }

    void Save_Map(string file){

        
    }

    void Load_Map(string file){



    }

    // Inits everything related to TerGen and saves
    void Init(){
        Init_TerGen();

        Load_Map("Default.sv");
    }
}