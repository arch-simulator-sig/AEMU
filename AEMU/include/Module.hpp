#pragma once
#include "clock.hpp"

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
        T *getNextDataP()
        {
            return &data[(global_clock + 1) % IO_BUFF_SIZE];
        }
        void setNextData(T data)
        {
            this->data[(global_clock + 1) % IO_BUFF_SIZE] = data;
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
    };

}
