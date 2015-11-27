#include <array>
#include <vector>
#include <limits>

// Following function templates can be used for any standard container with iterators.
// The first and second input argument can be different data type.

// C = A + B
template <typename InputIteratorA, typename InputIteratorB, typename OutputIterator>
void Add(InputIteratorA it_a, InputIteratorA it_a_last, InputIteratorB it_b, OutputIterator it_c)
{
	for (; it_a != it_a_last; ++it_a, ++it_b, ++it_c)
		*it_c = *it_a + *it_b;
}

// A += B
template <typename InputIterator, typename InOutputIterator>
void Add(InputIterator it_b, InputIterator it_b_last, InOutputIterator it_a)
{
	for (; it_b != it_b_last; ++it_a, ++it_b)
		*it_a = *it_a + *it_b;
}

/*
Fill the integral range value in an ascending order while preventing overflow by
comparing the range value with the maximum value at each iteration. (inefficient)
*/
template <typename Iterator, typename T>
std::enable_if_t<std::is_integral<T>::value, void> FillRange(Iterator it, Iterator itLast, T initValue)
{
	for (auto value = initValue, limitMax = std::numeric_limits<T>::max(), limitMin = std::numeric_limits<T>::min(); it != itLast; ++it)
	{
		*it = value;
		if (value == limitMax)
			value = limitMin;
		else
			++value;
	}
}

/*
Fill the floating point range value in an ascending order without the range check.
*/
template <typename Iterator, typename T>
std::enable_if_t<std::is_floating_point<T>::value, void> FillRange(Iterator it, Iterator itLast, T initValue)
{
	for (auto value = initValue; it != itLast; ++it, ++value)
		*it = value;
}



int main(void)
{
	std::array<int, 3> array1 = { 1, 2, 3 }, array2 = { 4, 5, 6 }, array3;
	std::array<short, 3> array4 = { 4, 5, 6 };
	std::vector<int> vector1 = { 1, 2, 3 }, vector2 = { 4, 5, 6 }, vector3(3);
	std::vector<short>  vector4 = { 4, 5, 6 };

	// InputIteratorA == InputIteratorB
	Add(array1.cbegin(), array1.cend(), array2.cbegin(), array3.begin());	
	Add(vector1.cbegin(), vector1.cend(), vector2.cbegin(), vector3.begin());

	// InputIteratorA == InputIteratorB
	Add(array1.cbegin(), array1.cend(), array2.begin());
	Add(vector1.cbegin(), vector1.cend(), vector2.begin());

	// InputIteratorA != InputIteratorB
	Add(array1.cbegin(), array1.cend(), array4.cbegin(), array3.begin());
	Add(vector1.cbegin(), vector1.cend(), vector4.cbegin(), vector3.begin());

	// InputIteratorA != InputIteratorB
	Add(array1.cbegin(), array1.cend(), array4.begin());
	Add(vector1.cbegin(), vector1.cend(), vector4.begin());

	std::array<unsigned char, 257> array5;
	std::vector<int> vector5(3);
	std::vector<double> vector6(10);
	FillRange(array5.begin(), array5.end(), 0);
	FillRange(vector5.begin(), vector5.end(), 10);
	FillRange(vector6.begin(), vector6.end(), 10.0);
}