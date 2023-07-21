#ifndef OBJECT_H
#define OBJECT_H

#include "../core.h"

extern Area_t __current_area;

/* ================================================================ */
/* ==================== TYPES IMPLEMENTATIONS ===================== */
/* ================================================================ */

struct _object {

    /* An object position on the screen */
    SDL_Point position;

    /* An object dimension. Width and height */
    SDL_Point dimensions;

    /* Object BG color */
    SDL_Color color;
};

/* ================================================================ */
/* ============================= API ============================== */
/* ================================================================ */

/**
 * 
*/
extern Object_t Object_create(int width, int height);

/* ================================================================ */

extern int Object_destroy(Object_t* object);

/* ================================================================ */

extern int Object_set_pos(Object_t object, int x, int y);

/* ================================================================ */

extern void Object_display(Object_t object);

/* ================================================================ */

extern int Object_is_inside_Area(const Object_t obj, const Area_t area);

/* ================================================================ */

extern int Object_set_color(const Object_t obj, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

/* ================================================================ */

extern int Object_get_color(const Object_t obj, SDL_Color* dst);

/* ================================================================ */

extern int Object_set_SDL_color(const Object_t obj, const SDL_Color* src);

#endif /* OBJECT_H */