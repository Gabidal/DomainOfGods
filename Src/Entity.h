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
    ITEM,
    ENTITY,

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
    0.01 * 0.0000000000001, // DOMAIN_HOLDER
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

enum class ATTRIBUTE_TYPES{
    // Physicals
    HEALTH,               // 10% to get
    HUNGER,               // 10% to get
    THIRST,               // 10% to get
    STRENGTH,             // 10% to get
    DEXTERITY,            // 10% to get
    AGILITY,              // 10% to get
    SIZE,                 // 10% to get

    // Mentals
    INTELLIGENCE,         // 10% to get
    MANA,                 // 10% to get
    SANITY,               // 10% to get

    // MISC
    LUCK,                 // 10% to get
    RADIOACTIVITY,       // 10% to get

    // Resistances
    HEAT_RESISTANCE,      // 10% to get
    COLD_RESISTANCE,      // 10% to get
    ELECTRICITY_RESISTANCE, // 10% to get
    POISON_RESISTANCE,    // 10% to get
    ACID_RESISTANCE,      // 10% to get

    END
};

const double ATTRIBUTE_Probabilities[] = {
    0.1,    // HEALTH
    0.1,    // HUNGER
    0.1,    // THIRST
    0.1,    // STRENGTH
    0.1,    // DEXTERITY
    0.1,    // AGILITY
    0.1,    // SIZE

    0.1,    // INTELLIGENCE
    0.1,    // MANA
    0.1,    // SANITY

    0.1,    // LUCK
    0.1,    // RADIOACTIVITY

    0.1,    // HEAT_RESISTANCE
    0.1,    // COLD_RESISTANCE
    0.1,    // ELECTRICITY_RESISTANCE
    0.1,    // POISON_RESISTANCE
    0.1,    // ACID_RESISTANCE

    1.0,    // END
};

