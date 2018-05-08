#ifndef MENU_H
#define MENU_H

void Initializers();
void FirstMenu();
void SecondMenu(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *menu_background, ALLEGRO_FONT *title, ALLEGRO_FONT *footer,
		  		ALLEGRO_FONT *font50, ALLEGRO_SAMPLE *sound_menu, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_TIMER *timer,
		  		ALLEGRO_EVENT *event, ALLEGRO_SAMPLE_INSTANCE *inst_sound_background);
void Controls(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *footer, ALLEGRO_FONT *subtitle,
			  ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_TIMER *timer, ALLEGRO_BITMAP *menu_background,
			  ALLEGRO_EVENT *event, ALLEGRO_SAMPLE_INSTANCE *inst_sound_background);
void Records(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *footer, ALLEGRO_FONT *subtitle,
			  ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_TIMER *timer, ALLEGRO_BITMAP *menu_background,
			  ALLEGRO_EVENT *event, ALLEGRO_SAMPLE_INSTANCE *inst_sound_background);
void Die(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue, int pontuation,
		 ALLEGRO_TIMER *timer, ALLEGRO_EVENT *event, ALLEGRO_SAMPLE_INSTANCE *inst_sound_background);

#endif //MENU_H