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

var ledPin = 18;

var blynkToken = 'PUT_YOUR_AUTHENTICATION_CODE';

// *** Start code *** //

var locked = true

//Setup servo and LED
var Gpio = require('pigpio').Gpio,
  led = new Gpio(ledPin,{mode: Gpio.OUTPUT});

  
//Setup blynk
var Blynk = require('blynk-library');
var blynk = new Blynk.Blynk(blynkToken, options= 
	{ connector:new Blynk.TcpClient()
  });
//var blynk = new Blynk.Blynk(blynkToken);
var v0 = new blynk.VirtualPin(0);
//r v1 = new blynk.VirtualPin(1);


console.log("locking door")
lockDoor()

v0.on('write', function(param) {
	console.log('Blynk Database Value: V0 = ', param);
  	if (param[0] === '0') { //unlocked
  		console.log("Door is unlocked");
		unlockDoor()
  	} else if (param[0] === '1') { //locked
  		console.log("Door is locked");
		lockDoor()
  	} else {
  		//blynk.notify("Door lock button was pressed with unknown parameter");
  	}
});


blynk.on('connect', function() { console.log("Blynk ready."); });
blynk.on('disconnect', function() { console.log("DISCONNECT"); });

function lockDoor() {
	locked = true

	// Turning led off 
	led.digitalWrite(0);
	
	// Send door is locked status
	//v1.write("Locked");

	//notify
  	//blynk.notify("Door has been locked!");
  	
}

function unlockDoor() {
	locked = false

	// Turning led off 
	led.digitalWrite(1);

	// Send door is unlocked status
	// v1.write("UnLocked");
	//notify
  	//blynk.notify("Door has been unlocked!"); 
}


