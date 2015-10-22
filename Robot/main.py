import robot
from time import sleep

robot.init()
robot.waitForStart()

while robot.isRunning():
	robot.mLeft = 100
	robot.mRight = 100
	sleep(0.5)
	robot.mLeft = -100
	robot.mRight = -100
	sleep(0.5)

robot.byeBye()