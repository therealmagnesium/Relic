#pragma once
#include "Relic/Entity/Vector2.h"

#include <string>
#include <SFML/Audio/Sound.hpp>

namespace Relic
{
    class Audio
    {
    public:
        Audio(const std::string& path); 
        
        void SetStartOffset(float secs);
        void SetLoop(bool loop);
        void Play();
    
    private:
        sf::Sound m_sound;
    };
}

