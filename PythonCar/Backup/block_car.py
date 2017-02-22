import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BCM)
import sys, tty, termios, time
from termcolor import colored, cprint

# Initializes Motor 1 and its GPIO pins and initial setup
mot1_int1_gp18 = 18
mot1_int1_gp23 = 23
GPIO.setup(mot1_int1_gp18, GPIO.OUT)
GPIO.setup(mot1_int1_gp23, GPIO.OUT)

motor1 = GPIO.PWM(18,100)
motor1.start(0)
motor1.ChangeDutyCycle(0)

motor1_2 = GPIO.PWM(23,100)
motor1_2.start(0)
motor1_2.ChangeDutyCycle(0)

 # Initializes Motor 2 and its GPIO pins and initial setup
mot2_in1_gp24 = 24
mot2_in2_gp25 = 25
GPIO.setup(mot2_in1_gp24, GPIO.OUT)
GPIO.setup(mot2_in2_gp25, GPIO.OUT)

motor2 = GPIO.PWM(24,100)
motor2.start(0)
motor2.ChangeDutyCycle(0)

motor2_2 = GPIO.PWM(25,100)
motor2_2.start(0)
motor2_2.ChangeDutyCycle(0)
 
 # Produces LED lights to shine as an indication of program running
#GPIO.setup(18, GPIO.OUT)
#GPIO.output(18, False)

#GPIO.setup(23, GPIO.OUT)
#GPIO.output(23, False)

# Reads key from keyboard as of the current moment. 
def getch():
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(sys.stdin.fileno())
        ch = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return ch

# This section of code defines the methods used to determine
# whether a motor needs to spin forward or backwards. The
# different directions are acheived by setting one of the
# GPIO pins to true and the other to false. If the status of
# both pins match, the motor will not turn.
def motor1_forward():
    GPIO.output(mot1_int1_gp18, False)
    GPIO.output(mot1_int1_gp23, True)
    motor1.ChangeDutyCycle(0)
    motor1_2.ChangeDutyCycle(99)
 
def motor1_reverse():
    GPIO.output(mot1_int1_gp18, True)
    GPIO.output(mot1_int1_gp23, False)
    motor1.ChangeDutyCycle(99)
    motor1_2.ChangeDutyCycle(0)
       
def motor1_stop():
    GPIO.output(mot1_int1_gp18, False)
    GPIO.output(mot1_int1_gp23, False)
    motor1.ChangeDutyCycle(0)
    motor1_2.ChangeDutyCycle(0)

def motor1_half():
    GPIO.output(mot1_int1_gp18, False)
    GPIO.output(mot1_int1_gp23, True)
    motor1.ChangeDutyCycle(0)
    motor1_2.ChangeDutyCycle(25)
 
def motor2_forward():
    GPIO.output(mot2_in1_gp24, True)
    GPIO.output(mot2_in2_gp25, False)
    motor2.ChangeDutyCycle(99)
    motor2_2.ChangeDutyCycle(0)
 
def motor2_reverse():
    GPIO.output(mot2_in1_gp24, False)
    GPIO.output(mot2_in2_gp25, True)
    motor2.ChangeDutyCycle(0)
    motor2_2.ChangeDutyCycle(99)
 
def motor2_stop():
 
    GPIO.output(mot2_in1_gp24, False)
    GPIO.output(mot2_in2_gp25, False)
    motor2.ChangeDutyCycle(0)
    motor2_2.ChangeDutyCycle(0)

def motor2_half():
    GPIO.output(mot2_in1_gp24, True)
    GPIO.output(mot2_in2_gp25, False)
    motor2.ChangeDutyCycle(25)
    motor2_2.ChangeDutyCycle(0)


# This method will toggle the lights on/off when the user
# presses a particular key. It will then change the status
# of the lights so it will know whether to turn them on or
# off when it is next called.
def toggleLights():
 
    global lightStatus
 
    if(lightStatus == False):
        GPIO.output(18, True)
        GPIO.output(23, True)
        lightStatus = True
    else:
        GPIO.output(18, False)
        GPIO.output(23, False)
        lightStatus = False
 
# This method will toggle the direction of the steering
# motor. The method will determine whether the user wants
# to turn left or right depending on the key they press and
# then make the appropriate adjustment. It works as a toggle
# because the program cannot read multiple pressed keys at
# the same time. The possible positions of the wheels are
# "right", "centre" and "left". It will then update the
# status of the wheel to access next time it is called.
def toggleSteering(directGPIOn):
 
    global wheelStatus
 
    if(directGPIOn == "right"):
        if(wheelStatus == "centre"):
            motor1_forward()
            motor2_half()        
            wheelStatus = "right"
        elif(wheelStatus == "left"):
            motor1_forward()
            motor2_half()
            wheelStatus = "centre"
 
    if(directGPIOn == "left"):
        if(wheelStatus == "centre"):
            motor1_half()
            motor2_forward()
            wheelStatus = "left"
        elif(wheelStatus == "right"):
            motor1_half()
            motor2_forward()
            wheelStatus = "centre"
 
# Setting the PWM pins to false so the motors will not move
# until the user presses the first key
GPIO.output(mot1_int1_gp18, False)
GPIO.output(mot1_int1_gp23, False)
GPIO.output(mot2_in1_gp24, False)
GPIO.output(mot2_in2_gp25, False)
 
lightStatus = False
wheelStatus = "centre"
 
 
# Instructions for when the user has an interface
print("q: stop motor")
print("w/s: acceleration")
print("a/d: steering")
print("l: lights")
print("x: exit")
 
 
 
while True:
    char = getch()
    if(char == "w"):
        motor2_forward()
        motor1_forward()
        wheelStatus = "centre"
 
    if(char == "s"):
        motor2_reverse()
        motor1_reverse()
     
    if(char == "d"):
        toggleSteering("right")
       
    if(char == "a"):
        toggleSteering("left")
 
    if(char == "l"):
        toggleLights()

    if(char == "q"):
        motor2_stop()
        motor1_stop()
        wheelStatus = "centre"
 
    if(char == "x"):
        cprint("Program Ended", 'red')
        break
               
    # The keyboard character variable will be set to blank, ready
    # to save the next key that is pressed
    char = ""

# Program will cease all GPIO activity before terminating
GPIO.cleanup()