startGameLoop macro
GameLoop:
mov ah, 00
cmp ah, 0
int 16h
jnz GameLoop
cmp ah, 1
je exit
endm
