#pragma once
class Monster
{
public:
	Monster();
	void initialise(int xPos, int yPos, int level, char type);
	void dead();
	void setXPosition(int &newX);
	void setYPosition(int &newY);
	bool isMonsterActive();
	bool checkIfDead();
	void takeDamage(int damage);
	int getXPosition();
	int getYPosition();
	int getHP();
	int getStrength();
	int getDefence();
	int getExp();
	int getGoldReward();
	char getType();
	void setHP(int hp);

private:
	bool _active;
	char _type;
	int _xPos;
	int _yPos;
	int _HP;
	int _strength;
	int _defence;
	int _expReward;
	int _goldReward;
};

