#include "AEMU.hpp"
#include <vector>
#include "trace_vcd.hpp"



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

    void traceModules()
    {
        #ifdef TRACE_VCD
        Trace::dumpTime(getCycle());
        for (auto module : modules)
        {
            module->trace();
        }
        #endif 
    }
    void resetModules()
    {
        updateModules();
        traceModules();
        for (auto module : modules)
        {
            module->reset();
        }
        clockInc();
        updateModules();
        traceModules();
    }

    /**
     * @note 采用循环遍历会导致CPU分支预测难以进行，在需要仿真速度的场景下建议手动展开循环。
    */
    void runModules(uint64_t cycles)
    {
        while (cycles--)
        {
            for (auto module : modules)
            {
                module->run();
            }
            clockInc();
            updateModules();
            traceModules();
        }
    }
    void declareModules()
    {
        for (auto module : modules)
        {
            module->declare();
        }
    }

   

}
