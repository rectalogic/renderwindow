import QtQuick
import MediaFX.RenderWindow

RenderWindow {
    width: 100
    height: 100

    Rectangle {
        width: 60
        height: 40
        color: "green"
        anchors.centerIn: parent
        RotationAnimation on rotation {
            duration: 1000
            from: 0
            to: 90
        }
    }
}
