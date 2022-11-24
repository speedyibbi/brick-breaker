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
mov ah, 0ch
mov al, backgroundColor
mov bx, windowHeight
mov cx, 0
mov dx, 0
push bx
clearScreenLoopOut:
mov bx, windowWidth
clearScreenLoopIn:
int 10h
inc cx
dec bx
cmp bx, 0
ja clearScreenLoopIn
pop bx
mov cx, 0
inc dx
dec bx
push bx
cmp bx, 0
ja clearScreenLoopOut
pop bx
ret
clearScreen endp

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
width1:
int 10h
inc cx
dec bh
cmp bh, 0
ja width1
mov bh, brickWidth
dec cx
height1:
int 10h
inc dx
dec bl
cmp bl, 0
ja height1
mov bl, brickHeight
dec dx
width2:
int 10h
dec cx
dec bh
cmp bh, 0
ja width2
inc cx
height2:
int 10h
dec dx
dec bl
cmp bl, 0
ja height2
inc dx
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
