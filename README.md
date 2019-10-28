# Simple Control Simulator

This application is a simulator for a simple controller. It was built as the capstone project for the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

## App Overview
The application implements a simple physical model and a controller. The phyical model is a House with four rooms (North, East, South, and West). Each room has a heater as well as a window. The House also has a fan which mixes the air of the four rooms. The House is located in a World which has an ambient temperature and solar radiation, both of which vary with the time of day. The Controller's objective is to regulate the temperature in each room to be as close as possible to the House desired temperature. The application has a text based UI which displays the time of day, the World ambient temperature and solar radiation, as well as the House room temperatures and state of the fan (on/off), heaters (on/off), and windows (open/closed).


## Dependencies

The following dependencies were set by Udacity and required to successfully build the application.
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./controller`

## Application code structure

The application consists of the `main()` function and four classes:

1. `World` : models the "outside world" environment. 

    * Objects: `_time_of_day`, `_ambient_temperature`, `_solar_radiation`, `_solar_angle`
    * Methods: `simulate()`, `getToD`, `getAmbientTemperature`, `GetSolarRadiation`, `GetSolarAngle`

2. `House` : models the system the Controller is operating on. Its state is determined by the World and the actions taken by the Controller.
    * Objects: `_actual_temperature` (vector), `_fan_status` (vector), `_heater_status` (vector), `_window_status` (vector).
    * Methods: `simulate()`, `getFan()`, `setFan()`, `getHeater()`, `setHeater()`, `getWindow()`, `setWindow()`

3. `Controller` : models a very simple controller.
    * Objects: `target_temperature`
    * Methods: `simulate()`

4. `UI` : The UI, or User Interface, prints out the value of some of the House and World objects.
    * Objects: 
    * Methods: `simulate()`

