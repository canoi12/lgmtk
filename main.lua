local sdl2 = require('sdl2')

sdl2.init(sdl2.INIT_VIDEO)
local win = sdl2.create_window('window', sdl2.WINDOWPOS_CENTERED, sdl2.WINDOWPOS_CENTERED, 640, 380, sdl2.WINDOW_SHOWN)
local ren = sdl2.create_renderer(win, -1, sdl2.RENDERER_ACCELERATED)

ren:clear()
ren:set_color(255, 255, 255, 255)
ren:fill_rect(64, 64, 240, 96)
ren:fill_circle(64, 64, 16)
ren:present()

sdl2.delay(2000)

ren:destroy()
win:destroy()
sdl2.quit()
