import robot
from time import sleep
import math

robot.init()
robot.waitForStart()

t = 0

while robot.isRunning():
	robot.mLeft = robot.mRight = 100*math.cos(t/1000)
	t += .003

robot.byeBye()