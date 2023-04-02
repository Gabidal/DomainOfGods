#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <vector>
#include <string>

using namespace std;

class FVector3{
public:
    float X = 0;
    float Y = 0;
    float Z = 0;

    FVector3() = default;

    FVector3(float x, float y, float z){
        X = x;
        Y = y;
        Z = z;
    }

    FVector3(const FVector3& vec){
        X = vec.X;
        Y = vec.Y;
        Z = vec.Z;
    }

    FVector3& operator=(const FVector3& vec){
        X = vec.X;
        Y = vec.Y;
        Z = vec.Z;
        return *this;
    }

    FVector3 operator+(const FVector3& vec){
        return FVector3(X + vec.X, Y + vec.Y, Z + vec.Z);
    }

    FVector3 operator-(const FVector3& vec){
        return FVector3(X - vec.X, Y - vec.Y, Z - vec.Z);
    }

    FVector3 operator*(const FVector3& vec){
        return FVector3(X * vec.X, Y * vec.Y, Z * vec.Z);
    }

    FVector3 operator/(const FVector3& vec){
        return FVector3(X / vec.X, Y / vec.Y, Z / vec.Z);
    }

    FVector3 operator+(float num){
        return FVector3(X + num, Y + num, Z + num);
    }

    FVector3 operator-(float num){
        return FVector3(X - num, Y - num, Z - num);
    }

    FVector3 operator*(float num){
        return FVector3(X * num, Y * num, Z * num);
    }

    FVector3 operator/(float num){
        return FVector3(X / num, Y / num, Z / num);
    }

    FVector3& operator+=(const FVector3& vec){
        X += vec.X;
        Y += vec.Y;
        Z += vec.Z;
        return *this;
    }

    FVector3& operator-=(const FVector3& vec){
        X -= vec.X;
        Y -= vec.Y;
        Z -= vec.Z;
        return *this;
    }

    FVector3& operator*=(const FVector3& vec){
        X *= vec.X;
        Y *= vec.Y;
        Z *= vec.Z;
        return *this;
    }

    FVector3& operator/=(const FVector3& vec){
        X /= vec.X;
        Y /= vec.Y;
        Z /= vec.Z;
        return *this;
    }
};

class IVector3{
public:
    int X = 0;
    int Y = 0;
    int Z = 0;

    IVector3() = default;

    IVector3(int x, int y, int z){
        X = x;
        Y = y;
        Z = z;
    }

    IVector3(const IVector3& vec){
        X = vec.X;
        Y = vec.Y;
        Z = vec.Z;
    }

    IVector3& operator=(const IVector3& vec){
        X = vec.X;
        Y = vec.Y;
        Z = vec.Z;
        return *this;
    }

    IVector3 operator+(const IVector3& vec){
        return IVector3(X + vec.X, Y + vec.Y, Z + vec.Z);
    }

    IVector3 operator-(const IVector3& vec){
        return IVector3(X - vec.X, Y - vec.Y, Z - vec.Z);
    }

    IVector3 operator*(const IVector3& vec){
        return IVector3(X * vec.X, Y * vec.Y, Z * vec.Z);
    }

    IVector3 operator/(const IVector3& vec){
        return IVector3(X / vec.X, Y / vec.Y, Z / vec.Z);
    }

    IVector3 operator+(int num){
        return IVector3(X + num, Y + num, Z + num);
    }

    IVector3 operator-(int num){
        return IVector3(X - num, Y - num, Z - num);
    }

    IVector3 operator*(int num){
        return IVector3(X * num, Y * num, Z * num);
    }

    IVector3 operator/(int num){
        return IVector3(X / num, Y / num, Z / num);
    }

    IVector3& operator+=(const IVector3& vec){
        X += vec.X;
        Y += vec.Y;
        Z += vec.Z;
        return *this;
    }

    IVector3& operator-=(const IVector3& vec){
        X -= vec.X;
        Y -= vec.Y;
        Z -= vec.Z;
        return *this;
    }

    IVector3& operator*=(const IVector3& vec){
        X *= vec.X;
        Y *= vec.Y;
        Z *= vec.Z;
        return *this;
    }

    IVector3& operator/=(const IVector3& vec){
        X /= vec.X;
        Y /= vec.Y;
        Z /= vec.Z;
        return *this;
    }
};

enum class ENTITY_TYPE{
    UNKNOWN,
    ITEM,
};


