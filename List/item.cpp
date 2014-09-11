#include "item.h"

#include <iostream>

Item::Item(int n) : id_(n)
{
	std::clog << "Item " << this->id << " is being created." << std::endl;
}

Item::Item(const Item &src) : id_(src.id)
{
	std::clog << "Item " << this->id << " is being copied." << std::endl;
}

Item::Item(Item &&src) : id_(src.id)
{
	std::clog << "Item " << this->id << " is being moved." << std::endl;
}

Item::~Item(void)
{
	std::clog << "Item " << this->id << " is being deleted." << std::endl;
}