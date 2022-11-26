; parameters = bh: upper-limit, bl: lower-limit
; return value in bx
generateRandomNumber proc uses ax cx dx
randomNumber:
mov ah, 00h
int 1ah
cmp dl, bh
ja randomNumber
cmp dl, bl
jb randomNumber
mov dh, 0
mov bx, dx
ret
generateRandomNumber endp

enableBall proc uses ax bx cx dx si
mov si, offset ballCoordinates
mov cx, [si]
mov dx, [si + 2]
mov ah, 0
mov al, ballDirection
cmp al, 10
je moveBallUp
cmp al, 20
je moveBallDown
jmp exitBall
moveBallUp:
call clearBall
dec dx
call updateBallCoordinates
call drawBall
jmp exitBall
moveBallDown:
call clearBall
inc dx
call updateBallCoordinates
call drawBall
jmp exitBall
exitBall:
ret
enableBall endp

enablePad proc uses ax bx cx dx si
mov si, offset padCoordinates
mov cx, [si]
mov dx, [si + 2]
push ax
mov ax, windowWidth
mov bh, 0
mov bl, padWidth
sub ax, bx
mov bx, ax
pop ax
cmp ah, 77
je drawRight
cmp ah, 75
je drawLeft
jmp exitPad
drawRight:
call clearPad
mov ah, 0
mov al, padSpeed
add cx, ax
cmp cx, bx
ja setToMax
call updatePadCoordinates
call drawPad
jmp exitPad
drawLeft:
call clearPad
mov ah, 0
mov al, padSpeed
sub cx, ax
cmp cx, bx
ja setToMin
call updatePadCoordinates
call drawPad
jmp exitPad
setToMax:
mov cx, bx
call updatePadCoordinates
call drawPad
jmp exitPad
setToMin:
mov cx, 0
call updatePadCoordinates
call drawPad
jmp exitPad
exitPad:
ret
enablePad endp

; parameters = cx: x-coordinate, dx: y-coordinate
updateBallCoordinates proc uses cx dx si
mov si, offset ballCoordinates
mov [si], cx
mov [si + 2], dx
ret
updateBallCoordinates endp

; parameters = cx: x-coordinate, dx: y-coordinate
updatePadCoordinates proc uses cx dx si
mov si, offset padCoordinates
mov [si], cx
mov [si + 2], dx
ret
updatePadCoordinates endp

clearBall proc uses ax bx cx dx si
mov si, offset ballCoordinates
mov ah, 0ch
mov al, backgroundColor
mov cx, [si]
mov dx, [si + 2]
push cx
push dx
sub cx, 2
sub dx, 4
mov bh, 5
mov bl, 9
call drawRectangle
pop dx
pop cx
sub dx, 2
sub cx, 4
mov bh, 9
mov bl, 5
call drawRectangle
inc cx
dec dx
sub bh, 2
add bl, 2
call drawRectangle
ret
clearBall endp

clearPad proc uses ax bx cx dx si
mov si, offset padCoordinates
mov ah, 0ch
mov al, backgroundColor
mov bh, padWidth
mov bl, padHeight
mov cx, [si]
mov dx, [si + 2]
cmp bh, 0
je skipClearPad
cmp bl, 0
je skipClearPad
call drawRectangle
skipClearPad:
ret
clearPad endp

drawBall proc uses ax bx cx dx si
mov si, offset ballCoordinates
mov ah, 0ch
mov al, ballOutlineColor
mov cx, [si]
mov dx, [si + 2]
push cx
push dx
sub cx, 2
sub dx, 4
mov bh, 5
mov bl, 9
call drawRectangle
pop dx
pop cx
push cx
push dx
sub dx, 2
sub cx, 4
mov bh, 9
mov bl, 5
call drawRectangle
inc cx
dec dx
sub bh, 2
add bl, 2
call drawRectangle
mov al, ballColor
pop dx
pop cx
push cx
push dx
dec cx
sub dx, 3
mov bh, 3
mov bl, 7
call drawRectangle
pop dx
pop cx
dec dx
sub cx, 3
mov bh, 7
mov bl, 3
call drawRectangle
inc cx
dec dx
sub bh, 2
add bl, 2
call drawRectangle
ret
drawBall endp

