cmake_minimum_required(VERSION 3.5)
project(freebsd-free)
add_compile_options(-std=c++1y)
add_executable(free src/main.cc src/memory.cc src/sysctl.cc)
target_link_libraries(free kvm)
install(TARGETS free
    RUNTIME DESTINATION bin
)
