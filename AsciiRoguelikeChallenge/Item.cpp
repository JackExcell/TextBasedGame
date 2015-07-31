#include "Item.h"


Item::Item(int itemId)
{
	//Current number of items = 11

	//The name, description and effects of the item are determined by its Id.
	//The switch statement below serves as a list of all available items in game,
	//specified by the given parameter.
	switch (itemId)
	{
	case 0:
		_name = "Healing Potion";
		_description = "Heals for 50 Health Points";
		_id = 0;
		_price = 30;

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
		_description = "Heals for 100 Health Points";
		_id = 1;
		_price = 50;

		_healAmount = 100;
		_healthLossAmount = 0;
		_strengthUp = 0;
		_strengthDown = 0;
		_defenceUp = 0;
		_defenceDown = 0;
		_maxHpUp = 0;
		_maxHpDown = 0;
		break;

	case 2:
		_name = "Strength Potion";
		_description = "Permenantly increase strength by 1";
		_id = 2;
		_price = 100;

		_healAmount = 0;
		_healthLossAmount = 0;
		_strengthUp = 1;
		_strengthDown = 0;
		_defenceUp = 0;
		_defenceDown = 0;
		_maxHpUp = 0;
		_maxHpDown = 0;
		break;

	case 3:
		_name = "Super Strength Potion";
		_description = "Permenantly increase strength by 2";
		_id = 3;
		_price = 150;

		_healAmount = 0;
		_healthLossAmount = 0;
		_strengthUp = 2;
		_strengthDown = 0;
		_defenceUp = 0;
		_defenceDown = 0;
		_maxHpUp = 0;
		_maxHpDown = 0;
		break;

	case 4:
		_name = "Berserk Potion";
		_description = "Permenantly increase strength by 3 at the cost of 1 defence.";
		_id = 4;
		_price = 250;

		_healAmount = 0;
		_healthLossAmount = 0;
		_strengthUp = 3;
		_strengthDown = 0;
		_defenceUp = 0;
		_defenceDown = 1;
		_maxHpUp = 0;
		_maxHpDown = 0;
		break;

	case 5:
		_name = "Stoneskin Potion";
		_description = "Permenantly increase defence by 1";
		_id = 5;
		_price = 100;

		_healAmount = 0;
		_healthLossAmount = 0;
		_strengthUp = 0;
		_strengthDown = 0;
		_defenceUp = 1;
		_defenceDown = 0;
		_maxHpUp = 0;
		_maxHpDown = 0;
		break;

	case 6:
		_name = "Steelskin Potion";
		_description = "Permenantly increase defence by 2";
		_id = 6;
		_price = 150;

		_healAmount = 0;
		_healthLossAmount = 0;
		_strengthUp = 0;
		_strengthDown = 0;
		_defenceUp = 2;
		_defenceDown = 0;
		_maxHpUp = 0;
		_maxHpDown = 0;
		break;

	case 7:
		_name = "Paladin's Elixir";
		_description = "Permenantly increase defence by 3 and Max HP by 20, at the cost of 1 strength.";
		_id = 7;
		_price = 250;

		_healAmount = 0;
		_healthLossAmount = 0;
		_strengthUp = 0;
		_strengthDown = 1;
		_defenceUp = 3;
		_defenceDown = 0;
		_maxHpUp = 20;
		_maxHpDown = 0;
		break;

	case 8:
		_name = "Vial of Dragon's Blood";
		_description = "This poisonous blood increases strength and defence by 1, but you take 50 damage. This will never reduce your health lower than 1 HP.";
		_id = 8;
		_price = 100;

		_healAmount = 0;
		_healthLossAmount = 50;
		_strengthUp = 1;
		_strengthDown = 0;
		_defenceUp = 1;
		_defenceDown = 0;
		_maxHpUp = 0;
		_maxHpDown = 0;
		break;

	case 9:
		_name = "Elixir of Life";
		_description = "Fully restores your Health";
		_id = 9;
		_price = 500;

		_healAmount = 99999;
		_healthLossAmount = 0;
		_strengthUp = 0;
		_strengthDown = 0;
		_defenceUp = 0;
		_defenceDown = 0;
		_maxHpUp = 0;
		_maxHpDown = 0;
		break;

	case 10:
		_name = "Demonic Contract";
		_description = "Offer some of your life force to the demons.\nSacrifice 20 of your Maximum possible HP to be fully healed and gain 1 strength and defence.";
		_id = 10;
		_price = 350;

		_healAmount = 99999;
		_healthLossAmount = 0;
		_strengthUp = 1;
		_strengthDown = 0;
		_defenceUp = 1;
		_defenceDown = 0;
		_maxHpUp = 0;
		_maxHpDown = 20;
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

int Item::getId()
{
	return _id;
}

int Item::getPrice()
{
	return _price;
}
