
template = """#include "MODULE_NAME.hpp"
#ifdef TRACE_VCD
#ifdef _MODULE_NAME
#undef _MODULE_NAME
#endif
#define _MODULE_NAME 1
enum
{
#define IO_DECLARE(module, declare, name, type, width) IFONE(_##module, Index_##module##_##name, )
#include "HEADER_FILE"
#undef IO_DECLARE
    __Index_MODULE_NAME_NUM
};
void MODULE_NAME::trace()
{
    TRACE_VCD_BEGIN();
#define IO_DECLARE(module, declare, name, type, width) IFONE(_##module, TRACE_VCD_DUMPVALUE(Index_##module##_##name, name, width);)
#include "HEADER_FILE"
#undef IO_DECLARE
}
void MODULE_NAME::declare()
{
    initSignalNames(__Index_MODULE_NAME_NUM);

#define IO_DECLARE(module, declare, name, type, width) IFONE(_##module, TRACE_VCD_DECLARE(Index_##module##_##name, name, width, type);)
    Trace::declareModuleBegin(name);
#include "HEADER_FILE"
    Trace::declareModuleEnd();
#undef IO_DECLARE
}
#else
void MODULE_NAME::trace()
{

}
void MODULE_NAME::declare()
{

}
#endif
"""


# import sys
# args = sys.argv
# if len(args) == 3:
#     module = args[1]
#     header = args[2]
# elif len(args) == 2:
#     module = args[1]
#     header = "Bundle.hpp"
# else :
#     print("must give 'module class name' and 'header file name only.")
import argparse

parser = argparse.ArgumentParser(description='Process some strings.')
parser.add_argument('-M','--module', type=str, help='the module class name')
parser.add_argument('-H','--header', type=str, default='Bundle.hpp', help='the header file name')

args = parser.parse_args()


module = args.module
header = args.header
module_template = "MODULE_NAME"
header_template = "HEADER_FILE"
template = template.replace(module_template, module)
template = template.replace(header_template, header)
# print(template)
with open("Trace{}.cpp".format(module), "w") as f:
    f.write(template)
