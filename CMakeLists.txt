cmake_minimum_required(VERSION 2.8.4)
project(XGac)
find_package(PkgConfig REQUIRED)

pkg_check_modules(DEPENDENCIES REQUIRED x11 cairo cairo-xlib pango pangocairo)
include_directories(${DEPENDENCIES_INCLUDE_PATHS})


add_subdirectory(Tests)
