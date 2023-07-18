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