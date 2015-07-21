#pragma once
#include <string>

class Item
{

public:
	Item(int itemId);
	std::string getName();
	std::string getDescription();
	int getHealAmount();
	int getHealthLossAmount();
	int getStrUp();
	int getStrDown();
	int getDefUp();
	int getDefDown();
	int getMaxHpUp();
	int getMaxHpDown();
	int getId();
	int getPrice();

private:
	std::string _name;
	std::string _description;

	int _id;
	int _healAmount;
	int _healthLossAmount;
	int _strengthUp;
	int _strengthDown;
	int _defenceUp;
	int _defenceDown;
	int _maxHpUp;
	int _maxHpDown;
	int _price;

};



