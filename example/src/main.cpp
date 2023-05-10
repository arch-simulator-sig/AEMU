#include "AEMU.hpp"
#include "IFU.hpp"
#include "RAM.hpp"
#include "common.hpp"

int main(int argc, char *argv[])
{
    RAM *ram = new RAM();
    IFU *ifu = new IFU();

    ram->bind(ifu);
    ifu->bind(ram);
    
    addModule(ifu);
    addModule(ram);

    resetModules();
    uint64_t cycle = 32ULL;

    runModules(cycle);
    
    /* 手动展开循环可以获得更好的性能。 */
    // for (uint64_t i = 0; i < cycle; i++)
    // {
    //     ifu->update();
    //     ram->update();
    //     ifu->run();
    //     ram->run();
    //     clockInc();
    // }
    return 0;
}