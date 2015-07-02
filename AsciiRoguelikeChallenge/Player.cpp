#include "Player.h"
#include <string>
#include <iostream>

using namespace std;

Player::Player()
{

}

void Player::newGame()
{
	_level = 1;
	_currentHP = 100;
	_maxHP = 100;
	_exp = 0;
	_totalExpNeededToLevel = 100;
	_strength = 5;
	_defence = 5;
}

void Player::takeDamage(int damage)
{
	_currentHP = _currentHP - damage;
}

void Player::earnExp(int exp)
{
	_exp = _exp + exp;
}

int Player::getLevel()
{
	return _level;
}

int Player::getStr()
{
	return _strength;
}

int Player::getDef()
{
	return _defence;
}

int Player::getCurrentHP()
{
	return _currentHP;
}

int Player::getMaxHP()
{
	return _maxHP;
}

int Player::getCurrentExp()
{
	return _exp;
}

int Player::getTotalExpNeededToLevel()
{
	return _totalExpNeededToLevel;
}

void Player::levelUp()
{
	if (_exp > _totalExpNeededToLevel)
	{
		cout << "Your experience in battle has increased your Level!" << endl;
		_level++;
		cout << "You reached level " + to_string(_level) + "!" << endl;
		_strength += (2 + _level);
		_defence += (2 + _level);
		_currentHP += 20 + (3 * _level);
		_maxHP += 20 + (3 * _level);

		//Set values for reaching the next level
		_exp -= _totalExpNeededToLevel;
		_totalExpNeededToLevel = 100 + (_level * 40);
	}
}
