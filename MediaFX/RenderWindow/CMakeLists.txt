# Copyright (C) 2025 Andrew Wason
# SPDX-License-Identifier: GPL-3.0-or-later

qt_add_qml_module(renderwindow
    PLUGIN_TARGET renderwindow
    URI MediaFX.RenderWindow
    SOURCES
    render_control.cpp
    render_window.cpp
)

target_link_libraries(renderwindow PUBLIC Qt6::Core Qt6::Gui Qt6::GuiPrivate Qt6::Qml Qt6::Quick)
