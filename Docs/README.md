# Documentation

<br />

<div align="center">
    This documentation helps you with creating your own games using the **custom programming language** :)
</div>


## Introduction

### Loading Games

As previously discussed in the root [README.md](../README.md), the game engine is hard coded to run a single implementation of a game under `$PROGRAM_ROOT/programs/main`. This main file is due to act as a bootloader for the console in the future. Right now this is where you will write your scripts to create your fun little games!

### About The Programming Language

The custom high-level programming language the handheld console uses is an implementation of a Tree-walk interpreted language fetches and executes instructions from the implementation file. This means, the game engine reads each line and executes it before going to the next line. This is a contrast from programming languages such as C++ which compiles the whole source code into binary format before running the program from the binary output instead of line-by-line as this programming language.

The interpreter was written with the help of [this excellent book](https://craftinginterpreters.com/)

The language syntax was inspired by **BASIC**: a former, important programming language in history.

## Basic Concepts

> [!Note]
> The language syntax is case sensitive and requires uppercase

### Comments

Comments are supported in the language. Any text starting at a leading `#` to the end of a line will be ignored.

```
    # Single line comment

    # Multi-line comments
    # can be created
    # like this
```

### Data Types

The language uses only ONE data type: a 16-bit integer. Every data or variable that you will be interacting with is a 16-bit integer, capable of storing `-32,768` to `32,767`. If you attempt to store numbers outside that range, you will encounter an integer underflow or overflow.

### Memory & Variables

The game engine acts as a virtual machine giving you a virtual memory heap structure that you can access directly. The heap structure contains single memory 'blocks' between `[0,63]`. 

> [!Note]
> Make sure to initialize memory blocks before using them. 

To write into memory block 40 a result of an equation:

```
    M40 = 18 * (-6 / 5)
```

To read from memory block 11 and 12, and store their sum into block 1: 

```
    M1 = M11 + M12
```

### Conditions

The programming language supports if statements and while loops. These control flows depend on comparisons and conditions. Values that are non zero are regarded as "true" and zero values are regarded as "false"

> [!Note]
> Any comparison operations returns a '1' or '0' integer

To check if Memory block 8 is greater than 6 and save the value true to block 7:

```
    M8 = 110
    M7 = M8 > 6     # M7 will store 1
```

To check is 8 is equal to 3:

```
    M0 = 8 == 3
```

Logic operators `NOT`, `OR` and `AND` are also supported. Remember non zero values are true!

```
    M7 = NOT 6      
    # Not of 6 (true) is 0 (false)
    # M7 stores 0 now

    M10 = (NOT 0) AND (5 + 6 == 11)
    # NOT 0 is 1 (true)
    # 5 + 6 == 11 is 1 (true)
    # 1 AND 1 is 1 (true)
```
    
### Control Flow

#### IF statements

If statements work in this language, just as any other language. An if statement requires an opening `IF`, a condition, proceeding `THEN` and closing `END` to signal to the interpreter the end of the current if statement.

To check if Memory block 5 is greater or equal to 4:

```
    IF M5 >= M4 THEN
        M4 = M4 + 1
    END
```

A single `ELSE` statement is allowed before the END statement:

```
    IF M5 >= M4 THEN
        M4 = M4 + 1
    ELSE
        M5 = M5 + 1
    END
```

Multiple `IF-ElSE` branches are allowed:

``` 
    IF NOT M0 OR M9 THEN
        # Branch 1
    ELSE IF
        # Branch 2
    ELSE IF 
        # Branch 3
    ELSE
        # Default Branch
    END
```

#### WHILE statements

While statements require an opening `WHILE`, a condition, proceeding `DO` and closing `END` to signal to the interpreter the end of the current if statement.


To loop 10 times:

```
    M0 = 0
    WHILE M0 < 10 DO
        M0 = M0 + 1
    END
```

`ELSE` statements for loops are not supported in this programming language. Actually very few languages support it! 

> [!Warning]
> Be wary of infinite loops :)

#### NESTING

Control flows can be nested into each other
```
    M0 = 0
    M1 = 3
    WHILE M0 < 10 DO
        M0 = M0 + 1

        IF M0 == 7 THEN
            M1 = 4

            WHILE M1 < 20 DO
                M1 = M1 + 2
            END
        END
    END
```

### Custom Functions

#### Overview

Functions work as usual in this language as every other language. When you define a function, the interpreter marks down the location of that function in the file in a function register. The function register behaves the similarly as the memory heap; a maximum of 16 functions from `0` to `15` are able to be defined.

#### Defenitions

Custom functions are primitive in this language. No return types or parameters are supported directly, however due to the nature of the direct access heap, one can reserve memory blocks for the parameters of a function or return data.


To define a simple function to add two numbers, this function will be stored in function registry location 6:

```

DEFINE FUNC6 THEN
    M3 = M1 + M2
END
```

> [!Note]
> The latest defenition of a function in registry X will always overwrite previous defenitions in registry X if they exist

#### Calling

To call the newly defined `FUNC6`, write:

```
CALL FUNC6
```

## BUILT-IN

### Overview

Various built in variables and functions are provided for you to interact with the game engine

### Variables

<table>
  <thead>
    <tr>
      <th width="30%">Variable Name</th>
      <th width="70%">Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><code>JOYSTICK_X</code> / <code>JOYSTICK_Y</code></td>
      <td>The current horizontal (X) and vertical (Y) coordinate inputs from the joystick. Ranges from `-100` to `100` to represent if pulled in one direction or the other. `0` if not moved.</td>
    </tr>
    <tr>
      <td><code>JOYSTICK_BUTTON</code></td>
      <td>The digital input state indicating whether the joystick is pressed down.</td>
    </tr>
    <tr>
      <td><code>BUTTON_A</code></td>
      <td>An auxiliary button 'A' utilized for secondary operations or actions.</td>
    </tr>
    <tr>
      <td><code>TIME</code></td>
      <td>A millisecond clock tracking elapsed time using an unsigned 16-bit integer that overflows/resets back to `0` after reaching `65,535`.</td>
    </tr>
    <tr>
      <td><code>SCREEN_WIDTH</code></td>
      <td>The maximum horizontal pixel resolution of the display screen.</td>
    </tr>
    <tr>
      <td><code>SCREEN_HEIGHT</code></td>
      <td>The maximum vertical pixel resolution of the display screen.</td>
    </tr>
  </tbody>
</table>

#### Functions

##### Updating Inputs


### Good Practices



