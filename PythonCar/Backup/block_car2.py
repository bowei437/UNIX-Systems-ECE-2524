#Import rpi.gpio is raspberry pi specific to get use of the GPIO on it
# It comes pre-installed generally on the full Raspbian image
import RPi.GPIO as GPIO 
#setmode BCM is just a general Raspberry pi command telling it to use the BCM manufacturered chip GPIO that the Pi uses. 
# These are hard set functions that you will pretty much always use
GPIO.setmode(GPIO.BCM)
# This just imports modules to allow you to use the terminal. Also another very standard command to give to a Python project
import sys, tty, termios, time


# Initializes Motor 1 and its GPIO pins and initial setup
# My motor 1 is connected to 18 and 23 of the GPIO so I set it as so here. 
# I hard code a variable to store 23 and 18 into
mot1_int1_gp18 = 18
mot1_int1_gp23 = 23
# Then I run GPIO Setup which is a command to set the I/O status as output there
GPIO.setup(mot1_int1_gp18, GPIO.OUT)
GPIO.setup(mot1_int1_gp23, GPIO.OUT)

# Thanks to the Texas Instruments L293D chip I am u sing. I can use PWM to modulate
# the signal so I can turn the car
# These commands here initialize PWM to the GPIO, frequency of 100 and I give command to start it
# Duty cycle is 0 to not make the car move yet. I just want to initialize.
motor1 = GPIO.PWM(18,100)
motor1.start(0)
motor1.ChangeDutyCycle(0)

motor1_2 = GPIO.PWM(23,100)
motor1_2.start(0)
motor1_2.ChangeDutyCycle(0)

 # Initializes Motor 2 and its GPIO pins and initial setup
 # Same idea as above
 #Motor 2 uses GPIO 24 and 25 and then I set to output
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
 



#This uses the python module above and reads in terminal/keyboard press and returns that character as 'ch'
# to my main function that calls it below
def getch():
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(sys.stdin.fileno())
        ch = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return ch

# Code definitions which define 'states' of motor


# NOTE that you may realize the logic for PWM for motor 1 is completely backwards
# This is because I wired the 2 DC motors in the same positve negative convention so 
# when it came time to run the code, one moved the motor backwards. 

# I could have either reversed the physical soldered wiring or the code. It was easier
# to change the code so I flipped the logic for Motor 1 backwards to compensate for flipped wiring.

# This function definition defines Motor 1 to move forward. 
def motor1_forward():
    GPIO.output(mot1_int1_gp18, False) # logic is backwards so the top pin is set to false
    GPIO.output(mot1_int1_gp23, True) # and the 'negative' or second one to true
    motor1.ChangeDutyCycle(0)
    motor1_2.ChangeDutyCycle(99) # and I make the second one set to 99 for near full power
 
 # This function defines motor 1 to move backwards
def motor1_reverse():
    GPIO.output(mot1_int1_gp18, True) # logic makes forward pin false as my wiring is flipped
    GPIO.output(mot1_int1_gp23, False)
    motor1.ChangeDutyCycle(99) # sets forward pin to output full power
    motor1_2.ChangeDutyCycle(0)

 # This function defines the motor1 to stop. I could have set both duty cycles to 0, but also setting GPIO out to false is good 
def motor1_stop():
    GPIO.output(mot1_int1_gp18, False)
    GPIO.output(mot1_int1_gp23, False)
    motor1.ChangeDutyCycle(0)
    motor1_2.ChangeDutyCycle(0)

# When I want my car to turn left/right. I want my motors to operate at half power.
def motor1_half():
    GPIO.output(mot1_int1_gp18, False) # same general logic as forwards for motor 1
    GPIO.output(mot1_int1_gp23, True)
    motor1.ChangeDutyCycle(0)
    motor1_2.ChangeDutyCycle(25) # however I reduce DutyCycle to 25 instead of 99. So not actually half, but moves at about half speed in real life
 
 # Functions to move Motor 2 in the same idea as the defined names
def motor2_forward(): 
    GPIO.output(mot2_in1_gp24, True) # Notice that motor 2 has the forward GPIO pin set to false. This is because it was wired correctly
    GPIO.output(mot2_in2_gp25, False) 
    motor2.ChangeDutyCycle(99) # Motor 2 also operates at full power
    motor2_2.ChangeDutyCycle(0)

# Makes motor 2 move backwards 
def motor2_reverse():
    GPIO.output(mot2_in1_gp24, False)
    GPIO.output(mot2_in2_gp25, True) # pins are flipped to reverse output GPIO signal
    motor2.ChangeDutyCycle(0)
    motor2_2.ChangeDutyCycle(99) # duty cycle is then also changed
 
 #Function to make motor2 also stop
def motor2_stop():
    GPIO.output(mot2_in1_gp24, False) # states are set to same so invalid so motors stop
    GPIO.output(mot2_in2_gp25, False)
    motor2.ChangeDutyCycle(0) # no movement in motors
    motor2_2.ChangeDutyCycle(0)
# Half power to make turning the Pi Car possible.
def motor2_half():
    GPIO.output(mot2_in1_gp24, True)
    GPIO.output(mot2_in2_gp25, False)
    motor2.ChangeDutyCycle(25)
    motor2_2.ChangeDutyCycle(0)


# For LEDs if I have them to toggle on and off. This was used more for debugging to make sure my connection
# to the Pi car was still active. I left it in but pins 4 and 17 turn on and off 2 LEDs
# Not currently used in my configuration.
def toggleLights():
 
    global lightControl
 
    if(lightControl == False):
        GPIO.output(4, True)
        GPIO.output(17, True)
        lightControl = True
    else:
        GPIO.output(4, False)
        GPIO.output(17, False)
        lightControl = False
 
# This will take in direction from keyboard press and orient car direction
# It remembers direction car is moving in to know how to re-orient 
def toggleSteering(directGPIOn):
 
    global curWheelPos
 
    if(directGPIOn == "right"):
        if(curWheelPos == "center"):
            motor1_forward()
            motor2_half()        
            curWheelPos = "right"
        elif(curWheelPos == "left"):
            motor1_forward()
            motor2_half()
            curWheelPos = "center"
 
    if(directGPIOn == "left"):
        if(curWheelPos == "center"):
            motor1_half()
            motor2_forward()
            curWheelPos = "left"
        elif(curWheelPos == "right"):
            motor1_half()
            motor2_forward()
            curWheelPos = "center"
 
# Setting the PWM pins to false so the motors will not move
# until the user presses the first key
GPIO.output(mot1_int1_gp18, False)
GPIO.output(mot1_int1_gp23, False)
GPIO.output(mot2_in1_gp24, False)
GPIO.output(mot2_in2_gp25, False)
 
lightControl = False
curWheelPos = "center"
 
 
# Instructions for when the user has an interface. This is also the general interface
print("Press the Keyboard button to move the car:")
print("w/s: acceleration")
print("a/d: steering")
print("l: lights")
print("x: exit")
 
 
 
while True:
    char = getch()
    if(char == "w"):
        motor2_forward()
        motor1_forward()
        curWheelPos = "center"
 
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
        curWheelPos = "center"
 
    if(char == "x"):
        print("Program Ended")
        break

    #else:
	#motor2_stop()
    #motor1_stop()
               
    # The keyboard character variable will be set to blank, ready
    # to save the next key that is pressed
    char = ""

# Program will cease all GPIO activity before terminating
GPIO.cleanup()