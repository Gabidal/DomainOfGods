#ifndef _RENDER_H_
#define _RENDER_H_

#include "../Dependencies/raylib.h"
#include <unordered_map>

#include "../Src/Entity.h"

using namespace std;

namespace RENDER{

    extern unordered_map<int, Texture2D> Tile_Textures;
    extern unordered_map<SPECIES, Texture2D> Entity_Textures;

    extern void Init();

    extern void Close();

    extern void Update_Frame();

}

#endif