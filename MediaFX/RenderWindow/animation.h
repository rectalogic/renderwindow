// Copyright (C) 2025 Andrew Wason
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QAnimationDriver>

class AnimationDriver : public QAnimationDriver {
public:
    AnimationDriver(QObject* parent = nullptr)
        : QAnimationDriver(parent)
    {
    }

    void setElapsed(qint64 elapsedMillis)
    {
        m_elapsed = elapsedMillis;
    }

    void advance() override
    {
        advanceAnimation();
    }

    qint64 elapsed() const override
    {
        return m_elapsed;
    }

private:
    qint64 m_elapsed = 0;
};
