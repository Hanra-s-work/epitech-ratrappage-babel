/*
** EPITECH PROJECT, 2024
** record_play
** File description:
** StreamData.hpp
*/

#pragma once

#include <vector>

namespace Audio
{
    struct StreamData
    {
        unsigned int duration;
        std::vector<float> samples;
    };
}
