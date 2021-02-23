#!/usr/bin/env node

//*** SMARTPHONE DOORLOCK ***//

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
// Parameters: buttonPin
// The GPIO pin the signal wire on your button
// is connected to. It is okay to have no button connected
//
// Parameters: ledPin
// The GPIO pin the signal wire on your led
// is connected to. It is okay to have no ledconnected
//
// Parameter: blynkToken
// The token which was generated for your blynk
// project
//
// **************************************** //
var unlockedState = 1000;
var lockedState = 2200;

var motorPin = 14;

var blynkToken = '2bUf_aeciHGxk045pkFXgO9Le8S8IoXs';

// *** Start code *** //

var locked = true

//Setup servo
var Gpio = require('pigpio').Gpio,
  motor = new Gpio(motorPin, {mode: Gpio.OUTPUT});
  
//Setup blynk
var Blynk = require('blynk-library');
var blynk = new Blynk.Blynk(blynkToken,
  options= { addr:"blynk-cloud.com", port:443 }
);
//var blynk = new Blynk.Blynk(blynkToken);
var v0 = new blynk.VirtualPin(0);
var v1 = new blynk.VirtualPin(1);
//var terminal = new blynk.VirtualPin(2);
var displayVal = new blynk.VirtualPin(3);

console.log("locking door")
lockDoor()

v0.on('write', function(param) {
	console.log('V0:', param);
  	if (param[0] === '0') { //unlocked
  		unlockDoor()
  	} else if (param[0] === '1') { //locked
  		lockDoor()
  	} else {
  		blynk.notify("Door lock button was pressed with unknown parameter");
  	}
});

v1.on('write', function(param) {
		if(param[0] == '1'){
			displayVal.write(getTemp());
			//terminal.write(getTemp());
			console.log(getTemp());
		}
});

/*terminal.on('write', function() {
	terminal.write(getTemp());
}); */

blynk.on('connect', function() { console.log("Blynk ready."); });
blynk.on('disconnect', function() { console.log("DISCONNECT"); });

function lockDoor() {
	motor.servoWrite(lockedState);
	locked = true

	//notify
  	blynk.notify("Door has been locked!");
  	
  	//After 1.5 seconds, the door lock servo turns off to avoid stall current
  	setTimeout(function(){motor.servoWrite(0)}, 1500)
}

function unlockDoor() {
	motor.servoWrite(unlockedState);
	locked = false

	//notify
  	blynk.notify("Door has been unlocked!"); 

  	//After 1.5 seconds, the door lock servo turns off to avoid stall current
  	setTimeout(function(){motor.servoWrite(0)}, 1500)
}

function getTemp() {
	const execSync = require('child_process').execSync;
	const output = execSync('vcgencmd measure_temp', { encoding: 'utf-8' });
	return output;
}
