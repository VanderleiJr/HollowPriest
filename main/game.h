#ifndef GAME_H
#define GAME_H

enum KEYS {UP, DOWN, LEFT, RIGHT};

void Game(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *footer,
		  ALLEGRO_SAMPLE *shot, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_TIMER *timer,
		  ALLEGRO_EVENT *event, ALLEGRO_SAMPLE_INSTANCE *inst_sound_background);
void LastKey(int key[], int *lastDirection);
int OrBitABit(int key[]);

#endif //GAME_H