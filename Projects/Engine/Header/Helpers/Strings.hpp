#pragma once

#include <string>
#include <sstream>
#include <random>
#include <ios>
#include <stdint.h>

namespace RNR
{
    class Strings
    {
        public:
            static uint8_t random_char();
            static std::string random_hex(const uint64_t length);
    };
}