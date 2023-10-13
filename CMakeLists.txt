cmake_minimum_required(VERSION 3.12)

project(HW3D_Triangles)

set(geo2D_files
    ../geometry/geometry2D.hpp
    ../geometry/geometry2D.cpp)
    set(geo3D_files
    ../geometry/geometry2D.hpp
    ../geometry/geometry2D.cpp
    ../geometry/geometry3D.hpp
    ../geometry/geometry3D.cpp)

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

add_executable(geo2D_tests tests/geo2D_tests.cpp ${geo2D_files})
add_executable(geo3D_tests tests/geo3D_tests.cpp ${geo3D_files})


add_executable(main main.cpp ${main_files})

target_link_libraries(geo2D_tests PRIVATE gtest)
target_link_libraries(geo3D_tests PRIVATE gtest)

include(GoogleTest)
gtest_discover_tests(geo2D_tests)
gtest_discover_tests(geo3D_tests)
