#include "core.h"

/* ================================================================ */

int Rect_is_full_inside(const SDL_Rect* src, const SDL_Rect* dst) {
    /* =========== VARIABLES ========== */

    int result = -1;

    /* ================================ */

    if ((src != NULL) && (dst != NULL)) {
        result = (
            (((src->x + src->w) <= (dst->x + dst->w)) && (src->x >= dst->x))
            &&
            (((src->y + src->h) <= (dst->y + dst->h)) && (src->y >= dst->y))
        );
    }
    
    /* ================================ */

    return result;
}

/* ================================================================ */

int Rect_is_collide(const SDL_Rect* rect_1, const SDL_Rect* rect_2) {
    /* =========== VARIABLES ========== */

    int result = -1;

    /* ================================ */

    if ((rect_1 != NULL) && (rect_2 != NULL)) {
        result = (
            (rect_1->x < (rect_2->x + rect_2->w)) && ((rect_1->x + rect_1->w) > rect_2->x)
            &&
            (rect_1->y < (rect_2->y + rect_2->h)) && ((rect_1->y + rect_1->h) > rect_2->y)
        );
    }

    /* ================================ */

    return result;
}