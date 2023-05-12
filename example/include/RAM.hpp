#pragma once
#include "macro.h"
#include "Module.hpp"
class IFU;
using namespace AEMU;

typedef struct
{
#define _RAM 1
#define IO_DECLARE(module, declare, name, type, width) IFONE(_##module, declare name;)
#include "Bundle.hpp"
#undef IO_DECLARE
#undef _RAM
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
    void update();
    void trace();
    void declare();
};