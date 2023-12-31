#include "./GGUI_Render.h"
#include "../Src/Entity.h"
#include "../Src/Globals.h"

#include "../Src/Map.h"

#include "../Dependencies/GGUI.h"
#include "./Models.h"

using namespace GGUI; 

std::unordered_map<PAGE_VIEW, std::function<void(bool)>> Pages;

PAGE_VIEW Current_Page = PAGE_VIEW::MENU;

void Activate_Page(PAGE_VIEW activate){
    GGUI::Pause_Renderer([=](){
        for (auto& p : Pages){
            p.second(p.first == activate);
        }
    });

    Current_Page = activate;
}

void Init_Menu_Screen(){

    List_View* Menu_Screen = new List_View(
        GGUI::Main,
        {
            new Button("Campaign", [](Button* self){ Activate_Page(PAGE_VIEW::CAMPAIGN); }),
            new Button("Options", [](Button* self){ Activate_Page(PAGE_VIEW::OPTIONS); }),
            new Button("Exit", [](Button* self){ GGUI::Exit(); }),
        },
        Grow_Direction::COLUMN
    );
    Menu_Screen->Show_Border(true);

    int Centered_Width = GGUI::Main->Get_Width() / 2;
    int Centered_Height = GGUI::Main->Get_Height() / 2;

    Menu_Screen->Set_Position({Centered_Width - Menu_Screen->Get_Width(), Centered_Height - Menu_Screen->Get_Height()});

    Pages[PAGE_VIEW::MENU] = [=](bool b){Menu_Screen->Show_Border(b);};
}

void Init_Campaign(){

    Element* Campaign = new Element(
        Main->Get_Width(),
        Main->Get_Height()
    );

    int Inspect_Tool_Width = Main->Get_Width() / 5;
    int Inspect_Tool_height = Main->Get_Height();

    int Bar_Width = Main->Get_Width();
    int Bar_Height = Main->Get_Height() / 10;

    Terminal_Canvas* map = new Terminal_Canvas(
        Main->Get_Width() - Inspect_Tool_Width, Main->Get_Height() - Bar_Height,
        {0, 0}
    );

    List_View* Inspect = new List_View(
        Campaign,
        {

        },
        Grow_Direction::COLUMN
    );
    Inspect->Set_Position({Main->Get_Width() - Inspect_Tool_Width, Bar_Height});

    List_View* Bar = new List_View(
        Campaign,
        {
            new Button("Menu", [=](Button*){ Activate_Page(PAGE_VIEW::MENU); }),
            new Button("Inventory", [=](Button*){ 
                if (GLOBALS::Focus)
                    Inspect->Add_Child(Display_Inventory(GLOBALS::Focus)); 
            })
        }
    );
    Bar->Set_Position({0, map->Get_Height()});

    Campaign->Add_Child(map);
    Campaign->Add_Child(Inspect);
    
    Pages[PAGE_VIEW::CAMPAIGN] = [=](bool b){ Campaign->Display(b); };

    Campaign->Display(false);

    Main->Add_Child(Campaign);

    thread Render_Stream = thread([=](){
        while(true){
            std::this_thread::sleep_for(std::chrono::milliseconds((int)GLOBALS::TICK_LENGTH));

            if (Current_Page != PAGE_VIEW::CAMPAIGN)
                continue;

            Update_Map(map);
        }
    });

    Render_Stream.detach();
}

Element* Display_Object(Entity* e){



}

Element* Display_Inventory(Entity* e){



}