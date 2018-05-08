#include "includes.h"

//FUNÇÕES DA LISTA

void CreateListWeapons(weaponsList *list){
	list->quantity = 0;
	list->first = NULL;
	list->last = NULL;
}

void CreateListBosses(bossesList *list){
	list->quantity = 0;
}

void LoadWeapon(typeWeapon *item, weaponsList *list){
	switch(list->quantity){
		case 0:
			list->first = item;
			list->last = item;
			item->next = item;
			item->previous = item;
			list->quantity++;
			return;
		case 1:
			list->last = item;
			list->first->next = item;
			item->next = list->first;
			item->previous = list->first;
			list->first->previous = item;
			list->quantity++;
			return;
		default:
			list->first->previous = item;
			item->next = list->first;
			item->previous = list->last;
			list->last->next = item;
			list->last = item;
			list->quantity++;
			return;
	}
}

void LoadBoss(typeBoss *item, bossesList *list){
	list->bosses[list->quantity] = *item;
	list->quantity++;
}

void InsertionWeapon(typeWeapon *item, weaponsList *list){
	switch(list->quantity){
		case 0:
			list->first = item;
			list->last = item;
			item->next = item;
			item->previous = item;
			list->quantity++;
			return ;
		case 1:
			list->last = item;
			list->first->next = item;
			item->next = list->first;
			item->previous = list->first;
			list->first->previous = item;
			list->quantity++;
			return ;
		case 2:
			list->first->previous = item;
			item->next = list->first;
			item->previous = list->last;
			list->last->next = item;
			list->last = item;
			list->quantity++;
			return ;
		case 3:
			free(item);
			return ;
	}
}

int RemoveWeapon(int position, weaponsList *list){
	typeWeapon * aux = NULL;
	switch(list->quantity){
		case 1:
			return 0;
		case 2:
			if(position == 1){
				aux = list->first;
				list->first = list->first->next;
			} else {
				aux = list->last;
				list->last = list->last->next;
			}
			list->first->next = list->first;
			list->first->previous = list->first;
			list->quantity--;
			free(aux);
			return 1;
		case 3:
			switch(position){
				case 1:
					aux = list->first;
					list->first = list->first->next;
					list->first->previous = list->last;
					list->last->next = list->first;
					break;
				case 2:
					aux = list->first->next;
					list->first->next = list->last;
					list->last->previous = list->first;
					break;
				case 3:
					aux = list->last;
					list->last = list->last->previous;
					list->first->previous = list->last;
					list->last->next = list->first;
					break;
			}
			list->quantity--;
			free(aux);
			return 1;
	}
	return 1;
}

void DeadBoss(int position, bossesList * list){
	list->bosses[position].totalLife *= 2;
	list->bosses[position].life = list->bosses[position].totalLife;
	list->bosses[position].damage *= 1.15;
	list->bosses[position].speed++;

}

typeWeapon * Search(int position, weaponsList *list){
	switch(position){
		case 1:
			return list->first;
		case 2:
			return list->first->next;
		default:
			return list->first->previous;
	}
}

typeWeapon * SearchByID(int ID, weaponsList *list){
	typeWeapon * aux = NULL;
	aux = malloc(sizeof(typeWeapon));
	*aux = *list->first;
	while(true){
		if(aux->ID == ID)
			return aux;
		else
			*aux = *aux->next;
	}


}