const vector<const char*> ATTRIBUTE_Names[] = {
    {"health", "life"}, // HEALTH
    {"hunger", "food"}, // HUNGER
    {"thirst", "water"}, // THIRST
    {"strength", "force"}, // STRENGTH
    {"dexterity", "agility"}, // DEXTERITY
    {"agility", "dexterity"}, // AGILITY
    {"size", "mass"}, // SIZE

    {"intelligence", "brain"}, // INTELLIGENCE
    {"mana", "magic"}, // MANA
    {"sanity", "mind"}, // SANITY

    {"luck", "fortune"}, // LUCK
    {"radioactivity", "radioactive"}, // RADIOACTIVITY

    {"heat resistance", "heat"}, // HEAT_RESISTANCE
    {"cold resistance", "cold"}, // COLD_RESISTANCE
    {"electricity resistance", "electricity"}, // ELECTRICITY_RESISTANCE
    {"poison resistance", "poison"}, // POISON_RESISTANCE
    {"acid resistance", "acid"}, // ACID_RESISTANCE

    {"", ""},
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

    pair<ATTRIBUTE_TYPES, float> Get_Most_Aggressive();

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

class STATS{
public:
    // Power describes everything, where 1 power equals to:
    // 1 Strength, 1 Damage, 1 Health, 1 Speed, 1 Defense, 1 Resistance, 1 Accuracy, 1 Evasion, 1 Crit Chance, 1 Crit Power
    // Then the equipped items decrease certain aspects or increase them.
    // The power is them multiplied by the RANK factor.
    int Power = 1;

    ATTRIBUTES Local;
    ATTRIBUTES Global;

    STATS() = default;

    // Operator overloads
    STATS& operator=(const STATS& stats){
        Power = stats.Power;
        Local = stats.Local;
        Global = stats.Global;
        return *this;
    }

    STATS& operator+=(const STATS& stats){
        Power += stats.Power;
        Local += stats.Local;
        Global += stats.Global;
        return *this;
    }

    STATS& operator-=(const STATS& stats){
        Power -= stats.Power;
        Local -= stats.Local;
        Global -= stats.Global;
        return *this;
    }

    STATS& operator*=(const STATS& stats){
        Power *= stats.Power;
        Local *= stats.Local;
        Global *= stats.Global;
        return *this;
    }

    STATS& operator/=(const STATS& stats){
        Power /= stats.Power;
        Local /= stats.Local;
        Global /= stats.Global;
        return *this;
    }

    STATS operator+(const STATS& stats){
        STATS temp = *this;
        temp += stats;
        return temp;
    }

    STATS operator-(const STATS& stats){
        STATS temp = *this;
        temp -= stats;
        return temp;
    }

    STATS operator*(const STATS& stats){
        STATS temp = *this;
        temp *= stats;
        return temp;
    }

    STATS operator/(const STATS& stats){
        STATS temp = *this;
        temp /= stats;
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
    MAGIC,          // 0.00001% to get
    RADIATION,      // 0.00001% to get
    PLASMA,         // 0.00001% to get
    GRAVITY,        // 0.00001% to get
    MAGNETISM,      // 0.00001% to get
    MATTER,         // 0.00001% to get
    ENERGY,         // 0.00001% to get
    DARKENERGY,     // 0.00001% to get
    DARKMATTER,     // 0.00001% to get
    LIGHTENERGY,    // 0.00001% to get
    LIGHTMATTER,    // 0.00001% to get

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

const string SPECIES_Names[] = {
    "bee",
    "butterfly",
    "caterpillar",
    "dragonfly",
    "fly",
    "grasshopper",
    "ladybug",
    "mosquito",
    "moth",
    "spider",
    "tick",
    "wasp",

    "ant",
    "ape",
    "bear",
    "bird",
    "boar",
    "buffalo",
    "cat",
    "chicken",
    "cow",
    "crocodile",
    "dog",
    "donkey",
    "duck",
    "elephant",
    "fish",
    "fox",
    "frog",
    "giraffe",
    "goat",
    "gorilla",
    "horse",
    "kangaroo",
    "lion",
    "monkey",
    "mouse",
    "panda",
    "pig",
    "rabbit",
    "rat",
    "rhinoceros",
    "sheep",
    "snake",
    "squirrel",
    "tiger",
    "turtle",
    "wolf",
    "zebra",

    "bush",
    "grass",
    "weed",
    "mushroom",
    "fungus",

    "fire",
    "ice",
    "earth",
    "water",
    "air",
    "lightning",
    "wind",
    "light",
    "darkness",

    "war",
    "peace",
    "death",
    "life",
    "hunger",
    "thirst",
    "sleep",
    "love",
    "hate",
    "harmony",
    "mind",
    "body",
    "spirit",
    "fate",
    "destiny",
    "time",

    "fire elemental",
    "ice elemental",
    "earth elemental",
    "water elemental",
    "air elemental",
    "lightning elemental",
    "wind elemental",
    "light elemental",
    "darkness elemental",
    "magical mass",
    "radiation mass",
    "electricity elemental",
    "plasma elemental",
    "gravity elemental",
    "magnetism elemental",
    "matter elemental",
    "energy elemental",
    "darkenergy elemental",
    "darkmatter elemental",
    "lightenergy elemental",
    "lightmatter elemental",

    "old one",
    "first one",
    "the great old one",
    "shape shifter",

    "the thing",
    "the thing that should not be",
    "the thing that cannot be",
    "the thing that is not",
    "the thing that was not",
    "the thing that will be",
    "the thing that will not be",
    "the thing that is",
    "the thing that was",
    "the thing that is and is not",

    "domain holder",

    "druid",
    "goblin",
    "orc",
    "troll",
    "elf",
    "dwarf",
    "fairy",
    "naga",
    "hobgoblin",
    "human",
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

    ATTRIBUTES Flat_Stats;

    vector<class Entity*> Equipped;
    vector<ATTRIBUTE_TYPES> Priorities;

    Body_Part() = default;
};

class Specie_Descriptor{
public:
    string Name = "";

    SPECIES Specie;
    RANK Rank;
    
    // Theses are pointer since when a limb is cut of it stays and someone other can pick it up.
    vector<Body_Part*> Body_Parts; 

    ATTRIBUTES Passive_Attributes;

    Specie_Descriptor() = default;
    Specie_Descriptor(Location position);
};

class Behaviour{
public:

    // This is an automated snap-shotting system which takes snapshots of the current entity stats, and the proceeding actions it took.

};

class String_Representation{
public:
    string ID = "";

    vector<string> Prefixes;
    vector<string> Suffixes;

    string History = "";

};

class Entity{
protected:
    String_Representation Info;

    Location Position;
    ENTITY_TYPE Type;
    CLASS Class;
    STATS Base_Stats;
    vector<ROLE> Roles;
    Specie_Descriptor Specie;

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
    ATTRIBUTES Current_Effects;

    // This moves in the 0.f - 100.f or x.f
    ATTRIBUTES Stats;

    // For AST
    Entity* Holder = nullptr;
    vector<Entity*> Inventory;
public:
    Entity(Location position);
    Entity(Location position, ENTITY_TYPE type);

    void Tick();
    void AI(Body_Part* brain);
    void Calculate_Passives();
    void Calculate_Effects();
    void Calculate_Locals();
    

    inline RANK Get_Rank(){ return Specie.Rank; }
    inline CLASS Get_Class(){ return Class; }
    inline Location Get_Position() { return Position; }
    inline float Get_Attribute(ATTRIBUTE_TYPES type, bool Local = false);
    inline string Get_Name() { return Info.ID; }
    inline ENTITY_TYPE Get_Type() { return Type; }

    inline string Construct_Name();
    inline string Construct_Description();
};


#endif