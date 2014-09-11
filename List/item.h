#if !defined(ITEM_H)
#define ITEM_H

class Item
{
public:
	Item(void) = delete;
	Item(int id);
	Item(const Item &src);
	Item(Item &&src);


	~Item(void);

	const int &id = this->id_;

protected:
	const int id_;

};

#endif
