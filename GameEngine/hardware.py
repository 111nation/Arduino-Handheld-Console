import serial

ser = serial.Serial('/dev/ttyACM0')
ser.baudrate = 9600
ser.timeout = 0.1
ser.write_timeout = 0.1


class Joystick:
    def __init__(self, x, y, clicked):
        self.x = x
        self.y = y
        self.clicked = clicked


joystick = Joystick(0, 0, False)


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
    if len(data) < 17:
        joystick.x = 0
        joystick.y = 0
        joystick.clicked = False
        return

    joystick.x = binary_to_int(data[0:8])
    joystick.y = binary_to_int(data[8:16])
    joystick.clicked = True if data[16] == "1" else False


def debug_joystick_actions():
    if joystick.x == 0 and joystick.y == 0 and not joystick.clicked:
        return

    print("X:", end="")
    print(joystick.x)

    print("Y:", end="")
    print(joystick.y)

    if joystick.clicked:
        print("Button pressed")
