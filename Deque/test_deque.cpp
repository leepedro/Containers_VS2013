#include <deque>
#include <vector>
#include <iostream>

template <typename T>
class ImageFrame
{
public:
	ImageFrame(void) = default;

	ImageFrame(::size_t sz, T value)
	{
		if (this->data_.size() != sz)
		{
			std::clog << "Re-sizing a vector." << std::endl;
			this->data_.resize(sz);
		}
		for (auto it = data_.begin(); it != data_.end(); ++it)
			*it = value;
	}

	ImageFrame(const ImageFrame<T> &src) : data_(src.data_)
	{
		std::clog << "Copying a vector." << std::endl;
	}

	ImageFrame(ImageFrame<T> &&src) : data_(std::move(src.data_))
	{
		std::clog << "Moving a vector." << std::endl;
	}

	void Print(void) const
	{
		std::clog << this->data_.at(2) << std::endl;
	}

	//void Copy(T value)
	//{
	//	for (auto it = data_.begin(); it != data_.end(); ++it)
	//		*it = value;
	//}

	void Resize(::size_t sz)
	{
		this->data_.resize(sz);
	}

protected:
	std::vector<T> data_;
};

template <typename T>
void CreateImageFrame(::size_t sz, T value, ImageFrame<T> &data)
{
	ImageFrame<T> data_(sz, value);	// resize
	std::swap(data_, data);			// move
}

// A FIFO buffer is defined as a std::deque<T>.
// Memory is first allocated for each new data block, and kept for the FIFO buffer by std::move(). (BETTER!)
// FIFO buffer does NOT allocate memory for itself.
void TestScenario1(void)
{
	std::deque<ImageFrame<unsigned char>> buffer;

	// For each input frame,
	// allocate memory, and then push the content to the buffer by moving.
	for (auto I = 0; I != 3; ++I)
	{
		ImageFrame<unsigned char> frame;
		CreateImageFrame<unsigned char>(64, I + 65, frame);	// resize, move
		buffer.push_back(std::move(frame));				// move
	}

	for (const auto &frame : buffer)
		frame.Print();

	{
		buffer.pop_front();
		ImageFrame<unsigned char> frame;
		CreateImageFrame<unsigned char>(64, 3 + 65, frame);	// resize, move
		buffer.push_back(std::move(frame));				// move
	}

	for (const auto &frame : buffer)
		frame.Print();
}

// A FIFO buffer is defined as a std::deque<T>.
// Memory is first allocated for each new data block, and the content is copied to the FIFO buffer.
// FIFO buffer DOES allocate memory for itself.
void TestScenario2(void)
{
	std::deque<ImageFrame<unsigned char>> buffer;

	// For each input frame,
	// allocate memory, and then push the content to the buffer by copying.
	for (auto I = 0; I != 3; ++I)
	{
		ImageFrame<unsigned char> frame;
		CreateImageFrame<unsigned char>(64, I + 65, frame);	// resize, move
		buffer.push_back(frame);						// copy
	}

	for (const auto &frame : buffer)
		frame.Print();

	{
		buffer.pop_front();
		ImageFrame<unsigned char> frame;
		CreateImageFrame<unsigned char>(64, 3 + 65, frame);	// resize, move
		buffer.push_back(frame);						// copy
	}

	for (const auto &frame : buffer)
		frame.Print();
}

// An ideal approach.
// A FIFO buffer is defined as a standard container.
// Memory is allocated only once for each element for the buffer instead of each new data block.
// Then, the new data block is copied to the last element, and the elements in the buffer are logically pushed without actually copying data.
// It is NOT possible at this moment because we cannot logically push data without copying the data.
int main(void)
{
	TestScenario1();
	TestScenario2();
}