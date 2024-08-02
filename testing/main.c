#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include "my_point.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Renderer* renderer;

// x e y representan la posicion del pixel que se pintara negro.
// Considerar que la ventana es de 640x480
void dibujar_1_punto(int x, int y) {
    SDL_RenderDrawPoint(renderer, x, y);
    SDL_RenderPresent(renderer);
}

int main(int argc, char ** argv) {
    // Semilla aleatoria
    srand(time(NULL));
    
    // Variables
    bool quit = false;
    SDL_Event event;

    // variables de nuestro poligono
    int n;
    printf("Ingrese el número de vértices del polígono: ");
    scanf("%d", &n);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // arreglo de n puntos que representan a una figura de n vertices
    Point vertices[n];
    for (int i = 0; i < n; i++) {
        // Calcular las coordenadas de los vértices
        float angle = 2 * M_PI * i / n;
        int x = (int)(SCREEN_WIDTH / 2 + (SCREEN_WIDTH / 4) * cos(angle));
        int y = (int)(SCREEN_HEIGHT / 2 + (SCREEN_HEIGHT / 4) * sin(angle));
        vertices[i] = crear_punto(x, y);
        dibujar_1_punto(x, y); // Dibujar los vértices
    }
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Se inicializa la librería SDL (Para dibujar)
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window * window = SDL_CreateWindow("Proyecto de ALP - UBB",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);

    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // Se pinta toda la pantalla de negro
    SDL_RenderClear(renderer);
    
    // color rojo para los puntos
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // puntos iniciales iniciados de manera random
    Point punto_actual = vertices[rand() % n];

    while (!quit) {
        // Se esperan 10 ms antes de continuar
        SDL_Delay(10);

        // Se verifica si se apreta el botón para cerrar la ventana
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
        }
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        // Elegir un nuevo punto aleatorio de los vértices del polígono
        Point nuevo_punto = vertices[rand() % n];

        // Actualizar el punto actual al punto medio entre este y el nuevo punto aleatorio
        punto_actual = div_escalar(suma_puntos(punto_actual, nuevo_punto), 2.0);

        // Dibujar el nuevo punto
        dibujar_1_punto(punto_actual.x, punto_actual.y);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    }

    // Limpiar variables de SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}