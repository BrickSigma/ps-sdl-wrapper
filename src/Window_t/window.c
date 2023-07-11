#include "window.h"

/* ================================================================ */
/* ======================= GLOBAL VARIABLES ======================= */
/* ================================================================ */

SDL_Color color = {0xFF, 0xFF, 0xFF, 0xFF};

SDL_Color* color_ptr = &color;

/* ================================================================ */
/* ==================== TYPES IMPLEMENTATIONS ===================== */
/* ================================================================ */

/**
 * The type used to identify a rendering context
*/
struct _context {
    /* Actual rendering context that is used by the window */
    void* context;

    /* Information about a renderer used by the window */
    uint8_t type;
};

struct _window_opts {
    /* Frames per second */
    size_t fps;

    /* How many ticks needed for one frame when FPS is set to some value */
    float ticks_per_frame;

    /* Time (ticks) passed since the last frame */
    uint64_t last_frame_start_ticks;
};

/* ================================================================ */
/* ======================= STATIC FUNCTIONS ======================= */
/* ================================================================ */

static Context_t Context_create(const Window_t window, uint8_t context_type, uint32_t renderer_sdl_options, const char* caller_name) {
    /* =========== VARIABLES ========== */

    /* Context we are creating */
    Context_t context = NULL;

    /* ================================= */



    /* ================================================================ */
    /* ================ Make sure a window is not NULL ================ */
    /* ================================================================ */

    if (window != NULL) {
        
        /* ================================================================ */
        /* ========== Dynamically allocate memory for a context =========== */
        /* ============= YOU NEED TO CALL free ON THIS OBJECT ============= */
        /* ================================================================ */

        if ((context = (Context_t) malloc(sizeof(struct _context))) != NULL) {

            /* ======================= Clear the memory ======================= */
            memset(context, 0, sizeof(struct _context));

            /* ===================== GPU accelerated one  ===================== */
            if ((context_type & RENDERER) > 0) {
                
                /* Set a renderer */
                context->context = (void*) SDL_CreateRenderer(window->window, 0, renderer_sdl_options);
            }

            /* ===================== CPU accelerated one  ===================== */
            else if ((context_type & SURFACE) > 0) {

                /* Set a renderer */
                context->context = (void*) SDL_GetWindowSurface(window->window);
            }

            /* ================================= */

            /* Set its type */
            context->type = context_type;

            /* Bind a context to the window */
            window->context = context;

            /* ================================= */



            if (window->context == NULL) {

                /* Destroy the context */
                free(context);

                /* ======================= Clear the memory ======================= */
                memset(context, 0, sizeof(struct _context));
            }
        }
        else {
            /* */
            warn_with_sys_msg(caller_name);
        }
    }
    else {
        /* */
        warn_with_user_msg(caller_name, "couldn't create a context");
    }



    /* ================================= */

    return context;
}

/* ================================================================ */

static int Context_destroy(Context_t* context, const char* caller_name) {
    /* =========== VARIABLES ========== */

    /* Operation result */
    int result = EXIT_FAILURE;

    /* Error message container */
    const char* error_msg;

    /* ================================= */



    /* ================================================================ */
    /* =============== Make sure a context is not NULL ================ */
    /* ================================================================ */

    if ((context != NULL) && (*context) != NULL) {

        /* ===================== GPU accelerated one  ===================== */
        if ((*context)->type == RENDERER) {

            /* Cast to the appropriate SDL structure */
            SDL_DestroyRenderer((SDL_Renderer*) (*context)->context);
        }

        /* ===================== CPU accelerated one  ===================== */
        else if ((*context)->type == SURFACE) {

            /* Cast to the appropriate SDL structure */
            SDL_FreeSurface((SDL_Surface*) (*context)->context);
        }

        /* ======================= Clear the memory ======================= */
        memset(*context, 0, sizeof(struct _context));

        result = EXIT_SUCCESS;
    }
    else {
        /* */
        warn_with_user_msg(caller_name, "provided context is NULL");
    }

    return result;
}

/* ================================================================ */
/* ======================= EXTERN FUNCTIONS ======================= */
/* ================================================================ */

