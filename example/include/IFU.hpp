#pragma once
#include "macro.h"
#include "Module.hpp"
using namespace AEMU;

class RAM;

typedef struct
{
#define _IFU 1
#define IO_DECLARE(module, declare, name, type, width) IFONE(_##module, declare name; )
#include "Bundle.hpp"
#undef IO_DECLARE
#undef _IFU
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
    void trace();
    void declare();
};