#ifndef INCLUDES_H
#define INCLUDES_H

//Bibliotecas C
#include <stdio.h>
#include <stdlib.h>
//Bibliotecas Allegro5
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
//Bibliotecas Próprias
#include "menu.h"
#include "game.h"
#include "characters.h"

//Constantes
#define FPS 30
#define WIDTH 1360
#define HEIGHT 800
#define CHARACTER_FRAME_WIDHT 32
#define CHARACTER_FRAME_HEIGHT 48
#define CHARACTER_SPEED 5
#define CHARACTER_MAX_LIFE 100
#define CHARACTER_MAX_STAMINA 100

//Cores
#define COLOR_BLACK al_map_rgb(0,0,0)
#define COLOR_WHITE al_map_rgb(255,255,255)

#endif	//INCLUDE_H