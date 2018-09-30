#pragma once

#include <functional>
#include <SFML/Graphics.hpp>

struct Vector2
{
    int x, z;
};

bool operator ==(const Vector2& left, const Vector2& right) noexcept;
bool operator !=(const Vector2& left, const Vector2& right) noexcept;

namespace std
{
    template<>
    struct hash<Vector2>
    {
        size_t operator()(const Vector2& vect) const noexcept
        {
            std::hash<decltype(vect.x)> hasher;

            auto hash1 = hasher(vect.x);
            auto hash2 = hasher(vect.z);

            return std::hash<decltype(vect.x)>{}((hash1 ^ hash2) >> 2);
        }
    };
}

namespace std
{
    template<>
    struct hash<sf::Vector3i>
    {
        size_t operator()(const sf::Vector3i& vect) const noexcept
        {
            std::hash<decltype(vect.x)> hasher;

            auto hash1 = hasher(vect.x);
            auto hash2 = hasher(vect.y);
            auto hash3 = hasher(vect.z);

            return std::hash<decltype(vect.x)>{}((hash1 ^ (hash2 << hash3) ^ hash3));
        }
    };
}

