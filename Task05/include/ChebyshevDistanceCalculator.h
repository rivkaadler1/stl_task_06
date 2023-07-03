#pragma once
#include "DistanceCalculator.h"

/**
 * The ChebyshevDistanceCalculator class is a concrete implementation of the DistanceCalculator class
 * that calculates the Chebyshev distance between two locations.
 */
class ChebyshevDistanceCalculator : public DistanceCalculator {
public:
    /**
     * Calculates the Chebyshev distance between two locations.
     *
     * @param loc1 The first location.
     * @param loc2 The second location.
     * @return The Chebyshev distance between the two locations.
     */
    double calculateDistance(const Location& loc1, const Location& loc2) override;
};


