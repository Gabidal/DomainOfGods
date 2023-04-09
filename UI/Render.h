#ifndef _RENDER_H_
#define _RENDER_H_

#include "../Dependencies/GGUI.h"
#include "../Src/Entity.h"

#include <map>
#include <vector>
#include <string>

using namespace std;

// BACKGROUND COLOR
inline map<RANK, GGUI::RGB> Rank_Color = {
    {RANK::NONE, GGUI::COLOR::GRAY},
    {RANK::SUPERNATURAL, GGUI::COLOR::DARK_MAGENTA},
    {RANK::HALF_BLOOD, GGUI::COLOR::DARK_RED},
    {RANK::DEMIGOD, GGUI::COLOR::DARK_YELLOW},
    {RANK::FALSE_GOD, GGUI::COLOR::YELLOW},
    {RANK::GOD, GGUI::COLOR::YELLOW},
    {RANK::TRUE_GOD, GGUI::COLOR::LIGHT_YELLOW},
    {RANK::DOMAIN_HOLDER, GGUI::COLOR::WHITE},
};

// FOREGROUND COLOR
inline map<CLASS, GGUI::RGB> Class_Color = {
    {CLASS::LOW, GGUI::COLOR::BLACK},
    {CLASS::MIDDLE, GGUI::COLOR::DARK_GRAY},
    {CLASS::HIGH, GGUI::COLOR::GRAY},
    {CLASS::TOP, GGUI::COLOR::LIGHT_GRAY},

    {CLASS::LEGACY, GGUI::COLOR::DARK_MAGENTA},
    {CLASS::MAGICAL, GGUI::COLOR::MAGENTA},
    
    {CLASS::RARE, GGUI::COLOR::YELLOW},
    {CLASS::RELIC, GGUI::COLOR::LIGHT_YELLOW},

    {CLASS::LEGENDARY, GGUI::COLOR::DARK_RED},
    {CLASS::DIVINE, GGUI::COLOR::RED},
    {CLASS::GUILD, GGUI::COLOR::LIGHT_RED},

    {CLASS::CHAMPION, GGUI::COLOR::DARK_YELLOW},
    {CLASS::HERO, GGUI::COLOR::YELLOW},
    {CLASS::WORLD, GGUI::COLOR::LIGHT_YELLOW},
};

// The text
inline map<ENTITY_TYPE, string> Entity_Type = {
    {ENTITY_TYPE::UNKNOWN, "?"},
    {ENTITY_TYPE::ITEM, "*"},
    {ENTITY_TYPE::ENTITY, "@"},
};
 
extern void Init_Render();

extern void Render_Tick();

#endif