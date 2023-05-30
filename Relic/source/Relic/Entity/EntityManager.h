#pragma once
#include <vector>
#include <memory>
#include <unordered_map>

namespace Relic
{
    class Entity;

    class EntityManager
    {
    public:
        EntityManager();

        void CullEntities(uint32_t renderWidth, uint32_t renderHeight);
        void HandleComponents();
        void Update();
        void RemoveInactiveEntities(std::vector<std::shared_ptr<Entity>>& entityVec);

        std::vector<std::shared_ptr<Entity>>& GetEntities();
        std::vector<std::shared_ptr<Entity>>& GetEntities(const std::string& tag);
        
        std::shared_ptr<Entity> AddEntity(const std::string& tag);
    private:
        std::vector<std::shared_ptr<Entity>> m_entities;
        std::vector<std::shared_ptr<Entity>> m_entitiesToAdd;
        std::unordered_map<std::string, std::vector<std::shared_ptr<Entity>>> m_entityMap;
        size_t m_totalEntities = 0;
    };
}
