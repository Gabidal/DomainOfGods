#ifndef _MAP_H_
#define _MAP_H_

#include <vector>
#include <map>
#include <string>

using namespace std;

class Entity;

namespace MAP{

    extern vector<Entity*> Entities;

    extern void Init_TerGen();

    extern void Init();

    extern void Save_Map();
    extern void Load_Map(string file);

}

#endif