#pragma once

class NonCopyable {
public:
	NonCopyable() = default;
	NonCopyable(NonCopyable&) = delete;
	void operator=(NonCopyable&) = delete;
};

class NonMovable {
public:
	NonMovable(NonMovable&&) = delete;

	NonMovable& operator=(NonMovable&&) = delete;

protected:
	NonMovable() = default;
};

class Singleton : public NonMovable, public NonCopyable { };