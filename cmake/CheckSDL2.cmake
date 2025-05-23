message("Check For SDL2 lib")

if (DEFINED MSVC)
    set (SDL_PRECOMP_DIR "${CACHE_DIR}/SDL2/MSVC" CACHE STRING "Set SDL2 dir")
elseif (DEFINED MINGW)
    set (SDL_PRECOMP_DIR "${CACHE_DIR}/SDL2/MINGW" CACHE STRING "Set SDL2 dir")
else ()
    set (SDL_PRECOMP_DIR "" CACHE STRING "Set SDL2 dir")
endif ()
set (SDL_SOURCE_DIR "${CACHE_DIR}/SDL2/source" CACHE STRING "Set SDL2 source dir")

if (NOT "${SDL_PRECOMP_DIR}" STREQUAL "")
set(SDL2_DIR "${SDL_PRECOMP_DIR}/cmake")
endif ()
message("testing builds/${triple}${LIB_PLATFORM}")
if (DEFINED SDL2_DIR)
    find_package(SDL2 REQUIRED)
elseif (NOT USE_SDL_SOURCE)
    find_path(SDL2_INCLUDE_DIR NAMES SDL2/SDL.h)
    if (SDL2_INCLUDE_DIR)
        set (SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIR}/SDL2)
    endif ()
    find_library(SDL2_Lib NAMES SDL2)
    if (NOT SDL2_Lib)
        message ("SDL2 Lib not found in system, looking for precompiled in ${CMAKE_SOURCE_DIR}/builds/${triple}${LIB_PLATFORM}")
        find_library(SDL2_Lib NAMES SDL2 PATHS "${CMAKE_SOURCE_DIR}/builds/${triple}${LIB_PLATFORM}/lib" NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
        find_path(SDL2_INCLUDE_DIR NAMES SDL.h PATHS "${SDL_SOURCE_DIR}/include" REQUIRED NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
        set (SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIR})
    endif ()
    find_library(SDL2_Main_Lib NAMES SDL2main PATHS "${CMAKE_SOURCE_DIR}/builds/${triple}${LIB_PLATFORM}")
endif ()

message("SDL2 Library ${SDL2_Lib}")
message("SDL2 INCLUDE ${SDL2_INCLUDE_DIRS}")

if ((NOT SDL2_FOUND AND SDL2_Lib) AND NOT TARGET SDL2::SDL2)
    message ("Import SDL2 Library")
    add_library(SDL2::SDL2 SHARED IMPORTED)
    set_property(TARGET SDL2::SDL2 PROPERTY IMPORTED_LOCATION ${SDL2_Lib})
    set (SDL2_LIBRARIES SDL2::SDL2)
    if (SDL2_Main_Lib AND NOT TARGET SDL2::Main)
        add_library(SDL2::Main SHARED IMPORTED)
        set_property(TARGET SDL2::Main PROPERTY IMPORTED_LOCATION ${SDL2_Main_Lib})
        target_link_libraries(SDL2::Main INTERFACE SDL2::SDL2)
        set (SDL2_LIBRARIES ${SDL2_LIBRARIES} SDL2::Main)
    endif ()
elseif (NOT SDL2_Lib AND NOT SDL2_FOUND)
    message("Compiling SDL2 from source")
    add_subdirectory(${SDL_SOURCE_DIR})
    set (SDL2_LIBRARIES SDL2::SDL2)
    if (SDL2_Main_Lib AND TARGET SDL2::Main)
        set (SDL2_LIBRARIES ${SDL2_LIBRARIES} SDL2::Main)
    endif ()
endif ()

