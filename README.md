# Arduino Handheld Gaming 
<br />

_Handheld console similar to a Game Boy and PSP_! 

> [!NOTE]
> Project is currently in the prototype phase. The end goal is a physical working handheld product

## Requirements and Dependencies
<br />

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



