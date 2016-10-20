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

    template <class T>
    int angleDegrees(sf::Vector2<T>& vec1, sf::Vector2<T>& vec2) {
        return atan2(vec2.y, vec2.x) - atan2(vec1.y, vec1.x);
    };

}

#endif //LEFT2DIE_VECTORUTIL_H
