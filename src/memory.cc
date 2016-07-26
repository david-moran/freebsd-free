#include "memory.hh"

namespace freebsd
{

uint32_t pages::page_size {sysctl::get<uint32_t>("vm.stats.vm.v_page_size")};

pages::pages() noexcept
    : pages(0)
{ }

pages::pages(uint32_t pages_count) noexcept
    : pages_count(pages_count)
{ }

pages::pages(const pages& other) noexcept
    : pages(other.pages_count)
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

pages& pages::operator=(const pages& other) noexcept
{
    this->pages_count = other.pages_count;
    return *this;
}

pages& pages::operator=(uint32_t pages_count) noexcept
{
    this->pages_count = pages_count;
    return *this;
}

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

swap::device::device(const kvm_swap& swap) noexcept
{
    _name = std::string(swap.ksw_devname);
    _total = static_cast<uint32_t> (swap.ksw_total);
    _free = static_cast<uint32_t> (swap.ksw_total) -
            static_cast<uint32_t> (swap.ksw_used);
}

const std::string& swap::device::name() const noexcept
{ return _name; }

const pages& swap::device::total() const noexcept
{ return _total; }

const pages& swap::device::free() const noexcept
{ return _free; }

swap::swap()
{
    uint32_t nswapdev = sysctl::get<uint32_t>("vm.nswapdev");

    kvm_t* kvm = kvm_open(nullptr, "/dev/null", nullptr, O_RDONLY, "kvm_open"); 
    if (kvm == nullptr)
    {
        throw std::runtime_error(
            "Can not open kernel virtual (KVM) memory image");
    }

    kvm_swap* swaps = new kvm_swap[nswapdev]; 
    int n = kvm_getswapinfo(kvm, swaps, nswapdev, 0);
    if (n == -1)
    {
        delete [] swaps;
        throw std::runtime_error(
            "Can not get swap info");
    }

    for (int i = 0; i <= n; i++)
    {
        devices.push_back({swaps[i]});
    }

    delete [] swaps;
    int err = kvm_close(kvm);
    if (err == -1)
    {
        throw std::runtime_error(
            "Can not close kernel virtual memory (KVM) image");
    }

}

swap::iterator swap::begin()
{ return devices.begin(); }

swap::const_iterator swap::begin() const
{ return devices.begin(); }

swap::const_iterator swap::cbegin() const
{ return devices.cbegin(); }

swap::iterator swap::end()
{ return devices.end(); }

swap::const_iterator swap::end() const
{ return devices.end(); }

swap::const_iterator swap::cend() const
{ return devices.cend(); }

};
