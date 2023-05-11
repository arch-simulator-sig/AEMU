#pragma once
#include "Module.hpp"

namespace AEMU
{
    void addModule(Module *module);
    void resetModules();
    void runModules(uint64_t cycles = 1);
    void updateModules();
    void traceModules();
    void declareModules();
}
