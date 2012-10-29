cmake_minimum_required (VERSION 2.6)
project (simpletron)

set(SIMPLETRON_SOURCES sml.c memory.c)
add_executable(simpletron ${SIMPLETRON_SOURCES})