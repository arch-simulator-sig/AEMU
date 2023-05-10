#include "trace_vcd.hpp"
#include <iostream>
#include <fstream>
#include <assert.h>

namespace AEMU::Trace
{
    static uint32_t name_num = 0;
    std::fstream file;
    void initTrace(std::string filename)
    {
        file.open(filename,std::ios::out);
        assert(file.is_open());
        writeString("$timescale 1ns $end\n");
        // std::cout << "$timescale 1ns $end\n";
    }

    void closeTrace()
    {
        file.close();
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
        // std::cout << str;
        file << str;
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
        std::string str = '#' + std::to_string(time) + '\n';
        writeString(str);
    }
}
