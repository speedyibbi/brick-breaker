setVideoMode proc uses ax
mov ah, 00
mov al, videoMode
int 10h
ret
setVideoMode endp

setVideoModeRules proc uses ax
mov ah, 00
mov al, videoModeRules
int 10h
ret
setVideoModeRules endp

setBackgroundColor proc uses ax bx cx dx
mov ah, 06h
mov al, 0
mov bh, backgroundColor
mov cx, 0
mov dh, 80
mov dl, 80
int 10h
ret
setBackgroundColor endp

; parameters = bh: upper-limit, bl: lower-limit
; return value in stack
generateRandomNumber proc uses ax bx dx
randomNumber:
mov ah, 00h
int 1ah
cmp dl, bh
ja randomNumber
cmp dl, bl
jb randomNumber
mov dh, 0
pop bx
push dx
push bx
ret
generateRandomNumber endp

clearScreen proc uses ax bx cx dx
; call setVideoMode
; call setBackgroundColor

; mov ah, 0ch
; mov al, backgroundColor
; mov bx, windowHeight
; mov cx, 0
; mov dx, 0
; push bx
; clearScreenLoopOut:
; mov bx, windowWidth
; clearScreenLoopIn:
; int 10h
; inc cx
; dec bx
; cmp bx, 0
; ja clearScreenLoopIn
; pop bx
; mov cx, 0
; inc dx
; dec bx
; push bx
; cmp bx, 0
; ja clearScreenLoopOut
; pop bx
ret
clearScreen endp

; parameters = cx: x-coordinate, dx: y-coordinate
drawPad proc uses ax bx cx dx
mov ah, 0ch
mov al, padOutlineColor
mov bh, padWidth
mov bl, padHeight
cmp bh, 0
je skipDrawPad
cmp bl, 0
je skipDrawPad
call drawRectangle
mov al, padColor
mov bh, padWidth
mov bl, padHeight
cmp bh, 3
jb skipDrawPad
cmp bl, 3
jb skipDrawPad
sub bh, 2
sub bl, 2
inc cx
inc dx
call drawRectangle
skipDrawPad:
ret
drawPad endp

drawLevelOneLayers proc uses ax bx dx
mov ah, 0
mov al, brickHeight
mov bl, levelOneLayers
drawLayers:
call drawBricksLayerOne
add dx, ax
dec bl
cmp bl, 0
jbe skipLayer
call drawBricksLayerTwo
add dx, ax
dec bl
cmp bl, 0
ja drawLayers
skipLayer:
ret
drawLevelOneLayers endp

; parameters = cx: x-coordinate, dx: y-coordinate
drawBricksLayerOne proc uses ax bx cx
mov ah, 0
mov al, brickWidth
mov bl, brickLayerCount
drawBricks:
call drawBrick
add cx, ax
dec bl
cmp bl, 0
ja drawBricks
ret
drawBricksLayerOne endp

; parameters = cx: x-coordinate, dx: y-coordinate
drawBricksLayerTwo proc uses ax bx cx
mov ah, 0
mov al, brickWidth
push ax
mov bl, 2
div bl
mov ah, 0
mov bl, brickLayerCount
dec bl
call drawHalfBrick
add cx, ax
pop ax
drawBricks:
call drawBrick
add cx, ax
dec bl
cmp bl, 0
ja drawBricks
call drawHalfBrick
ret
drawBricksLayerTwo endp

; parameters = cx: x-coordinate, dx: y-coordinate
drawBrick proc uses ax bx cx dx
mov ah, 0ch
mov al, brickOutlineColor
mov bh, brickWidth
mov bl, brickHeight
cmp bh, 0
je skipDrawBrick
cmp bl, 0
je skipDrawBrick
call drawRectangle
mov al, brickColor
mov bh, brickWidth
mov bl, brickHeight
cmp bh, 3
jb skipDrawBrick
cmp bl, 3
jb skipDrawBrick
sub bh, 2
sub bl, 2
inc cx
inc dx
call drawRectangle
skipDrawBrick:
ret
drawBrick endp

; parameters = cx: x-coordinate, dx: y-coordinate
drawHalfBrick proc uses ax bx cx dx
mov ah, 0ch
mov al, brickOutlineColor
push ax
mov ah, 0
mov al, brickWidth
mov bl, 2
div bl
mov bh, al
mov bl, brickHeight
pop ax
cmp bh, 0
je skipDrawBrick
cmp bl, 0
je skipDrawBrick
push bx
call drawRectangle
mov al, brickColor
pop bx
cmp bh, 3
jb skipDrawBrick
cmp bl, 3
jb skipDrawBrick
sub bh, 2
sub bl, 2
inc cx
inc dx
call drawRectangle
skipDrawBrick:
ret
drawHalfBrick endp

; parameters = al: color, bh: width, bl: height, cx: x-coordinate, dx: y-coordinate
drawRectangle proc uses ax bx cx dx
mov ah, 0ch
cmp bh, 0
je skipDrawRectangle
cmp bl, 0
je skipDrawRectangle
push bx
rectangleLoopOut:
push cx
rectangleLoopIn:
int 10h
inc cx
dec bh
cmp bh, 0
ja rectangleLoopIn
pop cx
pop bx
inc dx
dec bl
push bx
cmp bl, 0
ja rectangleLoopOut
pop bx
skipDrawRectangle:
ret
drawRectangle endp

;Next Line
NextLine proc uses ax dx
mov dl,10		;Next line
mov ah,02h
int 21h
ret 
NextLine endp

