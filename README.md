# CarND-Controls-PID
PID Steering Control Implementation

In this repository a PID controller that controls the CTE (Cross-Track Error) is implemented, making the robot track the center of the road for the simulation test track.

[//]: # (Image References)

[image1]: ./result.gif "result"

---
## Results
The results of the simulation of the PID steering control can bee seen in the following [video(link)](https://youtu.be/A7-6be1BLs4).

![alt text][image1]

In this video, the pid controller is tested at 2 speeds, around 30mph and around 55mph in order to test its robustness, in both cases it remains inside the driveable area, even though, the test at 55mph presents a more oscillatory behavior.

## Description of the controller
PID control has been the industry standard for decades, its simplicity and robustness have met few competitors, by combining the Proportional, Integral and Derevative action, it is possible to get quite stable and robust controllers.

* The Proportional action basically is in charge of regulating the error by generating an action that reduces it, this action is proportional to the error itself. So bigger errors will produce stronger actions. In general, choosing a bigger Kp will make the closed loop system more aggressive (faster and stronger response), but might lead to overshoot. The proportional action alone might also not be enough, since we could have steady state error produced by a non integrating plant (this is not the case for the steering of the vehicle) or not linearities, this is why the Integral action might be necesary in many cases.

* The Integral action is in charge of regulating the error when it remains in time due to non linearities in the system (i.e. the vehicle) like dead zone in the steering mechanism, steering offset, etc. this action is proportional to the integral of the error, the integral of the error being the best indicator of error remaining in time. In general, a bigger KI will produce stronger and faster control actions, which regulate the steady state error, however it also might generate more overshoot and even make the closed loop system unstable.

* The deravative error is basically on charge of damping the controller action by opossing to big change rates of the error. This way, when the error is being reduced to drastically (which might lead to high overshoot) the derivative actions reduces the control action, avoiding this overshoot and helping the system to converge in a softer way. In general a bigger Kd action will produce a damped behavior, however it might also induce oscillations around the steady state. Sensor Noise should also be taken into account when implementing the derivative action, this is why this action usually comes with low pass filtering.

## Tunning process
The PID architecture implemented was the architecture known as parallel PID:

steering = Kp * (error + Ki * int_error + Kd*diff_error)

which contrasts with the serial PID:

steering = Kp * error + Ki * int_error + Kd*diff_error

Parallel PID allows us to have Kp multiplicating all control actions, this way, it is easier to fine tune how strong we want the control action to be, since we only have to move Kp instead of all the parameters simultaneously.

The process followed to tune the controller was 100% experimental: First Ki and Kd were set to 0.0 and Kp was tunned until an acceptable response, with reduced overshoot for the first part of the track was obtained, then Kd was moved until a response with no apparent overshoot was obtained. Then Ki parameter was tunned until the vehicle was more centered, without producing extreme overshoot. Finally, Kp was retuned to allow the vehicle to stay in the road even in the sharp curves (stronger action was required).

The parameters obtained for this process were:

* Kp = 0.1
* Ki = 0.02
* Kd = 12.0

It is important to remember that these are the parameters for the Parallel PID architecture.

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1(mac, linux), 3.81(Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

Fellow students have put together a guide to Windows set-up for the project [here](https://s3-us-west-1.amazonaws.com/udacity-selfdrivingcar/files/Kidnapped_Vehicle_Windows_Setup.pdf) if the environment you have set up for the Sensor Fusion projects does not work for this project. There's also an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3).

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

Tips for setting up your environment can be found [here](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/f758c44c-5e40-4e01-93b5-1a82aa4e044f/concepts/23d376c7-0195-4276-bdf0-e02f1f3c665d)

