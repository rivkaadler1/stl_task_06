#pragma once
#include <string>
#include <map>
#include <set>
#include <vector>
#include <memory>
#include "Location.h"
#include "DistanceCalculator.h"
#include "ChebyshevDistanceCalculator.h"
#include "EuclideanDistanceCalculator.h"
#include "ManhattanDistanceCalculator.h"

/**
 * LocationSearcher is a class that allows searching for locations based on specific criteria.
 * It reads location data from a file, performs search operations, and provides search results.
 */
class LocationSearcher {
public:
    /**
     * Constructs a new LocationSearcher object.
     */
    LocationSearcher();

    /**
     * Runs the location search process.
     */
    void run();

private:
    /**
     * Reads location data from a file and populates the internal data structures.
     * The expected file format is:
     *   <city_name>
     *   <x-coordinate>-<y-coordinate>
     *   ...
     * Throws an exception if the file cannot be opened or if the data format is invalid.
     */
    void _readLocationData();

    /**
     * Prints an error message to the standard error stream.
     * @param message The error message to be printed.
     */
    void _printErrorMessage(const std::string& message);

    /**
     * Processes a location search by radius.
     * Prompts the user for input and performs the search based on the specified city, radius, and norm.
     * Prints the search results to the standard output.
     */
    void _processLocationSearchByRadius();

    /**
     * Filters cities based on their x-coordinate within a specified radius of a selected location.
     * @param selectedLocation The selected location to use as the center point.
     * @param radius The radius within which to filter the cities.
     * @return A set of city names that meet the filtering criteria.
     */
    std::set<std::string> _filterCitiesByXRange(const Location& selectedLocation, double radius) const;

    /**
     * Filters cities based on their y-coordinate within a specified radius of a selected location.
     * @param selectedLocation The selected location to use as the center point.
     * @param radius The radius within which to filter the cities.
     * @return A set of city names that meet the filtering criteria.
     */
    std::set<std::string> _filterCitiesByYRange(const Location& selectedLocation, double radius) const;

    /**
     * Retrieves cities that are located to the north of a selected location.
     * @param selectedLocation The selected location to use as the reference point.
     * @return A set of city names that are located to the north of the selected location.
     */
    std::set<std::string> _getCitiesToTheNorth(const Location& selectedLocation) const;

    /**
     * Finds the cities that appear in both the x-range cities and y-range cities sets.
     * @param xRangeCities A set of cities filtered based on their x-coordinate range.
     * @param yRangeCities A set of cities filtered based on their y-coordinate range.
     * @return A vector of city names that appear in both sets.
     */
    std::vector<std::string> _findMatchingCities(const std::set<std::string>& xRangeCities,
        const std::set<std::string>& yRangeCities) const;

    /**
     * Prints the search results to the standard output.
     * @param matchingCities A vector of city names that match the search criteria.
     * @param northernCities A set of city names that are located to the north of the selected city.
     * @param radius The specified radius used for the search.
     * @param norm The norm used for distance calculation.
     */
    void _printSearchResults(const std::vector<std::string>& matchingCities,
        const std::set<std::string>& northernCities, double radius, int norm) const;

    std::multimap<double, std::string> _xCoordinateMap;                         // Map of x-coordinate to city name
    std::multimap<double, std::string> _yCoordinateMap;                         // Map of y-coordinate to city name
    std::map<std::string, Location> _cityLocationMap;                           // Map of city name to location
    std::map<int, std::unique_ptr<DistanceCalculator>> _distanceCalculators;    // Map of norm to distance calculator
};

