#include "pch.h"
#include "Layer.h"
#include "LayerStack.h"

namespace Relic
{
    LayerStack::LayerStack()
    {
        m_layerInsert = begin();
    }

    LayerStack::~LayerStack()
    {
        for (Layer* layer : m_layers)
            delete layer;
    }

    void LayerStack::PushLayer(Layer* layer)
    { m_layerInsert = m_layers.emplace(m_layerInsert, layer); }

    void LayerStack::PopLayer(Layer* layer)
    {
        auto it = std::find(begin(), end(), layer);
        if (it != end())
        {
            m_layers.erase(it);
            m_layerInsert--;
        }
    }
}
