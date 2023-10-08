cmake_minimum_required(VERSION 3.12)

project(HW3D_Triangles)

set(geo_files
    ../geometry/geometry.hpp
    ../geometry/geometry.cpp
    ../geometry/algorithm.hpp
    ../geometry/algorithm.cpp)
set(isect_files
    ../geometry/geometry.hpp
    ../geometry/geometry.cpp
    ../geometry/algorithm.hpp
    ../geometry/algorithm.cpp
    ../intersection/intersect.hpp
    ../intersection/intersect.cpp
    ../intersection/degenerate.hpp
    ../intersection/degenerate.cpp)
set(deg_files
    ../geometry/geometry.hpp
    ../geometry/geometry.cpp
    ../geometry/algorithm.hpp
    ../geometry/algorithm.cpp
    ../intersection/intersect.hpp
    ../intersection/intersect.cpp
    ../intersection/degenerate.hpp
    ../intersection/degenerate.cpp)

set(main_files
    geometry/geometry.hpp
    geometry/geometry.cpp
    ../geometry/algorithm.hpp
    ../geometry/algorithm.cpp
    intersection/intersect.hpp
    intersection/intersect.cpp
    intersection/degenerate.hpp
    intersection/degenerate.cpp)

enable_testing()

add_subdirectory(googletest)

include_directories(googletest/include)

add_executable(geo_tests tests/geo_tests.cpp ${geo_files})
add_executable(isect_tests tests/isect_tests.cpp ${isect_files})
add_executable(deg_tests tests/deg_tests.cpp ${deg_files})

add_executable(main main.cpp ${main_files})

target_link_libraries(geo_tests PRIVATE gtest)
target_link_libraries(isect_tests PRIVATE gtest)
target_link_libraries(deg_tests PRIVATE gtest)

include(GoogleTest)
gtest_discover_tests(geo_tests)
gtest_discover_tests(isect_tests)
gtest_discover_tests(deg_tests)