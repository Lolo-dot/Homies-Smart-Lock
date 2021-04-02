This is the working directory for oled smart lock code

##### Terminal_pc13_virtual_button_success.ino
Code to test basic connection and functionality. Able to read and write text as well as turn on and of stm32 onboard led pin.

##### Create blynk-ser.sh
bash shell to bring the server online, as provided by default from the blynk library

##### ssd1306_128x64_spi_modified.ino
Initial working test code to get OLED to display animations. No blynk integration yet.

##### OLED_firmware_test_G.ino
Blynk app includes terminal, button (lock/unlock), value display ( of lock status)
and a superchart (of server data history)
OLED splash screen and setup blinks. Oled and led respond to door state
-requires optimized server synchronization and minor bug fixes

##### OLED_firmware_test_I_modified_success.ino
This is the most current version of the OLED subsystem code, as of March 20th. 
Uses the group authentication key and is on the same database as other components. 
It is not a final product because this modifies virtual pin 0 (lock and unlock state) and virtual pin 2 (status of lock and unlock state). 
In the future this should only read those values, not write them to the databse. 
Super chart is working for "live" data range.
  
##### OLED_firmware_final.ino
Final OLED subsystem firmware as of April 2nd. Fixes include  
-synced V0 pin value on boot   
-Read only for database values (lock unlock state)  
-Welcome message  display not showing  
