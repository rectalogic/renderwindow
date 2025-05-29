# Copyright (C) 2025 Andrew Wason
# SPDX-License-Identifier: GPL-3.0-or-later

qt_add_qml_module(renderwindow
    PLUGIN_TARGET renderwindow
    URI com.rectalogic.RenderWindow
    SOURCES
    render_window.cpp
    DEPENDENCIES
    QtQuick
)
