cmake_minimum_required(VERSION 3.16)
project(ArcadeBT
    VERSION 1.0
    DESCRIPTION "analysis framework for behavior trees"
    LANGUAGES C CXX
)

enable_testing()

# 3rd party libraries
find_package(GTest REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLog REQUIRED libglog)

find_package(Z3 4.8.15.0 EXACT REQUIRED)


add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(apps)