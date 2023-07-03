#pragma once
#include "DistanceCalculator.h"

/**
 * The EuclideanDistanceCalculator class is a concrete implementation of the DistanceCalculator class
 * that calculates the Euclidean distance between two locations.
 */
class EuclideanDistanceCalculator : public DistanceCalculator 
{
public:
    /**
     * Calculates the Euclidean distance between two locations.
     *
     * @param loc1 The first location.
     * @param loc2 The second location.
     * @return The Euclidean distance between the two locations.
     */
    double calculateDistance(const Location& loc1, const Location& loc2) override;
};
