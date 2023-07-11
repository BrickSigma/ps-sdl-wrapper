#ifndef WINDOW_H
#define WINDOW_H

#ifdef __cplusplus
    extern "C" {
#endif

#include "../core.h"

/* ================================================================ */
/* ==================== TYPES IMPLEMENTATIONS ===================== */
/* ================================================================ */

/**
 * The type used to identify a window
*/
struct _window {
    /* The member used to identify the actual window */
    SDL_Window* window;

    /* A rendering context of the window */
    Context_t context;

    /* Options of the window */
    struct _window_opts* options;
};

/* ================================================================ */
/* ============================= API ============================== */
/* ================================================================ */

/**
 * Create a new instance of a window.
 * 
 * @param name the name of the window. It appears at the top of the window
 * @param width the width of the window
 * @param height the height of the window
 * @param sdl_flags 0, or one or more SDL_WindowFlags OR'd together
 * @param context_type the type of the rendering context used by the window 
 * @param renderer_sdl_options 0, or one or more SDL_RendererFlags OR'd together. This argument is ignored, if you specified SURFACE as a rendering context
 * 
 * @return a new instance of a Window_t type ready to be displayed on the screen. NULL on failure.
*/
extern Window_t Window_create(const char* name, int width, int height, uint32_t sdl_flags, uint8_t context_type, uint32_t renderer_sdl_options);

/* ================================================================ */

extern int Window_destroy(Window_t* window);

/* ================================================================ */

extern int Window_clear(const Window_t window);

/* ================================================================ */

extern int Window_update(const Window_t window);

/* ================================================================ */

extern int Window_set_FPS(const Window_t window, size_t fps);

/* ================================================================ */

extern void Global_set_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

/* ================================================================ */

extern int Global_set_SDL_Color(const SDL_Color* color);

/* ================================================================ */

/**
 * Get a window rendering context type.
*/
extern uint8_t Window_get_context_type(const Window_t window);

/* ================================================================ */

extern void* Window_get_context(const Window_t window);

/* ================================================================ */

/**
 * Display an image as a background one. This function calls SDL_BlitScaled.
*/
extern void Window_display_BG(const Window_t window, const Image_t image);

/* ================================================================ */

#ifdef __cplusplus
    }
#endif

#endif