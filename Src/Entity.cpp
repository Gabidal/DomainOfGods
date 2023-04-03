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

ROLE Lot_Role(Location location){
    return Get_Rarity<ROLE>(location, ROLE_Probabilities);
}

SPECIES Lot_Species(Location location){
    return Get_Rarity<SPECIES>(location, SPECIES_Probabilities);
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
    
    Result.Power = Int_Range(GLOBALS::MIN_POWER, GLOBALS::MAX_POWER) * (int)e->Get_Rank();

    return Result;
}

ATTRIBUTES Lot_Attributes(Entity* e){
    ATTRIBUTES Result;

    for (ATTRIBUTE_TYPES Current_Attribute = (ATTRIBUTE_TYPES)0; (int)Current_Attribute < (int)ATTRIBUTE_TYPES::END; Current_Attribute = (ATTRIBUTE_TYPES)((int)Current_Attribute + 1)){
        
        // Lot if the current attribute is even given to the result.
        if (Float_Range(0.0f, 1.0f) < ATTRIBUTE_Probabilities[(int)Current_Attribute]){

            float Min = 1.f - (1.f / (float)e->Get_Class());
            float Max = 1.f + (1.f / (float)e->Get_Class());

            Result.Attributes[Current_Attribute] = Float_Range(Min, Max);
        }
    }

    return Result;
}

vector<Entity*> Lot_Items(Entity* e){
    vector<Entity*> Result;

    int Tmp_Size = e->Get_Attribute(ATTRIBUTE_TYPES::SIZE_MULTIPLIER);

    Entity* Current = new Entity(e->Get_Position(), ENTITY_TYPE::ITEM);

    for (;Current->Get_Attribute(ATTRIBUTE_TYPES::SIZE_MULTIPLIER) < Tmp_Size; Tmp_Size -= Current->Get_Attribute(ATTRIBUTE_TYPES::SIZE_MULTIPLIER)){
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

    // lot the roles
    for (int i = 0; i < Int_Range(0, Base_Stats.Power); i++){
        Roles.push_back(
            Lot_Role(location)
        );
    }

    // lot the species
    Specie = Lot_Species(location);

    // Lot random items for the entity
    if (Type != ENTITY_TYPE::ITEM){

        Holding = Lot_Items(this);

    }
}

void Entity::Update_Stats(){
    // We will decrement the Tmp_Size until the next item wont "fit"
    int Tmp_Size = Get_Attribute(ATTRIBUTE_TYPES::SIZE_MULTIPLIER);

    ATTRIBUTES New_Stats = Attributes;    

    for (Entity* item : Holding){
        if (item->Type == ENTITY_TYPE::ITEM){
            if (Tmp_Size - item->Get_Attribute(ATTRIBUTE_TYPES::SIZE_MULTIPLIER) >= 0){
                Tmp_Size -= item->Get_Attribute(ATTRIBUTE_TYPES::SIZE_MULTIPLIER);
                New_Stats += item->Attributes;
            }
        }
    }
}

string Entity::Get_Name(){
    string Result = "";



}
