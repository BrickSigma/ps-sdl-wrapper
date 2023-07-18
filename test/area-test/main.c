#include "../../src/core.h"
#include "../../src/Image_t/image.h"
#include "../../src/Area_t/area.h"


#define WIDTH 640

#define HEIGHT 480

/* ================================================================ */

extern Area_t __current_area;

int  main(int argc, char** argv) {
    /* =========== VARIABLES ========== */

    Window_t window = NULL;

    Area_t area1 = NULL;

    Object_t obj = NULL;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);

    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    window = Window_create("Basic Window", WIDTH, HEIGHT, SDL_WINDOW_SHOWN, SURFACE, NONE);

    if (window != NULL) {

        SDL_Rect rect = {0, 0, 100, 150};

        area1 = Area_create(&rect, NULL, window);

        __current_area = area1;

        obj = Object_create(10, 10);

        Area_info(area1);

        Window_set_FPS(window, 60);

        int quit = 0;

        int x_pos = obj->position.x;

        SDL_Event event;

        while (!quit) {

            while (SDL_PollEvent(&event)) {
                switch (event.type) {

                    case SDL_QUIT:
                        quit = !quit;

                        break;
                }
            }

            x_pos++;

            Object_set_pos(obj, x_pos, 0);

            Global_set_color(255, 255, 255, 255);

            Window_clear(window);

            Global_set_color(255, 0, 0, 255);

            Area_clear(area1);

            Object_display(obj);

            Window_update(window);
        }
    }

    Object_destroy(&obj);

    Area_destroy(&area1);

    Window_destroy(&window);

    SDL_Quit();

    return EXIT_SUCCESS;
}

/* ================================================================ */