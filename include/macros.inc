startGameLoop macro
GameLoop:
mov ah, 00
int 16h
jnz GameLoop
endm
