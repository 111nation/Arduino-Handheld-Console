# Arduino Handheld Gaming 
<br />

_Handheld console similar to a Game Boy and PSP_! 

Python based game engine

<div style="padding: 15px; border-left: 5px solid #e3b341; background-color: #fff9e6; color: #664d03; border-radius: 4px;">
  <strong>DEPRECIATED:</strong><br/><br/>
The handheld console device is planned to be a fully stand alone hand held that supports custom programmable games. Due to this the PyGame Engine has been depreciated. <br/><br/>

It is not feasable running a fully Python Environment with the limited 2KB of SRAM and 32KB of memory present in the Arduino. Additionally, Arduinos do not have an Operating System thus it is not possible running python environment. <br/>

The project has now shifted focus on building a custom graphics and game engine that supports users loading instructions for custom games. This required creating a new lightweight programming system that is built into the 32KB Arduino Firmware.

</div>

_There is no support for keyboard input with the PyGameEngine, the hardware control must be built_

## Requirements and Dependencies

### Software
1. Arduino IDE
2. Python3
3. [PyGame](https://www.pygame.org/)
4. [PySerial](https://pyserial.readthedocs.io/en/latest/pyserial.html)

### Hardware
1. 1 x Arduino Uno
2. 1 x `HW-504` Analogue Joystick Module
3. 1 x Push Button connected to 10k&ohm; resistor
4. 1 x RGB LED Module
5. Lots of wires!

## Setting up the Project

`Hardware/Hardware.ino` defines the data pins according to the `constexpr int` parameters. Wire the Joystick, RGB LED Module and Button according to these parameters.

Make sure you install [PyGame](https://www.pygame.org/) and [PySerial](https://pyserial.readthedocs.io/en/latest/pyserial.html). Under `GameEngine/hardware.py`, change the `ser = serial.Serial('/dev/ttyACM0')` to the port the Arduino is connected to on your computer. For example, `ser = serial.Serial('COM3')`, to connect to the COM3 Port on Windows. 

> [!TIP]
> To find out the Arduino's COM Port, use Arduino IDE or plug in your Arduino and use Device Manager (Windows) to determine which COM port the Arduino is connected to.


