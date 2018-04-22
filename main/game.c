#include "includes.h"

void Game(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *footer,
		  ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_TIMER *timer,
		  ALLEGRO_EVENT *event){

		int xVariation = -20;
		int yVariation = -20;
		int key[] = {0, 0, 0, 0};

		while(true){
			character protagonist;
			protagonist.sprite = al_load_bitmap("../media/sprites/character.png");
			protagonist.speed = 5;

			al_clear_to_color(al_map_rgb(130, 130, 130));
			al_draw_bitmap(protagonist.sprite, WIDTH/2 + xVariation, HEIGHT/2 + yVariation, 0);
			al_draw_text(footer, COLOR_WHITE, 0, HEIGHT - 20, ALLEGRO_ALIGN_LEFT, "Press [ESC] to menu");
			al_flip_display();

			al_wait_for_event(event_queue, event);
			if(event->type == ALLEGRO_EVENT_KEY_DOWN){
				if(event->keyboard.keycode == ALLEGRO_KEY_ESCAPE){
					al_destroy_bitmap(protagonist.sprite);
					return ;
				}
				switch(event->keyboard.keycode){
					case ALLEGRO_KEY_W:
						key[UP] = 1; break;
					case ALLEGRO_KEY_S:
						key[DOWN] = 1; break;
					case ALLEGRO_KEY_A:
						key[LEFT] = 1; break;
					case ALLEGRO_KEY_D:
						key[RIGHT] = 1; break;
				}
			}
			if(event->type == ALLEGRO_EVENT_KEY_UP){
				switch(event->keyboard.keycode){
					case ALLEGRO_KEY_W:
						key[UP] = 0; break;
					case ALLEGRO_KEY_S:
						key[DOWN] = 0; break;
					case ALLEGRO_KEY_A:
						key[LEFT] = 0; break;
					case ALLEGRO_KEY_D:
						key[RIGHT] = 0; break;
				}
			}
		yVariation -= key[UP] * protagonist.speed;
		yVariation += key[DOWN] * protagonist.speed;
		xVariation -= key[LEFT] * protagonist.speed;
		xVariation += key[RIGHT] * protagonist.speed;
	}
}