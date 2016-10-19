#ifndef LEFT2DIE_VECTORUTIL_H
#define LEFT2DIE_VECTORUTIL_H

#include <SFML/System/Vector2.hpp>
#include <math.h>

namespace util {
    template <class T>
    sf::Vector2<T> normalizeVector(sf::Vector2<T>& vec) {
        float length = sqrt((vec.x * vec.x) + (vec.y * vec.y));

        return (length) ? sf::Vector2<T>(vec.x/length, vec.y/length) : vec;
    };
}

#endif //LEFT2DIE_VECTORUTIL_H
