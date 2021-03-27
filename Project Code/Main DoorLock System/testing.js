#!/usr/bin/env node

//*** SMARTPHONE DOORLOCK TESTING***//

// ************* PARAMETERS *************** //
// 
// Parameters: unlockedState and lockedState
// These parameters are in microseconds.
// The servo pulse determines the degree 
// at which the horn is positioned. In our
// case, we get about 100 degrees of rotation
// from 1ms-2.2ms pulse width. You will need
// to play with these settings to get it to
// work properly with your door lock
//
// Parameters: motorPin
// The GPIO pin the signal wire on your servo
// is connected to
//
// **************************************** //


var unlockedState = 1000;
var lockedState = 2000;

var motorPin = 14;

// *** Start Code *** //

//Setup servo
var Gpio = require('pigpio').Gpio, motor = new Gpio(motorPin, {mode: Gpio.OUTPUT});

motor.servoWrite(lockedState);
setTimeout(function(){motor.servoWrite(unlockedState)}, 2000)
setTimeout(function(){motor.servoWrite(0)}, 4000)

setTimeout(function(){console.log("The Servo motor should turn atleast once by now")}, 4250)
