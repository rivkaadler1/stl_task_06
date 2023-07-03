#include "ManhattanDistanceCalculator.h"

double ManhattanDistanceCalculator::calculateDistance(const Location& loc1, const Location& loc2) {
    return std::abs(loc1._x - loc2._x) + std::abs(loc1._y - loc2._y);
}
