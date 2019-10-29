#ifndef WORLD_H
#define WORLD_H

class World 
{
    /*
    models the "outside world" environment
    */

    public:
    
    // Constructor and Deconstructors
    World(long time_step);
    //~World();

    // Getters and Setters
    long Clock();
    long TimeOfDay();
    double AmbientTemperature();
    double SolarRadiationLevel();
    double AzimuthAngle();

    // Typical behaviour methods
    void simulate();    // Public method to start simulating the World environment
    
    private:
    
    // Typical behaviour methods
    void _UpdateWorld();    // Private method to simluate the World environment
    void _UpdateClock();
    void _UpdateTimeOfDay();
    void _UpdateAmbientTemperature();
    void _UpdateSolarRadiationLevel();
    void _UpdateAzimuthAngle();

    long _time_step;
    long _clock;
    long _time_of_day;
    double _ambient_temperature;
    double _solar_radiation; 
    double _azimuth_angle;
};

#endif