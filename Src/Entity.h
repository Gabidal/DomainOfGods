#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <vector>
#include <string>
#include <unordered_map>

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

enum class ATTRIBUTE_TYPES{
    STRENGTH,               // 10% to get
    DAMAGE,                 // 10% to get
    HEALTH,                 // 10% to get
    SPEED,                  // 10% to get
    DEFENSE,                // 10% to get
    ACCURACY,               // 10% to get
    EVASION,                // 10% to get
    CRIT_CHANCE,            // 5% to get
    CRIT_POWER,             // 5% to get
    SIZE_MULTIPLIER,        // 0.001% to get
    // All resistances      
    HEAT_RESISTANCE,        // 5% to get
    COLD_RESISTANCE,        // 5% to get
    ELECTRICITY_RESISTANCE, // 5% to get
    POISON_RESISTANCE,      // 2.5% to get
    ACID_RESISTANCE,        // 2.5% to get
    RADIATION_RESISTANCE,   // 0.001% to get
    PSYCHIC_RESISTANCE,     // 1% to get
    SONIC_RESISTANCE,       // 2% to get
    LIGHT_RESISTANCE,       // 3.5% to get
    DARKNESS_RESISTANCE,    // 3% to get
    MAGIC_RESISTANCE,       // 5% to get
    PHYSICAL_RESISTANCE,    // 5% to get
    MENTAl_RESISTANCE,      // 1% to get
    ASTRAL_RESISTANCE,      // 0.1% to get
    DIMENSIONAL_RESISTANCE, // 0.01% to get
    NUCLEAR_RESISTANCE,     // 0.001% to get
    BIOLOGICAL_RESISTANCE,  // 0.001% to get
    NATURAL_RESISTANCE,     // 0.001% to get
    EXPLOSIVE_RESISTANCE,   // 0.1% to get

    END
};

const double ATTRIBUTE_Probabilities[] = {
    0.1,    // STRENGTH
    0.1,    // DAMAGE
    0.1,    // HEALTH
    0.1,    // SPEED
    0.1,    // DEFENSE
    0.1,    // ACCURACY
    0.1,    // EVASION
    0.05,   // CRIT_CHANCE
    0.05,   // CRIT_POWER
    0.00001,    // SIZE_MULTIPLIER
    // All resistances      
    0.05,   // HEAT_RESISTANCE
    0.05,   // COLD_RESISTANCE
    0.05,   // ELECTRICITY_RESISTANCE
    0.025,  // POISON_RESISTANCE
    0.025,  // ACID_RESISTANCE
    0.0001, // RADIATION_RESISTANCE
    0.01,   // PSYCHIC_RESISTANCE
    0.02,   // SONIC_RESISTANCE
    0.035,  // LIGHT_RESISTANCE
    0.03,   // DARKNESS_RESISTANCE
    0.05,   // MAGIC_RESISTANCE
    0.05,   // PHYSICAL_RESISTANCE
    0.01,   // MENTAl_RESISTANCE
    0.001,  // ASTRAL_RESISTANCE
    0.0001, // DIMENSIONAL_RESISTANCE
    0.00001,    // NUCLEAR_RESISTANCE
    0.00001,    // BIOLOGICAL_RESISTANCE
    0.00001,    // NATURAL_RESISTANCE
    0.0001, // EXPLOSIVE_RESISTANCE

    1.0,    // END
};

class ATTRIBUTES{
public:
    unordered_map<ATTRIBUTE_TYPES, float> Attributes;

    ATTRIBUTES() = default;
    
    float Get(ATTRIBUTE_TYPES type){
        if (Attributes.find(type) != Attributes.end())
            return Attributes[type];
        else
            return 1.f;   // Passive.
    }

    // Operator overloads
    float operator[](ATTRIBUTE_TYPES type){
        return Get(type);
    }

    ATTRIBUTES& operator=(const ATTRIBUTES& attr){
        Attributes = attr.Attributes;
        return *this;
    }

    ATTRIBUTES& operator+=(const ATTRIBUTES& attr){
        for (auto& it : attr.Attributes){
            Attributes[it.first] += it.second;
        }
        return *this;
    }

    ATTRIBUTES& operator-=(const ATTRIBUTES& attr){
        for (auto& it : attr.Attributes){
            Attributes[it.first] -= it.second;
        }
        return *this;
    }

    ATTRIBUTES& operator*=(const ATTRIBUTES& attr){
        for (auto& it : attr.Attributes){
            Attributes[it.first] *= it.second;
        }
        return *this;
    }

    ATTRIBUTES& operator/=(const ATTRIBUTES& attr){
        for (auto& it : attr.Attributes){
            Attributes[it.first] /= it.second;
        }
        return *this;
    }

    ATTRIBUTES operator+(const ATTRIBUTES& attr){
        ATTRIBUTES temp = *this;
        temp += attr;
        return temp;
    }

    ATTRIBUTES operator-(const ATTRIBUTES& attr){
        ATTRIBUTES temp = *this;
        temp -= attr;
        return temp;
    }

    ATTRIBUTES operator*(const ATTRIBUTES& attr){
        ATTRIBUTES temp = *this;
        temp *= attr;
        return temp;
    }

    ATTRIBUTES operator/(const ATTRIBUTES& attr){
        ATTRIBUTES temp = *this;
        temp /= attr;
        return temp;
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
    inline float Get_Attribute(ATTRIBUTE_TYPES type){ return Attributes[type] * Base_Stats.Power; }

};

#endif