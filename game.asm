.model small
.stack 100h
.data

include include\vars.inc

.code

include include\macros.inc

mov ax, @data
mov ds, ax

main proc
call setVideoMode
call setBackgroundColor

mov cx, 20
mov dx, 30
call drawLevelOneLayers

; mov cx, 270
; mov dx, 150
; call drawBrick

; CheckKeys:
; mov ah, 00
; int 16h
; jnz CheckKeys
; cmp ah, 72
; je drawUp
; cmp ah, 77
; je drawRight
; cmp ah, 80
; je drawDown
; cmp ah, 75
; je drawLeft
; cmp ah, 1
; je exit
; drawUp:
; call clearScreen
; dec dx
; call drawBrick
; ; mov al, backgroundColor
; ; mov bh, brickWidth
; ; mov bl, 1
; ; push dx
; ; add dl, brickHeight
; ; call drawRectangle
; ; pop dx
; jmp CheckKeys
; drawRight:
; call clearScreen
; inc cx
; call drawBrick
; jmp CheckKeys
; drawDown:
; call clearScreen
; inc dx
; call drawBrick
; jmp CheckKeys
; drawLeft:
; call clearScreen
; dec cx
; call drawBrick
; jmp CheckKeys

jmp exit
main endp

include include\procs.inc

exit:
mov ah, 4ch
int 21h

end