#ifndef __MEMORY_HH__
#define __MEMORY_HH__

#include <cstdint>
#include <list>
#include <string>

#include <fcntl.h>
#include <kvm.h>

#include "sysctl.hh"

namespace freebsd
{

class pages
{
    static uint32_t page_size;
    uint32_t pages_count;

public:
    pages() noexcept;
    pages(uint32_t pages_count) noexcept;
    pages(const pages& pages) noexcept;

    uint32_t count() const noexcept;
    uint64_t bytes() const noexcept;
    uint64_t kilobytes() const noexcept;
    uint64_t megabytes() const noexcept;
    uint64_t gigabytes() const noexcept;

    pages& operator=(const pages& other) noexcept;
    pages& operator=(uint32_t pages_count) noexcept;
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

class swap
{

public:
    class device
    {
        std::string _name;
        pages _total,
              _free;
    public:
        device(const kvm_swap& swap) noexcept;
        const std::string& name() const noexcept;
        const pages& total() const noexcept;
        const pages& free() const noexcept;
    };

private:
    using device_list = std::list<device>;
    device_list devices;

public:
    using iterator = device_list::iterator;
    using const_iterator = device_list::const_iterator;

    swap();

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;

    iterator end();
    const_iterator end() const;
    const_iterator cend() const;
};

}

#endif
