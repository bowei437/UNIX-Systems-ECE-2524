# Autor Ingmar Stapel
# Version 1.0
# Datum 20150106 08:28 AM

import webiopi

GPIO = webiopi.GPIO
	
# initiales setzen der Beschleunigung
acceleration = 0
# auf der Stelle drehen = false
spotturn = "false"

# In diesem Abschnitt werden die GPIO's fuer die
# Ansteuerung des Motortreibers festgelegt und
# initialisiert

# Die beiden GPIO's 27 und 22 legen fest in welche
# Richtung sich die Motoren z.B. links drehen sollen 
# und ob sich die Motoren drehen sollen.
motor1_in1_pin = 18
motor1_in2_pin = 27
GPIO.setFunction(motor1_in1_pin, GPIO.OUT)
GPIO.setFunction(motor1_in2_pin, GPIO.OUT)

# Die beiden GPIO's 24 und 25 legen fest in welche
# Richtung sich die Motoren z.B. rechts drehen sollen
# und ob sich die Motoren drehen sollen.
motor2_in1_pin = 24
motor2_in2_pin = 25
GPIO.setFunction(motor2_in1_pin, GPIO.OUT)
GPIO.setFunction(motor2_in2_pin, GPIO.OUT)

# Mit den GPIO' 4 und 17 wird das PWM Signal an den
# Motortreiber fuer die Motoren links und rechts
# uebertragen. Mit dem PWM Signal wird festgelegt
# wie schnell sich die Raeder linke oder recht drehen
# sollen.
motorpwm1_in1_pin = 4
motorpwm2_in1_pin = 17
GPIO.setFunction(motorpwm1_in1_pin, GPIO.PWM)
GPIO.setFunction(motorpwm2_in1_pin, GPIO.PWM)

def initiate():
	global spotturn
	global acceleration
	global motorLspeed
	global motorRspeed
	global speedstep
	
	spotturn = "false"
	acceleration = 0
	motorLspeed = 0
	motorRspeed = 0
	speedstep = 5

# Mit den Funktionen reverse() und forward() wird festgelegt in
# welche Richtung sich die Motoren drehen sollen.

def reverse():
    GPIO.digitalWrite(motor1_in1_pin, GPIO.HIGH)
    GPIO.digitalWrite(motor1_in2_pin, GPIO.LOW)
    GPIO.digitalWrite(motor2_in1_pin, GPIO.LOW)
    GPIO.digitalWrite(motor2_in2_pin, GPIO.HIGH)	
	
def  forward():
    GPIO.digitalWrite(motor1_in1_pin, GPIO.LOW)
    GPIO.digitalWrite(motor1_in2_pin, GPIO.HIGH)
    GPIO.digitalWrite(motor2_in1_pin, GPIO.HIGH)
    GPIO.digitalWrite(motor2_in2_pin, GPIO.LOW)
	
# Die Funktion stop() setzt den Motortreiber fuer die linke
# und rechte Seite auf False und stopt somit die Motoren.
# Weiter werden auch die Varialben fuer die Geschwindigkeit
# auf 0 zurueck gesetzt.
def stop():
	GPIO.digitalWrite(motor1_in1_pin, GPIO.LOW)
	GPIO.digitalWrite(motor1_in2_pin, GPIO.LOW)
	GPIO.digitalWrite(motor2_in1_pin, GPIO.LOW)
	GPIO.digitalWrite(motor2_in2_pin, GPIO.LOW)
	initiate()
	return 0, 0, 0
	
# Die Funktion setacceleration(... ) setzt die Geschwindigkeit der Motoren
def setacceleration(value):

	global motorLspeed
	global motorRspeed
	global acceleration
	global minspeed
	global maxspeed
	
	acceleration = acceleration + value
	
	minspeed, maxspeed = getMinMaxSpeed()
	
# Hier werden die min und max Werte der Geschwindigkeit ueberprueft
	if(acceleration < -40):
		acceleration = -40
	
	if(acceleration > 40):
		acceleration = 40	
	
	if(acceleration > 0):
		# Vorwaertsfahrt
		forward()
		motorLspeed = acceleration
		motorRspeed = acceleration
	elif(acceleration == 0):
		# stoppen der Motoren
		motorLspeed = acceleration
		motorRspeed = acceleration
		motorLspeed, motorRspeed, acceleration = stop()
	else:
		# Rueckwaertsfahrt
		reverse()
		motorLspeed = (acceleration * -1)
		motorRspeed = (acceleration * -1)
	
	motorLspeed, motorRspeed = check_motorpseed(motorLspeed, motorRspeed)

# Diese Funktion dient der Ueberpruefung der Motorgeschwindigkeiten links und rechts
def check_motorpseed(motorLspeed, motorRspeed):
	if (motorLspeed < minspeed):
		motorLspeed = minspeed

	if (motorLspeed > maxspeed):
		motorLspeed = maxspeed
		
	if (motorRspeed < minspeed):
		motorRspeed = minspeed

	if (motorRspeed > maxspeed):
		motorRspeed = maxspeed	
		
	return motorLspeed, motorRspeed

# Hier werden die Werte fuer die maximale und minimale Geschwindigkeit gesetzt
def getMinMaxSpeed():
	minspeed = 0
	maxspeed = 40
	return minspeed, maxspeed
	
# Diese Funktion liefert die Motorengeschwindigkeit zurueck
def getMotorSpeed():
	global motorLspeed
	global motorRspeed
	
	return motorLspeed, motorRspeed

