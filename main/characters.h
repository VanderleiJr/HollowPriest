#ifndef CHARACTERS_H
#define CHARACTERS_H

typedef struct {
	int life;
	int score;
	int speed;
	float stamina;
	int weaponEquiped;
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
	ALLEGRO_BITMAP *spriteVertical;
	ALLEGRO_BITMAP *spriteHorizontal;
}projectile;

typedef struct weapon{
	int ID;
	int numberAmmo;
	char name[15];
	struct weapon *next;
	struct weapon *previous;
	ALLEGRO_BITMAP *sprite;
	projectile ammo;
}typeWeapon;

typedef struct {
	int quantity;
	typeWeapon *first;
}weaponsList;

typedef struct {
	typeBoss bosses[5];
	typeBoss *first;
}bossesList;

#endif //CHARACTERS_H