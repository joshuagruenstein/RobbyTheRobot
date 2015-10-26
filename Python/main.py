import robot
from time import sleep

robot.waitForStart()

robot.penDown()

while robot.isRunning():
	robot.mLeft = 10
	robot.mRight = -10


robot.byeBye()