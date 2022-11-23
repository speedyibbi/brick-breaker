.model small
.stack 100h
.data

include include\vars.inc

.code
mov ax, @data
mov ds, ax

main proc
call setVideoMode
call setBackgroundColor

mov cx, 270
mov dx, 150
call drawBrick

jmp exit
main endp

include include\procs.inc

exit:
mov ah, 4ch
int 21h

end