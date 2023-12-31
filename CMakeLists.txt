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
set(tritri_files
    ../geometry/geometry2D.hpp
    ../geometry/geometry2D.cpp
    ../geometry/geometry3D.hpp
    ../geometry/geometry3D.cpp)

set(main_files
    geometry/geometry2D.hpp
    geometry/geometry2D.cpp
    geometry/geometry3D.hpp
    geometry/geometry3D.cpp
    intersect.hpp
    intersect.cpp)

enable_testing()

add_subdirectory(googletest)

include_directories(googletest/include)

add_executable(geo2D_tests tests/geo2D_tests.cpp ${geo2D_files})
add_executable(geo3D_tests tests/geo3D_tests.cpp ${geo3D_files})
add_executable(tritri_tests tests/tritri_tests.cpp ${tritri_files})


add_executable(main main.cpp ${main_files})

target_link_libraries(geo2D_tests PRIVATE gtest)
target_link_libraries(geo3D_tests PRIVATE gtest)
target_link_libraries(tritri_tests PRIVATE gtest)

include(GoogleTest)
gtest_discover_tests(geo2D_tests)
gtest_discover_tests(geo3D_tests)
gtest_discover_tests(tritri_tests)