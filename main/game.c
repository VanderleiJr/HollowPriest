#include "includes.h"

void Game(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *footer,
		  ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_TIMER *timer,
		  ALLEGRO_EVENT *event){

		int frameCount = 0;
		int lastDirection = 1;
		int xVariation = -16;
		int yVariation = -24;

		float xShot = (0.5 * WIDTH);
		float yShot = (0.9 * HEIGHT);

		int xShotVariation = 0;
		int yShotVariation = 0;
		int shotDistance = 0;
		int shotRotation = 0;

		int key[] = {0, 0, 0, 0};
		int keyShot[] = {0, 0, 0, 0};

		ALLEGRO_FONT *fontScore = al_load_ttf_font("../media/fonts/TheNovice.ttf", (0.05 * HEIGHT), 0);

		character protagonist;
		protagonist.spritesWalking = al_load_bitmap("../media/sprites/walking.png");
		protagonist.weaponEquiped = 0;
		protagonist.life = CHARACTER_MAX_LIFE;
		protagonist.score = 0;

		weaponsList protagonistWeapons;

		typeWeapon bow;
		bow.ID = 0;
		bow.numberAmmo = 1;
		strcpy(bow.name, "BOW");
		bow.sprite = al_load_bitmap("../media/sprites/weapon_bow.png");
		bow.ammo.ID = 0;
		bow.ammo.speed = 10;
		bow.ammo.spriteVertical = al_load_bitmap("../media/sprites/projectile_arrow_0.png");
		bow.ammo.spriteHorizontal = al_load_bitmap("../media/sprites/projectile_arrow_1.png");
		bow.ammo.sprite = bow.ammo.spriteVertical;

		typeWeapon knife;
		knife.ID = 1;
		knife.numberAmmo = 2;
		strcpy(knife.name, "KNIFE");
		knife.sprite = al_load_bitmap("../media/sprites/weapon_bow.png");
		knife.ammo.ID = 1;
		knife.ammo.speed = 15;
		knife.ammo.spriteVertical = al_load_bitmap("../media/sprites/projectile_knife_0.png");
		knife.ammo.spriteHorizontal = al_load_bitmap("../media/sprites/projectile_knife_1.png");
		knife.ammo.sprite = knife.ammo.spriteVertical;


		CreateList(&protagonistWeapons);
		Insertion(&bow, &protagonistWeapons);
		Insertion(&knife, &protagonistWeapons);


		while(true){

			al_clear_to_color(al_map_rgb(130, 130, 130));
			al_wait_for_event(event_queue, event);
			
			al_draw_bitmap_region(protagonist.spritesWalking, (OrBitABit(key)) * frameCount * CHARACTER_FRAME_WIDHT, lastDirection * CHARACTER_FRAME_HEIGHT, CHARACTER_FRAME_WIDHT, CHARACTER_FRAME_HEIGHT, WIDTH/2 + xVariation, HEIGHT/2 + yVariation, 0);
			al_draw_bitmap(Search(protagonist.weaponEquiped, &protagonistWeapons)->ammo.sprite, xShot + xShotVariation, yShot + yShotVariation, shotRotation);

			al_draw_textf(fontScore, COLOR_WHITE, WIDTH / 2, 5, ALLEGRO_ALIGN_CENTRE, "%06d", protagonist.score);
			al_draw_textf(fontScore, COLOR_WHITE, WIDTH - 20, 5, ALLEGRO_ALIGN_RIGHT, "LIFE: %d", protagonist.life);
			al_draw_text(footer, COLOR_WHITE, 0, HEIGHT - (0.025 * HEIGHT), ALLEGRO_ALIGN_LEFT, "Press [ESC] to menu");

			if(keyShot[UP]){
				yShotVariation -= Search(protagonist.weaponEquiped, &protagonistWeapons)->ammo.speed;
				shotDistance++;
				if(shotDistance > SHOT_DISTANCE){
					xShot = (0.5 * WIDTH);
					yShot = (0.9 * HEIGHT);
					keyShot[UP] = 0;
					shotDistance = 0;
					yShotVariation = 0;
				}
			} else if(keyShot[DOWN]){
				yShotVariation += Search(protagonist.weaponEquiped, &protagonistWeapons)->ammo.speed;
				shotDistance++;
				if(shotDistance > SHOT_DISTANCE){
					xShot = (0.5 * WIDTH);
					yShot = (0.9 * HEIGHT);
					keyShot[DOWN] = 0;
					shotDistance = 0;
					yShotVariation = 0;
					shotRotation = 0;
				}
			} else if(keyShot[LEFT]){
				xShotVariation -= Search(protagonist.weaponEquiped, &protagonistWeapons)->ammo.speed;
				shotDistance++;
				if(shotDistance > SHOT_DISTANCE){
					xShot = (0.5 * WIDTH);
					yShot = (0.9 * HEIGHT);
					keyShot[LEFT] = 0;
		 			shotDistance = 0;
					xShotVariation = 0;
					shotRotation = 0;
					Search(protagonist.weaponEquiped, &protagonistWeapons)->ammo.sprite = Search(protagonist.weaponEquiped, &protagonistWeapons)->ammo.spriteVertical;
				}
			} else if(keyShot[RIGHT]){
				xShotVariation += Search(protagonist.weaponEquiped, &protagonistWeapons)->ammo.speed;
				shotDistance++;
				if(shotDistance > SHOT_DISTANCE){
					xShot = (0.5 * WIDTH);
					yShot = (0.9 * HEIGHT);
					keyShot[RIGHT] = 0;
		 			shotDistance = 0;
					xShotVariation = 0;
					Search(protagonist.weaponEquiped, &protagonistWeapons)->ammo.sprite = Search(protagonist.weaponEquiped, &protagonistWeapons)->ammo.spriteVertical;
				}
			}

			al_flip_display();

			if(event->type == ALLEGRO_EVENT_KEY_DOWN){
				if(event->keyboard.keycode == ALLEGRO_KEY_ESCAPE){
					al_destroy_bitmap(protagonist.spritesWalking);
					return ;
				}

				//Movimentação do Personagem
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
						protagonist.life -= 1;
						protagonist.score += 5;
						protagonist.weaponEquiped = !protagonist.weaponEquiped;
				}

				//Ataque do Personagem
				if(!OrBitABit(keyShot)){
					switch(event->keyboard.keycode){
						case ALLEGRO_KEY_UP:
							if(!keyShot[UP]){
								xShot = (WIDTH/2 + xVariation);
								yShot = (HEIGHT/2 + yVariation);
								keyShot[UP] = 1;
							}
							break;
						case ALLEGRO_KEY_DOWN:
							if(!keyShot[DOWN]){
								xShot = (WIDTH/2 + xVariation);
								yShot = (HEIGHT/2 + yVariation) + 20;
								keyShot[DOWN] = 1;
								shotRotation = -1;
							}
							break;
						case ALLEGRO_KEY_LEFT:
							if(!keyShot[LEFT]){
								xShot = (WIDTH/2 + xVariation);
								yShot = (HEIGHT/2 + yVariation) + 20;
								keyShot[LEFT] = 1;
								shotRotation = -1;
								Search(protagonist.weaponEquiped, &protagonistWeapons)->ammo.sprite = Search(protagonist.weaponEquiped, &protagonistWeapons)->ammo.spriteHorizontal;
							}
							break;
						case ALLEGRO_KEY_RIGHT:
							if(!keyShot[RIGHT]){
								xShot = (WIDTH/2 + xVariation);
								yShot = (HEIGHT/2 + yVariation) + 20;
								keyShot[RIGHT] = 1;
								shotRotation = 0;
								Search(protagonist.weaponEquiped, &protagonistWeapons)->ammo.sprite = Search(protagonist.weaponEquiped, &protagonistWeapons)->ammo.spriteHorizontal;
							}
							break;
					}
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

//Função OR entre os elementos de um vetor de INT
int OrBitABit(int key[]){
	if(key[0] || key[1] || key[2] || key[3])
		return 1;
	return 0;
}

//FUNÇÕES DA LISTA

void CreateList(weaponsList *list){
	list->quantity = 0;
	list->first = NULL;
}

int Insertion(typeWeapon *item, weaponsList *list){
	switch(list->quantity){
		case 0:
			list->first = item;
			item->next = item;
			item->previous = item;
			list->quantity++;
			return 0;
		case 1:
			list->first->next = item;
			item->next = list->first;
			item->previous = list->first;
			list->first->previous = item;
			list->quantity++;
			return 0;
		case 2:
			list->first->previous = item;
			item->next = list->first;
			item->previous = list->first->next;
			list->first->next->next = item;
			list->quantity++;
		case 3:
			return -1;
	}
	return 0;
}

typeWeapon * Search(int position, weaponsList *list){
	switch(position){
		case 0:
			return list->first;
		case 1:
			return list->first->next;
		default:
			return list->first->previous;
	}
}
