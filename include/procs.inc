setVideoModeRules proc uses ax
mov ah, 00
mov al, videoModeRules
int 10h
ret
setVideoModeRules endp

; parameters = bh: upper-limit, bl: lower-limit
; return value in bx
generateRandomNumber proc uses ax cx dx
randomNumber:
mov ah, 00h
int 1ah
cmp dl, bh
ja randomNumber
cmp dl, bl
jb randomNumber
mov dh, 0
mov bx, dx
ret
generateRandomNumber endp

; return value in bx
getBallWindowWidthLimit proc uses ax
mov ax, windowWidth
mov bh, 0
mov bl, ballRadius
sub ax, bx
mov bx, ax
ret
getBallWindowWidthLimit endp

; return value in bx
getBallWindowHeightLimit proc uses ax
mov ax, windowHeight
mov bh, 0
mov bl, ballRadius
sub ax, bx
mov bx, ax
ret
getBallWindowHeightLimit endp

; return value in bx
checkBallScreenBoundaries proc uses ax cx dx
mov ah, 0
cmp al, 11
jne nextCheck1
mov bh, 0
mov bl, ballRadius
add bl, HUDSize
cmp dx, bx
ja skipCheck1
add al, 10
skipCheck1:
call getBallWindowWidthLimit
cmp cx, bx
jb exitBallCheck
inc al
jmp exitBallCheck
nextCheck1:
cmp al, 12
jne nextCheck2
mov bh, 0
mov bl, ballRadius
add bl, HUDSize
cmp dx, bx
ja skipCheck2
add al, 10
skipCheck2:
sub bl, HUDSize
cmp cx, bx
ja exitBallCheck
dec al
jmp exitBallCheck
nextCheck2:
cmp al, 21
jne nextCheck3
call getBallWindowHeightLimit
cmp dx, bx
jb skipCheck3
sub al, 10
skipCheck3:
call getBallWindowWidthLimit
cmp cx, bx
jb exitBallCheck
inc al
jmp exitBallCheck
nextCheck3:
cmp al, 22
jne exitBallCheck
call getBallWindowHeightLimit
cmp dx, bx
jb skipCheck4
sub al, 10
skipCheck4:
mov bh, 0
mov bl, ballRadius
cmp cx, bx
ja exitBallCheck
dec al
jmp exitBallCheck
exitBallCheck:
mov bx, ax
ret
checkBallScreenBoundaries endp

; return value in bx
checkBallPadCollisions proc uses ax cx dx si
mov si, offset padCoordinates
push ax
mov ah, 0
cmp al, 21
jne nextCheck
mov bx, [si]
.IF cx >= bx
    mov ah, 0
    mov al, padWidth
    add bx, ax
    .IF cx <= bx
        mov ah, 0
        mov al, ballRadius
        mov bx, [si + 2]
        sub bx, ax
        .IF dx >= bx
            pop ax
            mov ah, 0
            mov al, 11
            jmp exitBallCheckFinal
        .ENDIF
    .ENDIF
.ENDIF
jmp exitBallCheck
nextCheck:
cmp al, 22
jne exitBallCheck
mov bx, [si]
.IF cx >= bx
    mov ah, 0
    mov al, padWidth
    add bx, ax
    .IF cx <= bx
        mov ah, 0
        mov al, ballRadius
        mov bx, [si + 2]
        sub bx, ax
        .IF dx >= bx
            pop ax
            mov ah, 0
            mov al, 12
            jmp exitBallCheckFinal
        .ENDIF
    .ENDIF
.ENDIF
jmp exitBallCheck
exitBallCheck:
pop ax
exitBallCheckFinal:
mov bx, ax
ret
checkBallPadCollisions endp

; return value in bx
checkBallBrickEdges proc uses ax cx dx si di
push bx
call checkHalfBrick
.IF bx == 1
    pop bx
    push bx
    mov di, 1
.ELSE
    pop bx
    push bx
    mov di, 0
