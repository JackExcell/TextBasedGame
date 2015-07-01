#pragma once
class Monster
{
public:
	Monster();
	void initialise(int xPos, int yPos, int level, char type);
	void setXPosition(int &newX);
	void setYPosition(int &newY);
	bool isMonsterActive();
	int getXPosition();
	int getYPosition();
	int getHP();
	char getType();

private:
	bool _active;
	char _type;
	int _xPos;
	int _yPos;
	int _HP;
	int _strength;
	int _defence;
	int _expReward;
};