Window_t Window_create(const char* name, int width, int height, uint32_t sdl_flags, uint8_t context_type, uint32_t renderer_sdl_options) {
    /* =========== VARIABLES ========== */

    /* Window we are creating */
    Window_t window = NULL;

    /* Context we are creating */
    Context_t context = NULL;

    /* Window options container we are creating */
    struct _window_opts* options = NULL;

    /* ================================= */



    /* =============== Check for validity of a context ================ */
    if ((context_type & (RENDERER | SURFACE)) == (RENDERER | SURFACE))  {
        warn_with_user_msg(__func__, "you can't have both RENDERER and SURFACE to be specified");

        /* Failure */
        return NULL;
    }
    else if (((context_type & RENDERER) == 0) && ((context_type & SURFACE) == 0)) {
        warn_with_user_msg(__func__, "you have to provide a rendering context");

        /* Failure */
        return NULL;
    }

    /* ================================= */



    /* ================================================================ */
    /* ========= Dynamically allocate memory for every object ========= */
    /* ============= YOU NEED TO CALL free ON EVERY OBJECT ============ */
    /* ================================================================ */

    window = (Window_t) malloc(sizeof(struct _window));

    options = (struct _window_opts*) malloc(sizeof(struct _window_opts));

    /* ================================================================ */

    if ((window != NULL) && (options != NULL)) {
        
        /* ===================== Create a SDL window ====================== */
        if ((window->window = SDL_CreateWindow((name == NULL) ? "Window" : name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, sdl_flags)) != NULL) {

            /* ====================== Create a context ======================== */
            if ((window->context = Context_create(window, context_type, renderer_sdl_options, __func__)) == NULL) {

                /* Destroy the window */
                Window_destroy(&window);

                return NULL;
            }

            /* Set options */
            window->options = options;

            /* =================== Add new features here ====================== */

            /* 60 FPS by default */
            window->options->fps = 60;

            /* Compute the time needed by a frame */
            window->options->ticks_per_frame = 1000.0f / window->options->fps;
        }
        else {
            warn_with_user_msg(__func__, SDL_GetError());

            /* Destroy the window */
            Window_destroy(&window);
        }
    }
    else {
        warn_with_sys_msg(__func__);

        /* ====================== Deallocate objects ====================== */

        /* Free window  */
        free(window);

        /* Free options */
        free(options);
    }



    /* ================================= */

    return window;
}

/* ================================================================ */

int Window_destroy(Window_t* window) {
    /* =========== VARIABLES ========== */

    /* Operation result */
    int result = EXIT_FAILURE;

    /* ================================= */



    /* ================================================================ */
    /* ================ Make sure a window is not NULL ================ */
    /* ================================================================ */

    if ((window != NULL) && (*window != NULL)) {

        /* Destroy a context */
        Context_destroy(&(*window)->context, __func__);

        /* ======================= Clear the memory ======================= */
        memset((*window)->options, 0, sizeof(struct _window_opts));

        /* Destroy a window options container */
        free((*window)->options);

        /* Destroy a window */
        SDL_DestroyWindow((*window)->window);

        /* ======================= Clear the memory ======================= */
        memset(*window, 0, sizeof(struct _window));

        /* Destroy the window container itself */
        free(*window);

        /* ================================= */

        /* Set the window to be NULL */
        *window = NULL;

        result = EXIT_SUCCESS;
    }
    else {
        warn_with_user_msg(__func__, "provided window is NULL");
    }



    /* ================================= */

    return result;
}

/* ================================================================ */

int Window_clear(const Window_t window) {
    /* =========== VARIABLES ========== */

    /* Operation result */
    int result = EXIT_FAILURE;

    /* ================================= */



    /* ================================================================ */
    /* ================ Make sure a window is not NULL ================ */
    /* ================================================================ */

    if (window != NULL) {

        /* ===================== GPU accelerated one  ===================== */
        if (window->context->type == RENDERER) {

            if ((result = SDL_RenderClear((SDL_Renderer*) window->context->context)) != 0) {
                warn_with_user_msg(__func__, SDL_GetError());
            }
        }

        /* ===================== CPU accelerated one  ===================== */
        else if (window->context->type == SURFACE) {

            if ((result = SDL_FillRect((SDL_Surface*) window->context->context, NULL, SDL_MapRGBA(((SDL_Surface*) window->context->context)->format, color_ptr->r, color_ptr->g, color_ptr->b, color_ptr->a))) != 0) {
                warn_with_user_msg(__func__, SDL_GetError());
            }
        }
    }
    else {
        warn_with_user_msg(__func__, "provided window is NULL");
    }


    
    /* ================================= */

    return result;
}

/* ================================================================ */

