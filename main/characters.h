#ifndef CHARACTERS_H
#define CHARACTERS_H

typedef struct {
	char name[4];
	int score;
} Score;


typedef struct boss{
	int life;
	int totalLife;
	int speed;
	float damage;
	int frameWidht;
	int frameHeight;
	char name[15];
	float firstPositionX;
	float firstPositionY;
	float secondPositionX;
	float secondPositionY;
	ALLEGRO_BITMAP *sprite;
}typeBoss;

typedef struct {
	float speed;
	float damage;
	float distance;
	float rotationSpeed;
	ALLEGRO_BITMAP *sprite;
}projectile;

typedef struct weapon{
	int ID;
	char name[15];
	struct weapon *next;
	struct weapon *previous;
	projectile ammo;
}typeWeapon;

typedef struct {
	int quantity;
	typeWeapon *first;
	typeWeapon *last;
}weaponsList;

typedef struct {
	typeBoss bosses[5];
	int quantity;
}bossesList;

typedef struct {
	float life;
	int score;
	int speed;
	float stamina;
	float firstPositionX;
	float firstPositionY;
	float secondPositionX;
	float secondPositionY;
	weaponsList weapons;
	int weaponEquiped;
	ALLEGRO_BITMAP *spritesWalking;
}character;

#endif //CHARACTERS_H