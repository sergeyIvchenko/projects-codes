function plate_collision(ball, plate, speed) {
    if(ball.y > plate.y && ball.y < (plate.y + plate.height)){
        ball.timer_run = false
        speed.value = plate.moving ? plate.direction*plate.step/50 : 0
        ball.way *= -1
        ball.k = ball.k === 0 ?(ball.k+speed.value*2) : -(ball.k+speed.value*2)
        ball.b = ball.y - ball.k*ball.x
        return true
    }
    return false
}

function win_collision(ball,window){
    if(!ball.visible)return false
    if(ball.x <= 0){
        return 1
    }
    else if((ball.x + ball.width) >= window.width){
        return -1
    }
    return false
}

function window_collision(ball,window){
    if(!ball.visible)return false
    if(ball.y <= 0 || (ball.y+ball.height) >= window.height){
        ball.k = -ball.k
        ball.b = ball.y - ball.k*ball.x
        ball.x += ball.one_step
    }
}
