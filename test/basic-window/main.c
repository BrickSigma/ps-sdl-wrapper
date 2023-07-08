#include "../../src/Window_t/window.h"
#include "../../src/core.h"

#define WIDTH 640

#define HEIGHT 480

SDL_Color colors[2] = {
    (SDL_Color) {0x00, 0x00, 0x00, 0x00},
    (SDL_Color) {0xFF, 0xFF, 0xFF, 0xFF},
};

/* ================================================================ */

int  main(int argc, char** argv) {
    /* =========== VARIABLES ========== */

    Window_t window = NULL;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);

    window = Window_create("Basic Window", WIDTH, HEIGHT, SDL_WINDOW_SHOWN, SURFACE, NONE);

    if (window != NULL) {
        printf("OK\n");

        int quit = 0;

        SDL_Event event;

        uint64_t start = 0;
        float delta = 0;

        extern SDL_Color* color_ptr;

        size_t i = 0;


        while (!quit) {

            start = SDL_GetTicks64();

            while (SDL_PollEvent(&event)) {
                switch (event.type) {

                    case SDL_QUIT:
                        quit = !quit;

                        break;
                }
            }

            printf("%f\n", delta);

            Window_clear(window);

            Window_update(window);

            delta += (SDL_GetTicks64() - start) / 1000.0f;

            if (delta >= 3) {
                Global_set_SDL_Color(&colors[i++ % 2]);

                delta = 0;
            }
        }
    }

    Window_destroy(&window);

    SDL_Quit();

    return EXIT_SUCCESS;
}

/* ================================================================ */