#include "LocationSearcher.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>

LocationSearcher::LocationSearcher()
{
    _distanceCalculators[0] = std::make_unique<EuclideanDistanceCalculator>();
    _distanceCalculators[1] = std::make_unique<ChebyshevDistanceCalculator>();
    _distanceCalculators[2] = std::make_unique<ManhattanDistanceCalculator>();
}

void LocationSearcher::run()
{
    _readLocationData();
    _processLocationSearchByRadius();
}

void LocationSearcher::_readLocationData()
{
    std::ifstream file("data.txt");
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open data.txt");
    }

    std::string line;
    std::string cityName;
    std::string xStr, yStr;
    while (getline(file, cityName))
    {
        if (getline(file, line))
        {
            std::istringstream iss(line);
            if (!(getline(iss, xStr, '-') && getline(iss, yStr)))
            {
                throw std::runtime_error("Invalid file format: data.txt");
            }

            try
            {
                double x = std::stod(xStr);
                double y = std::stod(yStr);
                _cityLocationMap[cityName] = Location(x, y);
                _xCoordinateMap.emplace(x, cityName);
                _yCoordinateMap.emplace(y, cityName);
            }
            catch (const std::exception& e) {
                throw std::runtime_error("Invalid coordinate value: " + line);
            }
        }
        else
        {
            throw std::runtime_error("Incomplete data for city: " + cityName);
        }
    }

    file.close();
}

void LocationSearcher::_printErrorMessage(const std::string& message)
{
    std::cerr << "ERROR: " << message << std::endl;
}

void LocationSearcher::_processLocationSearchByRadius()
{
    std::string cityName;
    while (true)
    {
        std::cout << "Please enter the selected city name (or '0' to exit): ";
        std::getline(std::cin, cityName);

        if (cityName == "0") {
            break;
        }

        auto cityRange = _cityLocationMap.equal_range(cityName);
        if (cityRange.first == cityRange.second) {
            _printErrorMessage(cityName + " is not found in the city list. Please try again.");
            continue;
        }

        double radius;
        int norm;
        std::cout << "Please enter the desired radius: ";
        std::cin >> radius;
        std::cout << "Please enter the desired norm (0 - L2, Euclidean distance, 1 - Linf, Chebyshev distance, 2 - L1, Manhattan distance): ";
        std::cin >> norm;
        std::unique_ptr<DistanceCalculator>& distanceCalculator = _distanceCalculators[norm];
        const Location& selectedLocation = _cityLocationMap[cityName];

        std::set<std::string> xRangeCities = _filterCitiesByXRange(selectedLocation, radius);
        std::set<std::string> yRangeCities = _filterCitiesByYRange(selectedLocation, radius);
        std::set<std::string> northernCities = _getCitiesToTheNorth(selectedLocation);

        std::vector<std::string> matchingCities = _findMatchingCities(xRangeCities, yRangeCities);

        //filter matching cities by radius
        matchingCities.erase(std::remove_if(matchingCities.begin(), matchingCities.end(),
            [&](const std::string& city) {
                const Location& location = _cityLocationMap[city];
                return (distanceCalculator->calculateDistance(selectedLocation, location) > radius);
            }), matchingCities.end());

        _printSearchResults(matchingCities, northernCities, radius, norm);

        std::cout << std::endl;
    }
}

std::set<std::string> LocationSearcher::_filterCitiesByXRange(const Location& selectedLocation, double radius) const
{
    double xMin = selectedLocation._x - radius;
    double xMax = selectedLocation._x + radius;

    std::set<std::string> xRangeCities;
    std::transform(_xCoordinateMap.lower_bound(xMin), _xCoordinateMap.upper_bound(xMax),
        std::inserter(xRangeCities, xRangeCities.begin()),
        [](const std::pair<double, std::string>& entry) {
            return entry.second;
        });

    return xRangeCities;
}

std::set<std::string> LocationSearcher::_filterCitiesByYRange(const Location& selectedLocation, double radius) const
{
    double yMin = selectedLocation._y - radius;
    double yMax = selectedLocation._y + radius;

    std::set<std::string> yRangeCities;
    std::transform(_yCoordinateMap.lower_bound(yMin), _yCoordinateMap.upper_bound(yMax),
        std::inserter(yRangeCities, yRangeCities.begin()),
        [](const std::pair<double, std::string>& entry) {
            return entry.second;
        });

    return yRangeCities;
}

std::set<std::string> LocationSearcher::_getCitiesToTheNorth(const Location& selectedLocation) const
{
    std::set<std::string> northernCities;
    double yMax = selectedLocation._y;

    std::transform(_yCoordinateMap.lower_bound(yMax), _yCoordinateMap.end(),
        std::inserter(northernCities, northernCities.begin()),
        [](const std::pair<double, std::string>& entry) {
            return entry.second;
        });

    return northernCities;
}

std::vector<std::string> LocationSearcher::_findMatchingCities(const std::set<std::string>& xRangeCities,
    const std::set<std::string>& yRangeCities) const
{
    std::vector<std::string> matchingCities;

    std::set_intersection(xRangeCities.begin(), xRangeCities.end(),
        yRangeCities.begin(), yRangeCities.end(),
        std::back_inserter(matchingCities));

    return matchingCities;
}


void LocationSearcher::_printSearchResults(const std::vector<std::string>& matchingCities,
    const std::set<std::string>& northernCities, double radius, int norm) const
{
    std::cout << "Search results:" << std::endl;
    std::cout << matchingCities.size() << " city/cities found in the given radius." << std::endl;
    std::cout << northernCities.size() << " cities are to the north of the selected city." << std::endl;
    std::cout << "Matching cities within radius " << radius << " using the selected norm: " << norm << std::endl;

    std::copy(matchingCities.begin(), matchingCities.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

