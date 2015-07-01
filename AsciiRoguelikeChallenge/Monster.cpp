#include <iostream>
#include <string>

#include "Monster.h"

using namespace std;

Monster::Monster()
{
	_active = false;
}

void Monster::initialise(int xPos, int yPos, int level, char type)
{
	_active = true;
	
	switch (type)
	{
	case 'S':
		//Monster is of type Snake
		_xPos = xPos;
		_yPos = yPos;
		_type = type;
		_HP = 20 + (level * 2);
		_strength = 1 + level;
		_defence = 1 + level;
		_expReward = 25 + (level * 2);
		break;
	case 'O':
		//Monster is of type Ogre
		_xPos = xPos;
		_yPos = yPos;
		_type = type;
		_HP = 30 + (level * 3);
		_strength = 2 + (level*2);
		_defence = 1 + level;
		_expReward = 45 + (level * 3);
		break;
	case 'D':
		//Monster is of type Dragon
		_xPos = xPos;
		_yPos = yPos;
		_type = type;
		break;
	case 'K':
		//Monster is of type King
		_xPos = xPos;
		_yPos = yPos;
		_type = type;
		break;
	default:
		cout << "MONSTER DATA ERROR" << endl;
	}

}

bool Monster::isMonsterActive()
{
	return _active;
}

int Monster::getXPosition()
{
	return _xPos;
}

int Monster::getYPosition()
{
	return _yPos;
}

int Monster::getHP()
{
	return _HP;
}

void Monster::setXPosition(int &newX)
{
	_xPos = newX;
}

void Monster::setYPosition(int &newY)
{
	_yPos = newY;
}

char Monster::getType()
{
	return _type;
}