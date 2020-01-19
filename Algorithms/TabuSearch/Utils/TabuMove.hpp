#pragma once

#include <cstdint>


struct TabuMove
{
    TabuMove();

    uint32_t cadency;
    uint32_t beginVertex;
    uint32_t endVertex;
};
