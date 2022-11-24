setVideoMode proc uses ax
mov ah, 00
mov al, videoMode
int 10h
ret
setVideoMode endp

setBackgroundColor proc uses ax bx cx dx
mov ah, 06h
mov al, 0
mov bh, backgroundColor
mov cx, 0
mov dh, 80
mov dl, 80
int 10h
ret
setBackgroundColor endp

clearScreen proc uses ax bx cx dx
; call setVideoMode
; call setBackgroundColor

; mov ah, 0ch
; mov al, backgroundColor
; mov bx, windowHeight
; mov cx, 0
; mov dx, 0
; push bx
; clearScreenLoopOut:
; mov bx, windowWidth
; clearScreenLoopIn:
; int 10h
; inc cx
; dec bx
; cmp bx, 0
; ja clearScreenLoopIn
; pop bx
; mov cx, 0
; inc dx
; dec bx
; push bx
; cmp bx, 0
; ja clearScreenLoopOut
; pop bx
ret
clearScreen endp

drawLevelOneLayers proc uses ax bx dx
mov ah, 0
mov al, brickHeight
mov bl, levelOneLayers
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

; parameters = cx: x-coordinate, dx: y-coordinate
drawBrick proc uses ax bx cx dx
mov ah, 0ch
mov al, brickOutlineColor
mov bh, brickWidth
mov bl, brickHeight
cmp bh, 0
je skipDrawBrick
cmp bl, 0
je skipDrawBrick
call drawRectangle
mov al, brickColor
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
mov al, brickColor
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

test proc
endp