DisplayMenu proc uses ax
mov ah,09h
Int 21h
ret 
DisplayMenu endp

MenuAnimation proc uses ax bx cx dx si


mov cx,MenuTemp3
mov dx,00

more:
fin:
mov bl,20
mov bh,8


dow2:
dow1:
mov ah,0Ch
mov al,27h
int 10h
inc cx
dec bl
JNZ dow1

inc dx
dec bh
mov cx,MenuTemp3
mov bl,20
JNZ dow2

inc dx
inc dx

dec MenuTemp1
JNZ fin

mov ax,MenuTemp3
add ax,22
mov MenuTemp3,ax

mov dx,0
dec MenuTemp2
mov MenuTemp1,20
JNZ more

;Restoring Values
mov ax,0
mov al,MenuAnimationVal1
mov MenuTemp1,al
mov al,MenuAnimationVal2
mov MenuTemp2,al
mov ax,MenuAnimation_X_Axis
mov MenuTemp3,ax

ret
MenuAnimation endp



; Menu
menu proc uses ax bx cx dx si

mov si, 0
mov dh,6    ;X-Cordinates
mov dl,13    ;Y-Cordinates
mov cx, counter

DrawName:
mov ax,word ptr BrickName[si]
push ax
mov ah, 02h     ; Cusor Positioning
mov bx, 0
int 10h
pop ax
mov ah,09
mov bh, 0
mov bl,BrickNameColor
int 10h
inc si
inc dl

loop DrawName

call NextLine
call NextLine
call NextLine

;Output a display1
mov dx,offset display1
call DisplayMenu

call NextLine
call NextLine

;Output a display2
mov dx,offset display2
call DisplayMenu

call NextLine
call NextLine

;Output a display3
mov dx,offset display3
call DisplayMenu

call NextLine
call NextLine

call MenuAnimation
mov MenuTemp3,276 
call MenuAnimation

ret
menu endp

TName proc uses ax bx cx dx si


mov si, 0
mov dh,18    ;X-Cordinates
mov dl,7    ;Y-Cordinates
mov cx, MenuTakeNameLen

DrawNameTaker:
mov ax,word ptr MenuTakeName[si]
push ax
mov ah, 02h     ; Cusor Positioning
mov bx, 0
int 10h
pop ax
mov ah,09
mov bh, 0
mov bl,brickSpecialColor
int 10h
inc si
inc dl
loop DrawNameTaker

mov si,0
namer:
Mov ah, 01h         ;Taking Name of the User
Int 21h
mov namee[si],al	
inc si	
inc dl
cmp al,13
JNE namer
mov MenuChoice,0

namerexit:
ret
TName endp

instruction proc uses ax bx cx dx si
call setVideoModeRules
mov dx,offset rules
call NextLine
call DisplayMenu
mov cx,4
liner1:
call NextLine
loop liner1

mov dx,offset rule1
call DisplayMenu
call NextLine
call NextLine
mov dx,offset rule2
call DisplayMenu
call NextLine
call NextLine
mov dx,offset rule3
call DisplayMenu
mov cx,6

liner2:
call NextLine
loop liner2

mov dx,offset rule4
call DisplayMenu

mov cx,8
liner3:
call NextLine
loop liner3
mov dx,offset rule5
call DisplayMenu
enterToExitMenu:
    mov MenuChoice,1
    mov ah,1
    int 16h
    jnz enterToExitMenu
    mov ah,0
    int 16h
    cmp al,13


ret
instruction endp

ShowLeaderBoards proc uses ax bx cx dx si

;call setVideoModeRules
call setBackgroundColor ;Set Background Again
mov si, 0
mov dh,3    ;X-Cordinates
mov dl,13    ;Y-Cordinates
mov cx, LeaderBoardNameLen

DrawLeaderboard:
mov ax,word ptr LeaderBoardName[si]
push ax
mov ah, 02h     ; Cusor Positioning
mov bx, 0
int 10h
pop ax
mov ah,09
mov bh, 0
mov bl,BrickNameColor
int 10h
inc si
inc dl

loop DrawLeaderboard

enterToExitMenu:
    mov MenuChoice,1
    mov ah,1
    int 16h
    jnz enterToExitMenu
    mov ah,0
    int 16h
    cmp al,13


ret
ShowLeaderBoards endp

; Option choosed after selecting in menu
choice proc uses ax bx cx dx
again:
    mov ah,1
    int 16h
    jnz again
    mov ah,0
    int 16h
    cmp al,'1'
    JZ callname
    cmp al,'2'
    JZ callinstruction
    cmp al,'3'
    JZ callleaderboard
    jmp again

callname:    
call TName
jmp exitchoice

callinstruction:
call instruction
jmp exitchoice

callleaderboard:
call ShowLeaderBoards
jmp exitchoice

exitchoice:

ret 
choice endp


NewScreen proc uses ax bx cx dx si

mov ah, 06h
mov al, 0
mov bh, 0
mov cx, 0
mov dh, 80
mov dl, 80
int 10h

ret 
NewScreen endp

WinScreen proc uses ax bx cx dx si
mov si, 0
mov dh,12    ;X-Cordinates
mov dl,8    ;Y-Cordinates
mov cx, WinScreenNameLen

DrawWinScreen1:
mov ax,word ptr WinScreenName[si]
push ax
mov ah, 02h     ; Cusor Positioning
mov bx, 0
int 10h
pop ax
mov ah,09
mov bh, 0
mov bl,BrickNameColor
int 10h
inc si
inc dl

loop DrawWinScreen1
    mov ah,1
    int 16h
ret 
WinScreen endp