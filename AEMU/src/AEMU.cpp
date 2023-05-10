#include "AEMU.hpp"
#include <vector>

namespace AEMU
{
    std::vector<Module *> modules;

    void addModule(Module *module)
    {
        modules.push_back(module);
    }

    void updateModules()
    {
        for (auto module : modules)
        {
            module->update();
        }
    }

    void resetModules()
    {
        updateModules();
        for (auto module : modules)
        {
            module->reset();
        }
        clockInc();
    }

    /**
     * @note 采用循环遍历会导致CPU分支预测难以进行，在需要仿真速度的场景下建议手动展开循环。
    */
    void runModules(uint64_t cycles)
    {
        while (cycles--)
        {
            updateModules();
            for (auto module : modules)
            {
                module->run();
            }
            clockInc();
        }
    }

}
