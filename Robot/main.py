import robot
from random import randint

robot.mLeft = 100
robot.mRight = 100

robot.init()
robot.waitForStart()

while robot.isRunning():
	robot.mLeft = randint(0,100)
	robot.mRight = randint(0,100)

robot.byeBye()