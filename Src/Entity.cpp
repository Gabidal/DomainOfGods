#include "Entity.h"
#include "Globals.h"
#include "../Depedencies/TerGen.h"


template<typename T>
T Get_Rarity(Location location, const double Probability_Table[]){
    // Get the total probability by summing all the individual probabilities
    const double totalProbability = 1.0 - (0.99 * 0.0000000000000001);

    // Generate a random number between 0 and 1
    double random = TerGen::Noise(location.LOW, GLOBALS::Value_Noise); //(double)rand() / RAND_MAX;

    // Multiply the random number by the total probability to scale it to the correct range
    random *= totalProbability;

    // Determine which class the random number falls within
    T lootClass = T::END;
    double probabilitySum = 0.0;
    for (int i = 0; i < (int)T::END; i++) {
        probabilitySum += Probability_Table[i];
        if (random <= probabilitySum) {
            lootClass = static_cast<T>(i);
            break;
        }
    }
}

// The location affects the rarity of the rank.
// By using the Perlin Noise like random affection we can make it so, that the entity ranking goes up the closer you get
// to the center of the "hill" where the "hill" means the leader of an monster pack, or the treasure vault of the ruins. 
RANK Lot_Rank(Location location){
    return Get_Rarity<RANK>(location, RANK_Probabilities);
}

CLASS Lot_Class(Location location){
    return Get_Rarity<CLASS>(location, CLASS_Probabilities);
}

int Int_Range(int min, int max){
    return min + (rand() % (max - min + 1));
}

float Float_Range(float min, float max){
    return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
}

// The rank and the location of the entity affects the Stats.
STATS Lot_Stats(Entity* e){
    STATS Result;
    
    Result.Power = Int_Range(GLOBALS::MIN_RANK, GLOBALS::MAX_RANK) * (int)e->Get_Rank();

    return Result;
}

ATTRIBUTES Lot_Attributes(Entity* e){
    ATTRIBUTES Result;

    /*
    float Affect_Strength = 1.f;
    float Affect_Damage = 1.f;
    float Affect_Health = 1.f;
    float Affect_Speed = 1.f;
    float Affect_Defense = 1.f;
    // All resistances
    float Affect_Heat_Resistance = 1.f;
    float Affect_Cold_Resistance = 1.f;
    float Affect_Electricity_Resistance = 1.f;
    float Affect_Poison_Resistance = 1.f;
    float Affect_Acid_Resistance = 1.f;
    float Affect_Radiation_Resistance = 1.f;
    float Affect_Psychic_Resistance = 1.f;
    float Affect_Sonic_Resistance = 1.f;
    float Affect_Light_Resistance = 1.f;
    float Affect_Darkness_Resistance = 1.f;
    float Affect_Magic_Resistance = 1.f;
    float Affect_Physical_Resistance = 1.f;
    float Affect_Mental_Resistance = 1.f;
    float Affect_Astral_Resistance = 1.f;
    float Affect_Dimensional_Resistance = 1.f;
    float Affect_Nuclear_Resistance = 1.f;
    float Affect_Biological_Resistance = 1.f;
    float Affect_Natural_Resistance = 1.f;
    float Affect_Explosive_Resistance = 1.f;
    //--
    float Affect_Accuracy = 1.f;
    float Affect_Evasion = 1.f;
    float Affect_Crit_Chance = 1.f;
    float Affect_Crit_Power = 1.f;
    float Affect_Size = 1.f;
    */

    Result.Affect_Strength = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    Result.Affect_Damage = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    Result.Affect_Health = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    Result.Affect_Speed = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    Result.Affect_Defense = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    // All resistances
    Result.Affect_Heat_Resistance = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    Result.Affect_Cold_Resistance = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    Result.Affect_Electricity_Resistance = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    Result.Affect_Poison_Resistance = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    Result.Affect_Acid_Resistance = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    Result.Affect_Radiation_Resistance = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    Result.Affect_Psychic_Resistance = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    Result.Affect_Sonic_Resistance = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    Result.Affect_Light_Resistance = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    Result.Affect_Darkness_Resistance = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    Result.Affect_Magic_Resistance = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    Result.Affect_Physical_Resistance = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    Result.Affect_Mental_Resistance = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    Result.Affect_Astral_Resistance = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    Result.Affect_Dimensional_Resistance = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    Result.Affect_Nuclear_Resistance = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    Result.Affect_Biological_Resistance = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    Result.Affect_Natural_Resistance = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    Result.Affect_Explosive_Resistance = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    //---
    Result.Affect_Accuracy = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    Result.Affect_Evasion = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    Result.Affect_Crit_Chance = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    Result.Affect_Crit_Power = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));
    Result.Affect_Size = Float_Range(1.f - (1.f / (float)e->Get_Class()), 1.f + (1.f / (float)e->Get_Class()));

    return Result;
}

vector<Entity*> Lot_Items(Entity* e){
    vector<Entity*> Result;

    int Tmp_Size = e->Get_Size();

    Entity* Current = new Entity(e->Get_Position(), ENTITY_TYPE::ITEM);

    for (;Current->Get_Size() < Tmp_Size; Tmp_Size -= Current->Get_Size()){
        Result.push_back(Current);
        Current = new Entity(e->Get_Position(), ENTITY_TYPE::ITEM);
    }

    return Result;
}

Entity::Entity(Location location, ENTITY_TYPE type){

    Position = location;
    Type = type;
    Rank = Lot_Rank(location);
    Class = Lot_Class(location);

    Base_Stats = Lot_Stats(this);
    Attributes = Lot_Attributes(this);

    // Lot random items for the entity
    if (Type != ENTITY_TYPE::ITEM){

        Holding = Lot_Items(this);

    }
}

void Entity::Update_Stats(){
    // We will decrement the Tmp_Size until the next item wont "fit"
    int Tmp_Size = Base_Stats.Power;

    ATTRIBUTES New_Stats = Attributes;    

    for (Entity* item : Holding){
        if (item->Type == ENTITY_TYPE::ITEM){
            if (Tmp_Size - item->Base_Stats.Power >= 0){
                Tmp_Size -= item->Base_Stats.Power;
                New_Stats += item->Attributes;
            }
        }
    }
}
