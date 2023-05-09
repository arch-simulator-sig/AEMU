#include "RAM.hpp"
#include "IFU.hpp"

RAM::RAM(const char *name)
{
    this->name = name;
    IFONE(DUMP_WAVE_SUPPORT,init_names(1);)
    printf("$var %s %d %s %s $end\n","reg",32,signal_names.at(0).data(),"inst");
}
RAM::~RAM()
{
}
void RAM::bind(IFU *ifu)
{
    this->ifu = ifu;
}
void RAM::run()
{
    p = getDataP();
    auto ifu_out = ifu->getData();
    if (ifu_out.pc_valid)
        p->inst = ifu_out.pc;
    else
        p->inst = 0;
}
void RAM::reset()
{
    IO_RAM data = {.inst = 0};
    resetData(data);
}
#ifdef DUMP_WAVE_SUPPORT
#include <bitset>
void RAM::dump()
{
    auto data = getData();
    
    std::bitset<32> inst_bits(data.inst);
    dump_value(signal_names.at(0),inst_bits.to_string());
    
}
#endif