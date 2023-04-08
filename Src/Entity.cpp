#include "Entity.h"
#include "Globals.h"
#include "../Dependencies/TerGen.h"


template<typename T>
T Get_Rarity(Location location, const double Probability_Table[]){
    // Get the total probability by summing all the individual probabilities
    double totalProbability = 0;

    // sum all the probability table content
    for (int i = 0; i < (int)T::END; i++){
        totalProbability += Probability_Table[i];
    }

    // Generate a random number between 0 and 1
    // Altough TerGen returns -1 to 1 we need to normalize it to 0 to 1
    double Ceiling = 1;
    double Floor = -1;

    double random = TerGen::Noise(TerGen::Vector3(location.LOW.X, location.LOW.Y, location.LOW.Z), GLOBALS::Value_Noise); //(double)rand() / RAND_MAX;
    random = (random - Floor) / (abs(Floor) + Ceiling);

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

SPECIES Lot_Specie_Type(Location location){
    return Get_Rarity<SPECIES>(location, SPECIES_Probabilities);
}

int Int_Range(int min, int max){
    return min + (rand() % (max - min + 1));
}

float Float_Range(float min, float max){
    return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
}

template<typename T>
string Get_Name_From_Table(T enum_type, const vector<const char*> name_table[]){
    int Random_Index = Int_Range(0, name_table[(int)enum_type].size() - 1);
    return name_table[(int)enum_type][Random_Index];
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

// The rank and the location of the entity affects the Stats.
STATS Lot_Stats(Entity* e){
    STATS Result;
    
    Result.Power = Int_Range(GLOBALS::MIN_POWER, GLOBALS::MAX_POWER) * (int)e->Get_Rank();

    return Result;
}

vector<Entity*> Lot_Items(Body_Part* limb, Location position){
    vector<Entity*> Result;

    // these items will not be equipped asap, but the limb is presented here so that we generate only usable loot.
    // The  Int_Range(false, true) is because we dont want to fully equip all the area.
    for (int Current_Size = limb->Size; Current_Size > 0 && Int_Range(0, 2) > 0;){

        Entity* item = new Entity(position, ENTITY_TYPE::ITEM);



    }

    return Result;
}

Body_Part Lot_Body_Part(RANK r, BODY_PART_TYPES type = BODY_PART_TYPES::UNKNOWN){
    Body_Part Result;

    Result.Condition = Float_Range(0.1f, 1.f);
    Result.Size = Int_Range((int)r / 2, (int)r);

    if (type == BODY_PART_TYPES::UNKNOWN)
        Result.Type = (BODY_PART_TYPES)Int_Range((int)BODY_PART_TYPES::UNKNOWN, (int)BODY_PART_TYPES::END);
    else
        Result.Type = type;

    return Result;
}

float Entity::Get_Attribute(ATTRIBUTE_TYPES type, bool Local){
    float Result = 1.f;

    if (Local)
        Result *= Base_Stats.Local.Get(type);

    Result *= Base_Stats.Global.Get(type) * Base_Stats.Power;

    return Result;
}

Specie_Descriptor::Specie_Descriptor(Location position){
    Specie = Lot_Specie_Type(position);
    Name = SPECIES_Names[(int)Specie];
    Rank = Lot_Rank(position);

    // These are the quarantined chances of some limbs:
    // Head: 100%
    // Torso: 100%
    // 2x HANDS: 100%
    // 2x LEGS: 100%

    Body_Parts.push_back(new Body_Part(Lot_Body_Part(Rank, BODY_PART_TYPES::HEAD)));
    Body_Parts.push_back(new Body_Part(Lot_Body_Part(Rank, BODY_PART_TYPES::TORSO)));

    Body_Parts.push_back(new Body_Part(Lot_Body_Part(Rank, BODY_PART_TYPES::HAND)));
    Body_Parts.push_back(new Body_Part(Lot_Body_Part(Rank, BODY_PART_TYPES::HAND)));

    Body_Parts.push_back(new Body_Part(Lot_Body_Part(Rank, BODY_PART_TYPES::LEG)));
    Body_Parts.push_back(new Body_Part(Lot_Body_Part(Rank, BODY_PART_TYPES::LEG)));
}

Entity::Entity(Location location, ENTITY_TYPE type){
    Position = location;
    Type = type;
    Class = Lot_Class(location);

    if (Type != ENTITY_TYPE::ITEM){
        Specie = Specie_Descriptor(location);
        Base_Stats = Lot_Stats(this);

        // lot the roles
        for (int i = 0; i < Int_Range(0, Base_Stats.Power); i++){
            Roles.push_back(
                Lot_Role(location)
            );
        }

        // Lot random items for the entity
        for (auto* limb : Specie.Body_Parts){
            vector<Entity*> tmp = Lot_Items(limb, Position);

            // We put em here instead of the limb equip, because we want the entity to choose the right equipment based on the environment.
            this->Inventory.insert(this->Inventory.end(), tmp.begin(), tmp.end());
        }
    }
    else{
        // Entities dont need this, this is mainly for items.
        Base_Stats.Global = Lot_Attributes(this);
        Base_Stats.Local = Lot_Attributes(this);

    }

    // Run the tick for once to make sure everything is up to date.
    Tick();

    Info.ID = Construct_Name();
    Info.History = Construct_Description();
}

void Entity::AI(Body_Part* brain){

    // TODO: make all the UI for action making.

}

void Entity::Calculate_Passives(){
    for (auto* limb : Specie.Body_Parts){

        for (auto* equipped : limb->Equipped){

            for (auto& Attribute : Current_Effects.Attributes){
                if (Attribute.second < 1.f)
                    Attribute.second = max(equipped->Get_Attribute(Attribute.first, false) + Attribute.second, 2.f);


            }
        }
    }
}


void Entity::Calculate_Effects(){
    for (auto& Effect : Current_Effects.Attributes){
        // Multiplies with the direction vector.
        Stats.Attributes[Effect.first] *= Effect.second;
    }
}

void Entity::Tick(){
    ATTRIBUTES New_Stats = Current_Effects;    

    // TODO:
    // We can use the Current state and the all the passives + local + globals to make an vector which tells us the speed of some attributes going down or up.
    // This can be used as the "severity" scale factor

    // For each head the entity can make an decision per tick.
    for (auto* limb : Specie.Body_Parts)
        if (limb->Type == BODY_PART_TYPES::HEAD)
            AI(limb);

    // Addon to head decisions, the passives also must be calculated.
    Calculate_Passives();

    // Now calculate how the curses and negative/positive effects affect the main stats
    Calculate_Effects();
}

string Describe_Attribute_As_Adjective(bool is_positive){
    string Result = "";

    if (is_positive){
        Result = Positives[rand() % Positives.size()];
    } else {
        Result = Negatives[rand() % Negatives.size()];
    }

    return Result;
}


pair<ATTRIBUTE_TYPES, float> ATTRIBUTES::Get_Most_Aggressive(){
    float Most_Aggressive_Attribute_Value = 1.f;
    ATTRIBUTE_TYPES Most_Aggressive_Attribute = (ATTRIBUTE_TYPES)0;

    // Calculate the prefixes
    for (ATTRIBUTE_TYPES Current_Attribute = (ATTRIBUTE_TYPES)0; (int)Current_Attribute < (int)ATTRIBUTE_TYPES::END; Current_Attribute = (ATTRIBUTE_TYPES)((int)Current_Attribute + 1)){
        float Current_Value = Get(Current_Attribute);

        if (abs(Current_Value - 1.f) > abs(Most_Aggressive_Attribute_Value - 1.f)){
            Most_Aggressive_Attribute_Value = Current_Value;
            Most_Aggressive_Attribute = Current_Attribute;
        }
    }

    return make_pair(Most_Aggressive_Attribute, Most_Aggressive_Attribute_Value);
}

ATTRIBUTE_TYPES ATTRIBUTES::Get_Most_Low(){
    float Most_Low_Attribute_Value = 1.f;
    ATTRIBUTE_TYPES Most_Low_Attribute = (ATTRIBUTE_TYPES)0;

    for (auto i : Attributes){
        if (i.second < Most_Low_Attribute_Value){
            Most_Low_Attribute_Value = i.second;
            Most_Low_Attribute = i.first;
        }
    }

    return Most_Low_Attribute;
}

string Entity::Construct_Name(){
    return Name_Table[Int_Range(0, Name_Table.size() - 1)];
}

string Entity::Construct_Description(){
    string Result = "";

    return Result;
}
