#ifndef AREA_H
#define AREA_H

#include "../core.h"

#define AREA_NAME_S 32

/* ================================================================ */
/* ==================== TYPES IMPLEMENTATIONS ===================== */
/* ================================================================ */

struct _area {

    /* Physical dimensions of an area */
    SDL_Rect dimensions;

    /* Area's name */
    char label[AREA_NAME_S];

    /* Window associated with an area */
    Window_t window;
};

/* ================================================================ */
/* ============================= API ============================== */
/* ================================================================ */

/**
 * Create a new instance of an area. An area is a rectangular entity that abstracts drawing operations 
*/
extern Area_t Area_create(const SDL_Rect* dimensions, const char* name, const Window_t window);

/* ================================================================ */

/**
 * 
*/
extern int Area_destroy(Area_t* area);

/* ================================================================ */

extern void Area_info(const Area_t area);

/* ================================================================ */

extern int Area_clear(const Area_t area);

#endif /* AREA_H */