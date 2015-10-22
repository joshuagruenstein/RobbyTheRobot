import robot
from time import sleep
import math

robot.init()
robot.waitForStart()


while robot.isRunning():
	robot.mLeft = 100
	robot.mRight = 100

	sleep(0.5)

	robot.mLeft = 40
	robot.mRight = -40
	
	sleep(0.32)


robot.byeBye()