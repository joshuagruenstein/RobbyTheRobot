import socket
from threading import Thread
from time import sleep

HOST = '127.0.0.1'
PORT = 50007

mLeft = 0.0
mRight = 0.0
gyro = 0.0
distance = 0.0
penIs = False
penWidth = 5
penR = 0
penG = 0
penB = 0

running = True

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(1)

def waitForStart():
	global conn, addr
	print 'waiting for start...'
	conn, addr = s.accept()
	print 'connected to simulator'

	thread = Thread(target=beginSim, args =[])
	thread.start()

def beginSim():
	global running
	while running:
	    data = conn.recv(256)
	    if not data: break
	    conn.send(outString())
	    parseSensors(data)
	    sleep(.01)
	running = False
	conn.close()
	print 'connection broken'

def outString():
	penIsSize = penWidth if penIs else 0
	outey = str(mLeft)+','+str(mRight)+','+str(penIsSize)+','+str(penR)+','+str(penG)+','+str(penB)+'|'
	return outey

def parseSensors(data):
	global gyro, distance
	senseList = data.split(',')
	gyro = float(senseList[0])
	distance = float(senseList[1])

def penUp():
	global penIs
	penIs = False

def penDown():
	global penIs
	penIs = True

def byeBye():
	global running
	running = False

def isRunning():
	return running