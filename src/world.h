#ifndef WORLD_H
#define WORLD_H

class World 
{
    /*
    models the "outside world" environment
    */

    public:
    
    // Constructor and Deconstructors
    World(long time_step): _time_step(time_step) {}
    ~World() {};

    // Getters and Setters
    double getClock();
    double getAmbientTemperature();
    double getSolarRadiationLevel();
    double getSolarAngle();

    // Typical behaviour methods
    void simulate();    // Public method to start simulating the World environment
    
    private:
    
    // Typical behaviour methods
    void _UpdateWorld();    // Private method to simluate the World environment
    void _UpdateClock();
    void _UpdateAmbientTemperature();
    void _UpdateSolarRadiationLevel();
    void _UpdateSolarAngle();

    long _time_step;
    long _clock;
    double _ambient_temperature;
    double _solar_radiation; 
    double _solar_angle;
};

#endif