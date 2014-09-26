#include <valarray>

void Test1(void)
{
	std::valarray<unsigned char> data1(10), data2;
	std::valarray<float> f1;
	data2 = data1;
	data1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	auto cshifted1 = data1.cshift(1);
	auto cshifted2 = data1.cshift(-1);
	auto shifted1 = data1.shift(1);
	auto shifted2 = data1.shift(-1);
	// NOTE: slice is not another array.
	auto slice1 = data1[std::slice(0, 3, 2)];
}

int main(void)
{
	Test1();
}