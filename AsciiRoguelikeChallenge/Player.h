#pragma once
class Player
{
public:
	Player();

	void newGame();
	void setLevel();
	void setCurrentHP();
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


private:
	int _level;
	int _currentHP;
	int _maxHP;
	int _strength;
	int _defence;
};

