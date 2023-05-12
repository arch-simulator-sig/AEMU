#include "RAM.hpp"
#ifdef TRACE_VCD
#ifdef _RAM
#undef _RAM
#endif
#define _RAM 1
enum
{
#define IO_DECLARE(module, declare, name, type, width) IFONE(_##module, Index_##module##_##name, )
#include "Bundle.hpp"
#undef IO_DECLARE
    __Index_RAM_NUM
};
void RAM::trace()
{
    TRACE_VCD_BEGIN();
#define IO_DECLARE(module, declare, name, type, width) IFONE(_##module, TRACE_VCD_DUMPVALUE(Index_##module##_##name, name, width);)
#include "Bundle.hpp"
#undef IO_DECLARE
}
void RAM::declare()
{
    initSignalNames(__Index_RAM_NUM);

#define IO_DECLARE(module, declare, name, type, width) IFONE(_##module, TRACE_VCD_DECLARE(Index_##module##_##name, name, width, type);)
    Trace::declareModuleBegin(name);
#include "Bundle.hpp"
    Trace::declareModuleEnd();
#undef IO_DECLARE
}
#else
void RAM::trace()
{

}
void RAM::declare()
{

}
#endif
