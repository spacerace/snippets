#!/usr/bin/python

import pygame
from pygame.locals import QUIT
from sys import exit
import math
import cmath

size = 512
fsize = float(size)
ifsize = 1/float(size)

pygame.init()
win = pygame.display.set_mode((size, size), 0, 32)

def pump():
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            exit()

def cpow(x,p):
    i = complex(0,1)
    angle = cmath.phase(x)
    angle *= p
    mag = abs(x)
    mag = math.pow(mag,p)
    return cmath.exp(i*angle)*mag

def escapeTime(x, p, maxx):
    z = x
    iterr = 0
    while iterr < maxx:
        iterr += 1
        z = cpow(z,p) + x
        if abs(z) > 2:
            return iterr
    return 0

def draw(p):
    win.fill((255,255,255,255))
    for x in range(size):
        for y in range(size):
            xx = 5 *(x * ifsize - 0.5)
            yy = 5 * (y * ifsize - 0.5)
            et = escapeTime(complex(xx,yy), p, 25)
            if et > 0:
                red = et
                red = min(10*red,255)
                blue = et
                blue = min(10*blue,255)
                win.set_at((x,y),(red,0,blue,0))

#for i in range(100):
#    draw(i*0.1)
#    pygame.image.save(win, str(i)+"M.png")
draw(2)
pygame.display.update()
pygame.image.save(win, "Mandel.png")

while True:
    pump()
