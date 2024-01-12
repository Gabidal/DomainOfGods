#ifndef MODELS_H
#define MODELS_H

#include <vector>
#include <unordered_map>
#include "../Src/Entity.h"
#include "../Dependencies/GGUI.h"
#include "../Dependencies/TerGen.h"

#include "../Src/Globals.h"

namespace MAP{
    class Tile;
    extern TerGen::Generator* Particle_Generator;
    extern double Sigmoid(double x);
}

class Model{
public:
    std::vector<GGUI::Sprite> Frames;

    float Speed = 1.0f;

    Model(std::vector<GGUI::Sprite> frames, float speed = 1.0f){
        Frames = frames;
        Speed = speed;
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

        float tmp = TerGen::Warp_Noise({
            Position.HIGH.X + Position.CHUNK.X * GLOBALS::CHUNK_WIDTH,
            Position.HIGH.Y + Position.CHUNK.Y * GLOBALS::CHUNK_HEIGHT
        }, MAP::Particle_Generator);

        tmp = MAP::Sigmoid(tmp);

        Animation_Frame = tmp * UCHAR_MAX;
    }

    Particle(Location location){
        Position = location;

        float tmp = TerGen::Warp_Noise({
            Position.HIGH.X + Position.CHUNK.X * GLOBALS::CHUNK_WIDTH,
            Position.HIGH.Y + Position.CHUNK.Y * GLOBALS::CHUNK_HEIGHT
        }, MAP::Particle_Generator);

        tmp = MAP::Sigmoid(tmp);

        Animation_Frame = tmp * UCHAR_MAX;
    }

    Particle() = default;

    bool Is_Empty(){
        return Texture.Frames.size() == 0;
    }

    unsigned char Get_Animation_Frame_Offset(){
        return Animation_Frame;
    }

    Model Get_Texture(){
        return Texture;
    }
};

extern GGUI::Sprite Interpolate_Animation_Frame(Model m, unsigned char Animation_Frame);

extern void Init_Models();

// Tiles only affect the background color.
extern GGUI::RGB Render_Tile(MAP::Tile* t);

// Entities only affect the Text, and the foreground color.
extern GGUI::Sprite Render_Entity(Entity* e, unsigned char Animation_Frame);

extern void Update_Map(GGUI::Terminal_Canvas* tc, unsigned char Animation_Frame);

#endif