#pragma once
#include <vector>
#include "Item.h"
class Shop
{
public:
	Shop();
	void clearStock();
	void prepareStock(int currentFloor);
	void displayItemsForSale();
	int getStockSize();
	Item getItem(int selection);

private:
	std::vector<Item> _stock;
};

