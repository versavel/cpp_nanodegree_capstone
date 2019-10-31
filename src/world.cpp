#include <cmath>        // used by std::sin and std::cos
#include <algorithm>    // used by std::max
#include <iostream>
#include "world.h"

// static constants
static double const & pi = M_PI;
static long const kSecInHour = 3600;
static long const kSecInDay = 24 * kSecInHour;

// 
double radians(double seconds)
{
    return seconds * (2*pi) / kSecInDay;
}

// Constructor
World::World(long time_step)
{
    _clock = 0;
    _time_step = time_step;
    _time_of_day = 0;
    _ambient_temperature = 383;
    _solar_radiation = 0;
    _azimuth_angle = 0;
}

// Return simalation clock value (seconds)
long World::clock()
{
    return _clock;
}

double World::ambientTemperature()
{
    return _ambient_temperature;
}

long World::timeOfDay()
{
    return _time_of_day;
}

double World::solarRadiationLevel()
{
    return _solar_radiation;
}

double World::azimuthAngle()
{
    return _azimuth_angle;
}

// Typical behaviour methods
// Public method to start simulating the World environment
void World::simulate()
{
    updateWorld();
}

// Private method to simluate the World environment
void World::updateWorld()
{
    updateClock();
    updateTimeOfDay();
    updateAmbientTemperature();
    updateSolarRadiationLevel();
    updateAzimuthAngle();

}

// Updat the clock used by simulation functions. Units: seconds
void World::updateClock()
{
    _clock = _clock + _time_step;
}

// Update the time of day. Units: seconds
void World::updateTimeOfDay()
{
    _time_of_day = _clock % kSecInDay;
}

// Update the ambient/outdoor temperature. Units: K (Kelvin)
//      The ambient temperature is a sine wave swinging between 5 and 15C.
//      It peaks at 3 pm and has a 5 degree amplitude (i.e. 10 degree peak to bottom), 
void World::updateAmbientTemperature()
{
    _ambient_temperature = (10 + 273) + 5 * std::cos(radians(_clock - 15*kSecInHour));
}

// Update the level of solar radiation. Units: W m-2
//      The level of solar is modeled here as the positive part of a sine wave,
//      starting and ending at 6 am and 6 pm, respectively.
//      Its peak level is 400 W m-2, at 12 pm noon.
void World::updateSolarRadiationLevel()
{
    _solar_radiation = 400 * std::max(std::sin(radians(_time_of_day - 6*kSecInHour)), 0.);
}

// Update the azimuth angle of the sun, relative to the sun. Units: degrees
//      The azimuth angle is modeled as 90 degrees (East) at sunrise (6 am),
//      180 degrees (South) at 12 pm noon, and 270 degrees (West) at sunset (6pm).
void World::updateAzimuthAngle()
{
    _azimuth_angle = double(_time_of_day) / 240;
}

