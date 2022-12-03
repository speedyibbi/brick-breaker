setVideoMode macro
mov ah, 00
mov al, videoMode
int 10h
endm

setBackgroundColor macro
mov ah, 06h
mov al, 0
mov bh, backgroundColor
mov cx, 0
mov dh, 80
mov dl, 80
int 10h
endm

enableHUD macro
mov ah, 0ch
mov al, HUDColor
mov bh, 0
mov bl, HUDSize
mov cx, 0
mov dx, 0
HUDLoopOut:
HUDLoopIn:
int 10h
inc cx
cmp cx, windowWidth
jb HUDLoopIn
mov cx, 0
inc dx
cmp dx, bx
jb HUDLoopOut
mov ax, 0
mov bx, 0
mov cx, 0
mov dx, 0
endm

checkKeys macro
mov ah, 1
int 16h
jz GameLoop
mov ah, 0
int 16h
cmp ah, 1
je exit
endm

setupLevelOne macro
call drawLevelOneLayers
call drawBall
call drawPad
endm
