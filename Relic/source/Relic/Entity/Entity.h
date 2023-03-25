#pragma once
#include "Components.h"
#include <string>
#include <memory>

namespace Relic
{
    class Entity
    {
    public:
        std::shared_ptr<Tranform> transform;        

    public:
        void Destroy();

        bool IsActive() const;
        size_t GetId() const;
        const std::string& GetTag() const;

    private:
        Entity(const size_t id, const std::string& tag);

    private:
        bool m_active = true;
        size_t m_id = 0;
        std::string m_tag = "default";
    };
}