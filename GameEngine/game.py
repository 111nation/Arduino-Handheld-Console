import pygame
from hardware import control

BACKGROUND = "black"
STROKE_WIDTH = 2
ERASER_SIZE = 25

class Player:
    def __init__(self):
        self.x = int(240/2)
        self.y = int(240/2)
        self.size = 20
        self.thickness = 2
        self.velocity = 3

    def set_position(self, x, y):
        self.x = x
        self.y = y

    def move(self, vel_x, vel_y):
        # Velocity based movement
        self.x = int(self.x + vel_x)
        self.y = int(self.y + vel_y)

        if self.x < 0:
            self.x = 0
        elif self.x >= 240:
            self.x = 240-1

        if self.y < 0:
            self.y = 0
        elif self.y >= 240:
            self.y = 240-1

    def draw(self, screen):
        # Draw cross hair
        pygame.draw.rect(screen, "red", (self.x-self.thickness/2, self.y-self.size/2, self.thickness, self.size))
        pygame.draw.rect(screen, "red", (self.x-self.size/2, self.y-self.thickness/2, self.size, self.thickness))



class Canvas:
    def __init__(self):
        self.canvas = pygame.Surface((240, 240))
        self.canvas.fill(BACKGROUND)
        self.color_index = 0
    
    def change_color(self):
        self.color_index = self.color_index + 1

        if self.color_index >= 5: 
            self.color_index = 0

    def get_color(self):
        match self.color_index:
            case 0:
                return "white"
            case 1:
                return "blue"
            case 2: 
                return "red"
            case 3: 
                return "green"
            case 4:
                return "yellow"
            case _: 
                return "white"

    def draw(self, x, y):
        pygame.draw.circle(self.canvas, self.get_color(), (x,y), STROKE_WIDTH)
    
    def erase(self, x, y):
        pygame.draw.circle(self.canvas, BACKGROUND, (x,y), ERASER_SIZE)

    def display(self, screen):
        screen.blit(self.canvas, (0, 0))

# PREVENT CONTINUOUS PRESS
enable_color_switch = True
enable_mode_switch = True

# MODES
erase = False

player = Player()
canvas = Canvas()

def init():
    pygame.display.set_caption("Draw Game")

def main(screen):
    global enable_color_switch, enable_mode_switch, erase

    player.move((control.joystick.x/100.0) * player.velocity,
                (control.joystick.y/100.0) * player.velocity)

    # UPDATE COLOR MODE

    if control.joystick.clicked and enable_color_switch: 
        canvas.change_color()
        enable_color_switch = False
    elif not control.joystick.clicked:
        enable_color_switch = True

    # UPDATE DRAW MODE 

    if control.button_a and enable_mode_switch:
        erase = not erase
        enable_mode_switch = False

    if erase:
        canvas.erase(player.x, player.y)
    else:
        canvas.draw(player.x, player.y)

    if not control.button_a:
        enable_mode_switch = True

    # DISPLAY SCREEN

    screen.fill(BACKGROUND)
    canvas.display(screen)
    player.draw(screen)