// Rarity class like in Overlord
enum class CLASS{
    LOW,            // 20% of all
    MIDDLE,         // 40% of all
    HIGH,           // 30% of all
    TOP,            // 9% of all
    LEGACY,         // 99% of the 1%
    MAGICAL,        // 99% of the 0.01%
    RARE,           // 99% of the 0.0001%
    RELIC,          // 99% of the 0.000001%
    LEGENDARY,      // 99% of the 0.00000001%
    DIVINE,         // 99% of the 0.0000000001%
    GUILD,          // 99% of the 0.000000000001%
    CHAMPION,       // 99% of the 0.00000000000001%
    HERO,           // 99% of the 0.0000000000000001%
    WORLD,           // 1% of the  0.0000000000000001%

    END  // Just for counting.
};

// Define the probability ranges for each class
const double CLASS_Probabilities[] = {
    0.2,    // LOW
    0.4,    // MIDDLE
    0.3,    // HIGH
    0.09,   // TOP
    0.99 * 0.01,    // LEGACY
    0.99 * 0.0001,  // MAGICAL
    0.99 * 0.000001,   // RARE
    0.99 * 0.00000001,  // RELIC
    0.99 * 0.0000000001,    // LEGENDARY
    0.99 * 0.000000000001,  // DIVINE
    0.99 * 0.00000000000001,    // GUILD
    0.99 * 0.0000000000000001,  // CHAMPION
    0.99 * 0.000000000000000001,    // HERO
    0.01 * 0.0000000000000001, // WORLD
};

// The legendary Ascendancy rank from SCP-733
enum class RANK{
    NONE,           // 99% of all
    SUPERNATURAL,   // 99% of the 1%
    HALF_BLOOD,     // 99% of the 0.01%
    DEMIGOD,        // 99% of the 0.0001%
    FALSE_GOD,      // 99% of the 0.000001%
    GOD,            // 99% of the 0.00000001%
    TRUE_GOD,       // 99% of the 0.0000000001%
    DOMAIN_HOLDER,   // 1% of the  0.0000000001%

    END // Just for counting.
};

// Define the probability ranges for each rank
const double RANK_Probabilities[] = {
    0.99,   // NONE
    0.99 * 0.01,    // SUPERNATURAL
    0.99 * 0.0001,  // HALF_BLOOD
    0.99 * 0.000001,   // DEMIGOD
    0.99 * 0.00000001,  // FALSE_GOD
    0.99 * 0.0000000001,    // GOD
    0.99 * 0.000000000001,  // TRUE_GOD
    0.01 * 0.0000000000001, // DOMAIN_HOLDER
};

class Location{
public:
    FVector3 HIGH = {0, 0, 0};
    IVector3 LOW = {0, 0, 0};

    Location() = default;

    Location(FVector3 high, IVector3 low){
        HIGH = high;
        LOW = low;
    }

    Location(const Location& loc){
        HIGH = loc.HIGH;
        LOW = loc.LOW;
    }

    Location& operator=(const Location& loc){
        HIGH = loc.HIGH;
        LOW = loc.LOW;
        return *this;
    }

    Location operator+(const Location& loc){
        return Location(HIGH + loc.HIGH, LOW + loc.LOW);
    }

    Location operator-(const Location& loc){
        return Location(HIGH - loc.HIGH, LOW - loc.LOW);
    }

    Location operator*(const Location& loc){
        return Location(HIGH * loc.HIGH, LOW * loc.LOW);
    }

    Location operator/(const Location& loc){
        return Location(HIGH / loc.HIGH, LOW / loc.LOW);
    }

    Location operator+(int num){
        return Location(HIGH + num, LOW + num);
    }

    Location operator-(int num){
        return Location(HIGH - num, LOW - num);
    }

    Location operator*(int num){
        return Location(HIGH * num, LOW * num);
    }

    Location operator/(int num){
        return Location(HIGH / num, LOW / num);
    }

    Location& operator+=(const Location& loc){
        HIGH += loc.HIGH;
        LOW += loc.LOW;
        return *this;
    }

    Location& operator-=(const Location& loc){
        HIGH -= loc.HIGH;
        LOW -= loc.LOW;
        return *this;
    }

    Location& operator*=(const Location& loc){
        HIGH *= loc.HIGH;
        LOW *= loc.LOW;
        return *this;
    }

    Location& operator/=(const Location& loc){
        HIGH /= loc.HIGH;
        LOW /= loc.LOW;
        return *this;
    }
};