.ENDIF
mov si, offset brickCoordinates
mov ax, 0
mov al, bl
mov bl, 4
mul bl
mov bx, ax
mov ax, [si + bx]
.IF cx >= ax
    .IF di == 1
        mov di, ax
        mov ax, 0
        mov al, brickWidth
        mov bx, 0
        mov bl, 2
        div bl
        mov bh, 0
        mov bl, al
        mov ax, di
        add ax, bx
    .ELSE
        mov bx, 0
        mov bl, brickWidth
        add ax, bx
    .ENDIF
    .IF cx <= ax
        pop bx
        push bx
        mov ax, 0
        mov al, bl
        mov bl, 4
        mul bl
        mov bx, ax
        add bx, 2
        mov ax, [si + bx]
        .IF dx >= ax
            mov bx, 0
            mov bl, brickHeight
            add ax, bx
            .IF dx <= ax
                pop bx
                mov bx, 1
                jmp exitCheckBallBrickEdges
            .ENDIF
        .ENDIF
    .ENDIF
.ENDIF
pop bx
mov bx, 0
exitCheckBallBrickEdges:
ret
checkBallBrickEdges endp

; return value in bx
checkHalfBrick proc uses ax si
mov si, offset halfBricks
mov ax, bx
mov bx, 0
halfBrickLoop:
cmp ax, [si + bx]
je exitHalfBrickCheckTrue
add bx, 2
cmp bx, (((levelLayers / 2) * 2) * 2)
jb halfBrickLoop
exitHalfBrickCheckFalse:
mov bx, 0
jmp exitHalfBrickCheck
exitHalfBrickCheckTrue:
mov bx, 1
jmp exitHalfBrickCheck
exitHalfBrickCheck:
ret
checkHalfBrick endp

; return value in bx
checkBallBrickCollisions proc uses ax cx dx si
mov si, offset brickCoordinates
mov ah, 0
push ax
mov bx, 0
push bx
BrickCollisionLoop:
cmp al, 11
je UpRightCollisions
cmp al, 12
je UpLeftCollisions
cmp al, 21
je DownRightCollisions
cmp al, 22
je DownLeftCollisions
jmp next
UpRightCollisions:
mov bx, 0
mov bl, ballRadius
dec bx
add cx, bx
sub dx, bx
pop bx
push bx
call checkBallBrickEdges
.IF bx == 1
    pop bx
    push bx
    mov ax, bx
    mov bl, 4
    mul bl
    mov bx, ax
    mov ax, [si + bx]
    .IF cx == ax
        pop bx
        pop ax
        inc ax
        push ax
        push bx
    .ENDIF
    pop bx
    push bx
    mov ax, bx
    mov bl, 4
    mul bl
    mov bx, ax
    add bx, 2
    mov ax, [si + bx]
    mov bx, 0
    mov bl, brickHeight
    add ax, bx
    .IF dx == ax
        pop bx
        pop ax
        add ax, 10
        push ax
        push bx
    .ENDIF
    mov bx, 0
    mov bl, ballRadius
    dec bx
    sub cx, bx
    add dx, bx
    pop bx
    jmp exitBallBrickCollosionCheck
.ENDIF
mov bx, 0
mov bl, ballRadius
dec bx
sub cx, bx
add dx, bx
pop bx
pop ax
push ax
push bx
jmp next
UpLeftCollisions:
mov bx, 0
mov bl, ballRadius
dec bx
sub cx, bx
sub dx, bx
pop bx
push bx
call checkBallBrickEdges
.IF bx == 1
    pop bx
    push bx
    mov ax, bx
    mov bl, 4
    mul bl
    mov bx, ax
    mov ax, [si + bx]
    mov bx, 0
    mov bl, brickWidth
    add ax, bx
    .IF cx == ax
        pop bx
        pop ax
        dec ax
        push ax
        push bx
    .ENDIF
    pop bx
    push bx
    mov ax, bx
    mov bl, 4
    mul bl
    mov bx, ax
    add bx, 2
    mov ax, [si + bx]
    mov bx, 0
    mov bl, brickHeight
    add ax, bx
    .IF dx == ax
        pop bx
        pop ax
        add ax, 10
        push ax
        push bx
    .ENDIF
    mov bx, 0
    mov bl, ballRadius
    dec bx
    add cx, bx
    add dx, bx
    pop bx
    jmp exitBallBrickCollosionCheck
