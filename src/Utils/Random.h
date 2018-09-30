#pragma once

#include <random>
#include <ctime>

#include "CopyInhertance.h"

class Rand : public Singleton {
public:
	static Rand& get();

	int intInRange(int min, int max);

private:
	Rand();

	std::mt19937 randomEngine;
};