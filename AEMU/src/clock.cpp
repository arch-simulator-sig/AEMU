#include "clock.hpp"
uint64_t global_cycle = 0;

void clockInc()
{
    global_cycle++;
}
uint64_t getCycle()
{
    return global_cycle;
}
void setCycle(uint64_t cycle)
{
    global_cycle = cycle;
}