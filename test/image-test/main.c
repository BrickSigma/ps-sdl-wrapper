#include "../../src/core.h"
#include "../../src/Image_t/image.h"


#define WIDTH 640

#define HEIGHT 480

/* ================================================================ */

int  main(int argc, char** argv) {
    /* =========== VARIABLES ========== */

    Window_t window = NULL;

    Image_t BG_image = NULL;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);

    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    window = Window_create("Basic Window", WIDTH, HEIGHT, SDL_WINDOW_SHOWN, SURFACE, NONE);

    if (window != NULL) {

        int quit = 0;

        SDL_Event event;

        BG_image = Image_load("./images/image1.jpg");

        printf("%p\n", BG_image);

        printf("%p\n" , (BG_image = Image_optimize(BG_image, window)));

        while (!quit) {

            while (SDL_PollEvent(&event)) {
                switch (event.type) {

                    case SDL_QUIT:
                        quit = !quit;

                        break;
                }
            }

            Window_clear(window);

            Window_display_BG(window, BG_image);

            Window_update(window);
        }
    }

    Image_unload(BG_image);

    Window_destroy(&window);

    SDL_Quit();

    return EXIT_SUCCESS;
}

/* ================================================================ */