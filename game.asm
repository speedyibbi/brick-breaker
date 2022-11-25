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
mov cx, 160
mov dx, 150
call drawBall
mov cx, 120
mov dx, 190
call enablePad

jmp exit
main endp

include include\procs.inc

exit:
mov ah, 4ch
int 21h
end
