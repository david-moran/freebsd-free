#ifndef __MEMORY_HH__
#define __MEMORY_HH__

#include <cstdint>
#include <string>

#include "sysctl.hh"

namespace freebsd
{

class pages
{
    static uint32_t page_size;
    uint32_t pages_count;

public:
    pages(uint32_t pages_count) noexcept;

    uint32_t count() const noexcept;
    uint64_t bytes() const noexcept;
    uint64_t kilobytes() const noexcept;
    uint64_t megabytes() const noexcept;
    uint64_t gigabytes() const noexcept;
};

class memory
{
    pages _total     {sysctl::get<uint32_t>("vm.stats.vm.v_page_count")},
          _active    {sysctl::get<uint32_t>("vm.stats.vm.v_active_count")},
          _inactive  {sysctl::get<uint32_t>("vm.stats.vm.v_inactive_count")},
          _wired     {sysctl::get<uint32_t>("vm.stats.vm.v_wire_count")},
          _cached    {sysctl::get<uint32_t>("vm.stats.vm.v_cache_count")},
          _free      {sysctl::get<uint32_t>("vm.stats.vm.v_free_count")};
public:
    memory() noexcept;

    const pages& total() const noexcept;
    const pages& active() const noexcept;
    const pages& inactive() const noexcept;
    const pages& wired() const noexcept;
    const pages& cached() const noexcept;
    const pages& free() const noexcept;
};

}

#endif
