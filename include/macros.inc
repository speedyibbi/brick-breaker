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
