import robot
from time import sleep

robot.waitForStart()

robot.penDown()

while robot.isRunning():
	robot.mLeft = 50
	robot.mRight = 35


robot.byeBye()