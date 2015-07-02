#include "Player.h"


Player::Player()
{

}

void Player::newGame()
{
	_level = 1;
	_currentHP = 100;
	_maxHP = 100;
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