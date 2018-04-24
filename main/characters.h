#ifndef CHARACTERS_H
#define CHARACTERS_H

typedef struct {
	int life;
	int score;
	int stamina;
	ALLEGRO_BITMAP *spritesWalking;
}character;

typedef struct {
	int life;
	int speed;
	ALLEGRO_BITMAP *sprite;
}typeBoss;

typedef struct {
	int ID;
	float speed;
	ALLEGRO_BITMAP *sprite;
}projectile;

typedef struct {
	int ID;
	char name[15];
	ALLEGRO_BITMAP *sprite;
	projectile ammo;
}typeWeapon;

typedef struct {
	typeWeapon weapon[5];
	typeWeapon *first;
} weaponsList;

typedef struct {
	typeBoss bosses[5];
	typeBoss *first;
} bossesList;

#endif //CHARACTERS_H