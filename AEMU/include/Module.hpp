#pragma once
#include "trace_vcd.hpp"
#include "clock.hpp"
#include <vector>

#define IO_BUFF_SIZE 64

#if IO_BUFF_SIZE < 2
    #error IO_BUFF_SIZE must be at least 2
#endif

extern uint64_t global_cycle;
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
         * @brief 复位所有寄存器值。
         */
        virtual void reset(){};
        /**
         * @brief 更新模块的组合逻辑，在更新寄存器数据之前调用。
         */
        virtual void update(){};
        /**
         * @brief 在波形文件中声明模块所有信号
        */
        virtual void declare(){};
        /**
         * @brief 保存模块所有信号到波形文件中
        */
        virtual void trace(){};

        const char *name;

    protected:
        std::vector<std::string> signal_labels;
        void initSignalNames(uint32_t signal_num)
        {
            if (signal_labels.size() >= signal_num)
            {
                return;
            }
            size_t allocate_num = signal_num - signal_labels.size();
            for (size_t i = 0; i < allocate_num; i++)
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
        T data[IO_BUFF_SIZE];

    protected:
        /***
         * @brief 获取当前下一个周期端口数据指针，一般用于Module::run()更新模块所有寄存器值。
         */
        T *getNextDataP()
        {
            return &data[(global_cycle + 1) % IO_BUFF_SIZE];
        }
        /***
         * @brief 设置下一个周期端口数据，一般用于Module::reset()复位模块所有寄存器值。
         */
        void setNextData(T data)
        {
            this->data[(global_cycle + 1) % IO_BUFF_SIZE] = data;
        }
        /***
         * @brief 获取当前周期端口数据指针，用于Module::updata()更新组合逻辑输出端口。
         */
        T *getDataP()
        {
            return &data[global_cycle % IO_BUFF_SIZE];
        }

        /***
         * @brief 获取上周期端口数据指针，用于Module::trace()检查信号是否变化，无变化则不更新信号到文件中。
         */
        T *getLastDataP()
        {
            uint64_t index = global_cycle == 0 ? (IO_BUFF_SIZE - 1) : ((global_cycle - 1) % IO_BUFF_SIZE);
            return &data[index];
        }

    public:
        /***
         * @brief 获取当前周期端口数据，用于其他模块外部访问端口数据。
         */
        const T getData()
        {
            return data[global_cycle % IO_BUFF_SIZE];
        }
    };
}
