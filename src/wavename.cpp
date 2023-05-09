#include "wavename.hpp"
static uint32_t name_num = 0;

std::string allocate_name()
{

    std::string name = "*";
    uint32_t count = name_num;
    do
    {
        uint32_t index = count % 52;
        char c;
        if (index < 26)
            c = index + 'a';
        else
            c = index + 'A' - 26;
        name.append(1, c);
        count /= 52;
    } while (count);
    name_num++;
    return name;
}
#include <iostream>
void dump_value(std::string name, std::string value)
{

    std::cout << 'b' << value << ' ' << name << '\n';
}
