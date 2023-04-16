#include "Entity.h"
#include "Globals.h"
#include "../Dependencies/TerGen.h"
#include "Chaos.h"

#include <math.h>
#include <cmath>

void Location::Update_Chunk_Location(){
    IVector3 chunk_size = {GLOBALS::CHUNK_WIDTH, GLOBALS::CHUNK_HEIGHT, GLOBALS::CHUNK_DEPTH};

    CHUNK += HIGH % chunk_size;
}

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

    TerGen::Vector3 World_Position = {
        location.HIGH.X + location.CHUNK.X * GLOBALS::CHUNK_WIDTH,
        location.HIGH.Y + location.CHUNK.Y * GLOBALS::CHUNK_HEIGHT,
        location.HIGH.Z + location.CHUNK.Z * GLOBALS::CHUNK_DEPTH
    };

    double random = TerGen::Noise(World_Position, GLOBALS::Value_Noise); //(double)rand() / RAND_MAX;
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

constexpr float Get_Cap_Value(float cap_as_percentage){
    // Solve:
    // ((x - 0.5) / x) - cap
    // (x / x) - (0.5 / x) = cap
    // 1 - (0.5 / x) = cap
    // - (0.5 / x) = cap -1
    // 0.5 / x = -cap + 1
    // 0.5 = (-cap + 1) * x
    // 0.5/(-cap + 1) = ((-cap + 1) / (-cap + 1)) * x
    // 0.5/(1 - cap) = x
    return (0.5f / (1.f - cap_as_percentage));
}

bool Lot_Luck(Body_Part* limb){
    const float MAX_LUCK_CAP = Get_Cap_Value(GLOBALS::MAX_LUCK_PERCENTAGE);

    float AGGRESSIVENESS = 0.2f;

    // a - e^(-bx) * a
    float Max_Range = MAX_LUCK_CAP - (exp(-AGGRESSIVENESS * limb->Get(ATTRIBUTE_TYPES::LUCK))) * MAX_LUCK_CAP;

    return Float_Range(0.f, max(Max_Range, 0.001f)) > 0.5f;
}

// returns
float Transform_To_Non_Linear(float Full){
    return Full * 0.75f;
}

