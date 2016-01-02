#include <map>
#include <string>
#include <iostream>

class Info
{
public:
	Info(const Info &src) : name_(src.name_), address(src.address) {}
	Info(Info &&src) : name_(std::move(src.name_)), address(std::move(src.address)) {}	// necessary.
	Info(const std::string &name) : name_(name) {}
	
	const std::string &name = this->name_;

	void set_name(const std::string &name) { this->name_ = name; }

private:
	std::string name_;
	std::string address;
};

void test_map(void)
{
	std::map<int, Info> infos;
	infos.emplace(std::make_pair(1, Info("first")));
	infos.emplace(std::make_pair(2, Info("second")));
	infos.emplace(std::make_pair(3, Info("third")));
	infos.emplace(std::make_pair(2, Info("second_two")));	// This line is ignored.

	auto info_3_it = infos.find(3);
	info_3_it->second.set_name("new");	// This changes the values in the container because it is a reference.

	auto info_2 = infos.find(2)->second;
	std::cout << infos.find(2)->second.name.c_str() << std::endl;
	info_2.set_name("new second");				// This does NOT change the values in the container because info_2 is a copy.
	std::cout << infos.find(2)->second.name.c_str() << std::endl;

	auto &info_2_ref = infos.find(2)->second;
	std::cout << infos.find(2)->second.name.c_str() << std::endl;
	info_2_ref.set_name("new 2nd");				// This DOES change the values in the container because info_2 is a reference.
	std::cout << infos.find(2)->second.name.c_str() << std::endl;
}

int main(void)
{
	test_map();
}