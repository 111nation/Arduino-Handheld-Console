import pygame
import time
import hardware
import game

# pygame setup
pygame.init()
screen = pygame.display.set_mode((240, 240))
clock = pygame.time.Clock()
running = True

while running:
    # Update hardware
    hardware.read_serial_input()
    # hardware.debug_joystick_actions()

    # Update player
    game.player.move((hardware.joystick.x/100.0) * game.player.velocity,
                     (hardware.joystick.y/100.0) * game.player.velocity)

    # poll for events
    # pygame.QUIT event means the user clicked X to close your window
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # fill the screen with a color to wipe away anything from last frame
    screen.fill("black")

    # RENDER YOUR GAME HERE
    pygame.draw.rect(screen, "pink", (game.player.x,
                     game.player.y, game.player.width, 40))

    # flip() the display to put your work on screen
    pygame.display.flip()

    clock.tick(60)  # limits FPS to 60

hardware.signal_unready_for_communication()
hardware.ser.close()
time.sleep(0.1)
pygame.quit()
