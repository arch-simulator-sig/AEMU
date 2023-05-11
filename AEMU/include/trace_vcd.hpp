#pragma once
#include <string>
#include <cstdarg>
#include <bitset>

/* 定义TRACE_VCD以启用波形跟踪功能 */
#define TRACE_VCD

/* 默认波形保存周期上限 */
#define TRACE_MAX_CYCLE 10000

#ifdef TRACE_VCD
/**
 * @brief 声明保存的信号参数，用于Module::declare()
 * @param[in] index 波形在模块中标签的索引，不得超过总标签数目N（标签通过Output::initSignalNames(N)分配）。
 * @param[in] value 需要保存的信号
 * @param[in] width 信号位宽
 * @param[in] type  信号类型 可选值为：reg 和 wire 以及其他VCD支持关键词：event integer parameter real realtime supply0 supply1 tim tri triand trior trireg tri0 tri1 wand wor
 */
#define TRACE_VCD_DECLARE(index, value, width, type) AEMU::Trace::declareValue(#value, signal_labels.at(index), #type, width)

/**
 * @brief 获取本周期数据和上周期数据指针，用于Module::trace()中保存信号开始前
 */
#define TRACE_VCD_BEGIN()    \
    auto __now = getDataP(); \
    auto __prev = getLastDataP();

/**
 * @brief 保存信号到波形文件中，用于Module::trace()中保存信号值
 * @param[in] index 信号索引值，必须与声明一致
 * @param[in] value 信号值
 * @param[in] width 信号位宽，必须与声明一致
 * @note index和width必须与声明时保持一致
 */
#define TRACE_VCD_DUMPVALUE(index, value, width)                                \
    if (__now->value != __prev->value || AEMU::Trace::first_dump)               \
    {                                                                           \
        std::bitset<width> inst_bits(__now->value);                             \
        AEMU::Trace::dumpValue(signal_labels.at(index), inst_bits.to_string()); \
    }

/**
 * @brief 声明模块，在Module::declare()中调用
 * @param[in] name 模块名称
 * @param[in] ... 信号声明语句列表，在此声明所有信号。
 * @see TRACE_VCD_DECLARE(index, value, width, type)
 */
#define TRACE_VCD_INIT(name, ...)        \
    {                                    \
        Trace::declareModuleBegin(name); \
        __VA_ARGS__;                     \
        Trace::declareModuleEnd();       \
    }

#else
#define TRACE_VCD_DECLAR(index, value, width, type) {};

#define TRACE_VCD_BEGIN() {};

#define TRACE_VCD_DUMPVALUE(index, value, width) {};

#define TRACE_VCD_INIT(name, ...) {};

#endif

namespace AEMU::Trace
{
    extern bool first_dump;
    void initTrace(std::string filename);
    void closeTrace();
    std::string getLabel(uint32_t num);
    std::string allocateLabel();
    void dumpValue(std::string name, std::string value);
    void declareModuleBegin(std::string name);
    void declareModuleEnd();
    void declareValue(std::string name, std::string label, std::string type, uint32_t width);
    void dumpTime(uint64_t time);
    void dumpBufferWave(std::string filename);
}
