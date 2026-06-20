from pygame import joystick
import serial

CONTROL_DATA_LENGTH = 18

ser = serial.Serial('/dev/ttyACM0')
ser.baudrate = 9600
ser.timeout = 0.1
ser.write_timeout = 0.1

class Joystick:
    def __init__(self, x, y, clicked):
        self.x = x
        self.y = y
        self.clicked = clicked

class Control:
    def __init__(self, joystick, button_a) -> None:
        self.joystick = joystick
        self.button_a = button_a

control = Control(Joystick(0, 0, False), False)


def binary_to_int(binary):
    # Convert a signed byte (8 bits) to a integer
    if binary[0] == "0":
        return int(binary[1:8], 2)
    else:
        return -128 + int(binary[1:8], 2)


def signal_ready_for_communication():
    ser.write(b'1')


def signal_unready_for_communication():
    ser.write(b'0')


def read_serial_input():
    # Attempt to read from serial input
    if ser.in_waiting <= 0:
        signal_ready_for_communication()
        return

    data = ser.readline().rstrip().decode("ascii")

    # Ignore data thats too short
    if len(data) < CONTROL_DATA_LENGTH:
        control.joystick.x = 0
        control.joystick.y = 0
        control.joystick.clicked = False
        control.button_a = False
        return

    control.joystick.x = binary_to_int(data[0:8])
    control.joystick.y = binary_to_int(data[8:16])
    control.joystick.clicked = True if data[16] == '1' else False
    control.button_a = True if data[17] == '1' else False


def debug_control_actions():
    debug_joystick_actions()

    if control.button_a:
        print("Button A Pressed")


def debug_joystick_actions():
    joystick = control.joystick

    if joystick.x != 0 or joystick.y != 0:
        print("X:", end="")
        print(control.joystick.x)

        print("Y:", end="")
        print(control.joystick.y)

    if control.joystick.clicked:
        print("Joystick Pressed")
