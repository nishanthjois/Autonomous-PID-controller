# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

# Note 

In order to avoid build failure, I changed "main.cpp".

~~~~
/Users/hideto.kimura/carnd/carnd_term2/carnd_pid_control_project/src/main.cpp:39:5: error: 
      no matching member function for call to 'onMessage'
  h.onMessage([&pid](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t ...
                                                 ^
/usr/local/include/uWS/Group.h:69:10: note: candidate function not viable: no
      known conversion from '(lambda at
      /Users/hideto.kimura/carnd/carnd_term2/carnd_pid_control_project/src/main.cpp:39:15)'
      to 'std::function<void (WebSocket<true> *, char *, size_t, OpCode)>' (aka
      'function<void (WebSocket<true> *, char *, unsigned long, uWS::OpCode)>')
      for 1st argument
    void onMessage(std::function<void(WebSocket<isServer> *, char *, siz...
                                                          ^
/usr/local/include/uWS/Group.h:69:10: note: candidate function not viable: no
      known conversion from '(lambda at
      /Users/hideto.kimura/carnd/carnd_term2/carnd_pid_control_project/src/main.cpp:39:15)'
      to 'std::function<void (WebSocket<false> *, char *, size_t, OpCode)>' (aka
      'function<void (WebSocket<false> *, char *, unsigned long, uWS::OpCode)>')
      for 1st argument
~~~~
~~~~
h.onMessage([&pid](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, uWS::OpCode opCode) {
ws.send()
↓ (changed to pointer)
h.onMessage([&pid](uWS::WebSocket<uWS::SERVER> *ws, char *data, size_t length, uWS::OpCode opCode) {
ws->send()
~~~~

## Approach

Based on the value when operating the simulator with the game pad,   
I decided the upper and lower limits of the steering from -10.0 to 10.0.  
And like "behavior cloning project", I fixed throttle value at 0.3.  

I tuned Kp, Ki and Kd one by one, manually.  
Initial parameter is below.

~~~~~
double Kp = 0.1;  // proportional coefficient
double Ki = 0.0;  // integral coefficient
double Kd = 0.0;  // differential coefficient
~~~~~

If Kp > 1.0, then the car overshoots greatly, and if Kp < 0.1, then it could not turn around the curve.  
Finally I set Kp value at 0.2.

~~~~~
double Kp = 0.2;  // proportional coefficient
double Ki = 0.0;  // integral coefficient
double Kd = 0.0;  // differential coefficient
~~~~~

Next, Since Kd is a coefficient for the difference from the previous cte,  
I'd like to increase the steering value as the defference increases.  
So Kd must be greater than 1.0. Kd is bigger, the car can turn even if it is a tight curve.  
Finally I set Kd value at 4.0.

~~~~~
double Kp = 0.2;  // proportional coefficient
double Ki = 0.0;  // integral coefficient
double Kd = 4.0;  // differential coefficient
~~~~~

As the integrate value of cte increased, the car turned around the same spot.  
I tried Ki value from 0.1 to 0.0001 and finally I set Ki value at 0.0001.

~~~~~
double Kp = 0.2;  // proportional coefficient
double Ki = 0.0001;  // integral coefficient
double Kd = 4.0;  // differential coefficient
~~~~~

These hyper parameters brought the good result. The result is below.  
Please click on the images if you want to see the video:

<a href="http://www.youtube.com/watch?feature=player_embedded&v=yCJ-cya4jbI" target="_blank">
<img src="http://img.youtube.com/vi/yCJ-cya4jbI/0.jpg" alt="PID Control" width="240" height="180" border="10" />
</a>

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets) == 0.13, but the master branch will probably work just fine
  * Follow the instructions in the [uWebSockets README](https://github.com/uWebSockets/uWebSockets/blob/master/README.md) to get setup for your platform. You can download the zip of the appropriate version from the [releases page](https://github.com/uWebSockets/uWebSockets/releases). Here's a link to the [v0.13 zip](https://github.com/uWebSockets/uWebSockets/archive/v0.13.0.zip).
  * If you run OSX and have homebrew installed you can just run the ./install-mac.sh script to install this
* Simulator. You can download these from the [project intro page](https://github.com/udacity/CarND-PID-Control-Project/releases) in the classroom.

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./
