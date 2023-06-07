#pragma once
#include <vector>

namespace Relic
{
    class Layer;

    class LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PopLayer(Layer* layer);

        std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_layers.end(); }
    
    private:
        std::vector<Layer*> m_layers;
        std::vector<Layer*>::iterator m_layerInsert;
    };
}
