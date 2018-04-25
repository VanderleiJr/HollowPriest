#ifndef INCLUDES_H
#define INCLUDES_H

//Bibliotecas C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

#define MAX_WEAPONS 3

#define SHOT_DISTANCE 35

#define CHARACTER_SPEED 4
#define CHARACTER_MAX_LIFE 100
#define CHARACTER_MAX_STAMINA 100
#define CHARACTER_FRAME_WIDHT 48
#define CHARACTER_FRAME_HEIGHT 72

//Cores
#define COLOR_BLACK al_map_rgb(0,0,0)
#define COLOR_WHITE al_map_rgb(255,255,255)
#define COLOR_RED al_map_rgb(255,0,0)

#endif	//INCLUDE_H