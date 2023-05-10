#include "RAM.hpp"
#include "IFU.hpp"

RAM::RAM(const char *name)
{
    this->name = name;
    initSignalNames(2);
    Trace::declareModuleEnd();
    Trace::declareModuleBegin(name);
    TRACE_VCD_DECLAR(0, inst, 32, "reg");
    TRACE_VCD_DECLAR(1, ready, 1, "wire");
    Trace::declareModuleEnd();
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
    if (ifu_out.pc_valid && data->ready)
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
    p->ready = getCycle() % 4 == 0;
}

void RAM::trace()
{
    TRACE_VCD_BEGIN();
    TRACE_VCD_DUMPVALUE(0, inst, 32);
    TRACE_VCD_DUMPVALUE(1, ready, 1);
}