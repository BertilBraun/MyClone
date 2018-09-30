#include "Vector2.h"

bool operator==(const Vector2& left, const Vector2& right) noexcept
{
	return  (left.x == right.x) &&
			(left.z == right.z);
}

bool operator!=(const Vector2& left, const Vector2& right) noexcept
{
	return  (left.x != right.x) ||
			(left.z != right.z);
}
