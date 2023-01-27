import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0
import QtTest 1.2

Window {
    property alias mainheight: root.height
    id:root
    width: 1024
    height: 600
    visible: true
    title: qsTr("Pong")
    StartMenu{
        anchors.fill:parent
    }
}
