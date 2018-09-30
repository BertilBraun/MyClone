#pragma once
#include <mutex>

class Mutexes {
public:
	static Mutexes& get() {
		static Mutexes m;
		return m;
	}
	std::mutex mutex;
	std::mutex updateMutex;
	std::mutex blockMutex;
};