int Window_update(const Window_t window) {
    /* =========== VARIABLES ========== */

    /* Operation result */
    int result = EXIT_FAILURE;

    /* Time (in ticks) when the last frame ends */
    uint64_t last_frame_ticks = 0;

    /* ================================= */



    /* ================================================================ */
    /* ================ Make sure a window is not NULL ================ */
    /* ================================================================ */

    if (window != NULL) {

        /* Compute how much time the last frame took in ticks */
        last_frame_ticks = SDL_GetTicks64() - window->options->last_frame_start_ticks;

        /* ================================================================ */
        /* ======================= What to update  ======================== */
        /* ================================================================ */

        /* ===================== GPU accelerated one  ===================== */
        if (window->context->type == RENDERER) {
            SDL_RenderPresent((SDL_Renderer*) window->context->context);

            result = EXIT_SUCCESS;
        }

        /* ===================== CPU accelerated one  ===================== */
        else if (window->context->type == SURFACE) {
            result = SDL_UpdateWindowSurface(window->window);
        }



        /* ================================================================ */
        /* =========================== Cap FPS  =========================== */
        /* ================================================================ */

        if (window->options->ticks_per_frame > last_frame_ticks) {
            SDL_Delay(window->options->ticks_per_frame - last_frame_ticks);
        }

        /* ======================= Update a counter  ======================== */
        window->options->last_frame_start_ticks = SDL_GetTicks64();
    }
    else {
        warn_with_user_msg(__func__, "provided window is NULL");
    }



    /* ================================= */

    return result;
}

/* ================================================================ */

int Window_set_FPS(const Window_t window, size_t fps) {
    /* =========== VARIABLES ========== */

    /* Operation result */
    int result = EXIT_FAILURE;

    /* ================================= */



    /* ================================================================ */
    /* ================ Make sure a window is not NULL ================ */
    /* ================================================================ */

    if (window != NULL) {
        
        /* Set a new FPS value */
        window->options->fps = fps;

        /* Recompute ticks per frame */
        window->options->ticks_per_frame = 1000.0f / window->options->fps;

        result = EXIT_SUCCESS;
    }
    else {
        warn_with_user_msg(__func__, "provided window is NULL");
    }



    /* ================================= */

    return result;
}

/* ================================================================ */

void Global_set_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {

    /* New red value */
    color_ptr->r = red;

    /* New gree value */
    color_ptr->g = green;

    /* New blue value */
    color_ptr->b = blue;

    /* New alpha value */
    color_ptr->a = alpha;



    /* ================================= */

    return ;
}

/* ================================================================ */

int Global_set_SDL_Color(const SDL_Color* color) {
    /* =========== VARIABLES ========== */

    /* Operation result */
    int result = EXIT_FAILURE;

    /* ================================= */


    /* Check if color is not NULL first */
    color_ptr = (color != NULL) ? (SDL_Color*) color : color_ptr;

    /* Update return value */
    result = (color != NULL) ? EXIT_SUCCESS : EXIT_FAILURE;



    /* ================================= */

    return result;
}

/* ================================================================ */

uint8_t Window_get_context_type(const Window_t window) {
    /* =========== VARIABLES ========== */

    uint8_t context_type = 0;

    /* ================================= */

    /* ================================================================ */
    /* ================ Make sure a window is not NULL ================ */
    /* ================================================================ */

    if (window != NULL) {
        context_type = window->context->type;
    }
    else {
        warn_with_user_msg(__func__, "provided window is NULL");
    }

    /* ================================= */

    return context_type;
}

/* ================================================================ */

extern void* Window_get_context(const Window_t window) {
    /* =========== VARIABLES ========== */

    Context_t context = NULL;

    /* ================================= */

    /* ================================================================ */
    /* ================ Make sure a window is not NULL ================ */
    /* ================================================================ */

    if (window != NULL) {
        context = window->context->context;
    }
    else {
        warn_with_user_msg(__func__, "provided window is NULL");
    }

    /* ================================= */

    return context;
}

/* ================================================================ */

void Window_display_BG(const Window_t window, const Image_t image) {
    /* =========== VARIABLES ========== */

    SDL_Rect BG_dimension = {0, 0, 0, 0};

    /* ================================= */

    /* ================================================================ */
    /* ================ Make sure a window is not NULL ================ */
    /* ================================================================ */

    if (window != NULL) {
        
        /* ================================================================ */
        /* ================ Make sure an image is not NULL ================ */
        /* ================================================================ */

        if (image != NULL) {

            /* Get the size of a window's client area */
            SDL_GetWindowSize(window->window, &BG_dimension.w, &BG_dimension.h);

            if (window->context->type == SURFACE) {

                SDL_BlitScaled((SDL_Surface*) image, NULL, (SDL_Surface*) window->context->context, &BG_dimension);
            }
            else {
                warn_with_user_msg(__func__, "unsupported rendering context");
            }
        }
        else {
            warn_with_user_msg(__func__, "provided image is NULL");
        }
    }
    else {
        warn_with_user_msg(__func__, "provided window is NULL");
    }

    /* ================================= */

    return ;
}