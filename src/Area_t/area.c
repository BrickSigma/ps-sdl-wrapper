#include "./area.h"

extern SDL_Color* color_ptr;

/* ================================================================ */

Area_t Area_create(const SDL_Rect* dimensions, const char* name, const Window_t window) {
    /* =========== VARIABLES ========== */

    Area_t area = NULL;

    /* Area identifier */
    static size_t identifier = 0;

    /* ================================ */

    

    /* ================================================================ */
    /* ================ Make sure a window is not NULL ================ */
    /* ================================================================ */

    if (window == NULL) {
        warn_with_user_msg(__func__, "provided window is NULL");

        return area;
    }

    /* ================================================================ */

    /* ================================================================ */
    /* ========== Dynamically allocate memory for an object =========== */
    /* ============= YOU NEED TO CALL free ON THE OBJECT ============== */
    /* ================================================================ */

    if ((area = (Area_t) malloc(sizeof(struct _area))) != NULL) {
        
        area->dimensions = *dimensions;

        /* ================================ */

        if (name != NULL) {
            strncpy(area->label, name, AREA_NAME_S);
        }
        else {
            snprintf(area->label, AREA_NAME_S, "Area %zd", identifier++);
        }

        /* ================================ */

        area->window = window;
    }
    else {
        warn_with_sys_msg(__func__);
    }

    /* ================================ */
    
    return area;
}

/* ================================================================ */

int Area_destroy(Area_t* area) {
    /* =========== VARIABLES ========== */
    
    int result = -1;

    /* ================================ */



    /* ================================================================ */
    /* ================ Make sure an area is not NULL ================= */
    /* ================================================================ */

    if ((area != NULL) && (*area != NULL)) {

        /* Window is set to NULL. Its deletion is handled by calling Window_destroy function */
        (*area)->window = NULL;

        free(*area);

        /* ================================ */

        *area = NULL;

        result = 0;
    }
    else {
        warn_with_user_msg(__func__, "provided area is NULL");
    }

    /* ================================ */

    return result;
}

/* ================================================================ */

void Area_info(const Area_t area) {
    
    if (area != NULL) {
        printf("Area dimensions: [.x = %d; .y = %d; .w = %d; .h = %d]\nArea label: %s\nArea window: %p\n", area->dimensions.x, area->dimensions.y, area->dimensions.w, area->dimensions.h, area->label, area->window);
    }

    return ;
}

/* ================================================================ */

int Area_clear(const Area_t area) {
    /* =========== VARIABLES ========== */
    
    int result = -1;

    Context_t context = NULL;

    /* ================================ */



    /* ================================================================ */
    /* ================ Make sure an area is not NULL ================= */
    /* ================================================================ */

    if (area != NULL) {

        context = Window_get_context(area->window);

        /* */
        if (Window_get_context_type(area->window) == SURFACE) {

            if ((result = SDL_FillRect((SDL_Surface*) context, &area->dimensions, SDL_MapRGBA(((SDL_Surface*) context)->format, color_ptr->r, color_ptr->g, color_ptr->b, color_ptr->a))) != 0) {

                warn_with_user_msg(__func__, SDL_GetError());
            }
        }
    }
    else {
        warn_with_user_msg(__func__, "provided area is NULL");
    }

    /* ================================ */

    return result;
}