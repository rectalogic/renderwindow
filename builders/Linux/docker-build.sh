#!/usr/bin/env bash
# Copyright (C) 2025 Andrew Wason
# SPDX-License-Identifier: GPL-3.0-or-later

CURRENT=${BASH_SOURCE%/*}
source "$CURRENT/../versions"

# https://doc.qt.io/qt-6/get-and-install-qt-cli.html#providing-login-information
if [[ ! $QTACCOUNT ]]; then
    if [ $(uname) = "Darwin" ]; then
        QTACCOUNT=~/Library/Application\ Support/Qt/qtaccount.ini
    elif [ $(uname) = "Linux" ]; then
        QTACCOUNT=~/.local/share/Qt/qtaccount.ini
    fi
    if [ ! -f "$QTACCOUNT" ]; then
        echo "Must set QTACCOUNT to qtaccount.ini credentials"
        exit 1
    fi
fi

TAG=${TAG:-ghcr.io/rectalogic/renderwindow:${UBUNTU:-noble}-$(git branch --show-current)}
docker buildx build --secret id=qtaccount,src="$QTACCOUNT" --build-arg UBUNTU=${UBUNTU:-noble} --build-arg QT_VER=${QT_VER:?} --build-arg QT_INSTALLER_VER=${QT_INSTALLER_VER:?} --platform linux/amd64 --memory-swap -1 --load --tag ${TAG} --file "${CURRENT}/Dockerfile" "${CURRENT}/.."
