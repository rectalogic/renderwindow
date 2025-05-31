# Copyright (C) 2025 Andrew Wason
# SPDX-License-Identifier: GPL-3.0-or-later

cmake_minimum_required(VERSION 3.22)

project(renderwindow VERSION 1.0.0 LANGUAGES CXX)

find_package(Qt6 6.9 REQUIRED COMPONENTS Core Gui Qml Quick)

qt_standard_project_setup(REQUIRES 6.9)
qt_policy(SET QTP0001 NEW)
cmake_policy(SET CMP0079 NEW)
enable_testing(true)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options($<$<CONFIG:Debug>:-fsanitize=address>)
add_link_options($<$<CONFIG:Debug>:-fsanitize=address>)

add_subdirectory(MediaFX/RenderWindow)
add_subdirectory(tests)
