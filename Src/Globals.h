#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "../Depedencies/TerGen.h"

namespace GLOBALS{

    extern TerGen::Generator* Value_Noise;

    extern void Init_Globals();

    
    extern int MIN_RANK;
    extern int MAX_RANK;

}

#endif