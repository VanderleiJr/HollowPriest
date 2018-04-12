#ifndef GAME_H
#define GAME_H

//Bibliotecas C
#include <stdio.h>
#include <stdlib.h>
//Bibliotecas Allegro5
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

//Constantes
#define FPS 30
#define SPEED 5
#define WIDTH 1360
#define HEIGHT 800

//Cores
#define COLOR_BLACK al_map_rgb(0,0,0)
#define COLOR_WHITE al_map_rgb(255,255,255)

enum KEYS {UP, DOWN, LEFT, RIGHT};

void Initializers();
void ResetPosition(int *xVariation, int *yVariation);
void Game();

#endif //GAME_H