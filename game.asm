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
