#ifndef COLISION_H
#define COLISION_H

int ColisionRectangle(float shotFirstX, float shotFirstY, float shotSecondX, float shotSecondY,
					  typeBoss *boss); 
int ColisionCharacterBoss(character *character, typeBoss *boss);

#endif