# INPUT

Retrieve player input and update global variable states.

## Syntax

```
    CALL INPUT
```

## Function Parameters

This function does not utilize parameters.

## Remarks

On the emulated game engine, this function is **critical** to ensure that the SDL backend events are handled as well. Ensure that you constantly call this function within your main game loop to ensure that your game window does not get terminated or frozen by your operating system.

On the emulated game engine, this function listens for a physical joystick input from the arduino via serial communication. If this function cannot communicate with the arduino, the default behaviour is to listen for key input.
