#include "pch.h"
#include "Audio.h"

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/System/Time.hpp>

namespace Relic
{
    Audio::Audio(const std::string& path)
    {
        m_music = std::make_shared<sf::Music>();
        m_music->openFromFile(path);
        m_music->setLoop(true);
    }

    void Audio::SetLoop(bool loop)
        { m_music->setLoop(loop); }

    void Audio::SetStartOffset(float secs)
        { m_music->setPlayingOffset(sf::seconds(secs)); }

    void Audio::Play()
        { m_music->play(); }
}
