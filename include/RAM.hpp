#pragma once
#include "Module.hpp"
class IFU;

using namespace AEMU;
typedef struct
{
    uint32_t inst;
} IO_RAM;
class RAM : public Module, public Output<IO_RAM>
{
private:
    IO_RAM *p;
    IFU *ifu;

public:
    RAM() : RAM("ram"){};
    RAM(const char *name);
    ~RAM();
    void bind(IFU *ifu);
    void run();
    void reset();
    void dump();
};