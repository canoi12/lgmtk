# Lua Game Making Toolkit

Set of C libs to use in Lua game development.


I extracted these libraries from an other project of mine, the [selene](https://github.com/canoi12/selene) framework.
In selene, these libraries work as global modules, but I think is a better idea to keep it in this separated repository.


Present modules:

- sdl2 (SDL2)
- sdl3 (SDL3) *WIP*
- gl (OpenGL/OpenGLES)
- image (stb_image)
- font (stb_truetype)
- fs
- json


All of them are compiled as shared/dynamic libraries (.so/.dll).
A `lgmtk.so` is compiled too, it contains all the other modules and store it in a table.

```lua
local lgmtk = require('lgmtk')
print(lgmtk.sdl2)
```

You can use the other modules the same way, in the case you're using the `sdl2.so/sdl2.dll`, use it with:

```lua
local sdl2 = require('sdl2')

sdl2.init(sdl2.INIT_VIDEO)
local win = sdl2.create_window('window', sdl2.WINDOWPOS_CENTERED, sdl2.WINDOWPOS_CENTERED, 640, 380, sdl2.WINDOW_SHOWN)
local ren = sdl2.create_renderer(win, -1, sdl2.RENDERER_ACCELERATED)
local ev = sdl2.create_event()

local running = true
while running do
    while ev:poll() do
        local tp = ev:get_type()
        if tp == sdl2.QUIT then
            running = false
        end
    end
    ren:set_draw_color(0, 0, 0, 255)
    ren:clear()
    ren:set_draw_color(255, 255, 255, 255)
    ren:fill_rect(64, 64, 240, 96)
    ren:fill_circle(64, 64, 16)
    ren:present()
    sdl2.delay(16)
end

ren:destroy()
win:destroy()
sdl2.quit()
```
