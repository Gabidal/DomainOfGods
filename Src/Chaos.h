#ifndef _CHAOS_H_
#define _CHAOS_H_

#include "Entity.h"
#include "../Dependencies/TerGen.h"

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

namespace CHAOS{

    extern vector<Entity*> Get_Chunk_Content(IVector3 position);

    extern vector<Entity*> Get_Surrounding_Content(IVector3 position);
    extern vector<Entity*> Get_Surrounding_Content(IVector3 position, int Distance);

    extern vector<IVector3> Get_Surrounding_Positions(IVector3 center, int Reach = 1);
    extern vector<Entity*> Get_Surrounding_Content(IVector3 position);
}

#endif