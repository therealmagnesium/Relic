#include "pch.h"
#include "Entity.h"
#include "EntityManager.h"

namespace Relic
{
    EntityManager::EntityManager()
    {

    }

    void EntityManager::CullEntities(uint32_t renderWidth, uint32_t renderHeight)
    {
        for (auto& entity : m_entities)
        {
            if (entity->GetTag() == "ui")
                break;

            if (entity->IsInRenderView(renderWidth, renderHeight))
                entity->Enable();
            else
                entity->Disable();
        } 
    }

    void EntityManager::HandleComponents()
    {
        for (auto& e : m_entities)
        {
            e->GetComponent<Shape>().shape.SetPosition(e->GetX(), e->GetY());
            e->GetComponent<Shape>().shape.SetRotation(e->GetAngle());

            e->GetComponent<SpriteRenderer>().sprite.SetPosition(e->GetX(), e->GetY());
            e->GetComponent<SpriteRenderer>().sprite.SetRotation(e->GetAngle());

            e->GetComponent<Text>().text.SetPosition(e->GetX(), e->GetY());
        }
    }

    void EntityManager::Update()
    {
        for (auto& entity : m_entitiesToAdd)
        {
            m_entities.push_back(entity);
            m_entityMap[entity->GetTag()].push_back(entity);
        }

        m_entitiesToAdd.clear();

        RemoveInactiveEntities(m_entities);

        for (auto& [tag, EntityVec] : m_entityMap)
            RemoveInactiveEntities(EntityVec);
    }

    void EntityManager::RemoveInactiveEntities(EntityVec& entityVec)
    {
        for (auto& entity : entityVec)
        {
            entityVec.erase(std::remove_if(entityVec.begin(), entityVec.end(), [](std::shared_ptr<Entity> entity)
                            { return !entity->IsActive(); }), entityVec.end());
        }
    }

    std::shared_ptr<Entity> EntityManager::AddEntity(const std::string& tag)
    {
        auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));
        m_entitiesToAdd.push_back(entity);
        return entity;
    }

    EntityVec& EntityManager::GetEntities()
    {
        return m_entities;
    }

    EntityVec& EntityManager::GetEntities(const std::string& tag)
    {
        return m_entityMap[tag];
    }
}
