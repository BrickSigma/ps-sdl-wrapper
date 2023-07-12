#ifndef TYPES_H
#define TYPES_H

/* ================================================================ */
/* =========================== WINDOW_T =========================== */
/* ================================================================ */

/**
 * A structure that defines a window
*/
typedef struct _window* Window_t;

/**
 * A structure that defines a rendering context used by the window
*/
typedef struct _context* Context_t;

/* ================================================================ */
/* =========================== IMAGE_T ============================ */
/* ================================================================ */

/**
 * A structure that defines an image for a surface context. CPU accelerated
*/
typedef struct SDL_Surface* Image_t;

/* ================================================================ */
/* =========================== IMAGE_T ============================ */
/* ================================================================ */

/**
 * A structure that defines an area of a screen/window
*/
typedef struct _area* Area_t;

/* ================================================================ */

#endif /* TYPES_H */