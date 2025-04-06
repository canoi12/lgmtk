local cimgui = require('third.cimgui.generator.output.definitions')
local cimgui_enums = require('third.cimgui.generator.output.structs_and_enums')
local cimgui_impl = require('third.cimgui.generator.output.impl_definitions')

local lib = {
    enums = {},
    funcs = {},
    metas = {}
}

local func_list = {
    igBegin = true, igEnd = true,
    igText = true, igCreateContext = true, igDestroyContext = true,
    igGetIO = false, igStyleColorsDark = true, igGetDrawData = true,
    igRender = true, igNewFrame = true, igShowDemoWindow = true,
    igTextColored = true
}

for i,def in pairs(cimgui) do
    local func = def[1]
    if func_list[i] then
        local fn = {args={},ret={},name=func.funcname}
        table.insert(lib.funcs, fn)
        local args = fn.args
        local func_call = ''
        if func.ret ~= 'void' then
            func_call = func.ret .. ' res = '
            if func.ret == 'bool' then
                local ret = {}
                ret.name = 'res'
                ret.type = 'boolean'
                table.insert(fn.ret, ret)
            elseif func.ret == 'int' then
                local ret = {}
                ret.name = 'res'
                ret.type = 'integer'
                table.insert(fn.ret, ret)
            elseif func.ret:match('%w+%*') then
                local ret = {}
                ret.name = 'res'
                ret.type = 'lightuserdata'
                table.insert(fn.ret, ret)
            end
        end

        func_call = func_call .. i .. '('
        for j,v in ipairs(func.argsT) do
            args[j] = {name=v.name}
            local arg =  args[j]
            if v.name == '...' then break end
            if j > 1 then
                func_call = func_call .. ','
            end
            if v.type == 'const char*' then
                arg.type = 'string'
                func_call = func_call .. v.name
            elseif v.type == 'bool*' then
                arg.type = 'bool*'
                arg.default = func.defaults[v.name] or 'NULL'
                func_call = func_call .. '&' .. v.name
                local ret = {}
                ret.type = 'boolean'
                ret.name = v.name
                table.insert(fn.ret, ret)
            elseif v.type == 'const ImVec4' then
                arg.type = 'ImVec4'
                func_call = func_call .. '&' .. v.name
                for k=1,4 do
                    local ret = {}
                    ret.type = 'number'
                    ret.name = v.name .. '[' .. k .. ']'
                    table.insert(fn.ret, ret)
                end
            elseif v.type:match('Flags') then
                arg.type = 'integer'
                arg.default = func.defaults[v.name] or 0
                func_call = func_call .. v.name
            elseif v.type:match('%w+%*') then
                arg.type = 'pointer'
                arg.ctype = v.type
                func_call = func_call .. v.name
            end
        end
        func_call = func_call .. ')'
        fn.call = func_call
    end
end

table.insert(lib.funcs, {
    name = 'ImplSDL2_InitForSDLRenderer',
    call = 'ImGui_ImplSDL2_InitForSDLRenderer(win, ren)',
    args = {
        {name='win', type='pointer', ctype='SDL_Window*'},
        {name='ren', type='pointer', ctype='SDL_Renderer*'}
    },
    ret = {}
})

table.insert(lib.funcs, {
    name = 'ImplSDLRenderer2_Init',
    call = 'ImGui_ImplSDLRenderer2_Init(ren)',
    args = {
        {name='ren', type='pointer', ctype='SDL_Renderer*'}
    },
    ret = {}
})

table.insert(lib.funcs, {
    name = 'ImplSDLRenderer2_Shutdown',
    call = 'ImGui_ImplSDLRenderer2_Shutdown()',
    args = {},
    ret = {}
})

table.insert(lib.funcs, {
    name = 'ImplSDL2_Shutdown',
    call = 'ImGui_ImplSDL2_Shutdown()',
    args = {},
    ret = {}
})

table.insert(lib.funcs, {
    name = 'ImplSDLRenderer2_NewFrame',
    call = 'ImGui_ImplSDLRenderer2_NewFrame()',
    args = {},
    ret = {}
})

table.insert(lib.funcs, {
    name = 'ImplSDL2_NewFrame',
    call = 'ImGui_ImplSDL2_NewFrame()',
    args = {},
    ret = {}
})

