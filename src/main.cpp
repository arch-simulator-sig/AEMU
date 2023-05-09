#include "IFU.hpp"
#include "RAM.hpp"
#include <vector>
#include "clock.hpp"
#include "wavename.hpp"
#include <iostream>

#define CONNECT(a, b) \
    a.bind(&b);       \
    b.bind(&a);
int main(int argc, char *argv[])
{
    std::cout << "$timescale 1ns $end\n";
    
    std::cout << "$scope module ram $end\n";
    RAM ram;
    std::cout << "$upscope $end\n";
    
    std::cout << "$scope module ifu $end\n";
    IFU ifu;
    std::cout << "$upscope $end\n";


    CONNECT(ram, ifu);
    std::vector<Module *> modules;
    modules.push_back(&ram);
    modules.push_back(&ifu);

    for (auto module : modules)
    {
        module->reset();
    }

    for (size_t i = 0; i < 10; i++)
    {
        for (auto module : modules)
        {
            module->run();
#ifdef DUMP_WAVE_SUPPORT
            std::cout << "#" << getClock() + 1 << std::endl;
            module->dump();
#endif
        }
        
        clock_inc();
    }
    
    return 0;
}