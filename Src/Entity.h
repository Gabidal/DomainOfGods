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
    FLOOR,
    WALL,
    DOOR,
    CHEST,
    LIVING,
    TRAP,

    END
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

enum class ROLE{
    // These are roles that a entity can have, the roles are categorized into different themes.
    // NOTE: The roles do not contain races/species.

    // Adventurer roles
    HEALER,         // 5% to get
    TANK,           // 5% to get
    DPS,            // 5% to get
    MAGE,           // 5% to get
    SUPPORT,        // 5% to get
    ZOOLOGIST,      // 1% to get
    ARCHEOLOGIST,   // 1% to get
    HUNTER,         // 2.5% to get
    TRADER,         // 2.5% to get

    // Village roles
    BUILDER,        // 5% to get
    FARMER,         // 5% to get
    MINER,          // 5% to get
    GUARD,          // 3% to get
    WARDEN,         // 1% to get
    SCOUT,          // 10% to get
    HERO,           // 0.001% to get
    BARD,           // 6% to get
    NINJA,          // 2% to get

    // STRONGHOLD roles
    WIZARD,         // 5% to get
    NECROMANCER,    // 2% to get

    // Forest watcher
    FOREST_WATCHER, // 11% to get
    GARDENER,       // 5% to get
    WITCH,          // 2% to get

    // Town roles
    WITCH_DOCTOR,   // 0.01% to get
    PRIEST,         // 5% to get
    SHAMAN,         // 5% to get
    MAJOR,          // 1% to get
    
    // Army roles
    GENERAL,        // 0.1% to get
    COMMANDER,      // 0.2% to get
    CAPTAIN,        // 0.3% to get
    LIEUTENANT,     // 0.4% to get
    SERGEANT,       // 0.5% to get
    SOLDIER,        // 10% to get
    ARCHER,         // 10% to get
    SWORDSMAN,      // 5% to get
    PIKEMAN,        // 3% to get
    KNIGHT,         // 0.1% to get

    // castle roles
    PALADIN,        // 0.01% to get
    ARCHMAGE,       // 0.01% to get
    BISHOP,         // 0.01% to get
    KING,           // 0.001% to get
    QUEEN,          // 0.001% to get
    PRINCE,         // 0.002% to get
    PRINCESS,       // 0.002% to get
    NOBEL,          // 0.1% to get
    BARON,          // 0.1% to get
    BARONESS,       // 0.1% to get
    COUNT,          // 0.1% to get
    COUNTESS,       // 0.1% to get
    DUKE,           // 0.1% to get
    DUCHESS,        // 0.1% to get
    MARQUIS,        // 0.1% to get
    MARQUESS,       // 0.1% to get
    EARL,           // 0.1% to get

    // monster roles
    BOSS,           // 0.01% to get
    ELITE,          // 0.1% to get
    MINIBOSS,       // 0.2% to get
    MINIELITE,      // 0.5% to get
    MINION,         // 20% to get
    SLAVE,          // 15% to get

    END,
};

const double ROLE_Probabilities[] = {
    0.05,   // HEALER
    0.05,   // TANK
    0.05,   // DPS
    0.05,   // MAGE
    0.05,   // SUPPORT
    0.01,   // ZOOLOGIST
    0.01,   // ARCHEOLOGIST
    0.025,  // HUNTER
    0.025,  // TRADER

    0.05,   // BUILDER
    0.05,   // FARMER
    0.05,   // MINER
    0.03,   // GUARD
    0.01,   // WARDEN
    0.1,    // SCOUT
    0.00001,// HERO
    0.06,   // BARD
    0.02,   // NINJA

    0.05,   // WIZARD
    0.02,   // NECROMANCER

    0.11,   // FOREST_WATCHER
    0.05,   // GARDENER
    0.02,   // WITCH

    0.0001, // WITCH_DOCTOR
    0.05,   // PRIEST
    0.05,   // SHAMAN
    0.01,   // MAJOR

    0.001,  // GENERAL
    0.002,  // COMMANDER
    0.003,  // CAPTAIN
    0.004,  // LIEUTENANT
    0.005,  // SERGEANT
    0.1,    // SOLDIER
    0.1,    // ARCHER
    0.05,   // SWORDSMAN
    0.03,   // PIKEMAN
    0.001,  // KNIGHT

    0.0001, // PALADIN
    0.0001, // ARCHMAGE
    0.0001, // BISHOP
    0.00001,// KING
    0.00001,// QUEEN
    0.00002,// PRINCE
    0.00002,// PRINCESS
    0.001,  // NOBEL
    0.001,  // BARON
    0.001,  // BARONESS
    0.001,  // COUNT
    0.001,  // COUNTESS
    0.001,  // DUKE
    0.001,  // DUCHESS
    0.001,  // MARQUIS
    0.001,  // MARQUESS
    0.001,  // EARL

    0.0001, // BOSS
    0.001,  // ELITE
    0.002,  // MINIBOSS
    0.005,  // MINIELITE
    0.2,    // MINION
    0.15,   // SLAVE
};

