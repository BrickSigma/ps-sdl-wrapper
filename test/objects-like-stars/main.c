#include "../../src/core.h"

#include <time.h>

#define WIDTH 120

#define HEIGHT 120

#define STARS 4

#define STAR_SIZE 16

struct _timer {
    float time;

    float delta;
};

int Object__is_collide(const Object_t obj_1, const Object_t obj_2) {
    /* =========== VARIABLES ========== */

    SDL_Rect position_1;
    SDL_Rect position_2;

    /* ================================ */

    if ((obj_1 != NULL) && (obj_2 != NULL)) {
        position_1.x = obj_1->position.x;
        position_1.y = obj_1->position.y;

        position_1.w = obj_1->dimensions.x;
        position_1.h = obj_1->dimensions.y;

        position_2.x = obj_2->position.x;
        position_2.y = obj_2->position.y;

        position_2.w = obj_2->dimensions.x;
        position_2.h = obj_2->dimensions.y;

        return Rect_is_collide(&position_1, &position_2);
    }

    return -1;
}

/* ================================================================ */

int main(int argc, char** argv) {
    /* =========== VARIABLES ========== */

    int result = EXIT_SUCCESS;


    time_t t;

    size_t i = 0;
    size_t j = 0;



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



    SDL_Rect position = {0, 0, STAR_SIZE, STAR_SIZE};

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

                    (*(timers + i))->time = 1 + (float) (rand() % 1);

                    printf("%f\n", (*(timers + i))->time);

                    (*(timers + i))->delta = 0;
                }

                SDL_Event event;

                int quit = 0;

                uint64_t start;

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

                    for (i = 0; i < STARS; i++) {
                        (*(timers + i))->delta += (SDL_GetTicks64() - start) / 1000.0f;

                        if ((*(timers + i))->delta >= (*(timers + i))->time) {

                            for (j = 0; j < STARS; j++) {

                                if (i == j) continue ;

                                position.x = rand() % (WIDTH - STAR_SIZE);
                                position.y = rand() % (HEIGHT - STAR_SIZE);

                                Object_set_pos(*(stars + i), position.x, position.y);

                                if (Object__is_collide(*(stars + i), *(stars + j))) {
                                    printf("Collision detected\n");

                                    printf("[%d; %d]\n", i, j);

                                    j = 0;
                                }
                            }

                            (*(timers + i))->delta = 0;
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