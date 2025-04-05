#include "lgmtk.h"
#include "lua_helper.h"
#if !defined(OS_WIN)
#include <dirent.h>
#include <unistd.h>
#endif
#include <sys/stat.h>

static MODULE_FUNCTION(fs, exists) {
    INIT_ARG();
    CHECK_STRING(path);
    int exists = 1;
    struct stat info;
    if (stat(path, &info) == -1)
        exists = 0;
    PUSH_BOOLEAN(exists);
    return 1;
}

static MODULE_FUNCTION(fs, read) {
    INIT_ARG();
    CHECK_STRING(path);
    int to_userdata = 0;
if (lua_isboolean(L, arg)) to_userdata = lua_toboolean(L, arg++);
    #if defined(OS_WIN)
        FILE* fp;
        fopen_s(&fp, path, "rb");
    #else
        FILE* fp = fopen(path, "rb");
    #endif

    if (!fp) {
        lua_pushnil(L);
        lua_pushfstring(L, "[fs] failed to read file: %s", path);
        return 2;
    }

    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (to_userdata) {
        void* d = lua_newuserdata(L, size);
        (void)fread(d, 1, size, fp);
        fclose(fp);
        lua_pushinteger(L, size);
        return 2;
    }
    // NEW_UDATA_ADD(Data, d, size);
    // d->root = (char*)(d + 1);
    // fread(d->root, 1, size, fp);
    luaL_Buffer buf;
    luaL_buffinit(L, &buf);
    char* str = luaL_prepbuffsize(&buf, size);
    fread(str, 1, size, fp);
    fclose(fp);
    luaL_pushresult(&buf);

    return 1;
}

static MODULE_FUNCTION(fs, write) {
    INIT_ARG();
    void* text = NULL;
    size_t len;
    CHECK_STRING(path);
    if (lua_isstring(L, arg)) text = luaL_checklstring(L, arg++, &len);
    else if (lua_isuserdata(L, arg)) {
        text = lua_touserdata(L, arg++);
        len = luaL_checkinteger(L, arg);
    } else return luaL_argerror(L, arg, "string or userdata expected");
#if defined(OS_WIN)
    FILE* fp;
    fopen_s(&fp, path, "w");
#else
    FILE* fp = fopen(path, "w");
#endif
    if (!fp)
        return luaL_error(L, "failed to create file %s\n", path);
    int res = fwrite(text, 1, len, fp);
    fclose(fp);
    PUSH_BOOLEAN(res == len);
    return 1;
}

static MODULE_FUNCTION(fs, mkdir) {
    INIT_ARG();
    CHECK_STRING(path);
#if defined(OS_WIN)
    mkdir(path);
#else
    mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif
    return 0;
}

static MODULE_FUNCTION(fs, rmdir) {
    INIT_ARG();
    CHECK_STRING(path);
    rmdir(path);
    return 0;
}

int luaopen_fs(lua_State* L) {
    BEGIN_REG(reg)
        REG_FIELD(fs, exists),
        REG_FIELD(fs, read),
        REG_FIELD(fs, write),
        REG_FIELD(fs, mkdir),
        REG_FIELD(fs, rmdir),
    END_REG()
    luaL_newlib(L, reg);
    return 1;
}
