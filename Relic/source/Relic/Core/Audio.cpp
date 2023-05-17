#include "pch.h"
#include "Audio.h"

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/System/Time.hpp>

namespace Relic
{
    Audio::Audio(const std::string& path)
    {
        sf::SoundBuffer buff;
        buff.loadFromFile(path);

        m_sound.setBuffer(buff);
        m_sound.setLoop(false);
    }

    void Audio::SetLoop(bool loop)
        { m_sound.setLoop(loop); }

    void Audio::SetStartOffset(float secs)
        { m_sound.setPlayingOffset(sf::seconds(secs)); }

    void Audio::Play()
        { m_sound.play(); }
}