enum class SPECIES{
    // INSECT
    BEE,            // 5% to get 
    ANT,            // 5% to get
    WASP,           // 5% to get
    SPIDER,         // 5% to get
    SCORPION,       // 5% to get
    MOTH,           // 5% to get

    // DRAGON
    WYVERN,         // 0.001% to get
    ALBERTINE,      // 0.001% to get
    DRAAKAR,        // 0.001% to get
    DRACON,         // 0.001% to get
    DRAKE,          // 0.0001% to get life has obstacles get over them.
    STORMWING,      // 0.001% to get
    FIRESOTRM,      // 0.001% to get
    ICECUTTER,      // 0.001% to get
    SHADOWHARBINGER,// 0.001% to get
    GODCENT,        // 0.00001% to get

    // MACHINE
    CYBORG,         // 0.01% to get
    ROBOT,          // 0.01% to get
    CYBERNETIC,     // 0.01% to get
    AUTOMATON,      // 0.01% to get
    MECHANICAL,     // 0.01% to get
    NANOBOT,        // 0.01% to get
    MICROBOT,       // 0.01% to get
    AI,             // 0.01% to get
    ANDROID,        // 0.01% to get
    BROKENGOD,      // 0.00001% to get
    MECHA,          // 0.01% to get

    // PLANT
    TREE,           // 10% to get
    FLOWER,         // 5% to get
    BUSH,           // 5% to get
    GRASS,          // 10% to get
    WEED,           // 5% to get
    MUSHROOM,       // 5% to get
    FUNGUS,         // 5% to get

    // ELEMENTAL
    FIRE,           // 0.01% to get
    ICE,            // 0.01% to get
    EARTH,          // 0.01% to get
    WATER,          // 0.01% to get
    AIR,            // 0.01% to get
    LIGHTNING,      // 0.01% to get
    WIND,           // 0.01% to get
    LIGHT,          // 0.001% to get
    DARKNESS,       // 0.001% to get

    // GOD
    // conceptual categorical gods
    WAR,            // 0.00001% to get
    PEACE,          // 0.00001% to get
    DEATH,          // 0.00001% to get
    LIFE,           // 0.0001% to get
    HUNGER,         // 0.00001% to get
    THIRST,         // 0.00001% to get
    SLEEP,          // 0.00001% to get
    LOVE,           // 0.00001% to get
    HATE,           // 0.00001% to get
    HARMONY,        // 0.00001% to get
    MIND,           // 0.00001% to get
    BODY,           // 0.00001% to get
    SPIRIT,         // 0.00001% to get
    FATE,           // 0.000001% to get
    DESTINY,        // 0.000001% to get
    TIME,           // 0.000001% to get

    // elemental categorized gods
    FIRE,           // 0.00001% to get
    ICE,            // 0.00001% to get
    EARTH,          // 0.00001% to get
    WATER,          // 0.00001% to get
    AIR,            // 0.00001% to get
    LIGHTNING,      // 0.00001% to get
    WIND,           // 0.00001% to get
    LIGHT,          // 0.00001% to get
    DARKNESS,       // 0.00001% to get
    MAGIC,          // 0.00001% to get
    RADIATION,      // 0.00001% to get
    ELECTRICITY,    // 0.00001% to get
    PLASMA,         // 0.00001% to get
    GRAVITY,        // 0.00001% to get
    MAGNETISM,      // 0.00001% to get
    MATTER,         // 0.00001% to get
    ENERGY,         // 0.00001% to get
    DARKENERGY,     // 0.00001% to get
    DARKMATTER,     // 0.00001% to get
    LIGHTENERGY,    // 0.00001% to get
    LIGHTMATTER,    // 0.00001% to get
    HEAT,           // 0.00001% to get
    COLD,           // 0.00001% to get
    DARK,           // 0.00001% to get
    LIGHT,          // 0.00001% to get
    ELECTRICITY,    // 0.00001% to get
    PLASMA,         // 0.00001% to get
    GRAVITY,        // 0.00001% to get

    // H.P Lovefractian conspetualized horror types
    OLDONE,         // 0.000001% to get
    FIRSTONE,       // 0.000001% to get
    THEGREATOLDONE, // 0.000001% to get
    SHAPESHIFTER,   // 0.000001% to get

