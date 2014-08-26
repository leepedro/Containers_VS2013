#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <queue>

template<typename T>
class ImageFrame
{
public:
	ImageFrame(void) = default;

	ImageFrame(const ImageFrame<T> &src) : data(src.data)
	{
		std::cout << "Copying data." << std::endl;
	}

	ImageFrame(ImageFrame<T> &&src) : data(std::move(src.data))
	{
		std::cout << "Moving data." << std::endl;
	}

	std::vector<T> data;
};

int main(void)
{
	std::queue<ImageFrame<int>> buffer;
	for (int I = 0; I != 3; ++I)
	{
		ImageFrame<int> img;
		img.data.resize(10);
		std::iota(img.data.begin(), img.data.end(), I);
		buffer.push(std::move(img));	// img is moved in.
	}
	for (int I = 0; I != 3; ++I)
		buffer.pop();					// the elements do not move. Only index is rearranged.
}