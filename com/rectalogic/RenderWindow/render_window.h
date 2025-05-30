// Copyright (C) 2025 Andrew Wason
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once
#include <QByteArray>
#include <QObject>
#include <QQmlParserStatus>
#include <QQuickWindow>
#include <QtCore>
#include <QtQmlIntegration>
#include <memory>
#include <qtgui-config.h>
class RenderControl;
#if (QT_CONFIG(vulkan) && __has_include(<vulkan/vulkan.h>))
#define RENDERWINDOW_ENABLE_VULKAN
#endif
#ifdef RENDERWINDOW_ENABLE_VULKAN
#include <QVulkanInstance>
#endif
class RenderControl;

class RenderWindow : public QQuickWindow, public QQmlParserStatus {
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    QML_ELEMENT

public:
    using QQuickWindow::QQuickWindow;

    explicit RenderWindow();
    RenderWindow(RenderWindow&&) = delete;
    RenderWindow& operator=(RenderWindow&&) = delete;
    ~RenderWindow() override;

    Q_INVOKABLE QByteArray render();

protected:
    void classBegin() override { }
    void componentComplete() override;

private:
    Q_DISABLE_COPY(RenderWindow);

    RenderWindow(RenderControl* renderControl);

#ifdef RENDERWINDOW_ENABLE_VULKAN
    QVulkanInstance m_vulkanInstance;
#endif
    std::unique_ptr<RenderControl> m_renderControl;
    bool m_isValid = false;
};
