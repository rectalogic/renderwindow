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

qt_query_qml_module(renderwindow
    PLUGIN_TARGET renderwindow_plugin_target
    TARGET_PATH renderwindow_target_path
    QMLDIR renderwindow_qmldir
    TYPEINFO renderwindow_typeinfo
)

set(release_dir "Release/qml/${renderwindow_target_path}")
install(TARGETS "${renderwindow_plugin_target}"
    CONFIGURATIONS Release
    LIBRARY DESTINATION "${release_dir}"
    RUNTIME DESTINATION "${release_dir}"
)
install(FILES
    CONFIGURATIONS Release
    "${renderwindow_qmldir}"
    DESTINATION "${release_dir}"
)
install(FILES
    CONFIGURATIONS Release
    "${renderwindow_typeinfo}"
    DESTINATION "${release_dir}"
)
