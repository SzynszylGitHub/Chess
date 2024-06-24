#pragma once
#include "SFML/Graphics.hpp"

template<class T>
sf::Vector2f operator*(sf::Vector2f vec, T t) {
    return sf::Vector2f(vec.x / t, vec.y / t);
}

template<class T>
sf::Vector2f operator/(sf::Vector2f vec, T t) {
    return sf::Vector2f(vec.x / t, vec.y / t);
}

template<class T>
sf::Vector2f operator+(sf::Vector2f vec, T t) {
    return sf::Vector2f(vec.x / t, vec.y / t);
}

template<class T>
sf::Vector2f operator-(sf::Vector2f vec, T t) {
    return sf::Vector2f(vec.x - t, vec.y - t);
}

sf::Vector2f operator+(sf::Vector2f a,sf::Vector2f b) {
    return sf::Vector2f(a.x + b.x, a.y + b.y);
}

sf::Vector2f operator-(sf::Vector2f a, sf::Vector2f b) {
    return sf::Vector2f(a.x - b.x, a.y - b.y);
}

sf::Vector2f operator*(sf::Vector2f a, sf::Vector2f b) {
    return sf::Vector2f(a.x * b.x, a.y * b.y);
}

sf::Vector2f operator/(sf::Vector2f a, sf::Vector2f b) {
    return sf::Vector2f(a.x / b.x, a.y / b.y);
}