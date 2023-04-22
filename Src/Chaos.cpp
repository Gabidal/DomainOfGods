#include "Chaos.h"

namespace CHAOS{

    unordered_map<IVector3, Entity, IVector3> Entity_Chunks;

    vector<Entity*> Get_Chunk_Content(IVector3 position){
        return Entity_Chunks[position].Get_Holding();
    }

    // Goes through all the chunks and checks if some entity needs to be moved into another chunk.
    void Tick(){
        for (auto& Chunk : Entity_Chunks){
            for (auto& entity : Chunk.second.Get_Holding()){
                IVector3 Chunk_Coordinates;

                // update the entity CHUNK coordinates
                Location Current_Entity_Position = entity->Get_Position();

                Current_Entity_Position.Update_Chunk_Location();

                // check if the newly updated chunks coordinates match the map key, if not put em into a new chunk
                if (!(Current_Entity_Position.CHUNK == Chunk.first)){
                    Entity_Chunks[Current_Entity_Position.CHUNK].Add_Holding(entity);

                    // remove the entity from the old lost now
                    Chunk.second.Remove_Holding(entity);
                }
            }
        }
    }

    vector<IVector3> Get_Surrounding_Positions(IVector3 center, int Reach){
        vector<IVector3> Result;

        for (int y = -Reach; y <= Reach; y++){
            for (int x = -Reach; x <= Reach; x++){
                for (int z = -Reach; z <= Reach; z++){
                    Result.push_back(IVector3(center.X + x, center.Y + y, center.Z + z));
                }
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