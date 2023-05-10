#pragma once
#include "trace_vcd.hpp"
#include "clock.hpp"
#include <vector>

extern uint64_t global_clock;
namespace AEMU
{

    class Module
    {
    public:
        /**
         * @brief 更新所有寄存器值，每周期调用一次。
         */
        virtual void run(){};
        /**
         * 复位所有寄存器值。
         */
        virtual void reset(){};
        /**
         * 更新模块的组合逻辑，在更新寄存器数据之前调用。
         */
        virtual void update(){};

        virtual void trace(){};
        const char *name;

    protected:
        std::vector<std::string> signal_labels;
        void initSignalNames(uint32_t signal_num)
        {
            for (size_t i = 0; i < signal_num; i++)
            {
                auto label = AEMU::Trace::allocateLabel();
                signal_labels.push_back(label);
            }
        }
    };

    template <typename T>
    class Output
    {
    private:
        const static uint32_t IO_BUFF_SIZE = 2;
        T data[IO_BUFF_SIZE];

    protected:
        /***
         * @brief 获取当前下一个周期端口数据指针，一般用于Module::run()更新模块所有寄存器值。
         */
        T *getNextDataP()
        {
            return &data[(global_clock + 1) % IO_BUFF_SIZE];
        }
        /***
         * @brief 设置下一个周期端口数据，一般用于Module::reset()复位模块所有寄存器值。
         */
        void setNextData(T data)
        {
            this->data[(global_clock + 1) % IO_BUFF_SIZE] = data;
        }
        /***
         * @brief 获取当前周期端口数据指针，用于Module::updata()更新组合逻辑输出端口。
         */
        T *getDataP()
        {
            return &data[global_clock % IO_BUFF_SIZE];
        }

        T *getLastDataP()
        {
            uint64_t index = global_clock == 0 ? (IO_BUFF_SIZE - 1) : ((global_clock - 1) % IO_BUFF_SIZE);
            return &data[index];
        }

    public:
        /***
         * @brief 获取当前周期端口数据，用于其他模块外部访问端口数据。
         */
        const T getData()
        {
            return data[global_clock % IO_BUFF_SIZE];
        }
    };
}
