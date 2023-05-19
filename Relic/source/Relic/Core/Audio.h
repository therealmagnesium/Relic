#pragma once
#include "Relic/Entity/Vector2.h"

#include <string>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>

namespace Relic
{
    class Audio
    {
    public:
        Audio(const std::string& path = "assets/sounds/default.ogg"); 
        
        void SetStartOffset(float secs);
        void SetLoop(bool loop);
        void Play();
    
    private:
        sf::Music m_music;
    };
}

