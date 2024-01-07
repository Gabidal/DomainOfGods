#ifndef GGUI_RENDER_H
#define GGUI_RENDER_H

#include <unordered_map>
#include <functional>

enum class PAGE_VIEW{
    MENU,
    OPTIONS,
    CAMPAIGN,
};

namespace GGUI{
    class Element;
}

extern PAGE_VIEW Current_Page;

extern std::unordered_map<PAGE_VIEW, std::function<void(bool)>> Pages;

extern void Activate_Page(PAGE_VIEW activate);

extern void Init_Menu_Screen();

extern void Init_Campaign();

extern void Init_Controls();

extern GGUI::Element* Display_Object(class Entity* e);

extern GGUI::Element* Display_Inventory(class Entity* e);


#endif