class STATS{
public:
    // Power describes everything, where 1 power equals to:
    // 1 Strength, 1 Damage, 1 Health, 1 Speed, 1 Defense, 1 Resistance, 1 Accuracy, 1 Evasion, 1 Crit Chance, 1 Crit Power
    // Then the equipped items decrease certain aspects or increase them.
    // The power is them multiplied by the RANK factor.
    int Power = 1;

    STATS() = default;

};

class ATTRIBUTES{
public:
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

    ATTRIBUTES() = default;

    ATTRIBUTES(const ATTRIBUTES& attr){
        Affect_Strength = attr.Affect_Strength;
        Affect_Damage = attr.Affect_Damage;
        Affect_Health = attr.Affect_Health;
        Affect_Speed = attr.Affect_Speed;
        Affect_Defense = attr.Affect_Defense;
        Affect_Heat_Resistance = attr.Affect_Heat_Resistance;
        Affect_Cold_Resistance = attr.Affect_Cold_Resistance;
        Affect_Electricity_Resistance = attr.Affect_Electricity_Resistance;
        Affect_Poison_Resistance = attr.Affect_Poison_Resistance;
        Affect_Acid_Resistance = attr.Affect_Acid_Resistance;
        Affect_Radiation_Resistance = attr.Affect_Radiation_Resistance;
        Affect_Psychic_Resistance = attr.Affect_Psychic_Resistance;
        Affect_Sonic_Resistance = attr.Affect_Sonic_Resistance;
        Affect_Light_Resistance = attr.Affect_Light_Resistance;
        Affect_Darkness_Resistance = attr.Affect_Darkness_Resistance;
        Affect_Magic_Resistance = attr.Affect_Magic_Resistance;
        Affect_Physical_Resistance = attr.Affect_Physical_Resistance;
        Affect_Mental_Resistance = attr.Affect_Mental_Resistance;
        Affect_Astral_Resistance = attr.Affect_Astral_Resistance;
        Affect_Dimensional_Resistance = attr.Affect_Dimensional_Resistance;
        Affect_Nuclear_Resistance = attr.Affect_Nuclear_Resistance;
        Affect_Biological_Resistance = attr.Affect_Biological_Resistance;
        Affect_Natural_Resistance = attr.Affect_Natural_Resistance;
        Affect_Explosive_Resistance = attr.Affect_Explosive_Resistance;
        Affect_Accuracy = attr.Affect_Accuracy;
        Affect_Evasion = attr.Affect_Evasion;
        Affect_Crit_Chance = attr.Affect_Crit_Chance;
        Affect_Crit_Power = attr.Affect_Crit_Power;
        Affect_Size = attr.Affect_Size;
    }

    ATTRIBUTES& operator=(const ATTRIBUTES& attr){
        Affect_Strength = attr.Affect_Strength;
        Affect_Damage = attr.Affect_Damage;
        Affect_Health = attr.Affect_Health;
        Affect_Speed = attr.Affect_Speed;
        Affect_Defense = attr.Affect_Defense;
        Affect_Heat_Resistance = attr.Affect_Heat_Resistance;
        Affect_Cold_Resistance = attr.Affect_Cold_Resistance;
        Affect_Electricity_Resistance = attr.Affect_Electricity_Resistance;
        Affect_Poison_Resistance = attr.Affect_Poison_Resistance;
        Affect_Acid_Resistance = attr.Affect_Acid_Resistance;
        Affect_Radiation_Resistance = attr.Affect_Radiation_Resistance;
        Affect_Psychic_Resistance = attr.Affect_Psychic_Resistance;
        Affect_Sonic_Resistance = attr.Affect_Sonic_Resistance;
        Affect_Light_Resistance = attr.Affect_Light_Resistance;
        Affect_Darkness_Resistance = attr.Affect_Darkness_Resistance;
        Affect_Magic_Resistance = attr.Affect_Magic_Resistance;
        Affect_Physical_Resistance = attr.Affect_Physical_Resistance;
        Affect_Mental_Resistance = attr.Affect_Mental_Resistance;
        Affect_Astral_Resistance = attr.Affect_Astral_Resistance;
        Affect_Dimensional_Resistance = attr.Affect_Dimensional_Resistance;
        Affect_Nuclear_Resistance = attr.Affect_Nuclear_Resistance;
        Affect_Biological_Resistance = attr.Affect_Biological_Resistance;
        Affect_Natural_Resistance = attr.Affect_Natural_Resistance;
        Affect_Explosive_Resistance = attr.Affect_Explosive_Resistance;
        Affect_Accuracy = attr.Affect_Accuracy;
        Affect_Evasion = attr.Affect_Evasion;
        Affect_Crit_Chance = attr.Affect_Crit_Chance;
        Affect_Crit_Power = attr.Affect_Crit_Power;
        Affect_Size = attr.Affect_Size;
        return *this;
    }