.ENDIF
mov bx, 0
mov bl, ballRadius
dec bx
add cx, bx
add dx, bx
pop bx
pop ax
push ax
push bx
jmp next
DownRightCollisions:
mov bx, 0
mov bl, ballRadius
add cx, bx
add dx, bx
pop bx
push bx
call checkBallBrickEdges
.IF bx == 1
    pop bx
    push bx
    mov ax, bx
    mov bl, 4
    mul bl
    mov bx, ax
    mov ax, [si + bx]
    .IF cx == ax
        pop bx
        pop ax
        inc ax
        push ax
        push bx
    .ENDIF
    pop bx
    push bx
    mov ax, bx
    mov bl, 4
    mul bl
    mov bx, ax
    add bx, 2
    mov ax, [si + bx]
    .IF dx == ax
        pop bx
        pop ax
        sub ax, 10
        push ax
        push bx
    .ENDIF
    mov bx, 0
    mov bl, ballRadius
    sub cx, bx
    sub dx, bx
    pop bx
    jmp exitBallBrickCollosionCheck
.ENDIF
mov bx, 0
mov bl, ballRadius
sub cx, bx
sub dx, bx
pop bx
pop ax
push ax
push bx
jmp next
DownLeftCollisions:
mov bx, 0
mov bl, ballRadius
sub cx, bx
add dx, bx
pop bx
push bx
call checkBallBrickEdges
.IF bx == 1
    pop bx
    push bx
    mov ax, bx
    mov bl, 4
    mul bl
    mov bx, ax
    mov ax, [si + bx]
    mov bx, 0
    mov bl, brickWidth
    add ax, bx
    .IF cx == ax
        pop bx
        pop ax
        dec ax
        push ax
        push bx
    .ENDIF
    pop bx
    push bx
    mov ax, bx
    mov bl, 4
    mul bl
    mov bx, ax
    add bx, 2
    mov ax, [si + bx]
    .IF dx == ax
        pop bx
        pop ax
        sub ax, 10
        push ax
        push bx
    .ENDIF
    mov bx, 0
    mov bl, ballRadius
    add cx, bx
    sub dx, bx
    pop bx
    jmp exitBallBrickCollosionCheck
.ENDIF
mov bx, 0
mov bl, ballRadius
add cx, bx
sub dx, bx
pop bx
pop ax
push ax
push bx
jmp next
next:
pop bx
inc bx
push bx
cmp bx, ((brickLayerCount * levelLayers) + (levelLayers / 2))
jb BrickCollisionLoop
pop bx
exitBallBrickCollosionCheck:
pop ax
mov bx, ax
ret
checkBallBrickCollisions endp

