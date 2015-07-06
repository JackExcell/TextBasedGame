#pragma once
class Player
{
public:
	Player();

	void newGame();
	void setLevel();
	void takeDamage(int damage);
	void earnExp(int exp);
	void maxHpUp(int amount);
	void maxHpDown(int amount);
	void setStrength();
	void setDefence();
	void levelUp();
	void heal(int heal);
	void loseHealth(int amount);
	void takeDamage();
	void increaseStrength(int str);
	void decreaseStrength(int str);
	void increaseDefence(int def);
	void decreaseDefence(int def);
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

