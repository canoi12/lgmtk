# Lua Game Making Toolkit

Set of C libs to use in game development in Lua.


I extracted these libs from the global modules from an other project, [selene](https://github.com/canoi12/selene).
I'll keep it in this separated repository.

```lua
local sdl2 = require('sdl2')
if not sdl2.init(sdl2.INIT_VIDEO) then
    error('Failed to init SDL2:', sdl2.get_error())
end
local win = sdl2.create_window('My Game', sdl2.WINDOWPOS_CENTERED, sdl2.WINDOWPOS_CENTERED, 640, 380, sdl2.WINDOW_SHOWN)
local ren = sdl2.create_renderer(win, -1, sdl2.RENDERER_ACCELERATED)

local running = true
while running do
end
```
