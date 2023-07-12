#include "../../src/core.h"
#include "../../src/Image_t/image.h"
#include "../../src/Area_t/area.h"


#define WIDTH 640

#define HEIGHT 480

/* ================================================================ */

int  main(int argc, char** argv) {
    /* =========== VARIABLES ========== */

    Window_t window = NULL;

    Area_t area1 = NULL;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);

    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    window = Window_create("Basic Window", WIDTH, HEIGHT, SDL_WINDOW_SHOWN, SURFACE, NONE);

    if (window != NULL) {

        SDL_Rect rect = {0, 0, 100, 150};

        area1 = Area_create(&rect, NULL, window);

        Area_info(area1);

        int quit = 0;

        SDL_Event event;

        while (!quit) {

            while (SDL_PollEvent(&event)) {
                switch (event.type) {

                    case SDL_QUIT:
                        quit = !quit;

                        break;
                }
            }

            Global_set_color(255, 255, 255, 255);

            Window_clear(window);

            Global_set_color(255, 0, 0, 255);

            Area_clear(area1);

            Window_update(window);
        }
    }

    Area_destroy(&area1);

    Window_destroy(&window);

    SDL_Quit();

    return EXIT_SUCCESS;
}

/* ================================================================ */