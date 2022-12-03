.model small
.stack 100h
.data

include include\vars.inc

.code

include include\macros.inc

mov ax, @data
mov ds, ax

main proc

; call setBackgroundColor
againMenu:
call setVideoMode
call menu
call choice         ;Choosing 1 of the 3 Options given in Menu
cmp MenuChoice,1
JZ againMenu

call NewScreen ;Set Background Again
call WinScreen

; mov cx, 20
; mov dx, 30
; call drawLevelOneLayers
; mov cx, 120
; mov dx, 190
; call drawPad

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
; dec dx
; call drawPad
; jmp CheckKeys
; drawRight:
; inc cx
; call drawPad
; jmp CheckKeys
; drawDown:
; inc dx
; call drawPad
; jmp CheckKeys
; drawLeft:
; dec cx
; call drawPad
; jmp CheckKeys

jmp exit
main endp

include include\procs.inc

exit:
mov ah, 4ch
int 21h

end