    ATTRIBUTES& operator+=(const ATTRIBUTES& attr){
        Affect_Strength += attr.Affect_Strength;
        Affect_Damage += attr.Affect_Damage;
        Affect_Health += attr.Affect_Health;
        Affect_Speed += attr.Affect_Speed;
        Affect_Defense += attr.Affect_Defense;
        Affect_Heat_Resistance += attr.Affect_Heat_Resistance;
        Affect_Cold_Resistance += attr.Affect_Cold_Resistance;
        Affect_Electricity_Resistance += attr.Affect_Electricity_Resistance;
        Affect_Poison_Resistance += attr.Affect_Poison_Resistance;
        Affect_Acid_Resistance += attr.Affect_Acid_Resistance;
        Affect_Radiation_Resistance += attr.Affect_Radiation_Resistance;
        Affect_Psychic_Resistance += attr.Affect_Psychic_Resistance;
        Affect_Sonic_Resistance += attr.Affect_Sonic_Resistance;
        Affect_Light_Resistance += attr.Affect_Light_Resistance;
        Affect_Darkness_Resistance += attr.Affect_Darkness_Resistance;
        Affect_Magic_Resistance += attr.Affect_Magic_Resistance;
        Affect_Physical_Resistance += attr.Affect_Physical_Resistance;
        Affect_Mental_Resistance += attr.Affect_Mental_Resistance;
        Affect_Astral_Resistance += attr.Affect_Astral_Resistance;
        Affect_Dimensional_Resistance += attr.Affect_Dimensional_Resistance;
        Affect_Nuclear_Resistance += attr.Affect_Nuclear_Resistance;
        Affect_Biological_Resistance += attr.Affect_Biological_Resistance;
        Affect_Natural_Resistance += attr.Affect_Natural_Resistance;
        Affect_Explosive_Resistance += attr.Affect_Explosive_Resistance;
        Affect_Accuracy += attr.Affect_Accuracy;
        Affect_Evasion += attr.Affect_Evasion;
        Affect_Crit_Chance += attr.Affect_Crit_Chance;
        Affect_Crit_Power += attr.Affect_Crit_Power;
        Affect_Size += attr.Affect_Size;
        return *this;
    }

    ATTRIBUTES& operator-=(const ATTRIBUTES& attr){
        Affect_Strength -= attr.Affect_Strength;
        Affect_Damage -= attr.Affect_Damage;
        Affect_Health -= attr.Affect_Health;
        Affect_Speed -= attr.Affect_Speed;
        Affect_Defense -= attr.Affect_Defense;
        Affect_Heat_Resistance -= attr.Affect_Heat_Resistance;
        Affect_Cold_Resistance -= attr.Affect_Cold_Resistance;
        Affect_Electricity_Resistance -= attr.Affect_Electricity_Resistance;
        Affect_Poison_Resistance -= attr.Affect_Poison_Resistance;
        Affect_Acid_Resistance -= attr.Affect_Acid_Resistance;
        Affect_Radiation_Resistance -= attr.Affect_Radiation_Resistance;
        Affect_Psychic_Resistance -= attr.Affect_Psychic_Resistance;
        Affect_Sonic_Resistance -= attr.Affect_Sonic_Resistance;
        Affect_Light_Resistance -= attr.Affect_Light_Resistance;
        Affect_Darkness_Resistance -= attr.Affect_Darkness_Resistance;
        Affect_Magic_Resistance -= attr.Affect_Magic_Resistance;
        Affect_Physical_Resistance -= attr.Affect_Physical_Resistance;
        Affect_Mental_Resistance -= attr.Affect_Mental_Resistance;
        Affect_Astral_Resistance -= attr.Affect_Astral_Resistance;
        Affect_Dimensional_Resistance -= attr.Affect_Dimensional_Resistance;
        Affect_Nuclear_Resistance -= attr.Affect_Nuclear_Resistance;
        Affect_Biological_Resistance -= attr.Affect_Biological_Resistance;
        Affect_Natural_Resistance -= attr.Affect_Natural_Resistance;
        Affect_Explosive_Resistance -= attr.Affect_Explosive_Resistance;
        Affect_Accuracy -= attr.Affect_Accuracy;
        Affect_Evasion -= attr.Affect_Evasion;
        Affect_Crit_Chance -= attr.Affect_Crit_Chance;
        Affect_Crit_Power -= attr.Affect_Crit_Power;
        Affect_Size -= attr.Affect_Size;
        return *this;
    }

