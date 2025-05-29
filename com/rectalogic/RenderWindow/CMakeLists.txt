# Copyright (C) 2025 Andrew Wason
# SPDX-License-Identifier: GPL-3.0-or-later

qt_add_qml_module(renderwindow
    PLUGIN_TARGET renderwindow
    URI com.rectalogic.RenderWindow
    SOURCES
    render_window.cpp
)

target_link_libraries(renderwindow PUBLIC Qt6::Core Qt6::Gui Qt6::GuiPrivate Qt6::Qml Qt6::Quick)

set_target_properties(renderwindow PROPERTIES
    COMPONENT "${CMAKE_INSTALL_DEFAULT_COMPONENT_NAME}"
)