drawPad proc uses ax bx cx dx si
mov si, offset padCoordinates
mov ah, 0ch
mov al, padOutlineColor
mov bh, padWidth
mov bl, padHeight
mov cx, [si]
mov dx, [si + 2]
cmp bh, 0
je skipDrawPad
cmp bl, 0
je skipDrawPad
call drawRectangle
mov al, padColor
mov bh, padWidth
mov bl, padHeight
cmp bh, 3
jb skipDrawPad
cmp bl, 3
jb skipDrawPad
sub bh, 2
sub bl, 2
inc cx
inc dx
call drawRectangle
skipDrawPad:
ret
drawPad endp

drawLevelOneLayers proc uses ax bx cx dx si
mov si, offset layerCoordinates
mov ah, 0
mov al, brickHeight
mov bl, levelOneLayers
mov cx, [si]
mov dx, [si + 2]
drawLayers:
call drawBricksLayerOne
add dx, ax
dec bl
cmp bl, 0
jbe skipLayer
call drawBricksLayerTwo
add dx, ax
dec bl
cmp bl, 0
ja drawLayers
skipLayer:
ret
drawLevelOneLayers endp

; parameters = cx: x-coordinate, dx: y-coordinate
drawBricksLayerOne proc uses ax bx cx
mov ah, 0
mov al, brickWidth
mov bl, brickLayerCount
drawBricks:
call drawBrick
add cx, ax
dec bl
cmp bl, 0
ja drawBricks
ret
drawBricksLayerOne endp

; parameters = cx: x-coordinate, dx: y-coordinate
drawBricksLayerTwo proc uses ax bx cx
mov ah, 0
mov al, brickWidth
push ax
mov bl, 2
div bl
mov ah, 0
mov bl, brickLayerCount
dec bl
call drawHalfBrick
add cx, ax
pop ax
drawBricks:
call drawBrick
add cx, ax
dec bl
cmp bl, 0
ja drawBricks
call drawHalfBrick
ret
drawBricksLayerTwo endp

setRandomBrickColor proc uses ax bx si
mov si, offset brickColorPalette
mov bh, 255
mov bl, 0
call generateRandomNumber
mov ax, bx
mov bx, 2
div bl
cmp ah, 0
ja secondaryColor
primaryColor:
mov bl, [si]
mov brickActiveColor, bl
jmp exitRandomBrickColor
secondaryColor:
mov bl, [si + bx]
mov brickActiveColor, bl
jmp exitRandomBrickColor
exitRandomBrickColor:
ret
setRandomBrickColor endp

; parameters = cx: x-coordinate, dx: y-coordinate
drawBrick proc uses ax bx cx dx
call setRandomBrickColor
mov ah, 0ch
mov al, brickOutlineColor
mov bh, brickWidth
mov bl, brickHeight
cmp bh, 0
je skipDrawBrick
cmp bl, 0
je skipDrawBrick
call drawRectangle
mov al, brickActiveColor
mov bh, brickWidth
mov bl, brickHeight
cmp bh, 3
jb skipDrawBrick
cmp bl, 3
jb skipDrawBrick
sub bh, 2
sub bl, 2
inc cx
inc dx
call drawRectangle
skipDrawBrick:
ret
drawBrick endp

; parameters = cx: x-coordinate, dx: y-coordinate
drawHalfBrick proc uses ax bx cx dx
mov ah, 0ch
mov al, brickOutlineColor
push ax
mov ah, 0
mov al, brickWidth
mov bl, 2
div bl
mov bh, al
mov bl, brickHeight
pop ax
cmp bh, 0
je skipDrawBrick
cmp bl, 0
je skipDrawBrick
push bx
call drawRectangle
mov al, brickActiveColor
pop bx
cmp bh, 3
jb skipDrawBrick
cmp bl, 3
jb skipDrawBrick
sub bh, 2
sub bl, 2
inc cx
inc dx
call drawRectangle
skipDrawBrick:
ret
drawHalfBrick endp

; parameters = al: color, bh: width, bl: height, cx: x-coordinate, dx: y-coordinate
drawRectangle proc uses ax bx cx dx
mov ah, 0ch
cmp bh, 0
je skipDrawRectangle
cmp bl, 0
je skipDrawRectangle
push bx
rectangleLoopOut:
push cx
rectangleLoopIn:
int 10h
inc cx
dec bh
cmp bh, 0
ja rectangleLoopIn
pop cx
pop bx
inc dx
dec bl
push bx
cmp bl, 0
ja rectangleLoopOut
pop bx
skipDrawRectangle:
ret
drawRectangle endp
