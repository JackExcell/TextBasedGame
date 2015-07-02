#pragma once
class Player
{
public:
	Player();

	void newGame();
	void setLevel();
	void takeDamage(int damage);
	void earnExp(int exp);
	void setMaxHP();
	void setStrength();
	void setDefence();
	void levelUp();
	void heal();
	void takeDamage();
	void increaseStrength();
	void increaseDefence();
	int getLevel();
	int getStr();
	int getDef();
	int getCurrentHP();
	int getMaxHP();
	int getCurrentExp();
	int getTotalExpNeededToLevel();


private:
	int _level;
	int _currentHP;
	int _maxHP;
	int _strength;
	int _defence;
	int _exp;
	int _totalExpNeededToLevel;
};

