.model small
.stack 100h
.data

include include\vars.inc

.code

include include\macros.inc

mov ax, @data
mov ds, ax

main proc

setVideoMode
setBackgroundColor

setupLevelOne

mov si, offset brickCoordinates
mov bx, 0
looop:
push bx
call checkHalfBrick
.IF bx == 1
    pop bx
    push bx
    mov ax, bx
    mov bh, 0
    mov bl, 4
    mul bl
    mov bx, ax
    mov cx, [si + bx]
    add bx, 2
    mov dx, [si + bx]
    mov ax, 0
    mov al, brickWidth
    mov bh, 0
    mov bl, 2
    div bl
    mov bh, al
    mov bl, brickHeight
    mov al, 2fh
    call drawRectangle
.ELSE
    pop bx
    push bx
    mov ax, bx
    mov bh, 0
    mov bl, 4
    mul bl
    mov bx, ax
    mov cx, [si + bx]
    add bx, 2
    mov dx, [si + bx]
    mov bh, brickWidth
    mov bl, brickHeight
    mov al, 36h
    call drawRectangle
.ENDIF
pop bx
inc bx
cmp bx, ((brickLayerCount * levelLayers) + (levelLayers / 2))
jb looop

mov bh, 0
mov bl, ballSpeed
mov cx, 0
GameLoop:
cmp cx, 0
jne skipBall
call enableBall
skipBall:
add cx, bx
cmp cx, 5000
jb keys
mov cx, 0
keys:
checkKeys
call enablePad
jmp GameLoop

jmp exit
main endp

include include\procs.inc

exit:
mov ah, 4ch
int 21h
end
