import windows
import strings

cls
gfxMode()
clrDraw()

setPos(4, 3)
mov a myString
call putstr
endl

setColor(255, 0, 0)
moveTo(20, 40)
lineTo(20, 70)
moveTo(140, 40)
lineTo(140, 70)
moveTo(20, 40)
lineTo(140, 40)
moveTo(20, 70)
lineTo(140, 70)

setColor(0, 255, 0)
moveTo(50, 250)
lineTo(100, 100)
moveTo(50, 100)
lineTo(100, 250)

getkey
ret

myString:
"Hello World!"