    ATTRIBUTES& operator*=(const ATTRIBUTES& attr){
        Affect_Strength *= attr.Affect_Strength;
        Affect_Damage *= attr.Affect_Damage;
        Affect_Health *= attr.Affect_Health;
        Affect_Speed *= attr.Affect_Speed;
        Affect_Defense *= attr.Affect_Defense;
        Affect_Heat_Resistance *= attr.Affect_Heat_Resistance;
        Affect_Cold_Resistance *= attr.Affect_Cold_Resistance;
        Affect_Electricity_Resistance *= attr.Affect_Electricity_Resistance;
        Affect_Poison_Resistance *= attr.Affect_Poison_Resistance;
        Affect_Acid_Resistance *= attr.Affect_Acid_Resistance;
        Affect_Radiation_Resistance *= attr.Affect_Radiation_Resistance;
        Affect_Psychic_Resistance *= attr.Affect_Psychic_Resistance;
        Affect_Sonic_Resistance *= attr.Affect_Sonic_Resistance;
        Affect_Light_Resistance *= attr.Affect_Light_Resistance;
        Affect_Darkness_Resistance *= attr.Affect_Darkness_Resistance;
        Affect_Magic_Resistance *= attr.Affect_Magic_Resistance;
        Affect_Physical_Resistance *= attr.Affect_Physical_Resistance;
        Affect_Mental_Resistance *= attr.Affect_Mental_Resistance;
        Affect_Astral_Resistance *= attr.Affect_Astral_Resistance;
        Affect_Dimensional_Resistance *= attr.Affect_Dimensional_Resistance;
        Affect_Nuclear_Resistance *= attr.Affect_Nuclear_Resistance;
        Affect_Biological_Resistance *= attr.Affect_Biological_Resistance;
        Affect_Natural_Resistance *= attr.Affect_Natural_Resistance;
        Affect_Explosive_Resistance *= attr.Affect_Explosive_Resistance;
        Affect_Accuracy *= attr.Affect_Accuracy;
        Affect_Evasion *= attr.Affect_Evasion;
        Affect_Crit_Chance *= attr.Affect_Crit_Chance;
        Affect_Crit_Power *= attr.Affect_Crit_Power;
        Affect_Size *= attr.Affect_Size;
        return *this;
    }

    ATTRIBUTES& operator/=(const ATTRIBUTES& attr){
        Affect_Strength /= attr.Affect_Strength;
        Affect_Damage /= attr.Affect_Damage;
        Affect_Health /= attr.Affect_Health;
        Affect_Speed /= attr.Affect_Speed;
        Affect_Defense /= attr.Affect_Defense;
        Affect_Heat_Resistance /= attr.Affect_Heat_Resistance;
        Affect_Cold_Resistance /= attr.Affect_Cold_Resistance;
        Affect_Electricity_Resistance /= attr.Affect_Electricity_Resistance;
        Affect_Poison_Resistance /= attr.Affect_Poison_Resistance;
        Affect_Acid_Resistance /= attr.Affect_Acid_Resistance;
        Affect_Radiation_Resistance /= attr.Affect_Radiation_Resistance;
        Affect_Psychic_Resistance /= attr.Affect_Psychic_Resistance;
        Affect_Sonic_Resistance /= attr.Affect_Sonic_Resistance;
        Affect_Light_Resistance /= attr.Affect_Light_Resistance;
        Affect_Darkness_Resistance /= attr.Affect_Darkness_Resistance;
        Affect_Magic_Resistance /= attr.Affect_Magic_Resistance;
        Affect_Physical_Resistance /= attr.Affect_Physical_Resistance;
        Affect_Mental_Resistance /= attr.Affect_Mental_Resistance;
        Affect_Astral_Resistance /= attr.Affect_Astral_Resistance;
        Affect_Dimensional_Resistance /= attr.Affect_Dimensional_Resistance;
        Affect_Nuclear_Resistance /= attr.Affect_Nuclear_Resistance;
        Affect_Biological_Resistance /= attr.Affect_Biological_Resistance;
        Affect_Natural_Resistance /= attr.Affect_Natural_Resistance;
        Affect_Explosive_Resistance /= attr.Affect_Explosive_Resistance;
        Affect_Accuracy /= attr.Affect_Accuracy;
        Affect_Evasion /= attr.Affect_Evasion;
        Affect_Crit_Chance /= attr.Affect_Crit_Chance;
        Affect_Crit_Power /= attr.Affect_Crit_Power;
        Affect_Size /= attr.Affect_Size;
        return *this;
    }
};

