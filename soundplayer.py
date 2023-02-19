import serial
import subprocess
import ffmpeg
#from playsound import playsound
import pygame

pygame.init()
pygame.mixer.init()

snare = pygame.mixer.Sound('sound_files/snare.mp3')
hihat = pygame.mixer.Sound('sound_files/hihat.mp3')
crash = pygame.mixer.Sound('sound_files/crash.mp3')
splash = pygame.mixer.Sound('sound_files/splash.mp3')
tom = pygame.mixer.Sound('sound_files/tom.mp3')

arduino = serial.Serial('COM6', 115200, timeout=.1)

while True:
    data = arduino.readline()[:-2] 

    if data == b'':
        continue

    data = data.decode()

    if data[0] == "t":
        snare.play()
        print("LSnare\n")
    
    if data[1] == "s":
        snare.play()
        print("RSnare\n")
    elif data[1] == "h":
        hihat.play()
        print("RHihat\n")
    elif data[1] == "c":
        crash.play()
        print("RCrash\n")
    elif data[1] == "p":
        splash.play()
        print("RSplash\n")
    elif data[1] == "t":
        tom.play()
        print("RTom\n")