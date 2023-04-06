#pragma once
#include "Entity.h"

namespace Relic
{
    typedef std::vector<std::shared_ptr<Entity>> EntityVec;
    typedef std::unordered_map<std::string, std::vector<std::shared_ptr<Entity>>> EntityMap;

    class EntityManager
    {
    public:
        EntityManager();

        void Update();

        EntityVec& GetEntities();
        EntityVec& GetEntities(const std::string& tag);
        
        std::shared_ptr<Entity> AddEntity(const std::string& tag);
    private:
        EntityVec m_entities;
        EntityVec m_entitiesToAdd;
        EntityMap m_entityMap;
        size_t m_totalEntities = 0;
    };
}