class Entity{
protected:
    Location Position;
    ENTITY_TYPE Type;
    RANK Rank;
    CLASS Class;
    STATS Base_Stats;
    ATTRIBUTES Attributes;

    // For AST
    Entity* Holder = nullptr;
    vector<Entity*> Holding;
public:
    Entity(Location position, ENTITY_TYPE type);

    void Update_Stats();

    inline RANK Get_Rank(){ return Rank; }
    inline CLASS Get_Class(){ return Class; }
    inline Location Get_Position() { return Position; }

    inline int Get_Size(){ return Attributes.Affect_Size * Base_Stats.Power; }
    inline int Get_Strength(){ return Attributes.Affect_Strength * Base_Stats.Power; }
    inline int Get_Damage(){ return Attributes.Affect_Damage * Base_Stats.Power; }
    inline int Get_Health(){ return Attributes.Affect_Health * Base_Stats.Power; }
    inline int Get_Speed(){ return Attributes.Affect_Speed * Base_Stats.Power; }
    inline int Get_Defense(){ return Attributes.Affect_Defense * Base_Stats.Power; }
    inline int Get_Heat_Resistance(){ return Attributes.Affect_Heat_Resistance * Base_Stats.Power; }
    inline int Get_Cold_Resistance(){ return Attributes.Affect_Cold_Resistance * Base_Stats.Power; }
    inline int Get_Electricity_Resistance(){ return Attributes.Affect_Electricity_Resistance * Base_Stats.Power; }
    inline int Get_Poison_Resistance(){ return Attributes.Affect_Poison_Resistance * Base_Stats.Power; }
    inline int Get_Acid_Resistance(){ return Attributes.Affect_Acid_Resistance * Base_Stats.Power; }
    inline int Get_Radiation_Resistance(){ return Attributes.Affect_Radiation_Resistance * Base_Stats.Power; }
    inline int Get_Psychic_Resistance(){ return Attributes.Affect_Psychic_Resistance * Base_Stats.Power; }
    inline int Get_Sonic_Resistance(){ return Attributes.Affect_Sonic_Resistance * Base_Stats.Power; }
    inline int Get_Light_Resistance(){ return Attributes.Affect_Light_Resistance * Base_Stats.Power; }
    inline int Get_Darkness_Resistance(){ return Attributes.Affect_Darkness_Resistance * Base_Stats.Power; }
    inline int Get_Magic_Resistance(){ return Attributes.Affect_Magic_Resistance * Base_Stats.Power; }
    inline int Get_Physical_Resistance(){ return Attributes.Affect_Physical_Resistance * Base_Stats.Power; }
    inline int Get_Mental_Resistance(){ return Attributes.Affect_Mental_Resistance * Base_Stats.Power; }
    inline int Get_Astral_Resistance(){ return Attributes.Affect_Astral_Resistance * Base_Stats.Power; }
    inline int Get_Dimensional_Resistance(){ return Attributes.Affect_Dimensional_Resistance * Base_Stats.Power; }
    inline int Get_Nuclear_Resistance(){ return Attributes.Affect_Nuclear_Resistance * Base_Stats.Power; }
    inline int Get_Biological_Resistance(){ return Attributes.Affect_Biological_Resistance * Base_Stats.Power; }
    inline int Get_Natural_Resistance(){ return Attributes.Affect_Natural_Resistance * Base_Stats.Power; }
    inline int Get_Explosive_Resistance(){ return Attributes.Affect_Explosive_Resistance * Base_Stats.Power; }
    inline int Get_Accuracy(){ return Attributes.Affect_Accuracy * Base_Stats.Power; }
    inline int Get_Evasion(){ return Attributes.Affect_Evasion * Base_Stats.Power; }
    inline int Get_Crit_Chance(){ return Attributes.Affect_Crit_Chance * Base_Stats.Power; }
    inline int Get_Crit_Power(){ return Attributes.Affect_Crit_Power * Base_Stats.Power; }

};

#endif