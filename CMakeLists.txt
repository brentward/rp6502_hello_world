cmake_minimum_required(VERSION 3.13)

project(MY-RP6502-PROJECT C ASM)

add_subdirectory(rp6502-sdk)

add_executable(snesdraw)
target_sources(snesdraw PRIVATE
    src/controllers.h
    src/main.c
    src/controllers.s
)
target_link_libraries(snesdraw PRIVATE
    rp6502
)
