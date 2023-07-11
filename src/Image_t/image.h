#ifndef IMAGE_H
#define IMAGE_H

#ifdef __cplusplus
    extern "C" {
#endif

#include "../core.h"

/* ================================================================ */
/* ====================== TYPES DEFINITIONS ======================= */
/* ================================================================ */

/* ================================================================ */
/* ==================== TYPES IMPLEMENTATIONS ===================== */
/* ================================================================ */

/* ================================================================ */
/* ============================= API ============================== */
/* ================================================================ */

#define Image_unload(image) (SDL_FreeSurface((SDL_Surface*) image))

/**
 * Load an image. To use this function an SDL_image library should be initialized.
 * 
 * @param path is a path to an image file to load
 * 
 * @return Image_t on success, NULL on failure.
*/
extern Image_t Image_load(const char* path);

/* ================================================================ */

/**
 * This function is used to optimize images for faster repeat blitting
*/
extern Image_t Image_optimize(Image_t image, const Window_t window);

#ifdef __cplusplus
    }
#endif

#endif