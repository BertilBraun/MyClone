#include "Random.h"

Rand & Rand::get() {
	static Rand r;
	return r;
}

int Rand::intInRange(int min, int max) {

	std::uniform_int_distribution<int> dist(min, max);
	return dist(randomEngine);
}

Rand::Rand() {
	randomEngine.seed(std::time(nullptr));
}
