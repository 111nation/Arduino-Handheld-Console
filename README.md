# Arduino Handheld Console

<br />

<div align="center">
  The Arduino Handheld Console project that turns your Arduino into a handheld game station! Inspired by the Game Boy and PSP.

  The handheld Console features a **custom-written programming language** and **game engine**, allowing you to write your own games!

</div>

_Make sure to leave a GitHub star on this repo to show your support <3 :)_

<br />

>[!NOTE]
> The project is WIP!
> You can currently emulate and run the Game Engine on your laptop/computer.
> Future goals are to implement this on an Arduino.

<hr />

# Features

* 2D Game Engine
* Custom Game Scripting Language
* Joystick + Button support
* Console Emulation on PC

# Installation

## Binary Releases

Install the binary releases [here](https://github.com/111nation/Arduino-Handheld-Console/releases) for your target Operating System. 

<details>
  <summary>Windows</summary>

Unzip the downloaded zipped file and run the project within the folder by double-clicking on it.

Alternatively, you can open a terminal window **within the root of the folder** and execute the following to run via the CLI.

```powershell
.\main.exe
```

 </details>

 <details>
  <summary>Linux (Unix)</summary>
  
Unzip the downloaded zip file by running the following in the same directory as the downloaded zip file.
```bash
unzip <Folder Name> .
cd <Folder Name>
```
To execute the binary via CLI, execute:

```powershell
./main
```
    
 </details>
 

## Build From Source

Make sure you have the various prerequisites.

### Requirements
* C++ Compiler linked to your `PATH`
* CMake Version 3.23 or higher
* Make
* Git

### Building & Executing

> [!NOTE]
> Building commands may differ depending on your environment

Clone the repository onto your local system using the following.

```bash
git clone --recursive https://github.com/111nation/Arduino-Handheld-Console
```

Enter the cloned repository and enter the `GameEngine` directory to build and execute the Emulator.

```bash
cd Arduino-Handheld-Console
cd GameEngine

cmake -S . -B build
cmake --build build
```

## How the Game Engine Works

### Loading Games

When emulating the game engine on your personal computer, the game engine is hard coded to load a game from the programs folder, `$PROGRAM_ROOT/programs/main`, where `$PROGRAM_ROOT` is the current working directory the program was executed at. This currently functions as a basic bootloader for the game console to fetch the first instructions (which is just a single game at this point).

Depending if you downloaded a precompiled binary or built from source, `$PROGRAM_ROOT` is the unzipped folder installed the precompiled binary or `$PROGRAM_ROOT` is the `GameEngine` folder where cmake was executed.

Keep all custom written games in `$PROGRAM_ROOT/programs/`, 'load' a game by renaming it to `main` in the programs folder.

> [!TIP]
> Two sample games, a drawing and a pong game has been included as a demo

### Emulator Controls

<table>
	<tr>
		<th width="150px">Keys</th>
		<th width="300px">Description</th>
	</tr>
	<tr>
		<td>
			<kbd>w</kbd> / <kbd>a</kbd> / <kbd>s</kbd> / <kbd>d</kbd>
		</td>
		<td>
			Movement controls. emulates joystick, maps a keypress to -100%, 0% or 100% of equivalent joystick position.
		</td>
	</tr>
	<tr>
		<td>
			<kbd>E</kbd>
		</td>
		<td>
			Mapping to joystick click
		</td>
	</tr>
	<tr>
		<td>
			<kbd>O</kbd>
		</td>
		<td>
			Mapping to auxillary 'A' button
		</td>
	</tr>
</table>

### Scripting Games

This is the most fun part! This section is viewable at [Docs/README.md](Docs/README.md)

### Project Structure

<table>
  <thead>
    <tr>
      <th style="text-align: left;">Directory / Component</th>
      <th style="text-align: left;">Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><strong>DepreciatedPyGameEngine</strong></td>
      <td>Stores the legacy, deprecated Python-based game engine codebase.</td>
    </tr>
    <tr>
      <td><strong>Arduino</strong></td>
      <td>Stores the Arduino implementation used to control physical hardware inputs.</td>
    </tr>
    <tr>
      <td><strong>GameEngine</strong></td>
      <td>Stores the main source code and data for the active game engine.</td>
    </tr>
    <tr>
      <td><strong>Docs</strong></td>
      <td>Contains the system and API documentation for the current game engine.</td>
    </tr>
  </tbody>
</table>
