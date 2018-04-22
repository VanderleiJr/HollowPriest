#ifndef GAME_H
#define GAME_H

enum KEYS {UP, DOWN, LEFT, RIGHT};

void Game(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *footer,
		  ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_TIMER *timer,
		  ALLEGRO_EVENT *event);

#endif //GAME_H