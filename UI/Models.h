#ifndef MODELS_H
#define MODELS_H

#include <vector>
#include <unordered_map>
#include "../Src/Entity.h"
#include "../Dependencies/GGUI.h"

enum class MODEL_TYPE{
    UNKNOWN,
    TILE,
    ENTITY,
};

namespace MAP{
    class Tile;
}

// Accessed with index;
extern std::unordered_map<MODEL_TYPE, std::vector<std::string>> Models;

extern void Init_Models();

extern int Normalize_Float_To_Model_Index(float Elevation, MODEL_TYPE type);

extern GGUI::Sprite Render_Tile(MAP::Tile* t);

extern void Update_Map(GGUI::Terminal_Canvas* tc);

#endif