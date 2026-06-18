import pygame
import hardware

BACKGROUND = "black"

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
        self.x = self.x + vel_x
        self.y = self.y + vel_y

        if self.x < 0:
            self.x = 0
        elif self.x >= 240:
            self.x = 239

        if self.y < 0:
            self.y = 0
        elif self.y >= 240:
            self.y = 239

    def draw(self, screen):
        # Draw cross hair
        pygame.draw.rect(screen, "red", (self.x-self.thickness/2, self.y-self.size/2, self.thickness, self.size))
        pygame.draw.rect(screen, "red", (self.x-self.size/2, self.y-self.thickness/2, self.size, self.thickness))



class Canvas:
    def __init__(self):
        rows, cols = 240, 240
        self.canvas = [["" for _ in range(cols)] for _ in range(rows)] # 2D Matrix of pixels 
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
        self.canvas[int(y)][int(x)] = self.get_color()
    
    def erase(self, x, y):
        self.canvas[int(y)][int(x)] = ""

    def display(self, screen):
        for row in range(len(self.canvas)):
            for col in range(len(self.canvas[row])):
                color = self.canvas[row][col]
                pixel= (col, row, 1, 1)
                if color == "":
                    pygame.draw.rect(screen, BACKGROUND, pixel) 
                else:
                    pygame.draw.rect(screen, color, pixel) 

player = Player()
canvas = Canvas()

def main(screen):
    player.move((hardware.control.joystick.x/100.0) * player.velocity,
                (hardware.control.joystick.y/100.0) * player.velocity)

    if hardware.control.joystick.clicked: 
        canvas.change_color()

    if hardware.control.button_a:
        canvas.erase(player.x, player.y)
    else:
        canvas.draw(player.x, player.y)

    screen.fill(BACKGROUND)
    canvas.display(screen)
    player.draw(screen)
