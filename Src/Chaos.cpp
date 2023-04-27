#include "Chaos.h"
#include "../Dependencies/TerGen.h"
#include "../UI/Render.h"
#include "Globals.h"

namespace CHAOS{

    inline unordered_map<IVector3, vector<Entity*>, IVector3> Entity_Chunks;
    inline TerGen::Generator* Entity_Generator;

    void Init(){
        Entity_Generator = new TerGen::Generator();


    }

    int Normalize_Entity_Elevation(float Y) {
        int Normalized_Y = (abs(Y) * (int)RENDER::Entity_Textures.size());

        int Offset_Y = (Normalized_Y % (int)RENDER::Entity_Textures.size());

        return Offset_Y;
    }

    vector<Entity*> Get_Chunk_Content(IVector3 position){
        if (Entity_Chunks.find(position) != Entity_Chunks.end())
            return Entity_Chunks[position];

        vector<Entity*> Result;

        for (int Y = 0; Y < GLOBALS::CHUNK_HEIGHT; Y++){
            for (int X = 0; X < GLOBALS::CHUNK_WIDTH; X++){
                TerGen::Vector2 World_Position = {
                    (position.X * GLOBALS::CHUNK_WIDTH) + X,
                    (position.Y * GLOBALS::CHUNK_HEIGHT) + Y
                };

                double Value = TerGen::Warp_Noise(World_Position, Entity_Generator);

                Value = abs(Value);

                if (Value >= GLOBALS::ENTITY_DENSITY)
                    continue;

                Result.push_back(new Entity({{(float)X, (float)Y, 1}, position}, ENTITY_TYPE::ENTITY));
            }
        }

        Entity_Chunks[position] = Result;

        return Entity_Chunks[position];
    }

    // Goes through all the chunks and checks if some entity needs to be moved into another chunk.
    void Tick(){
        for (auto& Chunk : Entity_Chunks){
            vector<Entity *>& Content = Chunk.second;
            for (int i = 0; i < (int)Content.size(); i++){
                IVector3 Chunk_Coordinates;

                // Update AI
                Content[i]->Tick();
            
                // update the entity CHUNK coordinates
                Location Current_Entity_Position = Content[i]->Get_Position();

                Current_Entity_Position.Update_Chunk_Location();


                // check if the newly updated chunks coordinates match the map key, if not put em into a new chunk
                if (!(Current_Entity_Position.CHUNK == Chunk.first)){
                    Entity_Chunks[Current_Entity_Position.CHUNK].push_back(Content[i]);

                    // remove the entity from the old lost now
                    Chunk.second.erase(Chunk.second.begin() + i--);
                }
            }
        }
    }

    void Apply_Physics(){
        for (auto& Chunk : Entity_Chunks){
            vector<Entity *>& Content = Chunk.second;
            for (int i = 0; i < (int)Content.size(); i++){
                Content[i]->Physics();
            }
        }
    }

    vector<IVector3> Get_Surrounding_Positions(IVector3 center, int Reach){
        vector<IVector3> Result;

        for (int y = -Reach; y <= Reach; y++){
            for (int x = -Reach; x <= Reach; x++){
                Result.push_back(IVector3(center.X + x, center.Y + y, 0));
            }
        }

        return Result;
    }

    vector<Entity*> Get_Surrounding_Content(IVector3 position){
        vector<Entity*> Result;
        
        for (auto chunk_position : Get_Surrounding_Positions(position)){
            vector<Entity*> tmp = Get_Chunk_Content(chunk_position);

            Result.insert(Result.end(), tmp.begin(), tmp.end());
        }

        return Result;
    }

    vector<Entity*> Get_Surrounding_Content(IVector3 position, int Distance){
        vector<Entity*> Result;
        
        for (auto chunk_position : Get_Surrounding_Positions(position, Distance)){
            vector<Entity*> tmp = Get_Chunk_Content(chunk_position);

            Result.insert(Result.end(), tmp.begin(), tmp.end());
        }

        return Result;
    }

}