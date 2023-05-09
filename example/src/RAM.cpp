#include "RAM.hpp"
#include "IFU.hpp"

RAM::RAM(const char *name)
{
    this->name = name;
}
RAM::~RAM() {}
void RAM::bind(IFU *ifu)
{
    this->ifu = ifu;
}
void RAM::run()
{
    p = getNextDataP();
    auto ifu_out = ifu->getData();
    if (ifu_out.pc_valid && io_ready())
        p->inst = ifu_out.pc;
    else
        p->inst = 0;
}
void RAM::reset()
{
    IO_RAM data = {.inst = 0};
    setNextData(data);
}

bool RAM::io_ready()
{
    return getCycle() % 4 == 0;
}