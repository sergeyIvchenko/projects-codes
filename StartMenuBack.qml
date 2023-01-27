import QtQuick 2.12

Rectangle {
    id: menu
    gradient: Gradient{
        GradientStop{
            position: 0.0; color: "green"
        }
        GradientStop{
            position: 0.5;color: "yellow"
        }
        GradientStop{
            position: 1.0;color:"blue"
        }
    }
    clip:true
    RotationAnimation on rotation{
        easing.type: Easing.Linear
        from: 0; to:360
        duration: 5000
        loops: RotationAnimation.Infinite
    }
    scale:2.0
}