enableBall proc uses ax bx cx dx si
mov si, offset ballCoordinates
mov cx, [si]
mov dx, [si + 2]
mov ah, 0
mov al, ballDirection
mov bx, 0
cmp al, 11
je moveBallUpRight
cmp al, 12
je moveBallUpLeft
cmp al, 21
je moveBallDownRight
cmp al, 22
je moveBallDownLeft
jmp exitBall
moveBallUpRight:
call checkBallScreenBoundaries
cmp al, bl
jne changeDirection
call checkBallBrickCollisions
cmp al, bl
jne changeDirection
call clearBall
inc cx
dec dx
call updateBallCoordinates
call drawBall
jmp exitBall
moveBallUpLeft:
call checkBallScreenBoundaries
cmp al, bl
jne changeDirection
call checkBallBrickCollisions
cmp al, bl
jne changeDirection
call clearBall
dec cx
dec dx
call updateBallCoordinates
call drawBall
jmp exitBall
moveBallDownRight:
call checkBallScreenBoundaries
cmp al, bl
jne changeDirection
call checkBallPadCollisions
cmp al, bl
jne changeDirection
call checkBallBrickCollisions
cmp al, bl
jne changeDirection
call clearBall
inc cx
inc dx
call updateBallCoordinates
call drawBall
jmp exitBall
moveBallDownLeft:
call checkBallScreenBoundaries
cmp al, bl
jne changeDirection
call checkBallPadCollisions
cmp al, bl
jne changeDirection
call checkBallBrickCollisions
cmp al, bl
jne changeDirection
call clearBall
dec cx
inc dx
call updateBallCoordinates
call drawBall
jmp exitBall
changeDirection:
mov ballDirection, bl
jmp exitBall
exitBall:
ret
enableBall endp

enablePad proc uses ax bx cx dx si
mov si, offset padCoordinates
mov cx, [si]
mov dx, [si + 2]
push ax
mov ax, windowWidth
mov bh, 0
mov bl, padWidth
sub ax, bx
mov bx, ax
pop ax
cmp ah, 77
je drawRight
cmp ah, 75
je drawLeft
jmp exitPad
drawRight:
call clearPad
mov ah, 0
mov al, padSpeed
add cx, ax
cmp cx, bx
ja setToMax
call updatePadCoordinates
call drawPad
jmp exitPad
drawLeft:
call clearPad
mov ah, 0
mov al, padSpeed
sub cx, ax
cmp cx, bx
ja setToMin
call updatePadCoordinates
call drawPad
jmp exitPad
setToMax:
mov cx, bx
call updatePadCoordinates
call drawPad
jmp exitPad
setToMin:
mov cx, 0
call updatePadCoordinates
call drawPad
jmp exitPad
exitPad:
ret
enablePad endp

; parameters = cx: x-coordinate, dx: y-coordinate
updateBallCoordinates proc uses cx dx si
mov si, offset ballCoordinates
mov [si], cx
mov [si + 2], dx
ret
updateBallCoordinates endp

; parameters = cx: x-coordinate, dx: y-coordinate
updatePadCoordinates proc uses cx dx si
mov si, offset padCoordinates
mov [si], cx
mov [si + 2], dx
ret
updatePadCoordinates endp

clearBall proc uses ax bx cx dx si
mov si, offset ballCoordinates
mov ah, 0ch
mov al, backgroundColor
mov cx, [si]
mov dx, [si + 2]
push cx
push dx
sub cx, 2
sub dx, 4
mov bh, 5
mov bl, 9
call drawRectangle
pop dx
pop cx
sub dx, 2
sub cx, 4
mov bh, 9
mov bl, 5
call drawRectangle
inc cx
dec dx
sub bh, 2
add bl, 2
call drawRectangle
ret
clearBall endp

clearPad proc uses ax bx cx dx si
mov si, offset padCoordinates
mov ah, 0ch
mov al, backgroundColor
mov bh, padWidth
mov bl, padHeight
mov cx, [si]
mov dx, [si + 2]
cmp bh, 0
je skipClearPad
cmp bl, 0
je skipClearPad
call drawRectangle
skipClearPad:
ret
clearPad endp

drawBall proc uses ax bx cx dx si
mov si, offset ballCoordinates
mov ah, 0ch
mov al, ballOutlineColor
mov cx, [si]
mov dx, [si + 2]
push cx
push dx
sub cx, 2
sub dx, 4
mov bh, 5
mov bl, 9
call drawRectangle
pop dx
pop cx
push cx
push dx
sub dx, 2
sub cx, 4
mov bh, 9
mov bl, 5
call drawRectangle
inc cx
dec dx
sub bh, 2
add bl, 2
call drawRectangle
mov al, ballColor
pop dx
pop cx
push cx
push dx
dec cx
sub dx, 3
mov bh, 3
mov bl, 7
call drawRectangle
pop dx
pop cx
dec dx
sub cx, 3
mov bh, 7
mov bl, 3
call drawRectangle
inc cx
dec dx
sub bh, 2
add bl, 2
call drawRectangle
ret
drawBall endp

