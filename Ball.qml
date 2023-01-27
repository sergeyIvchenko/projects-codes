import QtQuick 2.12
import "Collision_funcs.js" as Collisions

Rectangle {
//    property int angle
    property int win_count: 0
    property int lose_count: 0
    property int way: -1
    property double k: 0
    property double b
    property alias timer_run: timer.running
    property double time: 3
    property double one_step: way * 5
    id: ball
    width: 10
    height: width
    radius: height / 2
//    Binding on y{
//        value: ball.k*ball.x+ball.b
//        delayed: true
//    }
    //onXChanged: console.log(x,";",y)
    Timer{
        id:timer
        running: false
//        triggeredOnStart: true
        interval: time
        repeat: true
        onTriggered: {
            //console.log(x)
            x += one_step
        }
    }
    onVisibleChanged:{
        if(visible){
           timer_run = true
        }
    }
    onXChanged: {
        switch(Collisions.win_collision(ball,parent)){
            case 1:{
                lose_count++
                break
            }
            case -1:{
                win_count++
                break
            }
            default:return
        }
        x = Qt.binding(function(){return parent.width/2 - width/2})
        k = 0
        b = parent.height/2 - height/2
        way = way > 0 ? -way : way
    }
    onYChanged:Collisions.window_collision(ball,parent)
}
