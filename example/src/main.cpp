#include "AEMU.hpp"
#include "IFU.hpp"
#include "RAM.hpp"
#include "common.hpp"
// #define SPEED_TEST
// #define UNROLL_LOOP
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
    uint64_t cycle = 100ULL;
#ifdef SPEED_TEST
    auto now = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    cycle = 100000000ULL;
#endif
#ifndef UNROLL_LOOP
    runModules(cycle);
#else
    /* 手动展开循环可以获得更好的性能。 */
    for (uint64_t i = 0; i < cycle; i++)
    {
        ifu->run();
        ram->run();
        clockInc();
        ifu->update();
        ram->update();
        Trace::dumpTime(getCycle());
        ifu->trace();
        ram->trace();
    }
#endif
#ifdef SPEED_TEST
    now = std::chrono::system_clock::now();
    ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() - ms;
    printf("%.03fMHz\n", cycle / 1000.0f / ms);
#endif
    Trace::dumpBufferWave("buffer.vcd");
    Trace::closeTrace();
    return 0;
}