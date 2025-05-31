// Copyright (C) 2025 Andrew Wason
// SPDX-License-Identifier: GPL-3.0-or-later
#include "render_window.h"
#include "animation.h"
#include "render_control.h"
#include <QByteArray>
#include <QDebug>
#include <QMessageLogContext>
#include <QQmlEngine>
#include <QQmlTypeNotAvailable>
#include <QQuickItem>
#ifdef RENDERWINDOW_ENABLE_VULKAN
#include <QQuickGraphicsConfiguration>
#include <QSGRendererInterface>
#include <QVersionNumber>
#endif

RenderWindow::RenderWindow(RenderControl* renderControl)
    : QQuickWindow(renderControl)
    , m_renderControl(renderControl)
    , m_animationDriver(new AnimationDriver())
{
}

RenderWindow::RenderWindow()
    : RenderWindow(new RenderControl())
{
    m_animationDriver->install();
#ifdef RENDERWINDOW_ENABLE_VULKAN
    if (rendererInterface()->graphicsApi() == QSGRendererInterface::Vulkan) {
        m_vulkanInstance.setExtensions(QQuickGraphicsConfiguration::preferredInstanceExtensions());
        m_vulkanInstance.setApiVersion(QVersionNumber(1, 0));
        m_vulkanInstance.create();
        if (!m_vulkanInstance.isValid()) {
            qCritical() << "Invalid Vulkan instance";
            return;
        }
        setVulkanInstance(&m_vulkanInstance);
    }
#endif
    if (!m_renderControl->initialize()) {
        qCritical() << "Failed to initialize QQuickRenderControl";
        return;
    }
    m_isValid = true;
}

RenderWindow::~RenderWindow() {
    if (m_animationDriver)
        m_animationDriver->uninstall();
}

void RenderWindow::componentComplete()
{
    // QQuickWindow does not resize contentItem
    // https://bugreports.qt.io/browse/QTBUG-55028
    contentItem()->setSize(size());
}

QByteArray RenderWindow::render(qint64 elapsedMillis)
{
    if (!m_isValid) {
        return QByteArray();
    }

    m_animationDriver->setElapsed(elapsedMillis);
    m_animationDriver->advance();

    QByteArray data = m_renderControl->renderFrame();
    return data;
}
