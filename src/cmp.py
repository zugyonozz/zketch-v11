import pygame
from pygame._sdl2.video import Window

pygame.init()

# Buat 2 window
w1 = Window("Window 1", size=(800, 600))
w2 = Window("Window 2", size=(800, 600))

running_w1 = True
running_w2 = True

while running_w1 or running_w2:
    for event in pygame.event.get():
        # Event close untuk masing-masing window
        if event.type == pygame.QUIT:
            if event.window.window == w1:
                running_w1 = False
            elif event.window.window == w2:
                running_w2 = False

        # Event mouse move
        elif event.type == pygame.MOUSEMOTION:
            if event.window == w1:
                print(f"Window 1\t: {{{event.pos[0]}, {event.pos[1]}}}")
            elif event.window == w2:
                print(f"Window 2\t: {{{event.pos[0]}, {event.pos[1]}}}")

pygame.quit()