#include "includes.h"

int ColisionRectangle(float shotFirstX, float shotFirstY, float shotSecondX, float shotSecondY, typeBoss *boss){
	if(shotFirstX >= boss->firstPositionX && shotFirstX <= boss->secondPositionX){
		if(shotFirstY >= boss->firstPositionY && shotFirstY <= boss->secondPositionY){
			return 1;
		}
	}
	if(shotSecondX >= boss->firstPositionX && shotSecondX <= boss->secondPositionX){
		if(shotSecondY >= boss->firstPositionY && shotSecondY <= boss->secondPositionY){
			return 1;
		}
	}

	if(shotFirstX >= boss->firstPositionX && shotFirstX <= boss->secondPositionX){
		if(shotSecondY >= boss->firstPositionY && shotSecondY <= boss->secondPositionY){
			return 1;
		}
	}
	if(shotSecondX >= boss->firstPositionX && shotSecondX <= boss->secondPositionX){
		if(shotFirstY >= boss->firstPositionY && shotFirstY <= boss->secondPositionY){
			return 1;
		}
	}
	return 0;
}

int ColisionCharacterBoss(character *protagonist, typeBoss *boss){
	if(protagonist->firstPositionX >= boss->firstPositionX && protagonist->firstPositionX <= boss->secondPositionX){
		if(protagonist->firstPositionY >= boss->firstPositionY && protagonist->firstPositionY <= boss->secondPositionY){
			return 1;
		}
	}
	if(protagonist->secondPositionX >= boss->firstPositionX && protagonist->secondPositionX <= boss->secondPositionX){
		if(protagonist->secondPositionY >= boss->firstPositionY && protagonist->secondPositionY <= boss->secondPositionY){
			return 1;
		}
	}

	if(protagonist->firstPositionX >= boss->firstPositionX && protagonist->firstPositionX <= boss->secondPositionX){
		if(protagonist->secondPositionY >= boss->firstPositionY && protagonist->secondPositionY <= boss->secondPositionY){
			return 1;
		}
	}
	if(protagonist->secondPositionX >= boss->firstPositionX && protagonist->secondPositionX <= boss->secondPositionX){
		if(protagonist->firstPositionY >= boss->firstPositionY && protagonist->firstPositionY <= boss->secondPositionY){
			return 1;
		}
	}
	if(boss->firstPositionX >= protagonist->firstPositionX && boss->firstPositionX <= protagonist->secondPositionX){
		if(boss->firstPositionY >= protagonist->firstPositionY && boss->firstPositionY <= protagonist->secondPositionY){
			return 1;
		}
	}
	return 0;
}