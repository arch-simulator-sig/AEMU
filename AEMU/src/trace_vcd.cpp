#include "trace_vcd.hpp"
#include <iostream>
#include <fstream>
#include <assert.h>
#include "clock.hpp"
#include "Module.hpp"
#include "AEMU.hpp"

namespace AEMU::Trace
{
    bool first_dump = true;
    static uint32_t name_num = 0;
    static uint64_t dump_num = 0;
    std::fstream file;

    void writeString(std::string str);

    void initTrace(std::string filename)
    {
#ifdef TRACE_VCD
        file.open(filename, std::ios::out);
        assert(file.is_open());
        writeString("$timescale 1ns $end\n");
#endif
        // std::cout << "$timescale 1ns $end\n";
    }

    void closeTrace()
    {
#ifdef TRACE_VCD
        file.close();
#endif
    }

    std::string getLabel(uint32_t num)
    {
        std::string name = "*";
        do
        {
            uint32_t index = num % 52;
            char c;
            if (index < 26)
                c = index + 'a';
            else
                c = index + 'A' - 26;
            name.append(1, c);
            num /= 52;
        } while (num);
        return name;
    }
    std::string allocateLabel()
    {
        return getLabel(name_num++);
    }

    void writeString(std::string str)
    {
#ifdef TRACE_VCD
        if (dump_num <= TRACE_MAX_CYCLE)
        {
            // std::cout << str;
            file << str;
        }
#else
        std::cerr << "Try to write vcd when TRACE is not defined.\n Write message: " << str;
#endif
    }

    void dumpValue(std::string name, std::string value)
    {
        std::string str = 'b' + value + ' ' + name + '\n';
        writeString(str);
    }

    void declareModuleBegin(std::string name)
    {
        std::string str = "$scope module " + name + " $end\n";
        writeString(str);
    }

    void declareModuleEnd()
    {
        writeString("$upscope $end\n");
    }

    void declareValue(std::string name, std::string label, std::string type, uint32_t width)
    {
        std::string str = "$var " + type + " " + std::to_string(width) + " " + label + " " + name + " $end\n";
        writeString(str);
    }

    void dumpTime(uint64_t time)
    {

#ifdef TRACE_VCD
        dump_num++;
        std::string str = '#' + std::to_string(time) + '\n';
        writeString(str);
#endif
    }

    void dumpBufferWave(std::string filename)
    {
        if (file.is_open())
        {
            closeTrace();
        }
        initTrace(filename);
        uint64_t total_cycle = getCycle();
        uint64_t start_cycle = 0;
        if (total_cycle >= IO_BUFF_SIZE)
        {
            start_cycle = total_cycle - (IO_BUFF_SIZE - 1);
        }
        dump_num = 0;
        first_dump = true;
        AEMU::declareModules();
        AEMU::updateModules();
        for (uint64_t cycle = start_cycle; cycle <= total_cycle; cycle++)
        {
            dump_num = 0;
            setCycle(cycle);
            AEMU::traceModules();
        }
    }
}
