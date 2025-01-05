# M5Dial getting started
This is a very basic example you can run on the M5Dial device. It is largely based on their example code from 
https://github.com/m5stack/M5Unified
and
https://github.com/m5stack/M5Dial

as well as info from https://www.youtube.com/watch?v=M8y-s4tGqwQ


The project includes the platfomio.ini file as well as an example to allow testing the main functions of touch display, encoder and button.
The platformio.ini was derived using the [PlatformIO Documentation](https://docs.platformio.org/en/stable/boards/espressif32/m5stack-core-esp32.html)
I found when I tried using the M5 logging functions that they didn't mix well with code where drawing on the screen was occuring (even when I set the screen loglevel to none) so in the example I am using the ESP_LOGx functions instead.

You chould be able to simply open up the folder in VSCode (assuming you have installed the PlatformIO VSCode extension), and it should automatically fetch and configure the toolchain, and then just click the upload button to load it to the dial.
