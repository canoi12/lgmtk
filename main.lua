-- local lgmtk = require('lgmtk')
local ig, err = require('imgui')
print(ig)
local sdl2 = require('sdl2')

if not ig then error(err) end
print(ig)

ig.CreateContext()


sdl2.init(sdl2.INIT_VIDEO)
local win = sdl2.create_window('window', sdl2.WINDOWPOS_CENTERED, sdl2.WINDOWPOS_CENTERED, 640, 380, sdl2.WINDOW_SHOWN)
local ren = sdl2.create_renderer(win, -1, sdl2.RENDERER_ACCELERATED)
local ev = sdl2.create_event()

print(win:get_handle(), ren:get_handle())
ig.ImplSDL2_InitForSDLRenderer(win:get_handle(), ren:get_handle())
ig.ImplSDLRenderer2_Init(ren:get_handle())

local x = 64
local y = 64
local running = true
while running do
    while ev:poll() do
        local tp = ev:get_type()
        if tp == sdl2.QUIT then
            running = false
        elseif tp == sdl2.MOUSEMOTION then
            local btn, mx, my = ev:mouse_motion()
            x = mx
            y = my
        end
        ig.ImplSDL2_ProcessEvent(ev)
    end
    ren:set_draw_color(0, 0, 0, 255)
    ren:clear()
    ren:set_draw_color(255, 255, 255, 255)
    ren:fill_rect(x, y, 240, 96)
    ren:set_draw_color(255, 0, 0, 255)
    ren:fill_circle(64, 64, 16)
    ig.ImplSDLRenderer2_NewFrame()
    ig.ImplSDL2_NewFrame()
    ig.NewFrame()

    ig.Begin('My Window')
    ig.Text('Hello World!')
    ig.End()

    ig.ShowDemoWindow()

    ig.Render()
    ig.ImplSDLRenderer2_RenderDrawData(ig.GetDrawData(), ren:get_handle())

    ren:present()
    sdl2.delay(16)
end

ig.ImplSDL2_Shutdown()
ig.ImplSDLRenderer2_Shutdown()

ren:destroy()
win:destroy()
sdl2.quit()
