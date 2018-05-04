#ifndef LIST_H
#define LIST_H

#include "characters.h"

void CreateListWeapons(weaponsList *list);
void CreateListBosses(bossesList *list);
void LoadWeapon(typeWeapon *item, weaponsList *list);
void LoadBoss(typeBoss *item, bossesList *list);
void InsertionWeapon(typeWeapon *item, weaponsList *list);
int RemoveWeapon(int position, weaponsList *list);
void DeadBoss(int position, bossesList * list);
typeWeapon * Search(int position, weaponsList *list);
typeWeapon * SearchByID(int ID, weaponsList *list);

#endif //LIST_H