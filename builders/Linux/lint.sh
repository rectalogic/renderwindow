#!/usr/bin/env bash
# Copyright (C) 2024 Andrew Wason
# SPDX-License-Identifier: GPL-3.0-or-later

CURRENT=${BASH_SOURCE%/*}
source "$CURRENT/../versions"

BUILD_TYPE=${BUILD_TYPE:-Debug}
RENDERWINDOW_BUILD=${BUILD_ROOT}/${BUILD_TYPE}
mkdir -p "${RENDERWINDOW_BUILD}"
cmake -S "${SOURCE_ROOT}" -B "$RENDERWINDOW_BUILD" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=${BUILD_TYPE} --install-prefix ${QTDIR} || exit 1

cd /renderwindow
git config --global --add safe.directory /renderwindow
FILES=$(git ls-files '**/*.cpp' '**/*.h')

echo clang-tidy
CLANGTIDY=$(/usr/bin/clang-tidy --quiet -p "${RENDERWINDOW_BUILD}" $FILES 2>&1 || exit 1)
# Manually suppress bogus error https://github.com/llvm/llvm-project/issues/58820
if echo "$CLANGTIDY" | egrep -v "qsharedpointer_impl\.h.*clang-analyzer-cplusplus\.NewDelete" | grep " warning: "; then
    echo "$CLANGTIDY"
    exit 1
fi

echo clazy
/usr/bin/clazy-standalone -p "${RENDERWINDOW_BUILD}/compile_commands.json" $FILES 2>&1 | (! grep warning || exit 1)
