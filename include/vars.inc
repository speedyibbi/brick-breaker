videoMode db 13h
windowWidth dw 320d
windowHeight dw 200d

backgroundColor db 12h
pixelColor db 36h

padWidth db 80d
padHeight db 5d
padSpeed db 5d
padColor db 22h
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
brickLayerCount = 10
brickActiveColor db 27h
brickColorPalette db 27h, 6fh, 2ah, 72h, 36h
; brick color palette format : primary, primary-light, secondary, secondary-light, special
brickOutlineColor db 00h

levelLayers = 2
layerCoordinates dw 60d, 30d
brickCoordinates dw ((brickLayerCount * levelLayers * 2) + ((levelLayers / 2) * 2)) dup(0)
brickCoordinatesIndex dw 0
halfBricks dw ((levelLayers / 2) * 2) dup(0)
halfBricksIndex db 0
