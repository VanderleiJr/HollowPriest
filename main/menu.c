#include "includes.h"

//Inicializadores
void Initializers(){
	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_acodec_addon();
	al_install_audio();
	al_reserve_samples(10);
	al_install_keyboard();
}

void FirstMenu(){
	//Variáveis
	int exit = 0;
	int menu = 0;
	int color = 0;
	int color_variation = 0;
	int menu_positionX = -110;
	int menu_variation = 0;

	//Leitura de Arquivos
	ALLEGRO_DISPLAY *display = al_create_display(WIDTH, HEIGHT);
	ALLEGRO_FONT *title = al_load_ttf_font("../media/fonts/FancyCardText.ttf", (0.1625 * HEIGHT), 0);
	ALLEGRO_FONT *font50 = al_load_ttf_font("../media/fonts/TheNovice.ttf", (0.0625 * HEIGHT), 0);
	ALLEGRO_FONT *footer = al_load_ttf_font("../media/fonts/TheNovice.ttf", (0.01875 * HEIGHT), 0);

	ALLEGRO_SAMPLE *sound_background = al_load_sample("../media/sounds/menuSound.ogg");
	ALLEGRO_SAMPLE_INSTANCE *inst_sound_background = al_create_sample_instance(sound_background);
	al_attach_sample_instance_to_mixer(inst_sound_background, al_get_default_mixer());
	al_set_sample_instance_playmode(inst_sound_background, ALLEGRO_PLAYMODE_LOOP);
	al_set_sample_instance_gain(inst_sound_background, 0.8);

	ALLEGRO_BITMAP *menu_background = al_load_bitmap("../media/sprites/menu_background.jpg");
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
	ALLEGRO_EVENT event;

	//Iniciadores de Eventos
	al_set_window_title(display, "666");
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_start_timer(timer);

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

		al_draw_text(title, COLOR_RED, WIDTH/2, HEIGHT / 2 - (0.1875 * HEIGHT), ALLEGRO_ALIGN_CENTRE, "Hollow Priest");

		al_draw_text(font50, al_map_rgb(color, color, color), WIDTH/2, HEIGHT / 2 + (0.1375 * HEIGHT), ALLEGRO_ALIGN_CENTRE, "Press [ENTER]");
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

		al_draw_text(footer, COLOR_WHITE, WIDTH/2, HEIGHT - (0.025 * HEIGHT), ALLEGRO_ALIGN_CENTRE, "Press [ESC] to exit");
		al_draw_text(footer, COLOR_WHITE, 0, HEIGHT - (0.025 * HEIGHT), 0, "By Vanderlei Junior");

		al_play_sample_instance(inst_sound_background);

		al_flip_display();
		al_wait_for_event(event_queue, &event);

		if(event.type == ALLEGRO_EVENT_KEY_DOWN){
			//ESC para SAIR
			if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
				exit = 1;
			}
			//ENTER para INICIAR
			if(event.keyboard.keycode == ALLEGRO_KEY_ENTER){
				SecondMenu(display, menu_background, title, footer, font50, sound_background, event_queue, timer, &event, inst_sound_background);
			}
		menu = !menu;
		}
	}

	//Finalizadores do Jogo
	al_destroy_font(font50);
	al_destroy_font(footer);
	al_destroy_bitmap(menu_background);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_sample(sound_background);
}

