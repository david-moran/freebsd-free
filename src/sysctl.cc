#include "sysctl.hh"

namespace freebsd
{

template<>
std::string sysctl::get<std::string>(const std::string& name)
{
    size_t bufsz;
    auto sctl = sysctlbyname;
    auto err = 0;

    err = sctl(name.c_str(), nullptr, &bufsz, nullptr, 0);
    if (err == -1)
        throw std::runtime_error(strerror(errno));

    auto buf = std::make_unique<char>(bufsz);
    err = sctl(name.c_str(), buf.get(), &bufsz, nullptr, 0);
    if (err == -1)
        throw std::runtime_error(strerror(errno));

    return std::move(std::string(buf.get()));
}

}
