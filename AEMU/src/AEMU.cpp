#include "AEMU.hpp"
#include <vector>

namespace AEMU
{
    std::vector<Module *> modules;

    void addModule(Module *module)
    {
        modules.push_back(module);
    }

    void reset()
    {
        for (auto module : modules)
        {
            module->reset();
        }
        clock_inc();
    }

    void run(uint64_t cycles)
    {
        while (cycles--)
        {
            for (auto module : modules)
            {
                module->run();
            }
            clock_inc();
        }
    }
}
