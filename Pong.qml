import QtQuick 2.12
import "Collision_funcs.js" as Collisions

FocusScope{
    Rectangle{
        anchors.fill: parent
        id:root
        color: "black"
        Plate{
            id: game_plate
            focus: true
            anchors{
                left: root.left
                leftMargin: 20
            }
        }
        Plate{
            id:bot_plate
            anchors{
                right:root.right
                rightMargin: 20
            }
            direction: game_plate.direction
            y:game_plate.y
            x:game_plate.x
        }
        Ball{
            focus:false
            id:ball
            x: root.width/2 - width/2
            b: root.height/2 - height/2
            //y: k * x + b
            Binding on y{
                value: ball.k*ball.x+ball.b
                delayed: true
            }
            onXChanged: {
                //console.log(bot_plate.x )
                if(x <= (game_plate.x + game_plate.width) ||
                        (x + width) >= (bot_plate.x)){
                    let speed = {value: 0}
                    if(one_step < 0 && Collisions.plate_collision(ball,game_plate,speed)){}
                    else if(one_step > 0 && Collisions.plate_collision(ball,bot_plate,speed)){}
                    else return
                    timer_run = true
                }
            }
        }
        WinMessage{
            id:win
            anchors{
                horizontalCenter: root.horizontalCenter
                top:root.top
                topMargin: 30
            }

            text: `${ball.win_count}:${ball.lose_count}`
        }
    }
}


