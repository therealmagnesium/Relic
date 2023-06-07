#pragma once
#include <cstdint>
#include <string>

struct PowerUpState
{
    bool has = false;
    bool shown = false;
    uint8_t type = 0;
    uint32_t activeTime = 0;
    uint32_t lastSpawnTime = 0;
    std::string text;
};
