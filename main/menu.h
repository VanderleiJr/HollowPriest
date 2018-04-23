#ifndef MENU_H
#define MENU_H

void Initializers();
void FirstMenu();
void SecondMenu(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *menu_background, ALLEGRO_FONT *title, ALLEGRO_FONT *footer,
		  		ALLEGRO_FONT *font50, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_TIMER *timer,
		  		ALLEGRO_EVENT *event);

#endif //MENU_H