project(freebsd-free)
add_compile_options(-std=c++1y)
add_executable(freebsd-free src/main.cc src/memory.cc src/sysctl.cc)
target_link_libraries(freebsd-free kvm)
