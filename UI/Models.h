#ifndef MODELS_H
#define MODELS_H

#include <vector>
#include <unordered_map>
#include "../Src/Entity.h"
#include "../Dependencies/GGUI.h"

namespace MAP{
    class Tile;
}

class Model{
public:
    std::vector<GGUI::Sprite> Frames;

    Model(std::vector<GGUI::Sprite> frames){
        Frames = frames;
    }

    Model() = default;
};

// Accessed with index;
extern std::unordered_map<std::string, std::vector<Model>> Models;

extern unsigned char Get_Model_Variation(std::string name);

class Particle{
protected:
    unsigned char Animation_Frame;
    Location Position;
    Model Texture;
public:

    void Set_Texture(std::string name){
        Texture = Models[name][Get_Model_Variation(name)];
    }

    Particle(std::string type, Location location){
        Position = location;

        Texture = Models[type][Get_Model_Variation(type)];

        Animation_Frame = sin(Position.HIGH.X * Position.CHUNK.X * 10) / 10 * cos(Position.HIGH.Y * Position.CHUNK.Y);
    }

    Particle(Location location){
        Position = location;

        Animation_Frame = sin(Position.HIGH.X * Position.CHUNK.X) * cos(Position.HIGH.Y * Position.CHUNK.Y);
    }

    Particle() = default;
};

extern void Init_Models();

// Tiles only affect the background color.
extern GGUI::RGB Render_Tile(MAP::Tile* t);

// Entities only affect the Text, and the foreground color.
extern GGUI::Sprite Render_Entity(Entity* e, unsigned char Animation_Frame);

extern void Update_Map(GGUI::Terminal_Canvas* tc, unsigned char Animation_Frame);

#endif