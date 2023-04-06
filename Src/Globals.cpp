#include "Globals.h"

#include <iostream>

using namespace std;

namespace GLOBALS{
    TerGen::Generator* Value_Noise = nullptr;

    int MIN_POWER = 1;
    int MAX_POWER = 10;

    void Init_Globals(){
        srand(time(NULL));

        Value_Noise = new TerGen::Generator();
    }

    bool DEBUG = true;
}

