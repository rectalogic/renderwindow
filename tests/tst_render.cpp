// Copyright (C) 2025 Andrew Wason
// SPDX-License-Identifier: GPL-3.0-or-later

#include <QByteArray>
#include <QImage>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QSize>
#include <QString>
#include <QWindow>
#include <QtCore>
#include <QtTest>
using namespace Qt::Literals::StringLiterals;

class tst_Render : public QObject {
    Q_OBJECT

public slots:
    void onCreated(QObject* object, const QUrl& url)
    {
        QVERIFY(object);
        QWindow* window = qobject_cast<QWindow*>(object);
        QSize size = window->size();
        for (int i = 0; i < 5; i++) { // NOLINT
            QByteArray data;
            QMetaObject::invokeMethod(object, "render",
                Q_RETURN_ARG(QByteArray, data),
                Q_ARG(qint64, static_cast<qint64>(i * 250)));
            QVERIFY(!data.isNull());
            QImage fixture(QFINDTESTDATA(u"fixtures/render-%1.png"_s.arg(i)));
            QImage image(reinterpret_cast<const uchar*>(data.constData()), size.width(), size.height(), QImage::Format_RGBA8888_Premultiplied); // NOLINT
            // image.save(u"render-%1.png"_s.arg(i));
            QCOMPARE_EQ(image, fixture.convertToFormat(QImage::Format_RGBA8888_Premultiplied));
            QTest::qWait(100); // NOLINT
        }
    }

private slots:
    void render()
    {
        QQmlApplicationEngine engine;
        connect(&engine, &QQmlApplicationEngine::objectCreated, this, &tst_Render::onCreated);
        engine.addImportPath(QFINDTESTDATA(".."));
        engine.load(QFINDTESTDATA("Render.qml"));
    }
};

QTEST_MAIN(tst_Render);
#include "tst_render.moc"