table.insert(lib.funcs, {
    name = 'ImplSDL2_ProcessEvent',
    call = 'ImGui_ImplSDL2_ProcessEvent(ev)',
    args = {
        {
            name = 'ev',
            type = 'pointer',
            ctype = 'SDL_Event*'
        }
    },
    ret = {}
})

table.insert(lib.funcs, {
    name = 'ImplSDLRenderer2_RenderDrawData',
    call = 'ImGui_ImplSDLRenderer2_RenderDrawData(data, ren)',
    args = {
        {
            name = 'data',
            type = 'pointer',
            ctype = 'ImDrawData*'
        },
        {
            name = 'ren',
            type = 'pointer',
            ctype = 'SDL_Renderer*'
        },
    },
    ret = {}
})

for i,enum in pairs(cimgui_enums.enums) do
    local name = i:match('%w+')
    lib.enums[name] = {name=name, values={}}
    for j,val in ipairs(enum) do
        local nm = val.name:match('_%w+'):sub(2)
        lib.enums[name].values[j] = {name=nm, value=val.value}
    end
end

local source = [[
#include "lgmtk.h"
#include "lua_helper.h"

#include "common.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS 1
#include "cimgui.h"
#include "cimgui_impl.h"

typedef struct { const char* name; int value; } CImguiEnum;

]]

for i,enum in pairs(lib.enums) do
    source = source .. 'const CImguiEnum l_' .. enum.name .. '[] = {\n'
    for j,v in ipairs(enum.values) do
        source = source .. '    {"' .. v.name .. '", ' .. v.value .. '},\n'
    end
    source = source .. '{NULL, 0},\n'
    source = source .. '};\n'
end

for i,func in ipairs(lib.funcs) do
    print(i, func)
    source = source .. 'static MODULE_FUNCTION(imgui, ' .. func.name .. ') {\n    INIT_ARG();\n'
    for j,v in ipairs(func.args) do
        if v.type == 'string' then
            source = source .. '    CHECK_STRING(' .. v.name .. ');\n'
        elseif v.type == 'integer' then
            if v.default then
                source = source .. '    OPT_INTEGER(' .. v.name .. ', ' .. (v.default or 0) .. ');\n'
            else
                source = source .. '    CHECK_INTEGER(' .. v.name .. ');\n'
            end
        elseif v.type == 'bool*' then
            source = source .. '    OPT_BOOLEAN(' .. v.name .. ', ' .. (v.default or 0) .. ');\n'
        elseif v.type == 'pointer' then
            source = source .. '    ' .. v.ctype .. ' ' .. v.name .. ' = (' .. v.ctype .. ')lua_touserdata(L, arg++);\n'
        end
    end
    source = source .. '    ' .. func.call .. ';\n'

    for j,v in ipairs(func.ret) do
        if v.type == 'boolean' then
            source = source .. '    lua_pushboolean(L, ' .. v.name .. ');\n'
        elseif v.type == 'integer' then
            source = source .. '    lua_pushinteger(L, ' .. v.name .. ');\n'
        elseif v.type == 'lightuserdata' then
            source = source .. '    lua_pushlightuserdata(L, ' .. v.name .. ');\n'
        end
    end
    source = source .. '    return ' .. #func.ret .. ';\n}\n'
end

source = source .. 'const luaL_Reg _func_regs[] = {\n'
for i,func in ipairs(lib.funcs) do
    source = source .. '    REG_FIELD(imgui, ' .. func.name .. '),\n'
end
source = source .. '    {NULL, NULL}\n};\n'

source = source .. [[
int luaopen_imgui(lua_State* L) {
    luaL_newlib(L, _func_regs);
]]
for i,enum in pairs(lib.enums) do
    source = source .. 'lua_newtable(L);\n'
    source = source  .. 'for (int i = 0; l_' .. enum.name .. '[i].name != NULL; i++) {\n'
    source = source .. '    lua_pushinteger(L, l_' .. enum.name .. '[i].value);\n'
    source = source .. '    lua_setfield(L, -2, l_' .. enum.name .. '[i].name);\n'
    source = source .. '}\n'
    source = source .. 'lua_setfield(L, -2, "' .. enum.name .. '");\n'
end
source = source .. [[
    return 1;
}
]]

local f = io.open('imgui.c', 'w')
f:write(source)
f:close()