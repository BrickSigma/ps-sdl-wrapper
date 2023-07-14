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

    /* Window associated with an area. When it's time to destroy an area, its window is set to NULL */
    Window_t window;
};

/* ================================================================ */
/* ============================= API ============================== */
/* ================================================================ */

/**
 * Create a new instance of an area. An area is a rectangular entity that abstracts drawing operations on a screen.
 * 
 * @param dimensions a rectangular that defines dimensions of an area
 * @param name an area's label. Can be displayed on the area
 * @param window a window associated with the area
 * 
 * @return a new instance of an Area_t object on success, NULL on failure.
*/
extern Area_t Area_create(const SDL_Rect* dimensions, const char* name, const Window_t window);

/* ================================================================ */

/**
 * Destroy an area. The function deallocates memory allocated by Area_create() to hold an area.
 * 
 * @param area an area to be destroyed
 * 
 * @return 0 on success, a negative value on error; information about the error occurred is printed to the console.
*/
extern int Area_destroy(Area_t* area);

/* ================================================================ */

extern void Area_info(const Area_t area);

/* ================================================================ */

/**
 * Clear/filled the area with the global color.
 * 
 * @param area an area to be cleared/filled
 * 
 * @return 0 on success, a negative value on error; information about the error occurred is printed to the console.
*/
extern int Area_clear(const Area_t area);

#endif /* AREA_H */