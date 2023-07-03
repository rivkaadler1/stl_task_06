#pragma once
#include "DistanceCalculator.h"

/**
 * The ManhattanDistanceCalculator class is a concrete implementation of the DistanceCalculator class
 * that calculates the Manhattan distance between two locations.
 */
class ManhattanDistanceCalculator : public DistanceCalculator
{
public:
    /**
     * Calculates the Manhattan distance between two locations.
     *
     * @param loc1 The first location.
     * @param loc2 The second location.
     * @return The Manhattan distance between the two locations.
     */
    double calculateDistance(const Location& loc1, const Location& loc2) override;
};
