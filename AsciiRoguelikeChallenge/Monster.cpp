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
		_HP = 25 + (level * 9);
		_strength = 3 + (level*4);
		_defence = 1 + level;
		_expReward = 25 + (level * 2);
		_goldReward = 12 + level;
		break;
	case 'O':
		//Monster is of type Ogre
		_xPos = xPos;
		_yPos = yPos;
		_type = type;
		_HP = 40 + (level * 9);
		_strength = 2 + (level*5);
		_defence = 1 + level;
		_expReward = 45 + (level * 3);
		_goldReward = 30 + (level * 2);
		break;
	case 'D':
		//Monster is of type Dragon
		_xPos = xPos;
		_yPos = yPos;
		_type = type;
		_HP = 80 + (level * 8);
		_strength = (level * 7);
		_defence = 5 + (level*4);
		_expReward = 120 + (level * 3);
		_goldReward = 50 + (level * 3);
		break;
	case 'K':
		//Monster is of type King
		_xPos = xPos;
		_yPos = yPos;
		_type = type;
		_HP = 1000;
		_strength = 70;
		_defence = 45;
		_expReward = 500;
		_goldReward = 1000;
		break;
	default:
		cout << "MONSTER DATA ERROR" << endl;
	}

}

void Monster::dead()
{
	_active = false;
}

bool Monster::isMonsterActive()
{
	return _active;
}

bool Monster::checkIfDead()
{
	if (_HP > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Monster::takeDamage(int damage)
{
	_HP = _HP - damage;
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

int Monster::getStrength()
{
	return _strength;
}

int Monster::getDefence()
{
	return _defence;
}

int Monster::getExp()
{
	return _expReward;
}

int Monster::getGoldReward()
{
	return _goldReward;
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

void Monster::setHP(int hp)
{
	_HP = hp;
}

void Monster::setInactive()
{
	_active = false;
}
