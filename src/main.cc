#include <iomanip>
#include <iostream>
#include <string>

#include <unistd.h>

#include "memory.hh"

template <typename T>
static void show_memory_stats(const T& format);

int main(int argc, char* argv[])
{
    int ch;
    auto format = &freebsd::pages::bytes;

    while((ch = getopt(argc, argv, "bkmg")) != -1)
    {
        switch(ch)
        {
        case 'b':
            format = &freebsd::pages::bytes;
            break;
        case 'k':
            format = &freebsd::pages::kilobytes;
            break;
        case 'm':
            format = &freebsd::pages::megabytes;
            break;
        case 'g':
            format = &freebsd::pages::gigabytes;
            break;
        default:
            exit(EXIT_FAILURE);
        }
    }

    show_memory_stats(format);

    return 0;
}

template <typename T>
static void show_memory_stats(const T& format)
{
    freebsd::memory m;
    std::cout 
              << std::setw(18) << "total"
              << std::setw(14) << "active"
              << std::setw(14) << "inactive"
              << std::setw(14) << "wired"
              << std::setw(14) << "cached"
              << std::setw(14) << "free" << std::endl;

    std::cout << "Mem:" 
              << std::setw(14) << (m.total().*format)()
              << std::setw(14) << (m.active().*format)()
              << std::setw(14) << (m.inactive().*format)()
              << std::setw(14) << (m.wired().*format)()
              << std::setw(14) << (m.cached().*format)()
              << std::setw(14) << (m.free().*format)() << std::endl;
}
