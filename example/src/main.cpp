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

    reset();
    uint64_t cycle = 32ULL;

    // run(cycle);
    for (uint64_t i = 0; i < cycle; i++)
    {
        ifu->run();
        ram->run();
        clock_inc();
    }
    return 0;
}