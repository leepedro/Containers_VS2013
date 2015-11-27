#include <set>
#include <string>

int main(void)
{
	std::set<std::string> set_1;
	set_1.insert("test 1");
	set_1.insert("test 2");
	set_1.insert("test 1");	// This line does NOT throw an error, but just be ignored.
}