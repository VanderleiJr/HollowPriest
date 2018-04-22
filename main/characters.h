#ifndef CHARACTERS_H
#define CHARACTERS_H

typedef struct {
	int life;
	int stamina;
	int speed;
	ALLEGRO_BITMAP *sprite;
}character;

typedef struct {
	int life;
	int speed;
	ALLEGRO_BITMAP *sprite;
}boss;

typedef struct {
	float speed;
	ALLEGRO_BITMAP *sprite;
}projectile;

typedef struct {
	int key;
	char name[15];
	ALLEGRO_BITMAP *sprite;
	projectile ammo;
}weapon;

#endif //CHARACTERS_H