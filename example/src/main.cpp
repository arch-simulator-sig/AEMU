#include "AEMU.hpp"
#include "IFU.hpp"
#include "RAM.hpp"
#include "common.hpp"

int main(int argc, char *argv[])
{
    Trace::initTrace("a.vcd");
    RAM *ram = new RAM();
    IFU *ifu = new IFU();

    ram->bind(ifu);
    ifu->bind(ram);
    
    addModule(ifu);
    addModule(ram);

    resetModules();
    // auto now = std::chrono::system_clock::now();
    // auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    
    uint64_t cycle = 32ULL;

    runModules(cycle);

    /* 手动展开循环可以获得更好的性能。 */
    // for (uint64_t i = 0; i < cycle; i++)
    // {
    //     ifu->update();
    //     ram->update();
    //     ifu->trace();
    //     ram->trace();
    //     ifu->run();
    //     ram->run();
    //     clockInc();
    // }
    
    // now = std::chrono::system_clock::now();
    // ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() - ms;
    // printf("%.03fMHz\n",cycle/1000.0f/ms);
    
    Trace::closeTrace();
    return 0;
}