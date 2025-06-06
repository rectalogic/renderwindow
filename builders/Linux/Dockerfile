# Copyright (C) 2023 Andrew Wason
# SPDX-License-Identifier: GPL-3.0-or-later

# syntax = docker/dockerfile:1.4

ARG UBUNTU=noble

FROM ubuntu:${UBUNTU} AS base

ENV container=docker
ENV DEBIAN_FRONTEND=noninteractive
ENV LANG=en_US.UTF-8
ENV LC_ALL=C.UTF-8
RUN apt-get -y update && apt-get -y install \
    curl \
    libx11-xcb1 \
    libxcb-cursor0 \
    libxcb-glx0 \
    libxcb-icccm4 \
    libxcb-image0 \
    libxcb-keysyms1 \
    libxcb-randr0 \
    libxcb-render-util0 \
    libxcb-shape0 \
    libxcb-shm0 \
    libxcb-sync1 \
    libxcb-xfixes0 \
    libxcb-xkb1 \
    libxcb1 \
    libxkbcommon-x11-0


FROM base AS qt

ARG QT_VER
ARG QT_INSTALLER_VER
ENV container=docker
ENV DEBIAN_FRONTEND=noninteractive
ENV LANG=en_US.UTF-8
ENV LC_ALL=C.UTF-8
RUN apt-get -y update && apt-get -y install \
    libdbus-1-3 \
    libfontconfig1 \
    libfreetype6 \
    libglib2.0-bin \
    libx11-6 \
    python3

SHELL ["/bin/bash", "-c"]
ARG TARGETPLATFORM
RUN --mount=type=secret,id=qtaccount,target=/root/.local/share/Qt/qtaccount.ini <<EOF
    if [ "${TARGETPLATFORM}" = "linux/arm64" ]; then
        ARCH=arm64
    else
        ARCH=x64
    fi
    QT_VER_NODOT=${QT_VER//.}
    QTSPEC=qt6.${QT_VER_NODOT}
    INSTALLER=qt-online-installer-linux-${ARCH}-${QT_INSTALLER_VER}.run
    curl -O https://qt.mirror.constant.com/archive/online_installers/${QT_INSTALLER_VER%.*}/${INSTALLER} \
    && chmod +x ${INSTALLER} \
    && ./${INSTALLER} --root /usr/local/Qt --accept-licenses --accept-obligations --default-answer --confirm-command \
      --auto-answer telemetry-question=No --no-default-installations --no-force-installations \
      install \
      qt.${QTSPEC}.linux_gcc_64 \
    && find /usr/local/Qt/Docs/Qt-${QT_VER} -type f -and -not -name '*.index' -delete \
    && curl -o iwyu-mapgen-qt.py https://raw.githubusercontent.com/include-what-you-use/include-what-you-use/clang_17/mapgen/iwyu-mapgen-qt.py \
    && python3 iwyu-mapgen-qt.py /usr/local/Qt/${QT_VER}/*/include > "/usr/local/Qt/${QT_VER}/qt.imp"
EOF


FROM base AS renderwindow
LABEL maintainer=rectalogic
ARG QT_VER
ARG UBUNTU=noble

ENV GALLIUM_DRIVER=softpipe
ENV LIBGL_ALWAYS_SOFTWARE=1
ENV DRI_NO_MSAA=1

ENV container=docker
ENV DEBIAN_FRONTEND=noninteractive
ENV LANG=en_US.UTF-8
ENV LC_ALL=C.UTF-8
RUN <<EOF
    apt-get -y update && apt-get -y install \
        bash \
        build-essential \
        clang-format-17 \
        clang-tidy \
        clazy \
        ffmpeg \
        fontconfig \
        fonts-liberation \
        git \
        gosu \
        iwyu \
        libavcodec-dev \
        libavfilter-dev \
        libavformat-dev \
        libavutil-dev \
        libglvnd-dev \
        libglx-mesa0 \
        libnss3 \
        libpulse0 \
        libvulkan-dev \
        libxcomposite1 \
        libxdamage1 \
        libxkbcommon-dev \
        libxi6 \
        libxrandr2 \
        libxrender1 \
        libxtst6 \
        mesa-vulkan-drivers \
        ninja-build \
        pkg-config \
        python3 \
        python3-pip \
        sudo \
        xvfb \
        xz-utils
EOF

RUN curl -L https://github.com/Kitware/CMake/releases/download/v3.29.2/cmake-3.29.2-linux-$(uname --machine).tar.gz | tar xfz - --strip-components=1 -C /usr/local

COPY --from=qt /usr/local/Qt /usr/local/Qt/

ARG TARGETPLATFORM
RUN <<EOF
if [ "${TARGETPLATFORM}" = "linux/arm64" ]; then
    QTDIR=/usr/local/Qt/${QT_VER}/gcc_arm64
else
    QTDIR=/usr/local/Qt/${QT_VER}/gcc_64
fi
mkdir -p /entrypoint
echo QTDIR=${QTDIR} >> /entrypoint/environment
echo PATH=${QTDIR}/bin:$PATH >> /entrypoint/environment
chmod +x /entrypoint/environment
EOF

ENV QT_VER=${QT_VER}

RUN ldconfig

RUN useradd -ms /bin/bash -d /renderwindow/build/Linux -g root -G sudo renderwindow
RUN echo "renderwindow ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/renderwindow && chmod 0440 /etc/sudoers.d/renderwindow
VOLUME /renderwindow
WORKDIR /renderwindow/build/Linux

COPY Linux/entrypoint.sh Linux/xvfb.sh /entrypoint/

ENTRYPOINT ["/entrypoint/entrypoint.sh"]
CMD ["/renderwindow/builders/renderwindow-build.sh"]
