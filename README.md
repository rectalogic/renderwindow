# Qt MediaFX.RenderWindow

`MediaFX.RenderWindow` is a QML `QQuickWindow` subclass that supports offscreen rendering of its contents via `QQuickRenderControl`.

Given this QML

```qml
import QtQuick.Controls
import MediaFX.RenderWindow

RenderWindow {
    width: 160
    height: 160
    Button {
        text: "The Button"
    }
}
```

Instantiate a `QQmlApplicationEngine`, [`addImportPath`](https://doc.qt.io/qt-6/qqmlengine.html#addImportPath) the module,
then invoke `render(millis)` on the `RenderWindow` to get a `QByteArray` of RGBA pixels.
