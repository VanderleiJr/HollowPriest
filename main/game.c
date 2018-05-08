#include "includes.h"

void Game(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *footer,
		  ALLEGRO_SAMPLE *shot, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_TIMER *timer,
		  ALLEGRO_EVENT *event, ALLEGRO_SAMPLE_INSTANCE *inst_sound_background){

		int auxFrameCount = 0;
		int frameCount = 0;
		int lastDirection = 1;
		int activeBoss = 0;
		int lifeBar = 0;
		int staminaBar = 0;
		int rotatedBoss = 0;

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

		ALLEGRO_SAMPLE *game_background = al_load_sample("../media/sounds/gameSound.ogg");
		
		srand(time(NULL));

		character protagonist;
		protagonist.score = 0;
		protagonist.speed = 3;
		protagonist.weaponEquiped = 1;
		protagonist.life = CHARACTER_MAX_LIFE;
		protagonist.stamina = CHARACTER_MAX_STAMINA;
		protagonist.firstPositionX = (WIDTH / 2) - (CHARACTER_FRAME_WIDTH / 2);
		protagonist.firstPositionY = (HEIGHT / 2) - (CHARACTER_FRAME_HEIGHT / 2);
		protagonist.secondPositionX = protagonist.firstPositionX + CHARACTER_FRAME_WIDTH;
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
		typeBoss bat;
		strcpy(bat.name, "BAT");
		bat.totalLife = 25;
		bat.life = bat.totalLife;
		bat.speed = 2.1;
		bat.damage = 0.1;
		bat.frameWidht = 55;
		bat.frameHeight = 55;
		bat.firstPositionX = 0.8 * WIDTH;
		bat.firstPositionY = 0.4 * HEIGHT;
		bat.secondPositionX = bat.firstPositionX + bat.frameWidht;
		bat.secondPositionY = bat.firstPositionY + bat.frameHeight;
		bat.sprite = al_load_bitmap("../media/sprites/bat.png");

		typeBoss javali;
		strcpy(javali.name, "JAVALI");
		javali.totalLife = 150;
		javali.life = javali.totalLife;
		javali.speed = 1.8;
		javali.damage = 0.2;
		javali.frameWidht = 100;
		javali.frameHeight = 68;
		javali.firstPositionX = 0.8 * WIDTH;
		javali.firstPositionY = 0.4 * HEIGHT;
		javali.secondPositionX = javali.firstPositionX + javali.frameWidht;
		javali.secondPositionY = javali.firstPositionY + javali.frameHeight;
		javali.sprite = al_load_bitmap("../media/sprites/javali.png");
		
		typeBoss demon;
		strcpy(demon.name, "DEMON");
		demon.totalLife = 300;
		demon.life = demon.totalLife;
		demon.speed = 1.0;
		demon.damage = 0.3;
		demon.frameWidht = 100;
		demon.frameHeight = 100;
		demon.firstPositionX = 0.8 * WIDTH;
		demon.firstPositionY = 0.4 * HEIGHT;
		demon.secondPositionX = demon.firstPositionX + demon.frameWidht;
		demon.secondPositionY = demon.firstPositionY + demon.frameHeight;
		demon.sprite = al_load_bitmap("../media/sprites/demon.png");

		typeBoss fireSkull;
		strcpy(fireSkull.name, "FIRE SKULL");
		fireSkull.totalLife = 450;
		fireSkull.life = fireSkull.totalLife;
		fireSkull.speed = 1.5;
		fireSkull.damage = 0.4;
		fireSkull.frameWidht = 200;
		fireSkull.frameHeight = 100;
		fireSkull.firstPositionX = 0.8 * WIDTH;
		fireSkull.firstPositionY = 0.4 * HEIGHT;
		fireSkull.secondPositionX = fireSkull.firstPositionX + fireSkull.frameWidht;
		fireSkull.secondPositionY = fireSkull.firstPositionY + fireSkull.frameHeight;
		fireSkull.sprite = al_load_bitmap("../media/sprites/fireskull.png");

		typeBoss darknessLord;
		strcpy(darknessLord.name, "DARKNESS LORD");
		darknessLord.totalLife = 600;
		darknessLord.life = darknessLord.totalLife;
		darknessLord.speed = 1.0;
		darknessLord.damage = 0.6;
		darknessLord.frameWidht = 300;
		darknessLord.frameHeight = 300;
		darknessLord.firstPositionX = 0.8 * WIDTH;
		darknessLord.firstPositionY = 0.4 * HEIGHT;
		darknessLord.secondPositionX = darknessLord.firstPositionX + darknessLord.frameWidht;
		darknessLord.secondPositionY = darknessLord.firstPositionY + darknessLord.frameHeight;
		darknessLord.sprite = al_load_bitmap("../media/sprites/darkness.png");

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

		LoadBoss(&bat, &allBosses);
		LoadBoss(&javali, &allBosses);
		LoadBoss(&demon, &allBosses);
		LoadBoss(&fireSkull, &allBosses);
		LoadBoss(&darknessLord, &allBosses);

		//Inicializa a lista de armas do personagem
		CreateListWeapons(&protagonist.weapons);
		InsertionWeapon(SearchByID((rand() % 5), &allWeapons), &protagonist.weapons);

		al_set_sample(inst_sound_background, game_background);
		al_set_sample_instance_gain(inst_sound_background, 0.5);
		al_play_sample_instance(inst_sound_background);


		while(true){

			al_draw_bitmap(gameFloor, 0, 0, 0);
			al_wait_for_event(event_queue, event);
			
			al_draw_bitmap_region(allBosses.bosses[activeBoss].sprite, (frameCount * allBosses.bosses[activeBoss].frameWidht), 0, allBosses.bosses[activeBoss].frameWidht, allBosses.bosses[activeBoss].frameHeight, allBosses.bosses[activeBoss].firstPositionX, allBosses.bosses[activeBoss].firstPositionY, (rotatedBoss * ALLEGRO_FLIP_HORIZONTAL));
			al_draw_bitmap_region(protagonist.spritesWalking, (OrBitABit(key)) * frameCount * CHARACTER_FRAME_WIDTH, lastDirection * CHARACTER_FRAME_HEIGHT, CHARACTER_FRAME_WIDTH, CHARACTER_FRAME_HEIGHT, protagonist.firstPositionX, protagonist.firstPositionY, 0);
			al_draw_bitmap(weaponFrame, (WIDTH * 0.429), (HEIGHT * 0.85), 0);
			al_draw_rotated_bitmap(Search(protagonist.weaponEquiped, &protagonist.weapons)->ammo.sprite, 25, 31.5, xShot + xShotVariation, yShot + yShotVariation, shotRotation, 0);
			al_draw_scaled_bitmap(Search(protagonist.weaponEquiped, &protagonist.weapons)->next->ammo.sprite, 0, 0, 50, 63, (WIDTH * 0.435), (HEIGHT * 0.855) ,33.3, 42, 0);
			al_draw_scaled_bitmap(Search(protagonist.weaponEquiped, &protagonist.weapons)->previous->ammo.sprite, 0, 0, 50, 63, (WIDTH * 0.54), (HEIGHT * 0.855) ,33.3, 42, 0);


			al_draw_bitmap_region(orbs, lifeBar, 0, 194, 162, WIDTH - 194, HEIGHT - 162, 0);
			al_draw_bitmap_region(orbs, staminaBar, 162, 194, 162, 0, HEIGHT - 162, 0);

			//Hitboxs
			//al_draw_rectangle(protagonist.firstPositionX, protagonist.firstPositionY, protagonist.secondPositionX, protagonist.secondPositionY, COLOR_WHITE, 0);
			//al_draw_rectangle(xShot + xShotVariation - 10, yShot + yShotVariation - 15, xShot + xShotVariation + 10, yShot + yShotVariation + 15, COLOR_WHITE, 0);
			//al_draw_rectangle(allBosses.bosses[activeBoss].firstPositionX, allBosses.bosses[activeBoss].firstPositionY, allBosses.bosses[activeBoss].secondPositionX, allBosses.bosses[activeBoss].secondPositionY, COLOR_WHITE, 0);

			al_draw_textf(fontScore, COLOR_WHITE, WIDTH / 2, 5, ALLEGRO_ALIGN_CENTRE, "%06d", protagonist.score);
			al_draw_textf(fontScore, COLOR_GREEN, 100, HEIGHT - 100, ALLEGRO_ALIGN_CENTRE, "%.0f", protagonist.stamina);
			al_draw_textf(fontScore, COLOR_RED, WIDTH - 100, HEIGHT - 100, ALLEGRO_ALIGN_CENTRE, "%.0f", protagonist.life);
			al_draw_textf(fontScore, COLOR_WHITE, WIDTH - 20, 0, ALLEGRO_ALIGN_RIGHT, "BOSS: %s", allBosses.bosses[activeBoss].name);
			al_draw_textf(fontScore, COLOR_WHITE, WIDTH - 20, 40, ALLEGRO_ALIGN_RIGHT, "LIFE: %d", allBosses.bosses[activeBoss].life);
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
					Die(display, event_queue, protagonist.score, timer, event, inst_sound_background);
					al_destroy_bitmap(protagonist.spritesWalking);
					al_destroy_bitmap(gameFloor);
					al_destroy_bitmap(weaponFrame);
					al_destroy_bitmap(orbs);
					al_destroy_bitmap(bat.sprite);
					al_destroy_bitmap(javali.sprite);
					al_destroy_bitmap(demon.sprite);
					al_destroy_bitmap(fireSkull.sprite);
					al_destroy_bitmap(bow.ammo.sprite);
					al_destroy_bitmap(knife.ammo.sprite);
					al_destroy_bitmap(lance.ammo.sprite);
					al_destroy_bitmap(shuriken.ammo.sprite);
					al_destroy_bitmap(axe.ammo.sprite);
					al_destroy_font(fontScore);
					al_destroy_sample(game_background);
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
					case ALLEGRO_KEY_Q:
						if(!OrBitABit(keyShot))
							protagonist.weaponEquiped++;
						if(protagonist.weaponEquiped > protagonist.weapons.quantity)
							protagonist.weaponEquiped = 1;
						break;
					case ALLEGRO_KEY_E:
						if(!OrBitABit(keyShot))
							protagonist.weaponEquiped--;
						if(protagonist.weaponEquiped <= 0)
							protagonist.weaponEquiped = protagonist.weapons.quantity;
						break;
					case ALLEGRO_KEY_SPACE:
						if(!OrBitABit(keyShot))
							if(RemoveWeapon(protagonist.weaponEquiped, &protagonist.weapons))
								protagonist.weaponEquiped = 1;
						break;
				}

				//Ataque do Personagem
				if(!OrBitABit(keyShot)){
					switch(event->keyboard.keycode){
						case ALLEGRO_KEY_UP:
							if(!keyShot[UP]){
								al_play_sample(shot, 1.1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
								xShot = protagonist.firstPositionX + 24;
								yShot = protagonist.firstPositionY + 36;
								keyShot[UP] = 1;
								shotRotation = 0;
							}
							break;
						case ALLEGRO_KEY_DOWN:
							if(!keyShot[DOWN]){
								al_play_sample(shot, 1.1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
								xShot = protagonist.firstPositionX + 24;
								yShot = protagonist.firstPositionY + 56;
								keyShot[DOWN] = 1;
								shotRotation = 3.14;
							}
							break;
						case ALLEGRO_KEY_LEFT:
							if(!keyShot[LEFT]){
								al_play_sample(shot, 1.1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
								xShot = protagonist.firstPositionX + 24;
								yShot = protagonist.firstPositionY + 46;
								keyShot[LEFT] = 1;
								shotRotation = 4.71;
							}
							break;
						case ALLEGRO_KEY_RIGHT:
							if(!keyShot[RIGHT]){
								al_play_sample(shot, 1.1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
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
			frameCount = ++auxFrameCount / 3;
			if(frameCount >= 7){
				auxFrameCount = 0;
			}

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

			if(((allBosses.bosses[activeBoss].firstPositionX + allBosses.bosses[activeBoss].secondPositionX) / 2) < ((protagonist.firstPositionX + protagonist.secondPositionX) / 2))
				rotatedBoss = 1;
			else
				rotatedBoss = 0;

			//Bordas da tela
			if(protagonist.firstPositionX < 0){
				protagonist.firstPositionX = 0;
				protagonist.secondPositionX = CHARACTER_FRAME_WIDTH;
			}
			if(protagonist.secondPositionX > WIDTH){
				protagonist.firstPositionX = WIDTH - CHARACTER_FRAME_WIDTH;
				protagonist.secondPositionX = WIDTH;
			}

			if(protagonist.firstPositionY < 0){
				protagonist.firstPositionY = 0;
				protagonist.secondPositionY = CHARACTER_FRAME_HEIGHT;
			}

			if(protagonist.secondPositionY > HEIGHT){
				protagonist.firstPositionY = HEIGHT - CHARACTER_FRAME_HEIGHT;
				protagonist.secondPositionY = HEIGHT;
			}

			//Condição de Morte do Personagem
			if(protagonist.life <= 0){
				Die(display, event_queue, protagonist.score, timer, event, inst_sound_background);
				al_destroy_bitmap(protagonist.spritesWalking);
				al_destroy_bitmap(gameFloor);
				al_destroy_bitmap(weaponFrame);
				al_destroy_bitmap(orbs);
				al_destroy_bitmap(bat.sprite);
				al_destroy_bitmap(javali.sprite);
				al_destroy_bitmap(demon.sprite);
				al_destroy_bitmap(fireSkull.sprite);
				al_destroy_bitmap(bow.ammo.sprite);
				al_destroy_bitmap(knife.ammo.sprite);
				al_destroy_bitmap(lance.ammo.sprite);
				al_destroy_bitmap(shuriken.ammo.sprite);
				al_destroy_bitmap(axe.ammo.sprite);
				al_destroy_font(fontScore);
				al_destroy_sample(game_background);
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
				protagonist.stamina += 10;
				if(protagonist.stamina > 100)
					protagonist.stamina = 100;
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
