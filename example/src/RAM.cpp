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
    auto data = getDataP();
    auto ifu_out = ifu->getData();
    if (ifu_out.pc_valid && data->port.ready)
        p->inst = ifu_out.pc;
    else
        p->inst = 0;
}
void RAM::reset()
{
    IO_RAM data = {.inst = 0};
    setNextData(data);
}

void RAM::update()
{
    p = getDataP();
    p->port.ready = getCycle() % 4 == 0;
}