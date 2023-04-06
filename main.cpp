#include <iostream>

#include "Src/Entity.h"
#include "Src/Globals.h"

using namespace std;

int main(){
    GLOBALS::Init_Globals();

    for (int i = 0; i < 100; i++)
        cout << Entity({{rand(), rand(), rand()}, {}}, ENTITY_TYPE::UNKNOWN).Get_Name() << endl;

    char umungus;
    cin >> umungus;
    return 0;    
}

