#!/usr/bin/env bash
# Copyright (C) 2023 Andrew Wason
# SPDX-License-Identifier: GPL-3.0-or-later

set -e

CURRENT=${BASH_SOURCE%/*}
source "$CURRENT/../versions"

BUILD_TYPE=${BUILD_TYPE:-Debug}
RENDERWINDOW_BUILD=${BUILD_ROOT}/${BUILD_TYPE}
mkdir -p "${RENDERWINDOW_BUILD}"
CC="clang" CXX="clang++" cmake -S "${SOURCE_ROOT}" -B "$RENDERWINDOW_BUILD" -DCMAKE_CXX_INCLUDE_WHAT_YOU_USE="/usr/bin/iwyu;-Xiwyu;--mapping_file=/usr/local/Qt/${QT_VER}/qt.imp;-Xiwyu;--mapping_file=/renderwindow/builders/Linux/iwyu.imp;-Xiwyu;--cxx17ns;-Xiwyu;--no_comments" --install-prefix ${QTDIR} && exec cmake --build "${RENDERWINDOW_BUILD}" --parallel 4
