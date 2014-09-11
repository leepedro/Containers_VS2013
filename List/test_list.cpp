#include "item.h"

#include <list>

void test_func_1(void)
{
	std::list<Item> list_1;
	list_1.emplace_back(1);
	Item item_1(2);

	// A new item is created and copied to the list.
	list_1.push_back(item_1);
}

void test_func_2(void)
{
	std::list<Item> list_1;
	list_1.emplace_back(1);
	Item item_1(2);

	// A new item is created and moved to the list.
	list_1.push_back(std::move(item_1));
}

void test_func_3(void)
{
	std::list<Item> list_1;
	list_1.emplace_back(1);
	list_1.emplace_back(2);
	list_1.emplace_back(3);
	list_1.emplace_back(4);

	// Remove one item.
	for (auto it = list_1.begin(); it != list_1.end();)
	{
		if (it->id == 2)
			it = list_1.erase(it);
		else
			++it;
	}
}



int main(void)
{
	test_func_3();
}