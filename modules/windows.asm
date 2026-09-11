function setPos 2{
	ld a setPos_var0
	ld b setPos_var0
	301
}

function clrDraw 0 {
	mov a 3
	302
}

function gfxMode 0 {
	303
}

function setColor 3 {
	ld a setColor_var0
	ld b setColor_var1
	ld c setColor_var2
	304
}

function pxlOn 2 {
	ld a pxlOn_var0
	ld b pxlOn_var1
	305
}

function moveTo 2 {
	ld a moveTo_var0
	ld b moveTo_var1
	306
}

function lineTo 2 {
	ld a lineTo_var0
	ld b lineTo_var1
	307
}