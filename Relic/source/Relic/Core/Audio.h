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
        Audio(const std::string& path); 
      
        /* Sets where the sound file starts playing. 
         * Parameters: 
         * secs - How many seconds the sound is offset by */
        void SetStartOffset(float secs);
        
        /* Sets whether the sound file should repeat.
         * Parameters:
         * loop - Determines if the sound should loop */
        void SetLoop(bool loop);
        
        /* Plays the sound file. */
        void Play();
       
        /* Stops the sound file while playing */
        void Stop();    
    
    private:
        std::shared_ptr<sf::Music> m_music;
    };
}

