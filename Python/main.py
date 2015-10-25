import robot
from time import sleep

robot.waitForStart()
robot.penIs = True

while robot.isRunning():
	robot.mLeft = 100
	robot.mRight = 100

	sleep(0.5)

	robot.mLeft = 40
	robot.mRight = -40
	
	sleep(0.32)


robot.byeBye()