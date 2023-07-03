#include "EuclideanDistanceCalculator.h"

double EuclideanDistanceCalculator::calculateDistance(const Location& loc1, const Location& loc2) {
    return std::sqrt(std::pow((loc1._x - loc2._x), 2) + std::pow((loc1._y - loc2._y), 2));
}