# Diese Funktion liefert die Schrittweite fuer die Beschleunigung
def getMotorSpeedStep():
	return 5	

# Ab hier werden fuer die Web-Oberflaeche / das Web-Interface die Knoepfe definiert.
# ButtonForward ist der Pfeil fuer die Vorwaertsfahrt	
@webiopi.macro
def ButtonForward():
	fowardAcc = 0
	fowardAcc = getMotorSpeedStep()

	setacceleration(fowardAcc)
	
	motorLspeed, motorRspeed = getMotorSpeed()
	
	# Hier findet die Umrechnung in Prozentwerte statt fuer das PWM Signal
	valueL = float(motorLspeed)/100
	valueR =  float(motorRspeed)/100
		
	GPIO.pulseRatio(motorpwm1_in1_pin, valueL)
	GPIO.pulseRatio(motorpwm2_in1_pin, valueL)

# ButtonReverse ist der Pfeil fuer die Rueckwaertsfahrt		
@webiopi.macro
def ButtonReverse():
	backwardAcc = 0
	backwardAcc = getMotorSpeedStep()

	setacceleration((backwardAcc*-1))
	
	motorLspeed, motorRspeed = getMotorSpeed()
	
	# Hier findet die Umrechnung in Prozentwerte statt fuer das PWM Signal
	valueL = float(motorLspeed)/100
	valueR =  float(motorRspeed)/100
		
	GPIO.pulseRatio(motorpwm1_in1_pin, valueL)
	GPIO.pulseRatio(motorpwm2_in1_pin, valueR)

# ButtonTurnLeft ist der Pfeil fuer die Linksfahrt		
@webiopi.macro
def ButtonTurnLeft():

	global motorLspeed
	global motorRspeed
	global acceleration
	global speedstep
	global spotturn

# Wenn spotturn den Wert "left" hat und die Geradeausfahrt acceleration = 0 dann
# ist ein Drehen auf der Stelle moeglich.	
	if(spotturn == "right" and acceleration == 0):
		motorLspeed, motorRspeed, acceleration = stop()
	
	if(acceleration == 0):
		spotturn = "left"
			
	if(motorRspeed < motorLspeed):
		motorRspeed = motorRspeed + speedstep	
	elif(acceleration == 0):
		GPIO.digitalWrite(motor1_in1_pin, GPIO.LOW)
		GPIO.digitalWrite(motor1_in2_pin, GPIO.HIGH)
		GPIO.digitalWrite(motor2_in1_pin, GPIO.LOW)
		GPIO.digitalWrite(motor2_in2_pin, GPIO.HIGH)

		motorLspeed = motorLspeed + speedstep
		motorRspeed = motorRspeed + speedstep
	else:
		motorLspeed = motorLspeed - speedstep

	motorLspeed, motorRspeed = check_motorpseed(motorLspeed, motorRspeed)		
	valueL = float(motorLspeed)
	valueR = float(motorRspeed)
		
	valueL = valueL/100
	valueR = valueR/100

	GPIO.pulseRatio(motorpwm1_in1_pin, valueL)
	GPIO.pulseRatio(motorpwm2_in1_pin, valueR)

	
# ButtonTurnLeft ist der Pfeil fuer die Rechtsfahrt
@webiopi.macro
def ButtonTurnRight():
	global motorLspeed
	global motorRspeed
	global acceleration
	global speedstep
	global spotturn

# Wenn spotturn den Wert "left" hat und die Geradeausfahrt acceleration = 0
# dann ist ein Drehen auf der Stelle moeglich.
	if(spotturn == "left" and acceleration == 0):
		motorLspeed, motorRspeed, acceleration = stop()
	if(acceleration == 0):
		spotturn = "right"
	
	if(motorLspeed < motorRspeed):
		motorLspeed = motorLspeed + speedstep	
	elif(acceleration == 0):
		GPIO.digitalWrite(motor1_in1_pin, GPIO.HIGH)
		GPIO.digitalWrite(motor1_in2_pin, GPIO.LOW)
		GPIO.digitalWrite(motor2_in1_pin, GPIO.HIGH)
		GPIO.digitalWrite(motor2_in2_pin, GPIO.LOW)

		motorLspeed = motorLspeed + speedstep
		motorRspeed = motorRspeed + speedstep
	else:
		motorRspeed = motorRspeed - speedstep

	motorLspeed, motorRspeed = check_motorpseed(motorLspeed, motorRspeed)		
	valueL = float(motorLspeed)
	valueR = float(motorRspeed)
		
	valueL = valueL/100
	valueR = valueR/100

	GPIO.pulseRatio(motorpwm1_in1_pin, valueL)
	GPIO.pulseRatio(motorpwm2_in1_pin, valueR)

# ButtonStop ist der Stop Knopf und haelt das Raspberry PI Auto an.	
@webiopi.macro
def ButtonStop():	
	stop()

initiate()

# starten des Web-Servers und vergabe der Zugangsdaten
server = webiopi.Server(port=8000, login="robot", password="robot")

# Hier werden die Buttons mit den definierten Funktionen hinterlegt
server.addMacro(ButtonForward)
server.addMacro(ButtonStop)
server.addMacro(ButtonReverse)
server.addMacro(ButtonTurnRight)
server.addMacro(ButtonTurnLeft)

webiopi.runLoop()
server.stop()