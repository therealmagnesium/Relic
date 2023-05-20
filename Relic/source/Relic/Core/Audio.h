#pragma once
#include "Relic/Entity/Vector2.h"

#include <string>
#include <memory>
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
        std::shared_ptr<sf::Music> m_music;
    };
}

