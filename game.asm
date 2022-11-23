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



jmp exit
main endp

include include\procs.inc

exit:
mov ah, 4ch
int 21h

end