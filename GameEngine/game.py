import pygame
import hardware


class Player:
    def __init__(self):
        self.x = 240/2
        self.y = 240/2
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
        elif self.x > 240:
            self.x = 240

        if self.y < 0:
            self.y = 0
        elif self.y > 240:
            self.y = 240

    def draw(self, screen):
        # Draw cross hair
        pygame.draw.rect(screen, "red", (self.x-self.thickness/2, self.y-self.size/2, self.thickness, self.size))
        pygame.draw.rect(screen, "red", (self.x-self.size/2, self.y-self.thickness/2, self.size, self.thickness))


player = Player()

class Canvas:
    def __init__(self):
        rows, cols = (240, 240)
        self.canvas = [[""]*cols]*rows # 2D Matrix of pixels 

    def draw(self, x, y, color):
        self.canvas[x][y] = color



def main(screen):
    player.move((hardware.control.joystick.x/100.0) * player.velocity,
                (hardware.control.joystick.y/100.0) * player.velocity)

    screen.fill("black")
    player.draw(screen)
