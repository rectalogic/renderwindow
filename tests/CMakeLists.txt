# Copyright (C) 2025 Andrew Wason
# SPDX-License-Identifier: GPL-3.0-or-later

find_package(Qt6 REQUIRED COMPONENTS Test)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

qt_add_executable(tst_render tst_render.cpp)
add_test(NAME tst_render COMMAND tst_render)
target_link_libraries(tst_render PRIVATE Qt6::Quick Qt::Test)
