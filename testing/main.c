#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "my_point.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

void dibujar_1_punto(SDL_Renderer *renderer, int x, int y) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // Color blanco
    SDL_RenderDrawPoint(renderer, x, y);
}

int main() {
    int NUM_PUNTOS;
    printf("Ingrese el número de puntos: ");
    scanf("%d", &NUM_PUNTOS);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL no pudo inicializarse. SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("SDL Puntos", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Ventana no pudo ser creada. SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_DestroyWindow(window);
        printf("Renderizador no pudo ser creado. SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    srand(time(NULL));

    Point* puntos = malloc(NUM_PUNTOS * sizeof(Point));
    for (int i = 0; i < NUM_PUNTOS; i++) {
        puntos[i] = crear_punto(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); // Fondo negro
    SDL_RenderClear(renderer);

    for (long i = 0; i < 100000; i++) {
        SDL_Event e;
        if (SDL_PollEvent(&e) && e.type == SDL_QUIT) break;

        int indice_punto = rand() % NUM_PUNTOS;
        dibujar_1_punto(renderer, puntos[indice_punto].x, puntos[indice_punto].y);

        SDL_RenderPresent(renderer);
        SDL_Delay(10); // Pequeña pausa para no sobrecargar el CPU
    }

    free(puntos);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}