void SecondMenu(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *menu_background, ALLEGRO_FONT *title, ALLEGRO_FONT *footer,
		  		ALLEGRO_FONT *font50, ALLEGRO_SAMPLE *sound_background, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_TIMER *timer,
		  		ALLEGRO_EVENT *event, ALLEGRO_SAMPLE_INSTANCE *inst_sound_background){

	const int numberOptions = 4;
	int selectOption = 0;
	int color = 0;
	int color_variation = 0;

	ALLEGRO_FONT *subtitle = al_load_ttf_font("../media/fonts/FancyCardText.ttf", (0.1375 * HEIGHT), 0);
	ALLEGRO_BITMAP *cursor = al_load_bitmap("../media/sprites/cursor.png");

	ALLEGRO_SAMPLE *shot = al_load_sample("../media/sounds/shot.ogg");
	
	while(true){
		al_draw_bitmap(menu_background, -270, 0, 0);
		al_draw_text(subtitle, al_map_rgb(color, 0, 0), WIDTH / 2, (0.185 * HEIGHT), ALLEGRO_ALIGN_CENTRE, "Hollow Priest");
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
		al_draw_text(font50, COLOR_WHITE, WIDTH / 2, (0.525 * HEIGHT), ALLEGRO_ALIGN_CENTRE, "New Game");
		al_draw_text(font50, COLOR_WHITE, WIDTH / 2, (0.600 * HEIGHT), ALLEGRO_ALIGN_CENTRE, "Last Plays");
		al_draw_text(font50, COLOR_WHITE, WIDTH / 2, (0.675 * HEIGHT), ALLEGRO_ALIGN_CENTRE, "Controls");
		al_draw_text(font50, COLOR_WHITE, WIDTH / 2, (0.750 * HEIGHT), ALLEGRO_ALIGN_CENTRE, "Exit");
		
		al_draw_text(footer, COLOR_WHITE, 0, HEIGHT - (0.025 * HEIGHT), 0, "By Vanderlei Junior");

		switch(selectOption){
			case 0:
				al_draw_bitmap(cursor, WIDTH / 2 - (0.147 * WIDTH), (0.550 * HEIGHT), 0);
				al_draw_bitmap(cursor, WIDTH / 2 + (0.117 * WIDTH), (0.550 * HEIGHT), 0);
				break;
			case 1:
				al_draw_bitmap(cursor, WIDTH / 2 - (0.147 * WIDTH), (0.625 * HEIGHT), 0);
				al_draw_bitmap(cursor, WIDTH / 2 + (0.117 * WIDTH), (0.625 * HEIGHT), 0);
				break;
			case 2:
				al_draw_bitmap(cursor, WIDTH / 2 - (0.147 * WIDTH), (0.700 * HEIGHT), 0);
				al_draw_bitmap(cursor, WIDTH / 2 + (0.117 * WIDTH), (0.700 * HEIGHT), 0);
				break;
			case 3:
				al_draw_bitmap(cursor, WIDTH / 2 - (0.147 * WIDTH), (0.775 * HEIGHT), 0);
				al_draw_bitmap(cursor, WIDTH / 2 + (0.117 * WIDTH), (0.775 * HEIGHT), 0);
				break;
		}

		al_flip_display();
		al_wait_for_event(event_queue, event);
		if(event->type == ALLEGRO_EVENT_KEY_DOWN){
			if(event->keyboard.keycode == ALLEGRO_KEY_ENTER){
				switch(selectOption){
					case 0:
						al_play_sample(shot, 1.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						Game(display, footer, shot, event_queue, timer, event, inst_sound_background);
						al_set_sample(inst_sound_background, sound_background);
						al_set_sample_instance_gain(inst_sound_background, 0.8);
						al_play_sample_instance(inst_sound_background);
						break;
					case 1:
						break;
					case 2:
						al_play_sample(shot, 1.3, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
						Controls(display, footer, subtitle, event_queue, timer, menu_background, event, inst_sound_background);
						break;
					case 3:
						al_destroy_font(subtitle);
						return ;
				}
			}
			switch(event->keyboard.keycode){
				case ALLEGRO_KEY_W:
				case ALLEGRO_KEY_UP:
					selectOption--; break;
				case ALLEGRO_KEY_S:
				case ALLEGRO_KEY_DOWN:
					selectOption++; break;
			}
			if(selectOption >= numberOptions)
				selectOption = 0;
			else if(selectOption < 0)
				selectOption = numberOptions - 1;
		}
	}
}

void Controls(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *footer, ALLEGRO_FONT *subtitle,
			  ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_TIMER *timer, ALLEGRO_BITMAP *menu_background,
			  ALLEGRO_EVENT *event, ALLEGRO_SAMPLE_INSTANCE *inst_sound_background){

	ALLEGRO_FONT *font40 = al_load_ttf_font("../media/fonts/TheNovice.ttf", (0.08 * HEIGHT), 0);
	ALLEGRO_BITMAP *wasd = al_load_bitmap("../media/sprites/controls_wasd.png");
	ALLEGRO_BITMAP *direction = al_load_bitmap("../media/sprites/controls_direction.png");
	ALLEGRO_BITMAP *shift = al_load_bitmap("../media/sprites/controls_shift.png");
	ALLEGRO_BITMAP *change = al_load_bitmap("../media/sprites/controls_qe.png");
	ALLEGRO_BITMAP *drop = al_load_bitmap("../media/sprites/controls_space.png");


	while(true){
		al_wait_for_event(event_queue, event);

		al_draw_bitmap(menu_background, -270, 0, 0);
		al_draw_text(subtitle, COLOR_RED, (0.5 * WIDTH), 0, ALLEGRO_ALIGN_CENTRE, "Controls");
		al_draw_text(font40, COLOR_WHITE, (0.02 * WIDTH), (0.2 * HEIGHT), 0, "Movimentation: ");
		al_draw_scaled_bitmap(wasd, 0, 0, 70, 20, (0.30 * WIDTH), (0.24 * HEIGHT), 280, 80, 0);

		al_draw_text(font40, COLOR_WHITE, (0.6 * WIDTH), (0.2 * HEIGHT), 0, "Run: ");
		al_draw_scaled_bitmap(shift, 0, 0, 50, 20, (0.68 * WIDTH), (0.23 * HEIGHT), 200, 80, 0);

		al_draw_text(font40, COLOR_WHITE, (0.02 * WIDTH), (0.4 * HEIGHT), 0, "Shot: ");
		al_draw_scaled_bitmap(direction, 0, 0, 70, 20, (0.11 * WIDTH), (0.44 * HEIGHT), 280, 80, 0);

		al_draw_text(font40, COLOR_WHITE, (0.02 * WIDTH), (0.6 * HEIGHT), 0, "Change Weapon: ");
		al_draw_scaled_bitmap(change, 0, 0, 50, 20, (0.32 * WIDTH), (0.63 * HEIGHT), 200, 80, 0);

		al_draw_text(font40, COLOR_WHITE, (0.02 * WIDTH), (0.8 * HEIGHT), 0, "Drop Weapon: ");
		al_draw_scaled_bitmap(drop, 0, 0, 60, 20, (0.28 * WIDTH), (0.83 * HEIGHT), 240, 80, 0);
		

		al_draw_text(footer, COLOR_WHITE, 0, HEIGHT - (0.025 * HEIGHT), 0, "Feito por Vanderlei de Brito Junior");
		al_flip_display();
		
		if(event->type == ALLEGRO_EVENT_KEY_DOWN){
			if(event->keyboard.keycode == ALLEGRO_KEY_ENTER || event->keyboard.keycode == ALLEGRO_KEY_ESCAPE){
				al_destroy_font(font40);
				al_destroy_bitmap(wasd);
				al_destroy_bitmap(direction);
				al_destroy_bitmap(shift);
				al_destroy_bitmap(change);
				al_destroy_bitmap(drop);
				return ;
			}
		}
	}

}

void Die(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue,
		 ALLEGRO_TIMER *timer, ALLEGRO_EVENT *event, ALLEGRO_SAMPLE_INSTANCE *inst_sound_background){
	
	int position = 0;
	char first = 'A', second = 'A' , third = 'A';
	char gitgud[20];

	ALLEGRO_FONT *title = al_load_ttf_font("../media/fonts/TheNovice.ttf", 150, 0);
	ALLEGRO_FONT *record = al_load_ttf_font("../media/fonts/TheNovice.ttf", 200, 0);
	ALLEGRO_BITMAP *cursor = al_load_bitmap("../media/sprites/cursor.png");
	ALLEGRO_SAMPLE *gameOver_background = al_load_sample("../media/sounds/gameOverSound.ogg");

	srand(time(NULL));
	switch(rand()%4){
		case 0:
			strcpy(gitgud, "YOU DIED"); break;
		case 1:
			strcpy(gitgud, "SE FUDEU"); break;
		case 2:
			strcpy(gitgud, "FALECEU"); break;
		case 3:
			strcpy(gitgud, "VIROU ESTASTISTICA"); break;
	}

	al_set_sample(inst_sound_background, gameOver_background);
	al_set_sample_instance_gain(inst_sound_background, 0.5);
	al_play_sample_instance(inst_sound_background);

	while(true){
		al_wait_for_event(event_queue, event);
		
		al_draw_filled_rectangle(0, (0.18 * HEIGHT), WIDTH, (0.80 * HEIGHT), COLOR_BLACK);

		al_draw_bitmap(cursor, (0.34 * WIDTH) + (position * (0.15 * WIDTH)), (0.45 * HEIGHT), 0);

		al_draw_text(title, COLOR_WHITE, (0.50 * WIDTH), (0.15 * HEIGHT), ALLEGRO_ALIGN_CENTRE, gitgud);
		al_draw_textf(record, COLOR_WHITE, (0.35 * WIDTH), (0.40 * HEIGHT), ALLEGRO_ALIGN_CENTRE, "%c", first);
		al_draw_textf(record, COLOR_WHITE, (0.50 * WIDTH), (0.40 * HEIGHT), ALLEGRO_ALIGN_CENTRE, "%c", second);
		al_draw_textf(record, COLOR_WHITE, (0.65 * WIDTH), (0.40 * HEIGHT), ALLEGRO_ALIGN_CENTRE, "%c", third);

		al_flip_display();

		if(event->type == ALLEGRO_EVENT_KEY_DOWN){
			if(event->keyboard.keycode == ALLEGRO_KEY_ENTER || event->keyboard.keycode == ALLEGRO_KEY_ESCAPE){
				al_destroy_font(title);
				al_destroy_font(record);
				al_destroy_bitmap(cursor);
				al_destroy_sample(gameOver_background);
				return ;
			}

			switch(event->keyboard.keycode){
				case ALLEGRO_KEY_W:
				case ALLEGRO_KEY_UP:
					switch(position){
						case 0:
							first--;
							if(first < 'A')
								first = 'Z';
							break;
						case 1:
							second--;
							if(second < 'A')
								second = 'Z';
							break;
						case 2:
							third--;
							if(third < 'A')
								third = 'Z';
							break;
					}
				break;
				case ALLEGRO_KEY_S:
				case ALLEGRO_KEY_DOWN:
					switch(position){
						case 0:
							first++; 
							if(first > 'Z')
								first = 'A';
							break;
						case 1:
							second++;
							if(second > 'Z')
								second = 'A';
							break;
						case 2:
							third++;
							if(third > 'Z')
								third = 'A';
							break;
					}
				break;
				case ALLEGRO_KEY_A:
				case ALLEGRO_KEY_LEFT:
					position--;
					if(position < 0)
						position = 2;
					break;
				case ALLEGRO_KEY_D:
				case ALLEGRO_KEY_RIGHT:
					position++;
					if(position > 2)
						position = 0;
					break;
			}
		}
	}
}