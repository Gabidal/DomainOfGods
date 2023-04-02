#include "Globals.h"

#include <iostream>

using namespace std;

TerGen::Generator* Value_Noise = nullptr;

int MIN_RANK = 1;
int MAX_RANK = 10;

void Init_Globals(){
    srand(time(NULL));

    Value_Noise = new TerGen::Generator();
}

