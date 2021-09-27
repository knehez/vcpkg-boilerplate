enable_testing()
find_package(GTest REQUIRED)

# eliminate cxx_std_11 invlid flag problem
set_target_properties(GTest::gtest PROPERTIES INTERFACE_COMPILE_FEATURES "")
set_target_properties(GTest::gmock_main PROPERTIES INTERFACE_COMPILE_FEATURES "")
set_target_properties(GTest::gtest_main PROPERTIES INTERFACE_COMPILE_FEATURES "")
set_target_properties(GTest::gmock PROPERTIES INTERFACE_COMPILE_FEATURES "")

set(BINARY ${CMAKE_PROJECT_NAME}_test)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.hpp *.cpp)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib GTest::gtest GTest::gtest_main)