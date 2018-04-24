#include "includes.h"

void Game(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *footer,
		  ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_TIMER *timer,
		  ALLEGRO_EVENT *event){

		int frameCount = 0;
		int lastDirection = 1;
		int xVariation = -20;
		int yVariation = -20;
		int key[] = {0, 0, 0, 0};


		ALLEGRO_FONT *fontScore = al_load_ttf_font("../media/fonts/TheNovice.ttf", (0.05 * HEIGHT), 0);

		character protagonist;
		protagonist.spritesWalking = al_load_bitmap("../media/sprites/walking.png");
		protagonist.life = CHARACTER_MAX_LIFE;
		protagonist.score = 0;


		weaponsList weapons;

		while(true){

			al_clear_to_color(al_map_rgb(130, 130, 130));
			al_wait_for_event(event_queue, event);
			al_draw_bitmap_region(protagonist.spritesWalking, (key[0] || key[1] || key[2] || key[3]) * frameCount * CHARACTER_FRAME_WIDHT, lastDirection * CHARACTER_FRAME_HEIGHT, CHARACTER_FRAME_WIDHT, CHARACTER_FRAME_HEIGHT, WIDTH/2 + xVariation, HEIGHT/2 + yVariation, 0);
			al_draw_textf(fontScore, COLOR_WHITE, 20, 5, 0, "SCORE: %d", protagonist.score);
			al_draw_textf(fontScore, COLOR_WHITE, WIDTH - 20, 5, ALLEGRO_ALIGN_RIGHT, "LIFE: %d", protagonist.life);
			al_draw_text(footer, COLOR_WHITE, 0, HEIGHT - (0.025 * HEIGHT), ALLEGRO_ALIGN_LEFT, "Press [ESC] to menu");
			al_flip_display();

			if(event->type == ALLEGRO_EVENT_KEY_DOWN){
				if(event->keyboard.keycode == ALLEGRO_KEY_ESCAPE){
					al_destroy_bitmap(protagonist.spritesWalking);
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
					case ALLEGRO_KEY_B:
						protagonist.life -= 10;
						protagonist.score += 5;
						break;
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
			if(frameCount++ % FPS >= 8)
				frameCount = 1;

			yVariation -= key[UP] * CHARACTER_SPEED;
			yVariation += key[DOWN] * CHARACTER_SPEED;
			xVariation -= key[LEFT] * CHARACTER_SPEED;
			xVariation += key[RIGHT] * CHARACTER_SPEED;

			LastKey(key, &lastDirection);
	}
}

//Função de Direção dos Sprites
void LastKey(int key[], int *lastDirection){
	if(key[0] == 1)
		*lastDirection = 0;
	if(key[1] == 1)
		*lastDirection = 1;
	if(key[2] == 1)
		*lastDirection = 2;
	if(key[3] == 1)
		*lastDirection = 3;
}