#pragma once
#include <array>

template <class T, size_t SIZE>
class Array3D {
public:
	T & getIndex(int x, int y, int z) {
		if (outOfRange(x) || outOfRange(y) || outOfRange(z))
			return data[0];
		return data[x + y * SIZE + z * SIZE * SIZE];
	}

	const T& getIndex(int x, int y, int z) const {
		if (outOfRange(x) || outOfRange(y) || outOfRange(z))
			return data[0];
		return data[x + y * SIZE + z * SIZE * SIZE];
	}

	T & getIndex(int i) {
		if (i < 0 || i >= SIZE * SIZE * SIZE)
			return data[0];

		return data[i];
	}

	const T& getIndex(int i) const {
		if (i < 0 || i >= SIZE * SIZE * SIZE)
			return data[0];
		return data[i];
	}

	void setIndex(int x, int y, int z, const T& newData) {
		if (outOfRange(x) || outOfRange(y) || outOfRange(z))
			return;
		data[x + y * SIZE + z * SIZE * SIZE] = newData;
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
	std::array<T, SIZE * SIZE * SIZE> data;
};
