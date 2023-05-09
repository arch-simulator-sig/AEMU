#pragma once
#include "config.hpp"
#include "clock.hpp"
#include "macro.h"
#include "wavename.hpp"
#include <vector>
#include <string>
#include <iostream>
extern uint64_t global_clock;
namespace AEMU
{
    template <typename T>
    class Output
    {
    private:
        const static uint32_t IO_BUFF_SIZE = 2;
        T data[IO_BUFF_SIZE];

    protected:
        /* getDataP() 和 setData() 所修改的输出端口输出等效于Verilog中寄存器赋值方式："<="。 */
        T *getDataP()
        {
            return &data[(global_clock + 1) % IO_BUFF_SIZE];
        }
        void setData(T data)
        {
            this->data[(global_clock + 1) % IO_BUFF_SIZE] = data;
        }
        void resetData(T data)
        {
            for (uint32_t i = 0; i < IO_BUFF_SIZE; i++)
            {
                this->data[i] = data;
            }
        }

    public:
        T getData()
        {
            return data[global_clock % IO_BUFF_SIZE];
        }
    };

    class Module
    {
    public:
        virtual void run() = 0;
        virtual void reset() = 0;
        const char *name;
        
#ifdef DUMP_WAVE_SUPPORT
    public:
        virtual void dump() = 0;

    protected:
        std::vector<std::string> signal_names;
        void init_names(uint32_t signal_num)
        {
            for (size_t i = 0; i < signal_num; i++)
            {
                signal_names.push_back(allocate_name());
            }
        }
#endif
    };

}
