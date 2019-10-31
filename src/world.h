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
    ~World() {};

    // Getters and Setters
    long clock();
    long timeOfDay();
    double ambientTemperature();
    double solarRadiationLevel();
    double azimuthAngle();

    // Typical behaviour methods
    void simulate();    // Public method to start simulating the World environment
    
    private:
    
    // Typical behaviour methods
    void updateWorld();    // Private method to simluate the World environment
    void updateClock();
    void updateTimeOfDay();
    void updateAmbientTemperature();
    void updateSolarRadiationLevel();
    void updateAzimuthAngle();

    long _time_step;
    long _clock;
    long _time_of_day;
    double _ambient_temperature;
    double _solar_radiation; 
    double _azimuth_angle;
};

#endif