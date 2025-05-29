// Copyright (C) 2025 Andrew Wason
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <QObject>
#include <QQuickWindow>

class RenderWindow : public QQuickWindow {
    Q_OBJECT
    QML_ELEMENT
    public:
        using QQuickWindow::QQuickWindow;

        explicit RenderWindow();
        RenderWindow(RenderWindow&&) = delete;
        RenderWindow& operator=(RenderWindow&&) = delete;
        ~RenderWindow() override;
    private:
        Q_DISABLE_COPY(RenderWindow);
};
