set(BINARY ${CMAKE_PROJECT_NAME})

enable_testing()

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})

add_executable(${BINARY} ${SOURCES})

# create a lib for unit testing and an .exe
add_library(${BINARY}_lib STATIC ${SOURCES})
target_link_libraries(${BINARY}_lib PRIVATE ${OpenCV_LIBS} Eigen3::Eigen)
target_link_libraries(${BINARY} PRIVATE ${OpenCV_LIBS} Eigen3::Eigen)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        target_compile_options(${BINARY} PRIVATE /openmp /fp:strict)
endif()

target_compile_definitions(${BINARY} PRIVATE CL_TARGET_OPENCL_VERSION=100)

#extra warnings
#target_compile_options(${BINARY}_lib PRIVATE -Wall -Wextra)
#file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/src/Release)
#file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/src/Debug)