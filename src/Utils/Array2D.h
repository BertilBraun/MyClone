#pragma once
#include <array>

template <class T, size_t SIZE>
class Array2D {
public:
	T& getIndex(int x, int y) {
		if (outOfRange(x) || outOfRange(y))
			return data[0]; 
		return data[x + SIZE * y];
	}

	const T& getIndex(int x, int y) const {
		if (outOfRange(x) || outOfRange(y))
			return data[0]; 
		return data[x + SIZE * y];
	}

	T& getIndex(int i) {
		if (i < 0 || i >= SIZE * SIZE)
			return data[0];
		return data[i];
	}

	const T& getIndex(int i) const {
		if (i < 0 || i >= SIZE * SIZE)
			return data[0];
		return data[i];
	}

	void setIndex(int x, int y, const T& newData) {
		if (outOfRange(x) || outOfRange(y))
			return;
		data[x + SIZE * y] = newData;
	}

	T& getMaxValue() {
		return *std::max_element(data.begin(), data.end());
	}
	
	const T& size() {
		return SIZE;
	}

	void fill(const T& val) {
		data.fill(val);
	}

	bool outOfRange(int index) {
		return index >= SIZE || index < 0;
	}

private:
	std::array<T, SIZE * SIZE> data;
};
