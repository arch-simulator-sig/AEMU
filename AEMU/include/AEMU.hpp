#pragma once
#include "Module.hpp"

namespace AEMU
{
    void addModule(Module *module);
    void reset();
    void run(uint64_t cycles = 1);
}
