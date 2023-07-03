#pragma once
#include "Location.h"
#include <cmath>

/**
 * The DistanceCalculator class is an abstract base class that defines an interface for calculating distances
 * between two locations in a two-dimensional space.
 */
class DistanceCalculator {
public:
    /**
     * Calculates the distance between two locations.
     *
     * @param loc1 The first location.
     * @param loc2 The second location.
     * @return The distance between the two locations.
     */
    virtual double calculateDistance(const Location& loc1, const Location& loc2) = 0;
};




