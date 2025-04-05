#include "lgmtk.h"
#include "common.h"

const luaL_Reg _modules[] = {
#if !defined(LGMTK_NO_GL)
    {"gl", luaopen_gl},
#endif
#if !defined(LGMTK_NO_SDL)
    {"sdl2", luaopen_sdl2},
#endif
    {"json", luaopen_json},
    {"image", luaopen_image},
    {"font", luaopen_font},
    {"fs", luaopen_fs},
    {NULL, NULL}
};

int luaopen_lgmtk(lua_State* L) {
    lua_newtable(L);
    for (int i = 0; _modules[i].name != NULL; i++) {
        _modules[i].func(L);
        lua_setfield(L, -2, _modules[i].name);
    }
    return 1;
}
