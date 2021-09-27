cmake_minimum_required(VERSION 3.15)
project(opencl-pde-solver VERSION 1.0
             DESCRIPTION "Partial Differential Equation Solver"
             LANGUAGES CXX)

find_package(Threads)
find_package(OpenMP)
find_package(OpenCL REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)

set_target_properties(opencv_core PROPERTIES INTERFACE_COMPILE_FEATURES "")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILE_FEATURES EHsc)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    if (!WIN32)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -fopenmp")
    endif()
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -openmp -v")
        set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} libomp.lib")
    endif()
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        add_compile_options("-march=native;$<$<CONFIG:DEBUG>:-g;-Wall;-Wpedantic;-fsanitize=address>")
        add_link_options("$<$<CONFIG:DEBUG>:-fsanitize=address>")
    endif()
endif()

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL_ERROR "*** Please switch to x64 build! ***")
endif()

include(CTest)

add_subdirectory(src)
add_subdirectory(test)