    // SCP & H.P Lovecraft Cycle
    THETHING,                   // 0.0000001% to get
    THETHINGTHATSHOULDNOTBE,    // 0.0000001% to get
    THETHINGTHATCANNOTBE,       // 0.0000001% to get
    THETHINGTHATISNOT,          // 0.0000001% to get
    THETHINGTHATWASNOT,         // 0.0000001% to get
    THETHINGTHATWILLBE,         // 0.0000001% to get
    THETHINGTHATWILLNOTBE,      // 0.0000001% to get
    THETHINGTHATIS,             // 0.0000001% to get
    THETHINGTHATWAS,            // 0.0000001% to get

    // DOMAIN HOLDER
    DOMAINHOLDER,               // 0.00000000000001% to get

    // FOREST FOLK
    DRUID,          // 2% to get
    GOBLIN,         // 10% to get
    ORC,            // 10% to get
    TROLL,          // 5% to get
    ELF,            // 10% to get
    DWARF,          // 10% to get
    FAIRY,          // 1% to get
    NAGA,           // 1% to get
    HOBGOBLIN,      // 5% to get
    HUMAN,          // 50% to get

    END,
};

const double SPECIES_Probabilities[] = {
    0.05,   // BUSH
    0.1,    // GRASS
    0.05,   // WEED
    0.05,   // MUSHROOM
    0.05,   // FUNGUS

    0.0001, // FIRE
    0.0001, // ICE
    0.0001, // EARTH
    0.0001, // WATER
    0.0001, // AIR
    0.0001, // LIGHTNING
    0.0001, // WIND
    0.0001, // LIGHT
    0.0001, // DARKNESS

    0.000001,  // WAR
    0.000001,  // PEACE
    0.000001,  // DEATH
    0.000001,  // LIFE
    0.000001,  // HUNGER
    0.000001,  // THIRST
    0.000001,  // SLEEP
    0.000001,  // LOVE
    0.000001,  // HATE
    0.000001,  // HARMONY
    0.000001,  // MIND
    0.000001,  // BODY
    0.000001,  // SPIRIT
    0.000001,  // FATE
    0.000001,  // DESTINY
    0.000001,  // TIME

    0.000001,  // FIRE
    0.000001,  // ICE
    0.000001,  // EARTH
    0.000001,  // WATER
    0.000001,  // AIR
    0.000001,  // LIGHTNING
    0.000001,  // WIND
    0.000001,  // LIGHT
    0.000001,  // DARKNESS
    0.000001,  // MAGIC
    0.000001,  // RADIATION
    0.000001,  // ELECTRICITY
    0.000001,  // PLASMA
    0.000001,  // GRAVITY
    0.000001,  // MAGNETISM
    0.000001,  // MATTER
    0.000001,  // ENERGY
    0.000001,  // DARKENERGY
    0.000001,  // DARKMATTER
    0.000001,  // LIGHTENERGY
    0.000001,  // LIGHTMATTER
    0.000001,  // HEAT
    0.000001,  // COLD
    0.000001,  // DARK
    0.000001,  // LIGHT
    0.000001,  // ELECTRICITY
    0.000001,  // PLASMA
    0.000001,  // GRAVITY
    
    0.0000001,  // OLDONE
    0.0000001,  // FIRSTONE
    0.0000001,  // THEGREATOLDONE
    0.0000001,  // SHAPESHIFTER

    0.00000001, // THETHING
    0.00000001, // THETHINGTHATSHOULDNOTBE
    0.00000001, // THETHINGTHATCANNOTBE
    0.00000001, // THETHINGTHATISNOT
    0.00000001, // THETHINGTHATWASNOT
    0.00000001, // THETHINGTHATWILLBE
    0.00000001, // THETHINGTHATWILLNOTBE
    0.00000001, // THETHINGTHATIS
    0.00000001, // THETHINGTHATWAS

    0.000000000000001, // DOMAINHOLDER

    0.02,   // DRUID
    0.1,    // GOBLIN
    0.1,    // ORC
    0.05,   // TROLL
    0.1,    // ELF
    0.1,    // DWARF
    0.01,   // FAIRY
    0.01,   // NAGA
    0.05,   // HOBGOBLIN
    0.5,    // HUMAN
};

class Entity{
protected:
    Location Position;
    ENTITY_TYPE Type;
    RANK Rank;
    CLASS Class;
    STATS Base_Stats;
    ATTRIBUTES Attributes;
    vector<ROLE> Roles;
    SPECIES Specie;

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

    inline string Get_Name();
};

string To_String(Entity* e){
    
}


#endif