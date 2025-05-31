#!/usr/bin/env bash
# Copyright (C) 2025 Andrew Wason
# SPDX-License-Identifier: GPL-3.0-or-later

CURRENT=${BASH_SOURCE%/*}
source "$CURRENT/versions"

BUILD_TYPE=${BUILD_TYPE:-Release}
ctest --test-dir "${BUILD_ROOT}/${BUILD_TYPE}" --output-on-failure "${@}" || exit 1
