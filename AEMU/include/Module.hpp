#pragma once
#include "clock.hpp"

extern uint64_t global_clock;
namespace AEMU
{

    class Module
    {
    public:
        virtual void run(){};
        virtual void reset(){};
        virtual void update(){};
        const char *name;
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
