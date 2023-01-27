import QtQuick 2.12

Rectangle{
    //property alias plheight: root.height
    property int step: 10
    property int direction
    //property double speed
    property alias moving: move_anim.running
    id: root
    color: "white"
    width: 10
    height: 180
    y: mainheight/2 - height/2
    Keys.onPressed: (event) =>
    {
        if(y >= 0 && event.key === Qt.Key_W){
            direction = -1
            y = y - step
        }
        if((y + height) >= mainheight){}
        else if(event.key === Qt.Key_S){
            direction = 1
            y = y + step
        }
        event.accepted = true
    }
    Behavior on y{
        id:behav
        animation:NumberAnimation{
            id:move_anim
            easing.type: Easing.Linear
            duration: 50

        }
    }
}