ATTRIBUTES Lot_Attribute_Scalers(Entity* e){
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

ATTRIBUTES Lot_Flat_Attributes(Specie_Descriptor* specie, Body_Part& limb){
    ATTRIBUTES Result;

    // First generate the pre determined attributes for the current specie.
    SPECIE_MINMAX MinMaxs = SPECIE_MINMAX_VALUES.at(specie->Specie);

    for (ATTRIBUTE_TYPES Attribute = (ATTRIBUTE_TYPES)0; (int)Attribute < (int)ATTRIBUTE_TYPES::END; Attribute = (ATTRIBUTE_TYPES)((int)Attribute + 1)){
        if (MinMaxs.Maximum_Attributes.Attributes.find(Attribute) != MinMaxs.Maximum_Attributes.Attributes.end()){
            Result.Attributes[Attribute] = Float_Range(MinMaxs.Minimum_Attributes.Attributes[Attribute], MinMaxs.Maximum_Attributes.Attributes[Attribute]);
        }
        else{
            // Preferably this would be erased, and all the stats are rang- limited in the JSONS.
            bool Extra_Modifier = Lot_Luck(&limb);

            if (Extra_Modifier){
                Result.Attributes[Attribute] = Float_Range(1.0f, (int)specie->Rank);
            }
        }
    }


    return Result;
}

float Body_Part::Get(ATTRIBUTE_TYPES attr){

    // The flat stat of the representing attribute.
    float Flat = Flat_Stats.Get(attr);

    if (Body){
        for (auto* limb : Body->Body_Parts){
            for (auto* equipped : limb->Equipped){
                if (limb != this && equipped->Get_Type() != ENTITY_TYPE::AURA)
                    continue;

                Flat *= equipped->Get_Attribute(attr);
            }
        }
    }   
    else{
        // This means that the limb has been cut off.
        return Flat;
    }

}

float Body_Part::Get_Local_Passives(ATTRIBUTE_TYPES attr){
    float Result = 0.0f;

    for (auto* equipped : Equipped){
        Result += equipped->Get_Attribute(attr);
    }

    return Result;
}

float Body_Part::Get_Global_Passives(ATTRIBUTE_TYPES attr){
    float Result = 0.0f;

    for (auto* limb : Body->Body_Parts){
        for (auto* equipped : limb->Equipped){
            if (equipped->Get_Type() != ENTITY_TYPE::AURA)
                continue;

            Result += equipped->Get_Attribute(attr);
        }
    }

}

vector<Entity*> Lot_Items(Body_Part* limb, Location position){
    vector<Entity*> Result;

    // these items will not be equipped asap, but the limb is presented here so that we generate only usable loot.
    // The  Int_Range(false, true) is because we dont want to fully equip all the area.
    for (int Current_Size = limb->Get(ATTRIBUTE_TYPES::SIZE); Current_Size > 0 && Lot_Luck(limb);){

        Entity* item = new Entity(position, ENTITY_TYPE::ITEM);

        Result.push_back(item);

        Current_Size -= item->Get_Attribute(ATTRIBUTE_TYPES::WEIGHT);
    }

    return Result;
}

Body_Part Lot_Body_Part(Specie_Descriptor* specie, BODY_PART_TYPES type = BODY_PART_TYPES::UNKNOWN){
    Body_Part Result;

    Result.Flat_Stats = Lot_Flat_Attributes(specie, Result);

    if (type == BODY_PART_TYPES::UNKNOWN)
        Result.Type = (BODY_PART_TYPES)Int_Range((int)BODY_PART_TYPES::UNKNOWN, (int)BODY_PART_TYPES::END);
    else
        Result.Type = type;

    Result.Priorities = {
        ATTRIBUTE_TYPES::HEALTH,
        ATTRIBUTE_TYPES::MANA,
        ATTRIBUTE_TYPES::HUNGER,
        ATTRIBUTE_TYPES::THIRST
    };

    return Result;
}

ENTITY_TYPE Lot_Entity_Type(){
    return (ENTITY_TYPE)Int_Range((int)ENTITY_TYPE::UNKNOWN, (int)ENTITY_TYPE::END);
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

    Body_Parts.push_back(new Body_Part(Lot_Body_Part(this, BODY_PART_TYPES::HEAD)));
    Body_Parts.push_back(new Body_Part(Lot_Body_Part(this, BODY_PART_TYPES::TORSO)));

    Body_Parts.push_back(new Body_Part(Lot_Body_Part(this, BODY_PART_TYPES::HAND)));
    Body_Parts.push_back(new Body_Part(Lot_Body_Part(this, BODY_PART_TYPES::HAND)));

    Body_Parts.push_back(new Body_Part(Lot_Body_Part(this, BODY_PART_TYPES::LEG)));
    Body_Parts.push_back(new Body_Part(Lot_Body_Part(this, BODY_PART_TYPES::LEG)));
}

Entity::Entity(Location position) : Entity(position, Lot_Entity_Type()){}

Entity::Entity(Location location, ENTITY_TYPE type){
    // Power is the descriptive value of an entity, whereas class is an upgradable value.
    Position = location;
    Type = type;
    Class = Lot_Class(location);

    if (Type == ENTITY_TYPE::ENTITY){
        Specie = Specie_Descriptor(location);

        // lot the talents for now and let the entity decide later on.
        for (int i = 0; i < Int_Range(0, (int)Specie.Rank); i++){
            Talent.push_back(
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
    else if (Type == ENTITY_TYPE::AURA || Type == ENTITY_TYPE::ITEM){
        

    }

    // Run the tick for once to make sure everything is up to date.
    Tick();

    Info = Construct_Name();
}

float Body_Part::Get_Power_Level(){
    float Result = 0.0f;

    for (auto* equipped : Equipped) Result += equipped->Get_Power_Level();

    for (auto& attr : Flat_Stats.Attributes) Result += attr.second; 
}

float Entity::Get_Power_Level(){
    float Result = 0.0f;

    // This will make sure that only equipped items are on display when scanning for power levels.
    for (auto* limb : Specie.Body_Parts) Result += limb->Get_Power_Level();

    // The change that this brings is so tiny that only HC, players will probably use.
    float Scaler = 1 + (1.f - SPECIES_Probabilities[(int)Specie.Specie]);
    Result *= Scaler;

    // This will only be applied to items anyway, so it wont be as an big affecter as the rank.
    Result *= max((int)Class, 1);

    // This is only for entities, so because we multiply it last it will also have the greatest affect. 
    Result *= max((int)Specie.Rank, 1);

    return Result;
}

Entity* Entity::Select_Target(vector<Entity*> nearby, ENTITY_TYPE type){
    float Own_Power_Level = Get_Power_Level();

    for (auto* ent : nearby){
        if (ent->Get_Type() != type)
            continue;

        if (ent->Get_Power_Level() <= Own_Power_Level)
            return ent;
    }

    return nullptr;
}

float Entity::Get_Distance(Entity* other){
    float Result = 0.f;

    IVector3 chunk_sub = other->Position.CHUNK - Position.CHUNK;
    FVector3 block_sub = other->Position.HIGH - Position.HIGH + chunk_sub;

    Result += sqrt(block_sub.X * block_sub.X + block_sub.Y * block_sub.Y + block_sub.Z * block_sub.Z);

    return Result;
}

// TASK SPACE

// The default do
void Task_Base::Do(){

}




// the consume do function
void Consume::Do(){
    // try to find any consumable items from the entity.
    for (auto& item : Limb->Body->Parent_Entity->Get_Holding()){
        if (item->Get_Type() != ENTITY_TYPE::CONSUMABLE)
            continue;

        // now check if the consumable even can fix the lacking attribute, if not then go to next consumable.
        if (item->Get_Attribute(Lacking_Attribute) <= 1.f)  // where lesser than 1 means negative, and 1 means attribute doesn't exist or it wont affect.
            continue;

        // maybe in need of transformation scaler.
        Limb->Flat_Stats.Attributes[Lacking_Attribute] *= item->Get_Attribute(Lacking_Attribute);

        // now also consume the consumable
        item->Update_Attribute(ATTRIBUTE_TYPES::HEALTH, item->Get_Attribute(Lacking_Attribute) / (2 / item->Get_Attribute(ATTRIBUTE_TYPES::EFFICIENCY)));

        // re-gen consumable if possible (potions)
        item->Tick();

        // if the consumable doesn't have any re-gen and its depleted, then remove the item.
        if (item->Get_Attribute(ATTRIBUTE_TYPES::HEALTH) <= 0.f)
            Limb->Body->Parent_Entity->Remove_Holding(item);
    }
}

// END OF TASK SPACE

// mundane tasks will usually contain tasks like: eating, drinking, sleeping, adventuring
void Entity::Stack_Mundane_Tasks(Body_Part* brain){



}

// Critical tasks are if HEALTH is near zero
void Entity::Stack_Critical_Tasks(Body_Part* brain){
    // check if the brains flat health is near zero
    float Current_Health_State = brain->Get(ATTRIBUTE_TYPES::HEALTH) / SPECIE_MINMAX_VALUES.at(Specie.Specie).Maximum_Attributes.Get(ATTRIBUTE_TYPES::HEALTH);

    if (Current_Health_State < 0.2f){
        Tasks.push_back(new Consume(ATTRIBUTE_TYPES::HEALTH));
    }

}

void Entity::AI(Body_Part* brain){

    // Randomize the priorities if the entity is high af.

    // TODO: make all the UI for action making.
    for (auto Priority : brain->Priorities){

        

    }

    
    Stack_Mundane_Tasks(brain);
    Stack_Critical_Tasks(brain);
    Re_Order_Tasks();
}

void Entity::Calculate_Passives(){
    // because of the nature of this function looping through the body parts, only specie::entities have passive calculations.
    for (auto* limb : Specie.Body_Parts){
        
        for (auto& attr : limb->Flat_Stats.Attributes){
            float Max_Attr_Value = SPECIE_MINMAX_VALUES.at(Specie.Specie).Maximum_Attributes.Get(attr.first);

            attr.second = min(limb->Get(attr.first), Max_Attr_Value);
        }

    }
}

// goes through all limbs and checks if their HP is lower than what can be, then use some of the hunger bar to re-gen HP.
void Entity::Passive_Heal_With(ATTRIBUTE_TYPES replenisher){
    for (auto* limb : Specie.Body_Parts){
        float Current_HP_Difference = abs(limb->Get(ATTRIBUTE_TYPES::HEALTH) - SPECIE_MINMAX_VALUES.at(Specie.Specie).Maximum_Attributes.Get(ATTRIBUTE_TYPES::HEALTH));

        //The hunger stat is always from 0.f to 1.f. So if the hunger is full then it will also heal fully.
        limb->Flat_Stats.Attributes[ATTRIBUTE_TYPES::HEALTH] += Transform_To_Non_Linear(Current_HP_Difference * limb->Get(replenisher));

        // only take a fraction of the hunger if the HP difference was larger than zero.
        limb->Flat_Stats.Attributes[replenisher] /= max(2 * (Current_HP_Difference / 10), 1.f);
    }
}

// Puts the critical tasks 
void Entity::Re_Order_Tasks(){
    // first clean done tasks.
    // breaks immediately if before done task is an undone task. 
    for (int i = Tasks.size() - 1; i >= 0 && Tasks[i]->Is_Done; i--){
        Tasks.erase(Tasks.begin() + i);
    }

    // sort vector list
    sort(Tasks.rbegin(), Tasks.rend(), [](Task_Base* a, Task_Base* b){
        return a->Is_Done > b->Is_Done;
    });
}

// After all the passives have been accounted for, we are going to apply them to the main flat stats.
void Entity::Calculate_Effects(){
    if (Type != ENTITY_TYPE::ENTITY)
        return;

    // The effect is diminished by the limb own local passives.
    // Globals could be affecting these "curses" way before the infliction of the values to the flat stats.
    for (auto& Effect : Current_Effects.Attributes){

        for (auto* limb : Specie.Body_Parts){

            // Because the effects are ranging from 0.0000001-esp to 1.99999+eps
            limb->Flat_Stats.Attributes[Effect.first] *= Effect.second;

            Effect.second *= limb->Get_Local_Passives(Effect.first);
        }
    }
}

void Entity::Tick(){
    ATTRIBUTES New_Stats = Current_Effects;    

    Passive_Heal_With(ATTRIBUTE_TYPES::HUNGER);
    Passive_Heal_With(ATTRIBUTE_TYPES::THIRST);

    // Now calculate how the curses and negative/positive effects affect the main stats
    Calculate_Effects();

    // This needs to be after effect calculation, since passives might hit ceiling even tho the effect should have been compensated and thus reached full usage.
    Calculate_Passives();

    // For each head the entity can make an decision per tick.
    for (auto* limb : Specie.Body_Parts)
        if (limb->Type == BODY_PART_TYPES::HEAD)
            AI(limb);
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

ATTRIBUTE_TYPES ATTRIBUTES::Get_Most_Aggressive(){
    float Most_High_Attribute_Value = 1.f;
    ATTRIBUTE_TYPES Most_High_Attribute = (ATTRIBUTE_TYPES)0;

    for (auto i : Attributes){
        if (i.second > Most_High_Attribute_Value){
            Most_High_Attribute_Value = i.second;
            Most_High_Attribute = i.first;
        }
    }

    return Most_High_Attribute;
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

String_Representation Entity::Construct_Name(){
    String_Representation Result;

    // the name is usually empty if not an living entity.
    if (Type == ENTITY_TYPE::ENTITY){
        Result.Name = Name_Table[rand() % (Name_Table.size() - 1)];
    }
    else if (Type == ENTITY_TYPE::ITEM){
        for (auto& attr : Current_Effects.Attributes){
            bool Is_Positive = attr.second >= 1.f;

            vector<const char*> variants;

            // We could use just vector instead of an pair, to then access the second by adding the boolean.
            if (Is_Positive)
                variants = ATTRIBUTE_DESCRIPTIONS.at(attr.first).second;
            else
                variants = ATTRIBUTE_DESCRIPTIONS.at(attr.first).first;

            Result.Name += string(variants[rand() % (variants.size() - 1)]) + " ";
        }
    }

    return Result;
}

