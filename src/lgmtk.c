#include "lgmtk.h"

const luaL_Reg _modules[] = {
    {"gl", luaopen_gl},
    {"sdl2", luaopen_sdl2},
    {"json", luaopen_json},
    {"image", luaopen_image},
    {NULL, NULL}
};

int luaopen_lgmtk(lua_State* L) {
    lua_newtable(L);
    for (int i = 0; _modules[i].name != NULL; i++) {
        luaL_requiref(L, _modules[i].name, _modules[i].func, 1);
        lua_setfield(L, -2, _modules[i].name);
    }
    return 1;
}
