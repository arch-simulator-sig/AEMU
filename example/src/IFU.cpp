#include "IFU.hpp"
#include "RAM.hpp"
#include "common.hpp"
#include "trace_vcd.hpp"

IFU::IFU(const char *name)
{
    this->name = name;
    declare();
}
IFU::~IFU() {}

void IFU::bind(RAM *ram)
{
    this->ram = ram;
}
void IFU::run()
{
    /* 获取下周期输出寄存器指针 */
    p = getNextDataP();
    /* 获取当前周期寄存器值 */
    auto data = getDataP();
    /* 获取当前周期ram模块输出寄存器值 */
    auto ram_out = ram->getData();
    /* 更新下周期寄存器值 */
    p->pc_valid = true;
    if (ram_out.ready && data->pc_valid)
    {
        p->pc = data->pc + 4;
    }
    else
    {
        p->pc = data->pc;
    }
    p->test1 = data->test1 + 1;
    p->test2 = data->test2 + 1;
    p->test3 = data->test3 + 1;
    p->test4 = data->test4 + 1;
    /* 读取ram模块输出数据 */
    // printf("cycle:\t%ld \tPC:0x%08x inst:0x%08x\n", getCycle(), data.pc, ram_out.inst);
}
void IFU::reset()
{
    IO_IFU data = {.pc = 0x80000000, .pc_valid = true};
    setNextData(data);
}
