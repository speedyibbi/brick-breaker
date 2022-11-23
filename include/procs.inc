setVideoMode proc uses ax
mov ah, 00
mov al, videoMode
int 10h
ret
setVideoMode endp

setBackgroundColor proc uses ax bx cx dx
mov ah, 06h
mov al, 0
mov cx, 0
mov dh, 80
mov dl, 80
mov bh, backgroundColor
int 10h
ret
setBackgroundColor endp

drawRectangle proc
ret
drawRectangle endp
