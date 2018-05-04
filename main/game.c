#include "includes.h"

void Game(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *footer,
		  ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_TIMER *timer,
		  ALLEGRO_EVENT *event){

		int frameCount = 0;
		int lastDirection = 1;
		int activeBoss = 0;
		int lifeBar = 0;
		int staminaBar = 0;

		float xShot = AMMO_POSITION_X;
		float yShot = AMMO_POSITION_Y;

		int xShotVariation = 0;
		int yShotVariation = 0;
		int shotDistance = 0;
		float shotRotation = 0;

		int key[] = {0, 0, 0, 0};
		int keyShot[] = {0, 0, 0, 0};

		ALLEGRO_FONT *fontScore = al_load_ttf_font("../media/fonts/TheNovice.ttf", (0.05 * HEIGHT), 0);
		ALLEGRO_BITMAP *gameFloor = al_load_bitmap("../media/sprites/game_floor.png");
		ALLEGRO_BITMAP *weaponFrame = al_load_bitmap("../media/sprites/weapon_frame.png");
		ALLEGRO_BITMAP *orbs = al_load_bitmap("../media/sprites/orb.png");
		
		srand(time(NULL));

		character protagonist;
		protagonist.score = 0;
		protagonist.speed = 3;
		protagonist.weaponEquiped = 0;
		protagonist.life = CHARACTER_MAX_LIFE;
		protagonist.stamina = CHARACTER_MAX_STAMINA;
		protagonist.firstPositionX = (WIDTH / 2) - (CHARACTER_FRAME_WIDHT / 2);
		protagonist.firstPositionY = (HEIGHT / 2) - (CHARACTER_FRAME_HEIGHT / 2);
		protagonist.secondPositionX = protagonist.firstPositionX + CHARACTER_FRAME_WIDHT;
		protagonist.secondPositionY = protagonist.firstPositionY + CHARACTER_FRAME_HEIGHT;
		protagonist.spritesWalking = al_load_bitmap("../media/sprites/walking.png");

		//Lista de Armas
		typeWeapon bow;
		strcpy(bow.name, "BOW");
		bow.ID = 0;
		bow.ammo.speed = 12;
		bow.ammo.damage = 2.6;
		bow.ammo.distance = 35;
		bow.ammo.sprite = al_load_bitmap("../media/sprites/projectile_arrow_0.png");

		typeWeapon knife;
		strcpy(knife.name, "KNIFE");
		knife.ID = 1;
		knife.ammo.speed = 15;
		knife.ammo.damage = 1.8;
		knife.ammo.distance = 40;
		knife.ammo.sprite = al_load_bitmap("../media/sprites/projectile_knife_0.png");

		typeWeapon lance;
		strcpy(lance.name, "LANCE");
		lance.ID = 2;
		lance.ammo.speed = 10;
		lance.ammo.damage = 3.8;
		lance.ammo.distance = 50;
		lance.ammo.sprite = al_load_bitmap("../media/sprites/projectile_lance_0.png");

		typeWeapon shuriken;
		strcpy(lance.name, "SHURIKEN");
		shuriken.ID = 3;
		shuriken.ammo.speed = 20;
		shuriken.ammo.damage = 1.2;
		shuriken.ammo.distance = 25;
		shuriken.ammo.rotationSpeed = 0.5;
		shuriken.ammo.sprite = al_load_bitmap("../media/sprites/projectile_shuriken_0.png");

		typeWeapon axe;
		strcpy(lance.name, "AXE");
		axe.ID = 4;
		axe.ammo.speed = 8;
		axe.ammo.damage = 4.2;
		axe.ammo.distance = 50;
		axe.ammo.rotationSpeed = 0.2;
		axe.ammo.sprite = al_load_bitmap("../media/sprites/projectile_axe_0.png");

		//Lista de Boss
		typeBoss demon;
		strcpy(demon.name, "DEMON");
		demon.totalLife = 150;
		demon.life = demon.totalLife;
		demon.speed = 1;
		demon.damage = 0.2;
		demon.frameWidht = 128;
		demon.frameHeight = 128;
		demon.firstPositionX = 0.8 * WIDTH;
		demon.firstPositionY = 0.4 * HEIGHT;
		demon.secondPositionX = demon.firstPositionX + demon.frameWidht;
		demon.secondPositionY = demon.firstPositionY + demon.frameHeight;

		typeBoss behemoth;
		strcpy(behemoth.name, "BEHEMOTH");
		behemoth.totalLife = 300;
		behemoth.life = behemoth.totalLife;
		behemoth.speed = 1;
		behemoth.damage = 0.5;
		behemoth.frameWidht = 256;
		behemoth.frameHeight = 256;
		behemoth.firstPositionX = 0.8 * WIDTH;
		behemoth.firstPositionY = 0.4 * HEIGHT;
		behemoth.secondPositionX = behemoth.firstPositionX + behemoth.frameWidht;
		behemoth.secondPositionY = behemoth.firstPositionY + behemoth.frameHeight;

		typeBoss bat;
		strcpy(bat.name, "BAT");
		bat.totalLife = 25;
		bat.life = bat.totalLife;
		bat.speed = 3;
		bat.damage = 0.01;
		bat.frameWidht = 32;
		bat.frameHeight = 32;
		bat.firstPositionX = 0.8 * WIDTH;
		bat.firstPositionY = 0.4 * HEIGHT;
		bat.secondPositionX = bat.firstPositionX + bat.frameWidht;
		bat.secondPositionY = bat.firstPositionY + bat.frameHeight;

		//Inicializa a lista com TODAS AS ARMAS
		weaponsList allWeapons;
		CreateListWeapons(&allWeapons);

		LoadWeapon(&bow, &allWeapons);
		LoadWeapon(&knife, &allWeapons);
		LoadWeapon(&lance, &allWeapons);
		LoadWeapon(&shuriken, &allWeapons);
		LoadWeapon(&axe, &allWeapons);

		//Inicializa a lista com TODOS OS BOSS
		bossesList allBosses;
		CreateListBosses(&allBosses);

		LoadBoss(&demon, &allBosses);
		LoadBoss(&behemoth, &allBosses);
		LoadBoss(&bat, &allBosses);

		//Inicializa a lista de armas do personagem
		CreateListWeapons(&protagonist.weapons);
		InsertionWeapon(SearchByID((rand() % 5), &allWeapons), &protagonist.weapons);

		while(true){

			al_draw_bitmap(gameFloor, 0, 0, 0);
			al_wait_for_event(event_queue, event);
			
			al_draw_bitmap_region(protagonist.spritesWalking, (OrBitABit(key)) * frameCount * CHARACTER_FRAME_WIDHT, lastDirection * CHARACTER_FRAME_HEIGHT, CHARACTER_FRAME_WIDHT, CHARACTER_FRAME_HEIGHT, protagonist.firstPositionX, protagonist.firstPositionY, 0);
			al_draw_bitmap(weaponFrame, (WIDTH * 0.464), (HEIGHT * 0.85), 0);
			al_draw_rotated_bitmap(Search(protagonist.weaponEquiped, &protagonist.weapons)->ammo.sprite, 25, 31.5, xShot + xShotVariation, yShot + yShotVariation, shotRotation, 0);
			
			al_draw_bitmap_region(orbs, lifeBar, 0, 194, 162, WIDTH - 194, HEIGHT - 162, 0);
			al_draw_bitmap_region(orbs, staminaBar, 162, 194, 162, 0, HEIGHT - 162, 0);

			//Hitboxs
			//al_draw_rectangle(protagonist.firstPositionX, protagonist.firstPositionY, protagonist.secondPositionX, protagonist.secondPositionY, COLOR_WHITE, 0);
			//al_draw_rectangle(xShot + xShotVariation - 10, yShot + yShotVariation - 15, xShot + xShotVariation + 10, yShot + yShotVariation + 15, COLOR_WHITE, 0);
			al_draw_rectangle(allBosses.bosses[activeBoss].firstPositionX, allBosses.bosses[activeBoss].firstPositionY, allBosses.bosses[activeBoss].secondPositionX, allBosses.bosses[activeBoss].secondPositionY, COLOR_WHITE, 0);

			al_draw_textf(fontScore, COLOR_WHITE, WIDTH / 2, 5, ALLEGRO_ALIGN_CENTRE, "%06d", protagonist.score);
			al_draw_textf(fontScore, COLOR_GREEN, 100, HEIGHT - 100, ALLEGRO_ALIGN_CENTRE, "%.0f", protagonist.stamina);
			al_draw_textf(fontScore, COLOR_RED, WIDTH - 100, HEIGHT - 100, ALLEGRO_ALIGN_CENTRE, "%.0f", protagonist.life);
			al_draw_textf(fontScore, COLOR_WHITE, WIDTH - 20, 40, ALLEGRO_ALIGN_RIGHT, "BOSS: %d", allBosses.bosses[activeBoss].life);
			al_draw_text(footer, COLOR_WHITE, WIDTH / 2, 0, ALLEGRO_ALIGN_CENTRE, "Press [ESC] to DIE");
			
			if(keyShot[UP]){
				yShotVariation -= Search(protagonist.weaponEquiped, &protagonist.weapons)->ammo.speed;
				shotDistance++;
				if(shotDistance > Search(protagonist.weaponEquiped, &protagonist.weapons)->ammo.distance){
					xShot = AMMO_POSITION_X;
					yShot = AMMO_POSITION_Y;
					keyShot[UP] = 0;
					shotDistance = 0;
					yShotVariation = 0;
					shotRotation = 0;
				}
			} else if(keyShot[DOWN]){
				yShotVariation += Search(protagonist.weaponEquiped, &protagonist.weapons)->ammo.speed;
				shotDistance++;
				if(shotDistance > Search(protagonist.weaponEquiped, &protagonist.weapons)->ammo.distance){
					xShot = AMMO_POSITION_X;
					yShot = AMMO_POSITION_Y;
					keyShot[DOWN] = 0;
					shotDistance = 0;
					yShotVariation = 0;
					shotRotation = 0;
				}
			} else if(keyShot[LEFT]){
				xShotVariation -= Search(protagonist.weaponEquiped, &protagonist.weapons)->ammo.speed;
				shotDistance++;
				if(shotDistance > Search(protagonist.weaponEquiped, &protagonist.weapons)->ammo.distance){
					xShot = AMMO_POSITION_X;
					yShot = AMMO_POSITION_Y;
					keyShot[LEFT] = 0;
		 			shotDistance = 0;
					xShotVariation = 0;
					shotRotation = 0;
				}
			} else if(keyShot[RIGHT]){
				xShotVariation += Search(protagonist.weaponEquiped, &protagonist.weapons)->ammo.speed;
				shotDistance++;
				if(shotDistance > Search(protagonist.weaponEquiped, &protagonist.weapons)->ammo.distance){
					xShot = AMMO_POSITION_X;
					yShot = AMMO_POSITION_Y;
					keyShot[RIGHT] = 0;
		 			shotDistance = 0;
					xShotVariation = 0;
					shotRotation = 0;	
				}
			}

			lifeBar = (10 - (int)(protagonist.life / 10)) * 194;
			if(protagonist.life > 100)
				lifeBar = 0;
			staminaBar = (10 - (int)(protagonist.stamina / 10)) * 194;

			if(OrBitABit(keyShot) && Search(protagonist.weaponEquiped, &protagonist.weapons)->ID >= 3){
				shotRotation += Search(protagonist.weaponEquiped, &protagonist.weapons)->ammo.rotationSpeed;
			}

			al_flip_display();

			if(event->type == ALLEGRO_EVENT_KEY_DOWN){
				if(event->keyboard.keycode == ALLEGRO_KEY_ESCAPE){
					al_destroy_bitmap(protagonist.spritesWalking);
					al_destroy_bitmap(gameFloor);
					al_destroy_bitmap(weaponFrame);
					//al_destroy_bitmap(demon.sprite);
					//al_destroy_bitmap(behemoth.sprite);
					//al_destroy_bitmap(bat.sprite);
					al_destroy_bitmap(bow.ammo.sprite);
					al_destroy_bitmap(knife.ammo.sprite);
					al_destroy_bitmap(lance.ammo.sprite);
					al_destroy_bitmap(shuriken.ammo.sprite);
					al_destroy_bitmap(axe.ammo.sprite);
					al_destroy_font(fontScore);
					return ;
				}

				//Movimentação do Personagem
				switch(event->keyboard.keycode){
					case ALLEGRO_KEY_LSHIFT:
						if(protagonist.stamina >= 5)
							protagonist.speed += 4;
						break;
					case ALLEGRO_KEY_W:
						key[UP] = 1; break;
					case ALLEGRO_KEY_S:
						key[DOWN] = 1; break;
					case ALLEGRO_KEY_A:
						key[LEFT] = 1; break;
					case ALLEGRO_KEY_D:
						key[RIGHT] = 1; break;
					case ALLEGRO_KEY_B:
						if(!OrBitABit(keyShot))
							protagonist.weaponEquiped++;
						if(protagonist.weaponEquiped >= protagonist.weapons.quantity)
							protagonist.weaponEquiped = 0;
						break;
					case ALLEGRO_KEY_V:
						if(RemoveWeapon(protagonist.weaponEquiped, &protagonist.weapons))
							protagonist.weaponEquiped = 0;
						break;
				}

				//Ataque do Personagem
				if(!OrBitABit(keyShot)){
					switch(event->keyboard.keycode){
						case ALLEGRO_KEY_UP:
							if(!keyShot[UP]){
								xShot = protagonist.firstPositionX + 24;
								yShot = protagonist.firstPositionY + 36;
								keyShot[UP] = 1;
								shotRotation = 0;
							}
							break;
						case ALLEGRO_KEY_DOWN:
							if(!keyShot[DOWN]){
								xShot = protagonist.firstPositionX + 24;
								yShot = protagonist.firstPositionY + 56;
								keyShot[DOWN] = 1;
								shotRotation = 3.14;
							}
							break;
						case ALLEGRO_KEY_LEFT:
							if(!keyShot[LEFT]){
								xShot = protagonist.firstPositionX + 24;
								yShot = protagonist.firstPositionY + 46;
								keyShot[LEFT] = 1;
								shotRotation = 4.71;
							}
							break;
						case ALLEGRO_KEY_RIGHT:
							if(!keyShot[RIGHT]){
								xShot = protagonist.firstPositionX + 24;
								yShot = protagonist.firstPositionY + 46;
								keyShot[RIGHT] = 1;
								shotRotation = 1.57;
							}
							break;
					}
				}
			}


			if(event->type == ALLEGRO_EVENT_KEY_UP){
				switch(event->keyboard.keycode){
					case ALLEGRO_KEY_LSHIFT:
						protagonist.speed = 2;
						break;
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

			//Contador de Frame para animações do personagem
			if(frameCount++ % FPS >= 8)
				frameCount = 1;

			//Perca de Vida por Colisão
			if(ColisionCharacterBoss(&protagonist, &allBosses.bosses[activeBoss]))
				protagonist.life -= allBosses.bosses[activeBoss].damage;

			//Perca de Vida do Boss
			if(ColisionRectangle(xShot + xShotVariation - 10, yShot + yShotVariation - 15, xShot + xShotVariation + 10, yShot + yShotVariation + 15, &allBosses.bosses[activeBoss]))
				if(OrBitABit(keyShot))
					allBosses.bosses[activeBoss].life -= Search(protagonist.weaponEquiped, &protagonist.weapons)->ammo.damage;

			//Decremento Gradual de Stamina
			if(protagonist.speed >= 5 && OrBitABit(key)){
				protagonist.stamina -= 0.4;
				if(protagonist.stamina <= 1){
					protagonist.speed = 2;
				}
			}

			//Aumento Gradual de Stamina
			if(protagonist.stamina <= 100){
				if(!OrBitABit(key))
					protagonist.stamina += 0.15;
				else
					protagonist.stamina += 0.05;
			}

			//Movimentação do Personagem
			protagonist.firstPositionY -= key[UP] 	 * protagonist.speed;
			protagonist.firstPositionY += key[DOWN]  * protagonist.speed;
			protagonist.firstPositionX -= key[LEFT]  * protagonist.speed;
			protagonist.firstPositionX += key[RIGHT] * protagonist.speed;

			protagonist.secondPositionY -= key[UP] 	  * protagonist.speed;
			protagonist.secondPositionY += key[DOWN]  * protagonist.speed;
			protagonist.secondPositionX -= key[LEFT]  * protagonist.speed;
			protagonist.secondPositionX += key[RIGHT] * protagonist.speed;
			LastKey(key, &lastDirection);

			//Condição de Morte do Personagem
			if(protagonist.life <= 0){
				Die(display, event_queue, timer, event);
				return ;
			}

			//Movimentação do boss
			if((allBosses.bosses[activeBoss].firstPositionX + allBosses.bosses[activeBoss].secondPositionX) / 2 > (protagonist.firstPositionX + protagonist.secondPositionX) / 2){
				allBosses.bosses[activeBoss].firstPositionX -= allBosses.bosses[activeBoss].speed;
				allBosses.bosses[activeBoss].secondPositionX -= allBosses.bosses[activeBoss].speed;
			} else {
				allBosses.bosses[activeBoss].firstPositionX += allBosses.bosses[activeBoss].speed;
				allBosses.bosses[activeBoss].secondPositionX += allBosses.bosses[activeBoss].speed;
			}
			if((allBosses.bosses[activeBoss].firstPositionY + allBosses.bosses[activeBoss].secondPositionY) / 2 > (protagonist.firstPositionY + protagonist.secondPositionY) / 2){
				allBosses.bosses[activeBoss].firstPositionY -= allBosses.bosses[activeBoss].speed;
				allBosses.bosses[activeBoss].secondPositionY -= allBosses.bosses[activeBoss].speed;
			} else {
				allBosses.bosses[activeBoss].firstPositionY += allBosses.bosses[activeBoss].speed;
				allBosses.bosses[activeBoss].secondPositionY += allBosses.bosses[activeBoss].speed;
			}

			//Condição de Morte do Boss
			if(allBosses.bosses[activeBoss].life <= 0){
				protagonist.score += allBosses.bosses[activeBoss].totalLife;
				DeadBoss(activeBoss, &allBosses);
				InsertionWeapon(SearchByID((rand() % 5), &allWeapons), &protagonist.weapons);
				activeBoss++;
				if(activeBoss >= allBosses.quantity){
					protagonist.life += 25;
					activeBoss = 0;
				}
			}

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
