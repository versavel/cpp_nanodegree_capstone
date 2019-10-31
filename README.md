# Simple Control Simulator

This application is a simulator for a simple controller regulating the temperature in a building. It was developed as the capstone project for the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

## The Application: Overview
The application implements a simple physical model and a controller. The phyical model is a Building with four rooms (North, East, South, and West). Each room has a heater which the Controller can turn on and off to heat the room. Each room also has a window which the Controller can open and close to vent to room with the outside air. The Building also has a fan which mixes the air of the four rooms. The Building is located in a World. The World has air at an ambient temperature and solar radiation, both of which vary with the time of day. The Controller's objective is to regulate the temperature in each room to be as close as possible to the Building desired temperature. The application has a text based UI which displays the time of the day, the ambient temperature, the level of solar radiation and the direction it's coming from, the Controller's target temperature, as well as the Building's room temperatures and state of the fan (on/off), heaters (on/off), and windows (open/closed).
The factors that impact the room are :

* Radiation from the sun
* Radiation from the temperature difference between the room and the outdoor ambient air
* Mixing of the air between rooms, controlled by the Controller
* Exchange of air between the room and the outdoor through the window, controlled by the Controller
* Heat from the room's heater, controller by the Controller

The application will run the simulation indefinitely and update the UI for every simulated hour. Press CTRL-C to stop the application. For best results, resize the height of the terminal window to 14 to 16 lines.

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

## Build Instructions

1. Clone this repo
1. Make a build directory in the top level project directory: `mkdir build && cd build`
1. Create the CMake files: `cmake ..`
1. Compile and link the source code: `make`
1. Run the application: `./controller`

## Application code structure

The application consists of the `main()` function and four classes:

1. `World` : models the "outside world" environment. 

    * Objects: `_clock`, `_time_of_day`, `_time_step`, `_ambient_temperature`, `_solar_radiation`, `_solar_angle`
    * Getters/Setters: `timeOfDay`, `ambientTemperature`, `solarRadiationLevel`, `azimuthAngle`
    * Behaviour methods: `simulate`, `updateWorld`, `updateClock`, `updateTimeOfDay`, `updateAmbientTemperature`, `updateSolarRadiationLevel`, `updateAzimuthAngle`

1. `Building` : models the system regulated by the Controller. Its state is determined by the World and the actions taken by the Controller.
    * Objects: `_actual_temperature` (vector), `_fan_state`, `_heater_state` (vector), `_window_state` (vector), `_last_clock`, `_current_clock`, `_interval`, `_world`
    * Getters and Setters: `getFan`, `setFan`, `getHeater`, `setHeater`, `getWindow`, `setWindow`, `roomTemperature`
    * Behaviour methods: `simulate`, `updateBuilding`, `updateActualTemperatures`

1. `Controller` : models a very simple controller.
    * Objects: `_world`, `_building`
    * Getter: `targetTemperature`
    * Behaviour methods: `simulate`, `updateController`, `updateHeatersAndWindows`, `updateFan`

1. `UI` : The UI, or User Interface, prints out the value of some of the Building and World objects.
    * Objects: `_world`, `_building`, `_controller`
    * Behaviour methods: `simulate`, `updateUI`, `printTopSection`, `printBottomSection`

The `main()` function instantiates an object for each class and then runs the simulation in an infinite loop. The application is run in a single thread. A future implementation could add concurrency, though it's not necessary since the application is plenty fast. As a matter of fact, main() puts the application to sleep for 150 milliseconds after each simulation step so that the user can read the UI and observe the results of every simulated hour.

## Rubric points addressed in the code

1. *The project demonstrates an understanding of C++ functions and control structures:* `controller.cpp` lines 25-42 is a good example of constrol structures using IF conditions and FOR loops

1. *The project uses Object Oriented Programming techniques:* the project has four classes. The `building.h` header file shows the class declaration for the Building class.

1. *Classes use appropriate access specifiers for class members:* The Building class declaration in `building.h` shows the use of the `public` (line 21) and `private` (line 49) access specifiers. Since there is no class inheriting from another class, `protected` wasn't used.

1. *Class constructors utilize member initialization lists:* The UI class constructor on lines 17 and 18 in `ui.h` uses an Initializer List.

1. *The project uses smart pointers instead of raw pointers:* lines 16 to 19 in `main.cpp` are a good example of the use of `shared_ptr` for shared class objects.