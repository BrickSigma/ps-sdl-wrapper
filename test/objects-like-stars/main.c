#include "../../src/core.h"

#include <time.h>

#define WIDTH 480

#define HEIGHT 480

#define STARS 16

#define STAR_SIZE 16

struct _timer {
    float time;

    float delta;
};

/* ================================================================ */

int main(int argc, char** argv) {
    /* =========== VARIABLES ========== */

    int result = EXIT_SUCCESS;


    time_t t;

    size_t i = 0;



    Window_t window = NULL;



    Area_t main_area = NULL;

    SDL_Rect main_area_dimensions = {0, 0, WIDTH, HEIGHT};



    SDL_Color colors[3] = {
        {0xf2, 0xbe, 0x22, 0xff},
        {0xf2, 0x97, 0x27, 0xff},
        {0xf2, 0xfc, 0x3d, 0xff},
    };



    Object_t stars[STARS];

    struct _timer* timers[STARS];

    /* ================================ */



    if (SDL_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {

        if ((window = Window_create("Stars", WIDTH, HEIGHT, SDL_WINDOW_SHOWN, SURFACE, NONE)) != NULL) {

            if ((main_area = Area_create(&main_area_dimensions, "Main Area", window)) != NULL) {
                
                srand((unsigned) time(&t));

                __current_area = main_area;

                Window_set_FPS(window, 60);

                for (; i < STARS; i++) {
                    *(stars + i) = Object_create(STAR_SIZE, STAR_SIZE);

                    Object_set_pos(*(stars + i), STAR_SIZE + rand() % WIDTH - STAR_SIZE, STAR_SIZE + rand() % HEIGHT - STAR_SIZE);

                    (*(stars + i))->color = colors[rand() % 3 + 1];
                }

                for (i = 0; i < STARS; i++) {
                    *(timers + i) = (struct _timer*) malloc(sizeof(struct _timer));

                    (*(timers + i))->time = 1 + (float) (rand() % 10);

                    printf("%f\n", (*(timers + i))->time);

                    (*(timers + i))->delta = 0;
                }

                SDL_Event event;

                int quit = 0;

                uint64_t start;

                float delta = 0;

                while (!quit) {

                    start = SDL_GetTicks64();

                    while (SDL_PollEvent(&event)) {
                        switch (event.type) {

                            case SDL_QUIT:
                                quit = !quit;

                                break;
                        }
                    }

                    Global_set_color(255, 255, 255, 255);

                    Window_clear(window);

                    for (i = 0; i < STARS; i++) {
                        Object_display(*(stars + i));
                    }

                    Window_update(window);

                    delta += (SDL_GetTicks64() - start) / 1000.0f;

                    for (i = 0; i < STARS; i++) {
                        (*(timers + i))->delta += (SDL_GetTicks64() - start) / 1000.0f;

                        if ((*(timers + i))->delta >= (*(timers + i))->time) {
                            (*(timers + i))->delta = 0;

                            Object_set_pos(*(stars + i), (rand() % (WIDTH - STAR_SIZE)), (rand() % (HEIGHT - STAR_SIZE)));

                            printf("Star %ld position: [%d; %d]\n", i, (*(stars + i))->position.x, (*(stars + i))->position.y);
                        }
                    }
                }
            }
            else {
                result = EXIT_FAILURE;
            }
        }
        else {
            result = EXIT_FAILURE;
        }
    }
    else {
        warn_with_user_msg(__func__, SDL_GetError());

        result = EXIT_FAILURE;
    }

    /* ================================ */

    for (i = 0; i < STARS; i++) {
       Object_destroy(&*(stars + i));
    }

    for (i = 0; i < STARS; i++) {
       free(*(timers + i));
    }

    Area_destroy(&main_area);

    Window_destroy(&window);

    SDL_Quit();

    /* ================================ */

    return result;
}