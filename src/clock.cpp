#include "clock.hpp"
uint64_t global_clock;
void clock_inc()
{
    global_clock++;
}
uint64_t getClock()
{
    return global_clock;
}
