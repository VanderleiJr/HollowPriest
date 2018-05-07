#ifndef INCLUDES_H
#define INCLUDES_H

//Bibliotecas C
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Bibliotecas Allegro5
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
//Bibliotecas Próprias
#include "menu.h"
#include "game.h"
#include "list.h"
#include "colision.h"
#include "characters.h"

//Constantes
#define FPS 30
#define WIDTH 1360
#define HEIGHT 800

#define MAX_WEAPONS 3

#define CHARACTER_MAX_LIFE 100
#define CHARACTER_MAX_STAMINA 100
#define CHARACTER_FRAME_WIDTH 48
#define CHARACTER_FRAME_HEIGHT 72

#define AMMO_POSITION_X ((0.5 * WIDTH))
#define AMMO_POSITION_Y ((0.9 * HEIGHT))
//Cores
#define COLOR_BLACK al_map_rgb(0,0,0)
#define COLOR_GREEN al_map_rgb(0,255,0)
#define COLOR_WHITE al_map_rgb(255,255,255)
#define COLOR_RED al_map_rgb(255,0,0)

#endif	//INCLUDE_H