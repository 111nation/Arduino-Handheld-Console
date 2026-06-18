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

    def draw(self, x, y, color):
        self.canvas[int(y)][int(x)] = color
    
    def erase(self, x, y):
        self.canvas[int(y)][int(x)] = ""

    def display(self, screen):
        for row in range(len(self.canvas)):
            for col in range(len(self.canvas[row])):
                color = self.canvas[row][col]
                pixel= (col, row, 2, 2)
                if color == "":
                    pygame.draw.rect(screen, BACKGROUND, pixel) 
                else:
                    pygame.draw.rect(screen, color, pixel) 

player = Player()
canvas = Canvas()

def main(screen):
    player.move((hardware.control.joystick.x/100.0) * player.velocity,
                (hardware.control.joystick.y/100.0) * player.velocity)

    screen.fill(BACKGROUND)
    canvas.draw(player.x, player.y, "white")
    canvas.display(screen)
    player.draw(screen)
