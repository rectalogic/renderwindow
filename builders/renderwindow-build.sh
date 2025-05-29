#!/usr/bin/env bash
# Copyright (C) 2025 Andrew Wason
# SPDX-License-Identifier: GPL-3.0-or-later

CURRENT=${BASH_SOURCE%/*}
source "$CURRENT/versions"

BUILD_TYPE=${BUILD_TYPE:-Release}
RENDERWINDOW_BUILD="${BUILD_ROOT}/${BUILD_TYPE}"
mkdir -p "$RENDERWINDOW_BUILD"
(cmake -S "${SOURCE_ROOT}" -B "$RENDERWINDOW_BUILD" -DCMAKE_BUILD_TYPE=$BUILD_TYPE --install-prefix "${QTDIR}" && cmake --build "$RENDERWINDOW_BUILD" && ${SUDO} cmake --install "$RENDERWINDOW_BUILD") || exit 1
