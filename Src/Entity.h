#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <vector>
#include <string>
#include <unordered_map>
#include <limits>
#include <cmath>
#include <math.h>
#include <algorithm>
#include <functional>

using namespace std;

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

    size_t operator()() const {
        // hash
        return (X * 73856093) ^ (Y * 19349663) ^ (Z * 83492791);
    }

    size_t operator()(const IVector3& key) const{
        return (*this)();
    }

    bool operator==(const IVector3& vec) const{
        return X == vec.X && Y == vec.Y && Z == vec.Z;
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

    IVector3 operator%(const IVector3& vec){
        return IVector3(X % vec.X, Y % vec.Y, Z % vec.Z);
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

    FVector3 operator%(const FVector3& vec){
        return FVector3(fmod(X, vec.X), fmod(Y, vec.Y), fmod(Z, vec.Z));
    }

    IVector3 operator%(const IVector3& vec){
        return IVector3((int)X % vec.X, (int)Y % vec.Y, (int)Z % vec.Z);
    }

    FVector3 operator+(const IVector3& vec){
        return FVector3(X + vec.X, Y + vec.Y, Z + vec.Z);
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

const vector<string> Name_Table = {
    "Aaron",
    "Abraham",
    "Adam",
    "Adrian",
    "Alan",
    "Albert",
    "Alexander",
    "Andrew",
    "Anthony",
    "Arthur",
    "Austin",
    "Benjamin",
    "Bernard",
    "Billy",
    "Blake",
    "Bob",
    "Bobby",
    "Bradley",
    "Brandon",
    "Brendan",
    "Brian",
    "Bruce",
    "Bryan",
    "Carl",
    "Charles",
    "Christian",
    "Christopher",
    "Clarence",
    "Clifford",
    "Clifton",
    "Clinton",
    "Colin",
    "Connor",
    "Curtis",
    "Dale",
    "Daniel",
    "Darren",
    "David",
    "Dean",
    "Dennis",
    "Derek",
    "Derrick",
    "Dillon",
    "Dominic",
    "Donald",
    "Douglas",
    "Dylan",
    "Edward",
    "Eric",
    "Eugene",
    "Evan",
    "Frank",
    "Franklin",
    "Fred",
    "Frederick",
    "Gary",
    "George",
    "Gerald",
    "Gilbert",
    "Gordon",
    "Gregory",
    "Harold",
    "Harry",
    "Henry",
    "Howard",
    "Hugh",
    "Ian",
    "Isaac",
    "Jack",
    "Jacob",
    "Jake",
    "James",
    "Jason",
    "Jeffrey",
    "Jeremy",
    "Jerry",
    "Joe",
    "Joel",
    "John",
    "Jonathan",
    "Joseph",
    "Joshua",
    "Justin",
    "Keith",
    "Kenneth",
    "Kevin",
    "Kyle",
    "Lance",
    "Larry",
    "Lawrence",
    "Lee",
    "Leo",
    "Leonard",
    "Leroy",
    "Leslie",
    "Lester",
    "Lewis",
    "Liam",
    "Lloyd",
    "Logan",
    "Louis",
    "Lucas",
    "Luther",
    "Malcolm",
    "Marcus",
    "Marvin",
    "Martin",
    "Matthew",
    "Maurice",
    "Max",
    "Melvin",
    "Michael",
    "Milton",
    "Nathan",
    "Neil",
    "Nicholas",
    "Noah",
    "Oliver",
    "Oscar",
    "Owen",
    "Patrick",
    "Paul",
    "Peter",
    "Philip",
    "Phillip",
    "Phillip",
    "Ralph",
    "Randy",
    "Raymond",
    "Reginald",
    "Richard",
    "Robert",
    "Roger",
    "Ronald",
    "Roy",
    "Russell",
    "Ryan",
    "Samuel",
    "Sean",
    "Sebastian",
    "Seth",
    "Shane",
    "Shawn",
    "Sidney",
    "Simon",
    "Stephen",
    "Steven",
    "Stewart",
    "Terry",
    "Theodore",
    "Thomas",
    "Timothy",
    "Trevor",
    "Victor",
    "Vincent",
    "Warren",
    "Wayne",
    "Wesley",
    "William",
    "Zachary",
};

enum class ENTITY_TYPE{
    UNKNOWN,
    
    ITEM,       // Item, like sword or armor.
    
    CONSUMABLE, // food, potion, although potions differ from food when they have regeneration

    ENTITY,     // Living thing.
    
    AURA,       // GLOBALS PASSIVES, like re-gen aura. healing.

    SKILL,      // SKILL ability, like attack or teleportation.

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

// Descriptive names about the class
const vector<const char*> CLASS_Names[] = {
    {"common", "low quality", "low level", "crappy", "worthless", "useless", "garbage", "trash"},                           // LOW
    {"uncommon", "medium quality", "medium level", "decent", "average", "mediocre", "okay", "good"},                        // MIDDLE
    {"rare", "high quality", "high level", "fine", "valuable", "nice", "excellent", "great"},                               // HIGH
    {"epic", "top quality", "top level", "epic", "legendary", "awesome", "amazing"},                               // TOP
    {"legacy", "rustic", "old", "ancient", "vintage", "antique", "rusty"},                                                  // LEGACY
    {"magic", "other world", "mysterious", "enchanted"},                                                                // MAGICAL
    {"rare", "valuable", "shiny", "epic"},                                                      // RARE
    {"relic", "runic", "rune", "craftian"},                                              // RELIC
    {"legendary", "mythical", "secret"},              // LEGENDARY
    {"divine", "holy", "glow", "angel"},                                      // DIVINE
    {"guild", "treasure", "nobel"},                                              // GUILD
    {"champion", "nation", "perfect"},                      // CHAMPION
    {"hero", "high-champion", "god slayer", "destruction", "one piece"},                                                      // HERO
    {"world", "universe", "multiverse", "omnipotent", "omniscient", "god", "domain"}
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
    std::numeric_limits<double>::min(), // DOMAIN_HOLDER
};

const vector<const char*> RANK_Names[] = {
    {"dull", "plain", "boring", "creped", "low-life"}, // NONE
    {"supernatural", "other worldly", "mysterious", "magician"},    // SUPERNATURAL
    {"half blood", "creped", "disgusting", "waste", "trash"},    // HALF_BLOOD
    {"demigod", "half god", "half celestial", "half divine", "demon", "unholy", "creped"},  // DEMIGOD
    {"false god", "false deity", "worshipped", "holy"},    // FALSE_GOD
    {"god", "deity", "celestial", "divine", "legendary"},    // GOD
    {"true god", "one above gods", "La Persona Superiore a Dio", "puppeteer"},  // TRUE_GOD
    {"world keeper", "world", "universe", "truth", "entropy", "from far beyond"} // DOMAIN_HOLDER
};

class Location{
public:
    FVector3 HIGH = {0, 0, 0};
    IVector3 CHUNK = {0, 0, 0};

    Location() = default;

    Location(FVector3 high, IVector3 low){
        HIGH = high;
        CHUNK = low;
    }

    Location(const Location& loc){
        HIGH = loc.HIGH;
        CHUNK = loc.CHUNK;
    }

    void Update_Chunk_Location();

    Location& operator=(const Location& loc){
        HIGH = loc.HIGH;
        CHUNK = loc.CHUNK;
        return *this;
    }

    Location operator+(const Location& loc){
        return Location(HIGH + loc.HIGH, CHUNK + loc.CHUNK);
    }

    Location operator-(const Location& loc){
        return Location(HIGH - loc.HIGH, CHUNK - loc.CHUNK);
    }

    Location operator*(const Location& loc){
        return Location(HIGH * loc.HIGH, CHUNK * loc.CHUNK);
    }

    Location operator/(const Location& loc){
        return Location(HIGH / loc.HIGH, CHUNK / loc.CHUNK);
    }

    Location operator+(int num){
        return Location(HIGH + num, CHUNK + num);
    }

    Location operator-(int num){
        return Location(HIGH - num, CHUNK - num);
    }

    Location operator*(int num){
        return Location(HIGH * num, CHUNK * num);
    }

    Location operator/(int num){
        return Location(HIGH / num, CHUNK / num);
    }

    Location& operator+=(const Location& loc){
        HIGH += loc.HIGH;
        CHUNK += loc.CHUNK;
        return *this;
    }

    Location& operator-=(const Location& loc){
        HIGH -= loc.HIGH;
        CHUNK -= loc.CHUNK;
        return *this;
    }

    Location& operator*=(const Location& loc){
        HIGH *= loc.HIGH;
        CHUNK *= loc.CHUNK;
        return *this;
    }

    Location& operator/=(const Location& loc){
        HIGH /= loc.HIGH;
        CHUNK /= loc.CHUNK;
        return *this;
    }
};

enum class ATTRIBUTE_TYPES{
    // Physicals
    HEALTH,               // 10% to get,       "unkind", "shamed", "hating" | "Kind", "Caring", "Loving"
    HUNGER,               // 10% to get,       "hungry" | "filling", "delicious".           Ranging from 0.f to 1.f independet if it is flat or scaling stat.
    THIRST,               // 10% to get,       "thirsty" | "refreshing", "delicious"
    STRENGTH,             // 10% to get,       "weak", | "strong"
    DEXTERITY,            // 10% to get,       "clumsy" | "deft"
    SIZE,                 // 10% to get,       "tiny" | "massive"
    WEIGHT,               // 10% to get,       "light", "levitating", "hollow" | "fat", "abessive", "your mom"
    REACH,               // 10% to get,        "short" | "long"

    // armour stuff
    ARMOUR,             // 10% to get,    "fragile armour" | "protective armour", "armour"
    // agility == evasion

    // attack stuff
    ARMOUR_PENETRATION, // 10% to get,     "dull", | "Piercing", "Sharp", "spiky", "rough", "weapon"
    // attacks speed == (agility + strength) / 2
    FIRE_DAMAGE,       // 10% to get,      "cold" | "Fire", "Flaming", "Burning"
    ICE_DAMAGE,        // 10% to get,      "hot" | "cold", "icy", "frozen"
    ELECTRICITY_DAMAGE, // 10% to get,    "insulated" | "electric", "shocking", "lightning"

    // movement stuff
    AGILITY,              // 10% to get,      "crippled" | "athletic"
    // speed is for movement speed, whereas agility is the aerobatics in a fight.
    SPEED,                  // 10% to get,     "slow" | "fast", "teleporting"
    VELOCITY,

    // Mentals
    INTELLIGENCE,         // 10% to get,      "stupid" | "wise"
    MANA,                 // 10% to get,      "" | "arcane", "magical"
    SANITY,               // 10% to get,      "insane", "murderous" | "sane"

    // MISC
    LUCK,                 // 10% to get,      "unlucky" | "lucky

    // Resistances
    HEAT_RESISTANCE,      // 10% to get,     "burning", "fire caching", "flammable" | "fireproof", "heatproof"
    COLD_RESISTANCE,      // 10% to get,    "frozen", "icy", "cold" | "coldproof", "iceproof", "insulated"
    ELECTRICITY_RESISTANCE, // 10% to get, "shocking", "lightning", "electric", "zapping" | "electrical", "insulated"

    EFFICIENCY,           // 10% to get,     "inefficient" | "efficient"

    END
};

const unordered_map<ATTRIBUTE_TYPES, pair<vector<const char*>, vector<const char*>>> ATTRIBUTE_DESCRIPTIONS = {
    {ATTRIBUTE_TYPES::HEALTH, {{"unkind", "shamed", "hating"}, {"Kind", "Caring", "Loving"}}},
    {ATTRIBUTE_TYPES::HUNGER, {{"hungry"}, {"filling", "delicious"}}},
    {ATTRIBUTE_TYPES::THIRST, {{"thirsty"}, {"refreshing", "delicious"}}},
    {ATTRIBUTE_TYPES::STRENGTH, {{"weak"}, {"strong"}}},
    {ATTRIBUTE_TYPES::DEXTERITY, {{"clumsy"}, {"deft"}}},
    {ATTRIBUTE_TYPES::SIZE, {{"tiny"}, {"massive"}}},
    {ATTRIBUTE_TYPES::WEIGHT, {{"light", "levitating", "hollow"}, {"fat", "abessive", "your mom"}}},
    {ATTRIBUTE_TYPES::REACH, {{"short"}, {"long"}}},

    {ATTRIBUTE_TYPES::ARMOUR, {{"fragile armour"}, {"protective armour", "armour"}}},
    {ATTRIBUTE_TYPES::ARMOUR_PENETRATION, {{"dull"}, {"Piercing", "Sharp", "spiky", "rough", "weapon"}}},
    {ATTRIBUTE_TYPES::FIRE_DAMAGE, {{"cold"}, {"Fire", "Flaming", "Burning"}}},
    {ATTRIBUTE_TYPES::ICE_DAMAGE, {{"hot"}, {"cold", "icy", "frozen"}}},
    {ATTRIBUTE_TYPES::ELECTRICITY_DAMAGE, {{"insulated"}, {"electric", "shocking", "lightning"}}},

    {ATTRIBUTE_TYPES::AGILITY, {{"crippled"}, {"athletic"}}},
    {ATTRIBUTE_TYPES::SPEED, {{"slow"}, {"fast", "teleporting"}}},
    {ATTRIBUTE_TYPES::VELOCITY, {{"slow"}, {"fast", "teleporting"}}},

    {ATTRIBUTE_TYPES::INTELLIGENCE, {{"stupid"}, {"wise"}}},
    {ATTRIBUTE_TYPES::MANA, {{}, {"arcane", "magical"}}},
    {ATTRIBUTE_TYPES::SANITY, {{"insane", "murderous"}, {"sane"}}},
    {ATTRIBUTE_TYPES::LUCK, {{"unlucky"}, {"lucky"}}},

    {ATTRIBUTE_TYPES::HEAT_RESISTANCE, {{"burning", "fire caching", "flammable"}, {"fireproof", "heatproof"}}},
    {ATTRIBUTE_TYPES::COLD_RESISTANCE, {{"frozen", "icy", "cold"}, {"coldproof", "iceproof", "insulated"}}},
    {ATTRIBUTE_TYPES::ELECTRICITY_RESISTANCE, {{"shocking", "lightning", "electric", "zapping"}, {"electrical", "insulated"}}},
    {ATTRIBUTE_TYPES::EFFICIENCY, {{"inefficient"}, {"efficient"}}},
};

const double ATTRIBUTE_Probabilities[] = {
    0.1,    // HEALTH
    0.1,    // HUNGER
    0.1,    // THIRST
    0.1,    // STRENGTH
    0.1,    // DEXTERITY
    0.1,    // SIZE
    0.1,    // WEIGHT
    0.1,    // REACH

    0.1,    // ARMOUR
    0.1,    // ARMOUR_PENETRATION

    0.1,    // FIRE_DAMAGE
    0.1,    // ICE_DAMAGE
    0.1,    // ELECTRICITY_DAMAGE

    0.1,    // AGILITY
    0.1,    // SPEED
    0.1,    // VELOCITY

    0.1,    // INTELLIGENCE
    0.1,    // MANA
    0.1,    // SANITY

    0.1,    // LUCK

    0.1,    // HEAT_RESISTANCE
    0.1,    // COLD_RESISTANCE
    0.1,    // ELECTRICITY_RESISTANCE

    0.1,    // EFFICIENCY

    1.0,    // END
};

const vector<const char*> ATTRIBUTE_Names[] = {
    {"health", "life"}, // HEALTH
    {"hunger", "food"}, // HUNGER
    {"thirst", "water"}, // THIRST
    {"strength"}, // STRENGTH
    {"dexterity"}, // DEXTERITY
    {"size"}, // SIZE
    {"weight"}, // WEIGHT
    {"reach"}, // REACH

    {"armour"}, // ARMOUR
    {"armour penetration", "armour-penetration", "ap"}, // ARMOUR_PENETRATION

    {"fire damage", "fire-damage", "fire", "flame"}, // FIRE_DAMAGE
    {"ice damage", "ice-damage", "ice"}, // ICE_DAMAGE
    {"electricity damage", "electricity-damage", "electricity", "electric"}, // ELECTRICITY_DAMAGE

    {"agility"}, // AGILITY
    {"speed"}, // SPEED
    {"velocity"}, // VELOCITY

    {"intelligence"}, // INTELLIGENCE
    {"mana", "magic"}, // MANA
    {"sanity"}, // SANITY

    {"luck"}, // LUCK

    {"heat resistance", "heat-resistance", "heat"}, // HEAT_RESISTANCE
    {"cold resistance", "cold-resistance", "cold"}, // COLD_RESISTANCE
    {"electricity resistance", "electricity-resistance", "electricity"}, // ELECTRICITY_RESISTANCE

    {"efficiency", "efficency"}, // EFFICIENCY

    {"", ""},
};

class ATTRIBUTES{
public:
    unordered_map<ATTRIBUTE_TYPES, float> Attributes;

    ATTRIBUTES() = default;
    ATTRIBUTES(ATTRIBUTE_TYPES type, float value){
        Attributes[type] = value;
    }
    ATTRIBUTES(vector<pair<ATTRIBUTE_TYPES, float>> values){
        for (auto& it : values){
            Attributes[it.first] = it.second;
        }
    }

    float Get(ATTRIBUTE_TYPES type) const{
        if (Attributes.find(type) != Attributes.end())
            return Attributes.at(type);
        else
            return 1.f;   // Passive.
    }

    ATTRIBUTE_TYPES Get_Most_Aggressive();

    ATTRIBUTE_TYPES Get_Most_Low();

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

const vector<const char*> ROLE_Names[] = {
    {"healer", "medic", "doctor", "nurse", "surgeon", "therapist", "psychiatrist", "pharmacist"},
    {"tank", "defender", "protector", "guardian", "shield", "shielder", "shieldbearer", "shieldguard"},
    {"dps", "damage", "damage dealer", "damage dealer", "damage dealer", "damage dealer", "damage dealer", "damage dealer"},
    {"mage", "wizard", "sorcerer", "warlock", "enchanter", "conjurer", "illusionist", "illusionist"},
    {"support", "supporter", "supporter", "supporter", "supporter", "supporter", "supporter", "supporter"},
    {"zookeeper", "zoologist", "zoologist", "zoologist", "zoologist", "zoologist", "zoologist", "zoologist"},
    {"archaeologist"},
    {"hunter", "hunter", "hunter", "hunter", "hunter", "hunter", "hunter", "hunter"},
    {"trader", "trader", "trader", "trader", "trader", "trader", "trader", "trader"},

    {"builder", "builder", "builder", "builder", "builder", "builder", "builder", "builder"},
    {"farmer", "farmer", "farmer", "farmer", "farmer", "farmer", "farmer", "farmer"},
    {"miner", "miner", "miner", "miner", "miner", "miner", "miner", "miner"},
    {"guard", "guard", "guard", "guard", "guard", "guard", "guard", "guard"},
    {"warden", "warden", "warden", "warden", "warden", "warden", "warden", "warden"},
    {"scout", "scout", "scout", "scout", "scout", "scout", "scout", "scout"},
    {"hero", "hero", "hero", "hero", "hero", "hero", "hero", "hero"},
    {"bard", "bard", "bard", "bard", "bard", "bard", "bard", "bard"},
    {"ninja", "ninja", "ninja", "ninja", "ninja", "ninja", "ninja", "ninja"},

    {"wizard"},
    {"necromancer"},

    {"forest watcher"},
    {"gardener"},
    {"witch"},
    {"witch doctor"},
    {"priest"},
    {"shaman"},
    {"major"},
    {"general"},
    {"commander"},
    {"captain"},
    {"lieutenant"},
    {"sergeant"},
    {"soldier"},
    {"archer"},
    {"swordsman"},
    {"pikeman"},
    {"knight"},
    {"paladin"},
    {"archmage"},
    {"bishop"},
    {"king"},
    {"queen"},
    {"prince"},
    {"princess"},
    {"noble"},
    {"baron"},
    {"baroness"},
    {"count"},
    {"countess"},
    {"duke"},
    {"duchess"},
    {"marquis"},
    {"marquess"},
    {"earl"},
    {"boss"},
    {"elite"},
    {"miniboss"},
    {"minielite"},
    {"minion"},
    {"slave"},

    {"none"}
};

enum class SPECIES{
    // First are the classified entity species that are almost omnipotent
    // Light potent
    ANGEL,          // std::numeric_limits<double>::min()
    GRACELING,     // std::numeric_limits<double>::min()

    // lesser light
    DEMON,          // std::numeric_limits<double>::min()
    AGONIST,       // std::numeric_limits<double>::min()

    // Then are all the most rares species
    DRAGON,         // 0.00001% to get
    ELEMENTAL,      // 0.00001% to get

    // secondary rare species
    MECHANITE,      // 0.001% to get
    FAIRY,          // 0.001% to get
    VAMPIRE,        // 0.002% to get

    // uncommon species
    WEREWOLF,       // 0.01% to get
    GHOUL,          // 0.01% to get
    ZOMBIE,         // 0.05% to get
    SKELETON,       // 0.05% to get

    // common species
    ELF,           // 25% to get
    DWARF,         // 25% to get
    GOBLIN,        // 25% to get
    HUMAN,         // 25% to get

    UNKNOWN,
    END,
};

const double SPECIES_Probabilities[] = {
    std::numeric_limits<double>::min(),         // ANGEL
    std::numeric_limits<double>::min(),        // GRACELING

    std::numeric_limits<double>::min(),         // DEMON
    std::numeric_limits<double>::min(),        // AGONIST

    0.00001,                                    // DRAGON
    0.00001,                                    // ELEMENTAL

    0.001,                                      // MECHANITE
    0.001,                                      // FAIRY
    0.002,                                      // VAMPIRE

    0.01,                                       // WEREWOLF
    0.01,                                       // GHOUL
    0.05,                                       // ZOMBIE
    0.05,                                       // SKELETON

    0.25,                                       // ELF
    0.25,                                       // DWARF
    0.25,                                       // GOBLIN
    0.25,                                       // HUMAN
};

const string SPECIES_Names[] = {
    "angel",
    "graceling",

    "demon",
    "agonist",

    "dragon",
    "elemental",

    "mechanite",
    "fairy",
    "vampire",

    "werewolf",
    "ghoul",
    "zombie",
    "skeleton",

    "elf",
    "dwarf",
    "goblin",
    "human",
};

class SPECIE_MINMAX{
public:
    ATTRIBUTES Minimum_Attributes;
    ATTRIBUTES Maximum_Attributes;

    SPECIE_MINMAX() = default;
    SPECIE_MINMAX(ATTRIBUTES min, ATTRIBUTES max) : Minimum_Attributes(min), Maximum_Attributes(max) {}
};

const unordered_map<SPECIES, SPECIE_MINMAX> SPECIE_MINMAX_VALUES = {
    // ANGEL specie limits and minimum attribute informations
    {SPECIES::ANGEL, {
        // Min values
        {{
            {ATTRIBUTE_TYPES::HEALTH, std::numeric_limits<float>::max() / 2},
            {ATTRIBUTE_TYPES::MANA, std::numeric_limits<float>::max() / 2},
        }},
        // Max values
        {{
            {ATTRIBUTE_TYPES::HEALTH, std::numeric_limits<float>::max()},
            {ATTRIBUTE_TYPES::MANA, std::numeric_limits<float>::max()},
        }}
    }},
    // GRACELING specie limits and minimum attribute informations
    {SPECIES::GRACELING, {
        // Min values
        {{
            {ATTRIBUTE_TYPES::HEALTH, std::numeric_limits<float>::max() / 2},
            {ATTRIBUTE_TYPES::MANA, std::numeric_limits<float>::max() / 2},
        }},
        // Max values
        {{
            {ATTRIBUTE_TYPES::HEALTH, std::numeric_limits<float>::max()},
            {ATTRIBUTE_TYPES::MANA, std::numeric_limits<float>::max()},
        }}
    }},
    // DEMON specie limits and minimum attribute informations
    {SPECIES::DEMON, {
        // Min values
        {{
            {ATTRIBUTE_TYPES::HEALTH, std::numeric_limits<float>::max() / 4},
            {ATTRIBUTE_TYPES::MANA, std::numeric_limits<float>::max() / 4},
        }},
        // Max values
        {{
            {ATTRIBUTE_TYPES::HEALTH, std::numeric_limits<float>::max() / 2},
            {ATTRIBUTE_TYPES::MANA, std::numeric_limits<float>::max() / 2},
        }}
    }},
    // AGONIST specie limits and minimum attribute informations
    {SPECIES::AGONIST, {
        // Min values
        {{
            {ATTRIBUTE_TYPES::HEALTH, std::numeric_limits<float>::max() / 2},
            {ATTRIBUTE_TYPES::MANA, std::numeric_limits<float>::max() / 2},
        }},
        // Max values
        {{
            {ATTRIBUTE_TYPES::HEALTH, std::numeric_limits<float>::max()},
            {ATTRIBUTE_TYPES::MANA, std::numeric_limits<float>::max()},
        }}
    }},
    // DRAGON specie limits and minimum attribute informations
    {SPECIES::DRAGON, {
        // Min values
        {{
            {ATTRIBUTE_TYPES::HEALTH, std::numeric_limits<short>::max() / 2},
            {ATTRIBUTE_TYPES::MANA, std::numeric_limits<short>::max() / 2},
        }},
        // Max values
        {{
            {ATTRIBUTE_TYPES::HEALTH, std::numeric_limits<short>::max()},
            {ATTRIBUTE_TYPES::MANA, std::numeric_limits<short>::max()},
        }}
    }},
    // ELEMENTAL specie limits and minimum attribute informations
    {SPECIES::DRAGON, {
        // Min values
        {{
            {ATTRIBUTE_TYPES::HEALTH, std::numeric_limits<short>::max() / 2},
            {ATTRIBUTE_TYPES::MANA, std::numeric_limits<short>::max() / 2},
        }},
        // Max values
        {{
            {ATTRIBUTE_TYPES::HEALTH, std::numeric_limits<short>::max()},
            {ATTRIBUTE_TYPES::MANA, std::numeric_limits<short>::max()},
        }}
    }},
    // MECHANITE specie limits and minimum attribute informations
    {SPECIES::MECHANITE, {
        // Min values
        {{
            {ATTRIBUTE_TYPES::HEALTH, 100.f},
            {ATTRIBUTE_TYPES::MANA, 0.f},
        }},
        // Max values
        {{
            {ATTRIBUTE_TYPES::HEALTH, 200.f},
            {ATTRIBUTE_TYPES::MANA, 1.f},
        }}
    }},
    // FAIRY specie limits and minimum attribute informations
    {SPECIES::FAIRY, {
        // Min values
        {{
            {ATTRIBUTE_TYPES::HEALTH, 100.f},
            {ATTRIBUTE_TYPES::MANA, 100.f},
        }},
        // Max values
        {{
            {ATTRIBUTE_TYPES::HEALTH, 200.f},
            {ATTRIBUTE_TYPES::MANA, 200.f},
        }}
    }},
    // VAMPIRE specie limits and minimum attribute informations
    {SPECIES::FAIRY, {
        // Min values
        {{
            {ATTRIBUTE_TYPES::HEALTH, std::numeric_limits<short>::max() / 2},
            {ATTRIBUTE_TYPES::MANA, 100.f},
        }},
        // Max values
        {{
            {ATTRIBUTE_TYPES::HEALTH, std::numeric_limits<short>::max()},
            {ATTRIBUTE_TYPES::MANA, 200.f},
        }}
    }},
    // WEREWOLF specie limits and minimum attribute informations
    {SPECIES::WEREWOLF, {
        // Min values
        {{
            {ATTRIBUTE_TYPES::HEALTH, 100.f},
            {ATTRIBUTE_TYPES::MANA, 50.f},
        }},
        // Max values
        {{
            {ATTRIBUTE_TYPES::HEALTH, 250.f},
            {ATTRIBUTE_TYPES::MANA, 150.f},
        }}
    }},
    // GHOUL specie limits and minimum attribute informations
    {SPECIES::GHOUL, {
        // Min values
        {{
            {ATTRIBUTE_TYPES::HEALTH, 100.f},
            {ATTRIBUTE_TYPES::MANA, 0.f},
        }},
        // Max values
        {{
            {ATTRIBUTE_TYPES::HEALTH, 300.f},
            {ATTRIBUTE_TYPES::MANA, 10.f},
        }}
    }},
    // ZOMBIE specie limits and minimum attribute informations
    {SPECIES::ZOMBIE, {
        // Min values
        {{
            {ATTRIBUTE_TYPES::HEALTH, 10.f},
            {ATTRIBUTE_TYPES::MANA, 0.f},
        }},
        // Max values
        {{
            {ATTRIBUTE_TYPES::HEALTH, 100.f},
            {ATTRIBUTE_TYPES::MANA, 10.f},
        }}
    }},
    // SKELETON specie limits and minimum attribute informations
    {SPECIES::SKELETON, {
        // Min values
        {{
            {ATTRIBUTE_TYPES::HEALTH, 2.f},
            {ATTRIBUTE_TYPES::MANA, 0.f},
        }},
        // Max values
        {{
            {ATTRIBUTE_TYPES::HEALTH, 55.f},
            {ATTRIBUTE_TYPES::MANA, 1.f},
        }}
    }},
    // ELF specie limits and minimum attribute informations
    {SPECIES::ELF, {
        // Min values
        {{
            {ATTRIBUTE_TYPES::HEALTH, 10.f},
            {ATTRIBUTE_TYPES::MANA, 20.f},
        }},
        // Max values
        {{
            {ATTRIBUTE_TYPES::HEALTH, 90.f},
            {ATTRIBUTE_TYPES::MANA, 120.f},
        }}
    }},
    // DWARF specie limits and minimum attribute informations
    {SPECIES::DWARF, {
        // Min values
        {{
            {ATTRIBUTE_TYPES::HEALTH, 30.f},
            {ATTRIBUTE_TYPES::MANA, 0.f},
        }},
        // Max values
        {{
            {ATTRIBUTE_TYPES::HEALTH, 150.f},
            {ATTRIBUTE_TYPES::MANA, 1.f},
        }}
    }},
    // GOBLIN specie limits and minimum attribute informations
    {SPECIES::GOBLIN, {
        // Min values
        {{
            {ATTRIBUTE_TYPES::HEALTH, 10.f},
            {ATTRIBUTE_TYPES::MANA, 1.f},
        }},
        // Max values
        {{
            {ATTRIBUTE_TYPES::HEALTH, 96.f},
            {ATTRIBUTE_TYPES::MANA, 10.f},
        }}
    }},
    // HUMAN specie limits and minimum attribute informations
    {SPECIES::HUMAN, {
        // Min values
        {{
            {ATTRIBUTE_TYPES::HEALTH, 1.f},
            {ATTRIBUTE_TYPES::MANA, 1.f},
        }},
        // Max values
        {{
            {ATTRIBUTE_TYPES::HEALTH, 100.f},
            {ATTRIBUTE_TYPES::MANA, 100.f},
        }}
    }},
};

const unordered_map<SPECIES, string> SPECIE_Descriptions = {
    {
        SPECIES::ANGEL,
        R"""(
            Angels, most glorified species, that serve gods and beyond.
            Although they dont have what is needed to be considered as gods, they live happily with their circumstances.
        )"""
    },
    {
        SPECIES::GRACELING,
        R"""(
            Gracelings, worshippers of Grace.
            Enforcing action upon receiving orders from high above.
        )"""
    },
    {
        SPECIES::DEMON,
        R"""(
            Demons, acting purely on instinct and desires of the flesh and Him who seeks chaos.
            They feed themselves full of fear from those who dont know any better.
        )"""
    },
    {
        SPECIES::AGONIST,
        R"""(
            Agonists, worshippers of Agony. 
            Agony is that which is not, thus all shall burn to ashes and turn back to which it came.
        )"""
    },

    {
        SPECIES::DRAGON,
        R"""(
            Dragons, conquerors of the night sky, terror of all those who neglect their offerings.
        )"""
    },
    {
        SPECIES::ELEMENTAL,
        R"""(
            Elementals, the very essence of the elements that surround us everyday.
            Diaries of the old cosmos written down for those who seek em. 
        )"""
    },

    {
        SPECIES::MECHANITE,
        R"""(
            Mechanites, worshippers of the broken god.
            May god be whole again. Hatred against all that is unnatural be it hypocritical.
        )"""
    },
    {
        SPECIES::FAIRY,
        R"""(
            Fairies, as charming as deadly.
            Does the world wrap in itself when you stumble upon the land of the small. 
        )"""
    },
    {
        SPECIES::VAMPIRE,
        R"""(
            Vampires, indestructible organism, capable of rejuvenating for eons to become.
            The only thing that can stop them is what breakfasts are made for.
        )"""
    },

    {
        SPECIES::WEREWOLF,
        R"""(
            Werewolves, the most feared of all the species.
            They are the ones who are not afraid of the dark.
        )"""
    },
    {
        SPECIES::GHOUL,
        R"""(
            Ghouls, creatures of the night that feed on the flesh of the dead.
            They roam the cemeteries and tombs, searching for their next meal.
        )"""
    },
    {
        SPECIES::ZOMBIE,
        R"""(
            Zombies, reanimated corpses that hunger for the living.
            Their rotting flesh and vacant eyes strike fear into the hearts of those who encounter them.
        )"""
    },
    {
        SPECIES::SKELETON,
        R"""(
            Skeletons, the remnants of the once living.
            They rattle and clatter as they roam the world, searching for their purpose.
        )"""
    },

    {
        SPECIES::ELF,
        R"""(
            Elves, creatures of grace and beauty.
            They possess a deep connection to nature and the magic that flows within it.
        )"""
    },
    {
        SPECIES::DWARF,
        R"""(
            Dwarves, the masters of the earth and all its treasures.
            They are renowned for their craftsmanship and their love of ale.
        )"""
    },
    {
        SPECIES::GOBLIN,
        R"""(
            Goblins, the mischievous tricksters of the underworld.
            They are known for their love of shiny things and their quick wit.
        )"""
    },
    {
        SPECIES::HUMAN,
        R"""(
            Humans, the most adaptable and varied of all the species.
            They possess an insatiable curiosity and a drive to explore and conquer new frontiers.
        )"""
    }
};

const vector<string> Positives = {
    "superior",
    "great",
    "greater",
    "wise",
    "powerful",
    "strong",
    "mighty",
    "brave",
    "courageous",
    "fearless",
    "fierce",
    "bold",
    "daring",
    "valiant",
};

const vector<string> Negatives = {
    "inferior",
    "weak",
    "weaker",
    "feeble",
    "fearful",
    "cowardly",
    "frightened",
    "timid",
    "scared",
    "shy",
    "shit",
    "bad",
    "rotten",
};

enum class BODY_PART_TYPES{
    UNKNOWN,
    HAND,
    LEG,
    TAIL,
    HEAD,
    TORSO,
    END
};

const double BODY_PART_Probabilities[] = {
    0.0f,
    0.2f,
    0.2f,
    0.2f,
    0.01f,
    0.02f,
};

class Body_Part{
public:
    BODY_PART_TYPES Type;

    // The flat stats are affected by their local effects and the global passives.
    ATTRIBUTES Flat_Stats;

    vector<class Entity*> Equipped;
    vector<ATTRIBUTE_TYPES> Priorities;

    class Specie_Descriptor* Body = nullptr;

    Body_Part() = default;

    float Get(ATTRIBUTE_TYPES);
    float Get_Local_Passives(ATTRIBUTE_TYPES);
    float Get_Global_Passives(ATTRIBUTE_TYPES);
    float Get_Power_Level();
};

class Specie_Descriptor{
public:
    string Name = "";

    SPECIES Specie = SPECIES::UNKNOWN;
    RANK Rank = RANK::NONE;
    
    // Theses are pointer since when a limb is cut of it stays and someone other can pick it up.
    vector<Body_Part*> Body_Parts; 

    class Entity* Parent_Entity = nullptr;

    Specie_Descriptor() = default;
    Specie_Descriptor(Location position, class Entity* parent);

    float Get(ATTRIBUTE_TYPES Global_Attribute);
};

class Behaviour{
public:

    // This is an automated snap-shotting system which takes snapshots of the current entity stats, and the proceeding actions it took.

};

class String_Representation{
public:
    string Name = "";

    vector<string> SUBSTANTIVES;
    vector<string> VERBS;
    vector<string> ADJECTIVES;
    
    string Description = "";
};

enum class TASK_TYPES{
    UNKNOWN,
    FIGHT,
    LOOT,
    FIND,
    CONSUME,
    CONDITION,
};

class Task_Base{
public:
    // This is for functions to handle things.
    TASK_TYPES Type;
    bool Is_Critical = false;
    bool Is_Done = false;

    Body_Part* Limb = nullptr;

    Task_Base() = default;

    virtual void Do();  // for UNKNOWN
};

class Fight : public Task_Base{
public:
    class Entity* Target;
    class Entity* Skill;    // this contains a weapon of choice or an skill.

    Fight(class Entity* target) : Target(target) { Type = TASK_TYPES::FIGHT; }
    Fight(ENTITY_TYPE type_to_fight) { Type = TASK_TYPES::FIGHT; }

    // after killed the enemy initiate Looting task.
    void Do() override;
};

class Loot : public Task_Base{
public:
    class Entity* Lootable;

    ATTRIBUTES Preferred_Attributes;

    Loot(class Entity* lootable) : Lootable(lootable) { Type = TASK_TYPES::LOOT;  }
    Loot(class Entity* lootable, ATTRIBUTES preferred_attributes) : Lootable(lootable), Preferred_Attributes(preferred_attributes) { Type = TASK_TYPES::LOOT; }

    // if the lootable isn't in reach, then initiate path find task
    void Do() override;
};

class Find : public Task_Base{
public:
    Location Target_Position = {{0, 0, 0}, {0, 0, 0}};
    ENTITY_TYPE Target_Type = ENTITY_TYPE::UNKNOWN;

    TASK_TYPES Prefer_Action_After_Find;

    Find(Location target, TASK_TYPES prefer_action_after_find, Body_Part* limb) : Target_Position(target), Prefer_Action_After_Find(prefer_action_after_find) { Type = TASK_TYPES::FIND; Limb = limb;  }
    Find(ENTITY_TYPE type, TASK_TYPES prefer_action_after_find, Body_Part* limb) : Target_Type(type), Prefer_Action_After_Find(prefer_action_after_find) { Type = TASK_TYPES::FIND; Limb = limb; }

    void Do() override;
};

class Consume : public Task_Base{
public:
    ATTRIBUTE_TYPES Lacking_Attribute;

    Consume(ATTRIBUTE_TYPES lacking_attribute) : Lacking_Attribute(lacking_attribute) { Type = TASK_TYPES::CONSUME; }

    void Do() override;
};

class Condition : public Task_Base{
public:
    Task_Base* True = nullptr;
    Task_Base* False = nullptr;

    function<bool()> Condition_Func;

    Condition(function<bool()> condition_func, Task_Base* true_task, Task_Base* false_task) : Condition_Func(condition_func), True(true_task), False(false_task) { Type = TASK_TYPES::CONDITION; }

    void Do() override;
};

class Entity{
protected:
    String_Representation Info;

    Location Position;
    ENTITY_TYPE Type;
    CLASS Class;
    vector<ROLE> Roles;
    vector<ROLE> Talent;    // if the role is pointing to same type as the talent the entity gets an bonus output.
    Specie_Descriptor Specie;
    vector<Task_Base*> Tasks;

    // The current state vectors, this includes:
    // - Bleed
    // - Poison
    // - Sleep
    // - Stun
    // - Confusion
    // - Paralysis
    // - Blindness
    // - Deafness
    // - Fear
    // - Rage

    // Also used as the Global stat
    // - Auras

    // These affects all the limbs, if not item.
    ATTRIBUTES Current_Effects;
    // NOTE: The flat stats are gotten from the body parts.

    // For AST
    Entity* Holder = nullptr;
    vector<Entity*> Inventory;
public:
    Entity() = default;
    Entity(Location position);
    Entity(Location position, ENTITY_TYPE type);

    void Tick();
    void AI(Body_Part* brain);
    void Physics();
    
    // State Analyzers
    void Stack_Mundane_Tasks(Body_Part* brain);
    void Stack_Critical_Tasks(Body_Part* brain);
    void Process_Tasks(Body_Part* brain);

    // Passives
    void Calculate_Passives();
    void Calculate_Effects();
    void Passive_Heal_With(ATTRIBUTE_TYPES replenisher);
    void Re_Order_Tasks();
    
    inline RANK Get_Rank(){ return Specie.Rank; }
    inline CLASS Get_Class(){ return Class; }
    inline Location Get_Position() { return Position; }
    inline string Get_Name() { return Info.Name; }
    inline ENTITY_TYPE Get_Type() { return Type; }
    inline float Get_Attribute(ATTRIBUTE_TYPES attr) { Current_Effects.Get(attr); }
    inline vector<Entity*>& Get_Holding() { return Inventory; }
    inline float Get_Power_Level();
    inline Task_Base* Get_Next_Task();
    inline void Add_Task(Task_Base* task) { Tasks.push_back(task); }
    inline Specie_Descriptor* Get_Specie() { return &Specie; }
    
    inline void Move_To(FVector3 Position);

    inline void Update_Attribute(ATTRIBUTE_TYPES type, float new_value) { Current_Effects.Attributes[type] = new_value; }

    inline void Add_Holding(Entity* e){ Inventory.push_back(e); }
    inline void Remove_Holding(Entity* e){ Inventory.erase(std::find(Inventory.begin(), Inventory.end(), e)); }

    inline Entity* Select_Target(vector<Entity*> nearby, ENTITY_TYPE type);

    inline String_Representation Construct_Name();

    inline float Get_Distance(Entity* other);
};


#endif