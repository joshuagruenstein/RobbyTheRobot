import robot
from time import sleep

robot.waitForStart()

robot.penDown()

while robot.isRunning():
	robot.penG=255
	robot.penR=0
	robot.penB=0

	robot.mLeft = 50
	robot.mRight = 0
	sleep(.50)

	robot.penR=255
	robot.penG=0
	robot.penB=0
	
	robot.mLeft = 60
	robot.mRight = 60
	sleep(.90)

robot.byeBye()