videoMode db 13h
videoModeRules db 12h
windowWidth dw 320d
windowHeight dw 200d

backgroundColor db 12h
pixelColor db 36h

HUDSize db 25d
HUDColor db 22h
HUDFrameColor db 26h

padWidth db 80d
padHeight db 5d
padSpeed db 5d
padColor db 1fh
padOutlineColor db 00h
padCoordinates dw 120d, 190d

ballRadius db 5d
ballSpeed db 2d
ballColor db 36h
ballOutlineColor db 00h
ballCoordinates dw 160d, 150d
ballDirection db 11d
; ball direction format : 00d, 01d, 02d, 10dd, 11d, 12d, 20d, 21d, 22d
; first-digit: 0 = no-direction, 1 = up, 2 = down
; second-digit: 0 = no-direction, 1 = right, 2 = left

brickWidth db 20d
brickHeight db 10d
brickSpecialColor db 36h
brickLayerCount = 10
brickActiveColor db 27h
brickColorPalette db 27h, 6fh, 2ah, 72h, 36h
; brick color palette format : primary, primary-light, secondary, secondary-light, special
brickOutlineColor db 00h

levelLayers = 3
layerCoordinates dw 60d, 55d
brickCoordinates dw ((brickLayerCount * levelLayers * 2) + ((levelLayers / 2) * 2)) dup(0)
brickCoordinatesIndex dw 0
halfBricks dw ((levelLayers / 2) * 2) dup(0)
halfBricksIndex db 0

; Menu Var
outer db 10
BrickName db 66,114,105,99,107,32,66,114,101,97,107,101,114
counter dw 13
BrickNameColor db 20h           ;Dark Blue color
opt db ?
MenuTakeName db 69,110,116,101,114,32,121,111,117,114,32,110,97,109,101,58,32
MenuTakeNameLen dw 17

; Menu Display
display1 db "           1. Play Game",'$'
display2 db "           2. Rules",'$'
display3 db "           3. LeaderBoards",'$'
takename db "       Enter Your Name: ",'$'
namee db 10 dup (?),'$'

;Rules Display Variables
rules db "                              Rules$"
rule1 db "1.  There are a Total of 3 Levels$"
rule2 db "2.  Break all the bricks to clear the Level.$"
rule3 db "3.  If the ball falls down the Pad you Lose.$"
rule4 db "                              Best of Luck!!!$"
rule5 db "                      Press Any Key to go back to the Menu.$"
MenuChoice db 1     ;Choice whether to play game or go back to Menu

;Menu Animation loopers
MenuAnimationVal1 db 20
MenuAnimationVal2 db 2
MenuAnimation_X_Axis dw 3
MenuTemp1 db 20
MenuTemp2 db 2
MenuTemp3 dw 3

; LeaderBoards Variables
LeaderBoardName db 76,101,97,100,101,114,32,66,111,97,114,100
LeaderBoardNameLen dw 12

;Win Screen Variables
WinScreenName db 67,111,110,103,114,97,116,117,108,97,116,105,111,110,32,89,111,117,32,87,111,110
WinScreenNameLen dw 22
