import QtQuick 2.12
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.12
import QtQuick.Window 2.0

Item {
    id: startMenu
    StartMenuBack{
        id:backmenu
        anchors.fill:startMenu
        focus: false
        z: -1
    }
    ColumnLayout{
        id: layoutmenu
        anchors.centerIn: startMenu
        spacing:20
        Text{
            Layout.alignment: Qt.AlignCenter
            text:"Pong"
            font{
                bold: true
                family: "Helvetica"
                pixelSize: 32
            }
        }

        Button{
            Layout.alignment: Qt.AlignCenter
            id: gameButton
            Layout.preferredHeight:  30
            Layout.preferredWidth: buttontxt.width + 20*2
            background:Rectangle{
                radius: 5
                color: "lightgray"
            }
            checkable: true
            Text{
                id:buttontxt
                anchors.centerIn: gameButton
                text:"Почати гру"
                color: "white"
            }
            onClicked: {
                backmenu.visible = false;
                layoutmenu.visible = false;
                layoutmenu.focus = false;
                game.visible = true;
                game.focus = true;
                visibility = Window.Maximized
            }
        }
    }
    Pong{
        id:game
        anchors.fill:startMenu
        focus:false
        visible: false
    }
//    onActiveFocusChanged: console.log(game.activeFocus)
}
