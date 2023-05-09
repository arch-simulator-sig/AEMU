#include "clock.hpp"
uint64_t global_clock = 0;

void clock_inc()
{
    global_clock++;
}
uint64_t getCycle()
{
    return global_clock;
}
