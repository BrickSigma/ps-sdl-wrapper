#include "object.h"
 
extern SDL_Color* color_ptr;

extern Area_t __current_area;

/* ================================================================ */

Object_t Object_create(int width, int height) {
    /* =========== VARIABLES ========== */

    Object_t obj = NULL;

    /* ================================ */



    /* ================================================================ */
    /* ========= Dynamically allocate memory for every object ========= */
    /* ============= YOU NEED TO CALL free ON EVERY OBJECT ============ */
    /* ================================================================ */

    if ((obj = (Object_t) malloc(sizeof(struct _object))) != NULL) {

        /* ======================= Clear the memory ======================= */
        memset(obj, 0, sizeof(struct _object));

        obj->dimensions.x = width;
        obj->dimensions.y = height;
    }
    else {
        warn_with_sys_msg(__func__);
    }

    /* ================================ */

    return obj;
}

/* ================================================================ */

int Object_destroy(Object_t* object) {
    /* =========== VARIABLES ========== */

    int result = -1;

    /* ================================ */



    /* ================================================================ */
    /* =============== Make sure an object is not NULL ================ */
    /* ================================================================ */

    if ((object != NULL) && (*object != NULL)) {

        free(*object);

        /* ================================ */

        *object = NULL;
    }
    else {
        warn_with_user_msg(__func__, "provided object is NULL");
    }

    /* ================================ */

    return result;
}

/* ================================================================ */

int Object_set_pos(Object_t object, int x, int y) {
    /* =========== VARIABLES ========== */

    int result = -1;

    /* ================================ */



    /* ================================================================ */
    /* =============== Make sure an object is not NULL ================ */
    /* ================================================================ */

    if (object != NULL) {

        object->position.x = x;
        object->position.y = y;
    }
    else {
        warn_with_user_msg(__func__, "provided object is NULL");
    }

    /* ================================ */

    return result;
}

/* ================================================================ */

void Object_display(Object_t object) {
    /* =========== VARIABLES ========== */

    SDL_Rect render_position = {0, 0, 0, 0};

    /* Save an old color value */
    SDL_Color global_color = {color_ptr->r, color_ptr->g, color_ptr->b, color_ptr->a};

    /* ================================ */

    

    /* ================================================================ */
    /* =============== Make sure an object is not NULL ================ */
    /* ================================================================ */

    if (object != NULL) {

        if (__current_area != NULL) {

            if (Window_get_context_type(__current_area->window) == SURFACE) {

                render_position.x = __current_area->dimensions.x + object->position.x;
                render_position.y = __current_area->dimensions.y + object->position.y;

                /* X position corresponds to an object width */
                render_position.w = object->dimensions.x;

                /* Y position corresponds to an object height */
                render_position.h = object->dimensions.y;

                /* ================================ */

                if (!Rect_is_full_inside(&render_position, &__current_area->dimensions)) {
                    return ;
                }

                /* ================================ */

                Global_set_color(object->color.r, object->color.g, object->color.b, object->color.a);

                SDL_FillRect((SDL_Surface*) Window_get_context(__current_area->window), &render_position, SDL_MapRGBA(((SDL_Surface*) Window_get_context(__current_area->window))->format, object->color.r, object->color.g, object->color.b, object->color.a));
            }
            else {
                warn_with_user_msg(__func__, "objects are dedicated for CPU accelerator, use Sprite_t instead");
            }
        }   
        else {
            warn_with_user_msg(__func__, "there is no area");
        }

        /* Restore the previous color */
        Global_set_SDL_Color(&global_color);
    }
    else {
        warn_with_user_msg(__func__, "provided object is NULL");
    }

    /* ================================ */

    return ;
}

/* ================================================================ */

int Object_is_inside_Area(const Object_t obj, const Area_t area) {
    
}