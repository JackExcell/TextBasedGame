#include "Shop.h"
#include <iostream>
#include <string>


Shop::Shop()
{

}

void Shop::clearStock()
{
	_stock.clear();
}

void Shop::prepareStock(int currentFloor)
{
	clearStock();

	Item item0(0);//Healing Potion
	Item item1(1);//Super Healing Potion
	Item item2(2);//Strength Potion
	Item item3(3);//Super Strength Potion
	Item item4(4);//Berserk Potion
	Item item5(5);//Stoneskin Potion
	Item item6(6);//Steelskin Potion
	Item item7(7);//Paladin's Elixir
	Item item8(8);//Vial of Dragon's Blood
	Item item9(9);//Elixir of Life
	Item item10(10);//Demonic Contract

	//The items available depend on which floor/level the player is currently on.
	//This switch case will add items to the store for the specified floor and 
	//every floor below. (Due to intentionally missing break statements.)
	//Only the highest 9 items are used.
	//Items usually need only be listed once across the entire switch statement otherwise
	//duplicates may appear in the in game shop.
	switch (currentFloor)
	{
	case 10:

	case 9:
		if (_stock.size() == 9)
		{
			_stock.erase(_stock.begin());
			_stock.push_back(item9);
		}
		else
		{
			_stock.push_back(item9);
		}
		
	case 8:

	case 7:

	case 6:
		if (_stock.size() == 9)
		{
			_stock.erase(_stock.begin());
			_stock.push_back(item3);
		}
		else
		{
			_stock.push_back(item3);
		}

		if (_stock.size() == 9)
		{
			_stock.erase(_stock.begin());
			_stock.push_back(item4);
		}
		else
		{
			_stock.push_back(item4);
		}

		if (_stock.size() == 9)
		{
			_stock.erase(_stock.begin());
			_stock.push_back(item6);
		}
		else
		{
			_stock.push_back(item6);
		}

		if (_stock.size() == 9)
		{
			_stock.erase(_stock.begin());
			_stock.push_back(item7);
		}
		else
		{
			_stock.push_back(item7);
		}
	case 5:

	case 4:

	case 3:
		if (_stock.size() == 9)
		{
			_stock.erase(_stock.begin());
			_stock.push_back(item0);
		}
		else
		{
			_stock.push_back(item0);
		}

		if (_stock.size() == 9)
		{
			_stock.erase(_stock.begin());
			_stock.push_back(item1);
		}
		else
		{
			_stock.push_back(item1);
		}

		if (_stock.size() == 9)
		{
			_stock.erase(_stock.begin());
			_stock.push_back(item2);
		}
		else
		{
			_stock.push_back(item2);
		}

		if (_stock.size() == 9)
		{
			_stock.erase(_stock.begin());
			_stock.push_back(item5);
		}
		else
		{
			_stock.push_back(item5);
		}
	case 2:

	case 1:
		break;
	}
}

void Shop::displayItemsForSale()
{
	for (int i = 0; i < _stock.size(); i++)
	{
		std::cout << std::to_string(i + 1) + " - " + _stock[i].getName() + " (" + std::to_string(_stock[i].getPrice()) + " gold)" << std::endl;
	}
}

int Shop::getStockSize()
{
	return _stock.size();
}

Item Shop::getItem(int selection)
{
	int index = selection - 1;
	Item item = _stock[index];
	return item;
}

