#pragma once

namespace Relic
{
    class Scene;

    class Layer
    {
    public:
        Layer() {}
        virtual ~Layer() {}

        virtual void OnAttach() {};
        virtual void OnDetach() {};
        virtual void OnUpdate(float dt) {};
  
        bool IsEnabled() const { return m_enabled; };

        void Enable() { m_enabled = true; }
        void Disbale() { m_enabled = false; }
     
    private: 
        bool m_enabled = false; 
    };
}
