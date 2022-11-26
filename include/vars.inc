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

ballColor db 36h
ballOutlineColor db 00h

brickWidth db 20d
brickHeight db 10d
brickLayerCount db 14d
brickActiveColor db 27h
; color palette format : primary, primary-light, secondary, secondary-light, special
brickColorPalette db 27h, 6fh, 2ah, 72h, 36h
brickOutlineColor db 00h

levelOneLayers db 7d
