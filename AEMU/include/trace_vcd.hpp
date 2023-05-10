#pragma once
#include <string>
#include <cstdarg>
#include <bitset>
#define TRACE_VCD_DECLAR(index, value, width, type) AEMU::Trace::declareValue(#value, signal_labels.at(index), type, width)
#define TRACE_VCD_BEGIN() auto now = getDataP(); auto prev = getLastDataP();
#define TRACE_VCD_DUMPVALUE(index, value, width)            \
if(now->value != prev->value || getCycle() < 2){                                                \
    std::bitset<width> inst_bits(now->value);                                \
    AEMU::Trace::dumpValue(signal_labels.at(index), inst_bits.to_string()); \
}

namespace AEMU::Trace
{
    void initTrace(std::string filename);
    void closeTrace();
    std::string getLabel(uint32_t num);
    std::string allocateLabel();
    void writeString(std::string str);
    void dumpValue(std::string name, std::string value);
    void declareModuleBegin(std::string name);
    void declareModuleEnd();
    void declareValue(std::string name, std::string label, std::string type, uint32_t width);
    void dumpTime(uint64_t time);
}
