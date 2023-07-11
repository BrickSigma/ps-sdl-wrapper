#include "./image.h"

/* ================================================================ */

Image_t Image_load(const char* path) {
    /* =========== VARIABLES ========== */

    Image_t image = NULL;

    /* ================================ */

    if ((image = IMG_Load(path)) == NULL) {
        warn_with_user_msg(__func__, IMG_GetError());
    }

    /* ================================ */

    return image;
}

/* ================================================================ */

Image_t Image_optimize(Image_t image, const Window_t window) {
    /* =========== VARIABLES ========== */

    /* A new, optimized image */
    Image_t optimized_image = NULL;

    /* ================================ */

    /* ================================================================ */
    /* ================ Make sure an image is not NULL ================ */
    /* ================================================================ */

    if (image != NULL) {

        /* ================================================================ */
        /* ================ Make sure a window is not NULL ================ */
        /* ================================================================ */

        if (window != NULL) {
            
            if (Window_get_context_type(window) == SURFACE) {

                /* Convert the given image */
                optimized_image = SDL_ConvertSurface(image, ((SDL_Surface*) Window_get_context(window))->format, 0);

                if (optimized_image != NULL) {
                    
                    /* Unload the old image */
                    Image_unload(image);
                }
                else {
                    warn_with_user_msg(__func__, SDL_GetError());
                }
            }
            else {
                warn_with_user_msg(__func__, "unsupported rendering context, try to use textures instead");
            }
        }
        else {
            warn_with_user_msg(__func__, "provided window is NULL");
        }
    }
    else {
        warn_with_user_msg(__func__, "provided image is NULL");
    }

    /* ================================ */

    return optimized_image;
}