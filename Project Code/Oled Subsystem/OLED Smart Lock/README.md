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
