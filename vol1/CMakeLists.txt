#    /the-towel/vol1/CMakeLists.txt
#
#    @author zmij
#    @date Jan 25, 2017

cmake_minimum_required(VERSION 2.6)

if (NOT GTEST_INCLUDE_DIRS)
    find_package(GTest REQUIRED)
endif()
if (NOT CMAKE_THREAD_LIBS_INIT)
    find_package(Threads REQUIRED)
endif()

# Add your package dependencies for test here

include_directories(${GTEST_INCLUDE_DIRS})

set(
    test_program_SRCS
    # Add your sources here
    iostreamable.cpp
    has_call_operator.cpp
    is_metafunction.cpp
)
add_executable(test-vol1 ${test_program_SRCS})
target_link_libraries(
    test-vol1
    ${GTEST_BOTH_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    # Add your libraries here
)

if (GTEST_XML_OUTPUT)
    set (
        TEST_ARGS
        --gtest_output=xml:test-volume-1-detail.xml
    )
endif()

add_test(
    NAME test-volume-1
    COMMAND test-vol1 ${TEST_ARGS}
)
