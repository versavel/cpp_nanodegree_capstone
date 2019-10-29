#include <cmath>        // used by std::sin and std::cos
#include <algorithm>    // used by std::max
#include <iostream>
#include "world.h"

double const & pi = M_PI;
long const kSecInHour = 3600;
long const kSecInDay = 24 * kSecInHour;


double radians(double seconds)
{
    return seconds * (2*pi) / kSecInDay;
}

// Constructor
World::World(long time_step)
{
    _clock = 0; // 82800;
    _time_step = time_step;
    _time_of_day = 0;
    _ambient_temperature = 383;
    _solar_radiation = 0;
    _azimuth_angle = 0;
}

// Deconstructor
//World::~World() {};

// Return simalation clock value (seconds)
long World::Clock()
{
    return _clock;
}

double World::AmbientTemperature()
{
    return _ambient_temperature;
}

long World::TimeOfDay()
{
    return _time_of_day;
}

double World::SolarRadiationLevel()
{
    return _solar_radiation;
}

double World::AzimuthAngle()
{
    return _azimuth_angle;
}

// Typical behaviour methods
// Public method to start simulating the World environment
void World::simulate()
{
    _UpdateWorld();
}

// Private method to simluate the World environment
void World::_UpdateWorld()
{
    _UpdateClock();
    _UpdateTimeOfDay();
    _UpdateAmbientTemperature();
    _UpdateSolarRadiationLevel();
    _UpdateAzimuthAngle();

}

// Updat the clock used by simulation functions. Units: seconds
void World::_UpdateClock()
{
    _clock = _clock + _time_step;
}

// Update the time of day. Units: seconds
void World::_UpdateTimeOfDay()
{
    _time_of_day = _clock % kSecInDay;
}

// Update the ambient/outdoor temperature. Units: K (Kelvin)
//      The ambient temperature is a sine wave swinging between 5 and 15C.
//      It peaks at 3 pm and has a 5 degree amplitude (i.e. 10 degree peak to bottom), 
void World::_UpdateAmbientTemperature()
{
    _ambient_temperature = (10 + 273) + 5 * std::cos(radians(_clock - 15*kSecInHour));
}

// Update the level of solar radiation. Units: W m-2
//      The level of solar is modeled here as the positive part of a sine wave,
//      starting and ending at 6 am and 6 pm, respectively.
//      Its peak level is 1000 W m-2, at 12 pm noon.
void World::_UpdateSolarRadiationLevel()
{
    _solar_radiation = 1000 * std::max(std::sin(radians(_time_of_day - 6*kSecInHour)), 0.);
}

// Update the azimuth angle of the sun, relative to the sun. Units: radians
//      The azimuth angle is modeled as 90 degrees (East) at sunrise (6 am),
//      180 degrees (South) at 12 pm noon, and 270 degrees (West) at sunset (6pm).
void World::_UpdateAzimuthAngle()
{
    _azimuth_angle = radians(_time_of_day);
}

