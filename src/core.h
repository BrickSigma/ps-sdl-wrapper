#ifndef CORE_H
#define CORE_H

#ifdef __cplusplus
    extern "C" {
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

#include "../guard/guard.h"
#include "./types.h"

#include "./Window_t/window.h"
#include "./Image_t/image.h"
#include "./Area_t/area.h"
#include "./Object_t/object.h"

/* ================================================================ */

#define NONE 0

/* Types of the rendering contexts */
enum _renderer_types {
    /* GPU accelerated rendering context */
    RENDERER = (1 << 0),    /* 1 */

    /* CPU accelerated rendering context */
    SURFACE = (1 << 1),     /* 2 */
};



/* Color that is used in drawing operations */
extern SDL_Color color;

/* A pointer to the global color structure */
extern SDL_Color* color_ptr;

/* Global current area */
extern Area_t __current_area;

/* ================================================================ */

extern int Rect_is_full_inside(const SDL_Rect* src, const SDL_Rect* dst);

/* ================================================================ */

#ifdef __cplusplus
    }
#endif

#endif /* CORE_H */