#ifndef LGMTK_H_
#define LGMTK_H_

#include <stdio.h>
#include <stdlib.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#if !defined(LGMTK_NO_GL)
#include "glad/glad.h"
#endif

#if !defined(LGMTK_NO_SDL)
#include <SDL.h>
#include <SDL_opengl.h>
#endif

#if defined(_WIN32)
#define OS_WIN 1
#elif defined(__linux__)
#define OS_LINUX 1
#elif defined(__android__)
#define OS_ANDROID  1
#elif defined(__EMSCRIPTEN__)
#define OS_EMSCRIPTEN 1
#endif

#ifndef LGMTK_API
    #if defined(_WIN32)
        #if defined(LGMTK_EXPORT_DLL)
            #define LGMTK_API __declspec(dllexport)
        #elif defined(LGMTK_IMPORT_DLL)
            #define LGMTK_API __declspec(dllimport)
        #else
            #define LGMTK_API 
        #endif
    #else
        #define LGMTK_API extern
    #endif
#endif

typedef struct FontGlyph FontGlyph;
struct FontGlyph {
    int ax, ay;
    int bl, bt;
    int bw, bh;
    int tx;
};

#if defined(__cplusplus)
extern "C" {
#endif

#if !defined(LGMTK_NO_SDL)
LGMTK_API int luaopen_sdl2(lua_State* L);
#endif
LGMTK_API int luaopen_image(lua_State* L);
#if !defined(LGMTK_NO_GL)
LGMTK_API int luaopen_gl(lua_State* L);
#endif
LGMTK_API int luaopen_json(lua_State* L);

LGMTK_API int luaopen_font(lua_State* L);
LGMTK_API int luaopen_fs(lua_State* L);

LGMTK_API int luaopen_lgmtk(lua_State* L);

#if defined(__cplusplus)
}
#endif

#endif /* LGMTK_H_ */
