#pragma once
class Player
{
public:
	Player();

	void newGame();
	void setLevel(int level);
	void setHP(int hp);
	void setMaxHP(int hp);
	void setStrength(int str);
	void setDefence(int def);
	void setCurrentExp(int exp);
	void setExpNeededToLevel(int exp);
	void setGold(int gold);
	void takeDamage(int damage);
	void earnExp(int exp);
	void earnGold(int gold);
	void loseGold(int gold);
	void maxHpUp(int amount);
	void maxHpDown(int amount);
	void levelUp();
	void heal(int heal);
	void loseHealth(int amount);
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
	int getGold();
	bool isPlayerDead();


private:
	int _level;
	int _currentHP;
	int _maxHP;
	int _strength;
	int _defence;
	int _exp;
	int _totalExpNeededToLevel;
	int _gold = 0;
};

