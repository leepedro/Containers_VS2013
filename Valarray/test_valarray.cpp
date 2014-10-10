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

void TestCasting(void)
{
	// Widening casting runs with little-endian.
	std::valarray<unsigned char> data_b1 = { 1, 2, 3, 4, 5, 6, 7, 8 };
	std::valarray<unsigned short> data_s1(reinterpret_cast<unsigned short *>(std::begin(data_b1)), 4);
	// {513, 1027, 1541, 2055}

	// Multi-byte data type can be stored as byte type and restored to original values.
	std::valarray<float> data_f1 = { 1.0, 2.0, 3.0, 4.0 };
	std::valarray<unsigned char> data_b2(reinterpret_cast<unsigned char *>(std::begin(data_f1)), 16);
	std::valarray<float> data_f2(reinterpret_cast<float *>(std::begin(data_b2)), 4);
}

int main(void)
{
	//Test1();
	TestCasting();
}