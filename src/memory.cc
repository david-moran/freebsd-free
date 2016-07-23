#include "memory.hh"

namespace freebsd
{

uint32_t pages::page_size {sysctl::get<uint32_t>("vm.stats.vm.v_page_size")};

pages::pages(uint32_t pages_count) noexcept
    : pages_count(pages_count)
{ }

uint32_t pages::count() const noexcept
{ return pages_count; }

uint64_t pages::bytes() const noexcept
{ return pages_count * static_cast<uint64_t>(page_size); }

uint64_t pages::kilobytes() const noexcept
{ return bytes() / 1024; }

uint64_t pages::megabytes() const noexcept
{ return kilobytes() / 1024; }

uint64_t pages::gigabytes() const noexcept
{ return megabytes() / 1024; }

memory::memory() noexcept
{ }

const pages& memory::total() const noexcept
{ return _total; }

const pages& memory::active() const noexcept
{ return _active; }

const pages& memory::inactive() const noexcept
{ return _inactive; }

const pages& memory::wired() const noexcept
{ return _wired; }

const pages& memory::cached() const noexcept
{ return _cached; }

const pages& memory::free() const noexcept
{ return _free; }

};
