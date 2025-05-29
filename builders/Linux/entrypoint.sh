#!/usr/bin/env bash

OLD_UID=$(id -u renderwindow)
NEW_UID=$(stat -c "%u" /renderwindow/CMakeLists.txt)
if [ ! -z "$NEW_UID" -a "$NEW_UID" != "0" -a "$OLD_UID" != "$NEW_UID" ]; then
    usermod -u "$NEW_UID" -o renderwindow
fi

export $(cat /entrypoint/environment)

mkdir -p /renderwindow/build/Linux && chown -R renderwindow /renderwindow/build/Linux
exec gosu renderwindow /entrypoint/xvfb.sh "$@"
