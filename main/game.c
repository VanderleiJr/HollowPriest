#include "game.h"

//Inicializadores
void Initializers(){
	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_install_keyboard();
}

void ResetPosition(int *xVariation, int *yVariation){
	*xVariation = -20;
	*yVariation = -20;
}

void Game(){
	//Variáveis
	int exit = 0;
	int menu = 0;
	int color = 0;
	int color_variation = 0;
	int menu_positionX = -110;
	int menu_variation = 0;
	int xVariation = -20;
	int yVariation = -20;
	int key[] = {0, 0, 0, 0};

	//Leitura de Arquivos
	ALLEGRO_DISPLAY *display = al_create_display(WIDTH, HEIGHT);
	ALLEGRO_FONT *title = al_load_ttf_font("../media/fonts/FancyCardText.ttf", 130, 0);
	ALLEGRO_FONT *font50 = al_load_ttf_font("../media/fonts/TheNovice.ttf", 50, 0);
	ALLEGRO_FONT *footer = al_load_ttf_font("../media/fonts/TheNovice.ttf", 15, 0);
	ALLEGRO_BITMAP *character = al_load_bitmap("../media/sprites/character.png");
	ALLEGRO_BITMAP *menu_background = al_load_bitmap("../media/sprites/menu_background.jpg");
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
	ALLEGRO_EVENT event;

	//Iniciadores de Eventos
	al_set_window_title(display, "666");
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_start_timer(timer);

	//Criação do Menu
	while(!exit){
		//al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_bitmap(menu_background, menu_positionX, 0, 0);
		if(!menu_variation){
			if(--menu_positionX <= -400)
				menu_variation = !menu_variation;
		} else {
			if(++menu_positionX >= -110)
				menu_variation = !menu_variation;
		}

		al_draw_text(title, al_map_rgb(255, 0, 0), WIDTH/2, HEIGHT / 2 - 150, ALLEGRO_ALIGN_CENTRE, "Hollow Priest");

		al_draw_text(font50, al_map_rgb(color, color, color), WIDTH/2, HEIGHT / 2 + 110, ALLEGRO_ALIGN_CENTRE, "Press [ENTER]");
		if(!color_variation){
			color+=5;
			if(color == 255){
				color_variation = !color_variation;
			}
		} else {
			color-=5;
			if(color == 0){
				color_variation = !color_variation;
			}
		}

		al_draw_text(footer, COLOR_WHITE, WIDTH/2, HEIGHT - 20, ALLEGRO_ALIGN_CENTRE, "Press [ESC] to exit");
		al_draw_text(footer, COLOR_WHITE, 0, HEIGHT - 20, 0, "By Vanderlei Junior");
		al_flip_display();
		al_wait_for_event(event_queue, &event);

		if(event.type == ALLEGRO_EVENT_KEY_DOWN){
			//ESC para SAIR
			if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
				exit = 1;
			}
			//ENTER para INICIAR
			if(event.keyboard.keycode == ALLEGRO_KEY_ENTER){
				while(!menu){

					al_clear_to_color(al_map_rgb(130, 130, 130));
					al_draw_bitmap(character, WIDTH/2 + xVariation, HEIGHT/2 + yVariation, 0);
					al_draw_text(footer, COLOR_WHITE, 0, HEIGHT - 20, ALLEGRO_ALIGN_LEFT, "Press [ESC] to menu");
					al_flip_display();

					ALLEGRO_EVENT event;
					al_wait_for_event(event_queue, &event);
					if(event.type == ALLEGRO_EVENT_KEY_DOWN){
						if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
							menu = !menu;
						}
						switch(event.keyboard.keycode){
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
					if(event.type == ALLEGRO_EVENT_KEY_UP){
						switch(event.keyboard.keycode){
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
				yVariation -= key[UP] * SPEED;
				yVariation += key[DOWN] * SPEED;
				xVariation -= key[LEFT] * SPEED;
				xVariation += key[RIGHT] * SPEED;
				}
			}
		menu = !menu;
		ResetPosition(&xVariation, &yVariation);
		}
	}

	//Finalizadores do Jogo
	al_destroy_font(title);
	al_destroy_font(font50);
	al_destroy_font(footer);
	al_destroy_bitmap(menu_background);
	al_destroy_bitmap(character);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);
}


