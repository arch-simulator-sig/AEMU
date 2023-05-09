#pragma once
#include "Module.hpp"
#include "stdio.h"
#include <vector>
#include <string>

using namespace AEMU;

class RAM;

typedef struct
{
    uint32_t pc;
    bool pc_valid;
} IO_IFU;

class IFU : public Module, public Output<IO_IFU>
{
private:
    IO_IFU *p;
    RAM *ram;

public:
    IFU() : IFU("ifu") {}
    IFU(const char *name);
    ~IFU();

    void bind(RAM *ram);
    void run();
    void reset();
#ifdef DUMP_WAVE_SUPPORT
public:
    void dump();
#endif // DUMP_WAVE_SUPPORT
};