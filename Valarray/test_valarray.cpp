#include <valarray>
#include <complex>

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
	auto it_1 = std::begin(data1);
	auto end_1 = std::end(data1);

	// In little-endian system, two bytes {1, 2} became one short as 2x256 + 1 = 513.
	auto cast_it_1 = reinterpret_cast<unsigned short *>(it_1);

	std::valarray<std::complex<float>> data3(3);
	data3[0] = std::complex<float>(1.0f, 2.0f);
}

int main(void)
{
	Test1();
}