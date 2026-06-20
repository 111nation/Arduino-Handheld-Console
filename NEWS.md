### 20 June 2026

The handheld console device is planned to be a fully stand alone hand held that supports custom programmable games. Due to this the PyGame Engine has been depreciated. The Arduino is meant to handle interpreting custom game instructions and running a full Python Environment is not feasable with the limited 2KB of SRAM and 32KB of memory present in the Arduino. Additionally, Arduinos do not have an Operating System thus it is not possible running python environment.

The project has now shifted focus on building a custom graphics and game engine that supports users loading instructions for custom games. This required creating a new lightweight programming system that is built into the 32KB Arduino Firmware.

This will be a massive challenge balancing features and performance. THe screen to be used will most likely be the W18366 Wave 2.4" SPI  65K Colour display.

TO DO:
- Create custom scripting language
- Create interpreter for scripting language
- Figure out possible SD card reading for loading games
- Map game engine to work on external display.

