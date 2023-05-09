#include "IFU.hpp"
#include "RAM.hpp"
#include "wavename.hpp"

IFU::IFU(const char *name) 
{
    this->name = name;
    IFONE(DUMP_WAVE_SUPPORT,init_names(2);)
    printf("$var %s %d %s %s $end\n","reg",32,signal_names.at(0).data(),"pc");
    printf("$var %s %d %s %s $end\n","reg",1,signal_names.at(1).data(),"pc_valid");
}
IFU::~IFU()
{
       
}

void IFU::bind(RAM *ram)
{
    this->ram = ram;
}
void IFU::run()
{
    p = getDataP();
    auto data = getData();
    // auto ram_out = ram->getData();

    // printf("cycle:%ld PC:0x%08x inst:0x%08x\n",getClock(),data.pc,ram_out.inst);
    p->pc = data.pc + 4;;
    p->pc_valid = true;
    // printf("cycle:%ld\tPC 0x%08x => 0x%08x, get inst: 0x%08x\n", getClock(), data.pc, p->pc, ram_out.inst);
}
void IFU::reset()
{
    IO_IFU data = {.pc = 0x80000000, .pc_valid = true};
    resetData(data);
}
#ifdef DUMP_WAVE_SUPPORT
#include <bitset>
void IFU::dump()
{
    auto data = getData();

    std::bitset<32> pc_bits(data.pc);
    dump_value(signal_names.at(0),pc_bits.to_string());

    std::bitset<1> pc_valid_bits(data.pc_valid);
    dump_value(signal_names.at(1),pc_valid_bits.to_string());
}
#endif