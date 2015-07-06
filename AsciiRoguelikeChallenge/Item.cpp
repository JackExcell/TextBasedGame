#include "Item.h"


Item::Item(int itemId)
{
	//The name, description and effects of the item are determined by its Id.
	//The switch statement below serves as a list of all available items in game,
	//specified by the given parameter.
	switch (itemId)
	{
	case 0:
		_name = "Healing Potion";
		_description = "Heals for 50 Health Points";
		_id = 0;

		_healAmount = 50;
		_healthLossAmount = 0;
		_strengthUp = 0;
		_strengthDown = 0;
		_defenceUp = 0;
		_defenceDown = 0;
		_maxHpUp = 0;
		_maxHpDown = 0;
		break;

	case 1:
		_name = "Super Healing Potion";
		_description = "Heals for 180 Health Points";
		_id = 1;

		_healAmount = 180;
		_healthLossAmount = 0;
		_strengthUp = 0;
		_strengthDown = 0;
		_defenceUp = 0;
		_defenceDown = 0;
		_maxHpUp = 0;
		_maxHpDown = 0;
		break;
	}
}

std::string Item::getName()
{
	return _name;
}

std::string Item::getDescription()
{
	return _description;
}

int Item::getHealAmount()
{
	return _healAmount;
}

int Item::getHealthLossAmount()
{
	return _healthLossAmount;
}

int Item::getStrUp()
{
	return _strengthUp;
}

int Item::getStrDown()
{
	return _strengthDown;
}

int Item::getDefUp()
{
	return _defenceUp;
}

int Item::getDefDown()
{
	return _defenceDown;
}

int Item::getMaxHpUp()
{
	return _maxHpUp;
}

int Item::getMaxHpDown()
{
	return _maxHpDown;
}
