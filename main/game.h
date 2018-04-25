#ifndef GAME_H
#define GAME_H

#include "characters.h"

enum KEYS {UP, DOWN, LEFT, RIGHT};

void Game(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *footer,
		  ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_TIMER *timer,
		  ALLEGRO_EVENT *event);
void LastKey(int key[], int *lastDirection);
int OrBitABit(int key[]);

//FUNÇÕES DA LISTA
void CreateList(weaponsList *list);
int Insertion(typeWeapon *item, weaponsList *list);
typeWeapon * Search(int position, weaponsList *list);

#endif //GAME_H