drawPad proc uses ax bx cx dx si
mov si, offset padCoordinates
mov ah, 0ch
mov al, padOutlineColor
mov bh, padWidth
mov bl, padHeight
mov cx, [si]
mov dx, [si + 2]
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

drawLevelOneLayers proc uses ax bx cx dx si di
mov si, offset layerCoordinates
mov di, 0
mov bx, 0
mov brickCoordinatesIndex, bx
mov halfBricksIndex, bl
mov ah, 0
mov al, brickHeight
mov bl, levelLayers
mov cx, [si]
mov dx, [si + 2]
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
mov bx, 0
mov brickCoordinatesIndex, bx
mov halfBricksIndex, bl
mov di, 0
ret
drawLevelOneLayers endp

; parameters = bx: index, cx: x-coordinate, dx: y-coordinate
insertBrickCoordinates proc uses bx cx dx si
mov si, offset brickCoordinates
mov bx, brickCoordinatesIndex
mov [si + bx], cx
add bx, 2
mov [si + bx], dx
add bx, 2
mov brickCoordinatesIndex, bx
ret
insertBrickCoordinates endp

; parameters = bx: index, cx: x-coordinate, dx: y-coordinate
insertHalfBrick proc uses bx si
mov si, offset halfBricks
mov bh, 0
mov bl, halfBricksIndex
mov [si + bx], di
add bx, 2
mov halfBricksIndex, bl
ret
insertHalfBrick endp

; parameters = cx: x-coordinate, dx: y-coordinate
drawBricksLayerOne proc uses ax bx cx dx
mov ah, 0
mov al, brickWidth
mov bx, (brickLayerCount * 4)
drawBricks:
call drawBrick
call insertBrickCoordinates
inc di
add cx, ax
sub bx, 4
cmp bx, 0
ja drawBricks
ret
drawBricksLayerOne endp

; parameters = cx: x-coordinate, dx: y-coordinate
drawBricksLayerTwo proc uses ax bx cx dx
mov ah, 0
mov al, brickWidth
push ax
mov bl, 2
div bl
mov ah, 0
mov bx, (brickLayerCount * 4)
call drawHalfBrick
call insertHalfBrick
call insertBrickCoordinates
inc di
sub bx, 4
add cx, ax
pop ax
drawBricks:
call drawBrick
call insertBrickCoordinates
inc di
add cx, ax
sub bx, 4
cmp bx, 0
ja drawBricks
call drawHalfBrick
call insertHalfBrick
call insertBrickCoordinates
inc di
ret
drawBricksLayerTwo endp

setRandomBrickColor proc uses ax bx si
mov si, offset brickColorPalette
mov bh, 255
mov bl, 0
call generateRandomNumber
mov ax, bx
mov bx, 2
div bl
cmp ah, 0
ja secondaryColor
primaryColor:
mov bl, [si]
mov brickActiveColor, bl
jmp exitRandomBrickColor
secondaryColor:
mov bl, [si + bx]
mov brickActiveColor, bl
jmp exitRandomBrickColor
exitRandomBrickColor:
ret
setRandomBrickColor endp

; parameters = cx: x-coordinate, dx: y-coordinate
drawBrick proc uses ax bx cx dx
call setRandomBrickColor
mov ah, 0ch
mov al, brickOutlineColor
mov bh, brickWidth
mov bl, brickHeight
cmp bh, 0
je skipDrawBrick
cmp bl, 0
je skipDrawBrick
call drawRectangle
mov al, brickActiveColor
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
mov al, brickActiveColor
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
setBackgroundColor ;Set Background Again
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