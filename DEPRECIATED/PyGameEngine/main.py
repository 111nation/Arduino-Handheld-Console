import pygame
import time
import hardware
import game

SCREEN_WIDTH = 240
SCREEN_HEIGHT = 240

# pygame setup
pygame.init()
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Game")
clock = pygame.time.Clock()
running = True

game.init()

while running:
    hardware.read_serial_input()
    hardware.debug_control_actions()

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    game.main(screen)

    # Update player

    pygame.display.flip()
    clock.tick(60)  # 60 FPS

hardware.signal_unready_for_communication()
hardware.ser.close()
time.sleep(0.1)
pygame.quit()
