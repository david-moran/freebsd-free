#ifndef _SYSCTL_HH_
#define _SYSCTL_HH_

#include <cerrno>
#include <cstdio>

#include <exception>
#include <memory>
#include <string>

#include <sys/types.h>
#include <sys/sysctl.h>

namespace freebsd
{

class sysctl
{
public:
    template <typename T>
    static T get(const std::string& name);
};

template<typename T>
T sysctl::get(const std::string& name)
{
    T buf;
    size_t bufsz = sizeof(T);
    auto sctl = sysctlbyname;
    auto err = 0;
    err = sctl(name.c_str(), &buf, &bufsz, nullptr, 0);
    if (err == -1)
        throw std::runtime_error(strerror(errno));

    return buf;
}

}

#endif // _SYSCTL_HH_
