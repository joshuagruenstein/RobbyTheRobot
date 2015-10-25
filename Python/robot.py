import socket
from threading import Thread

HOST = '127.0.0.1'
PORT = 50007

mLeft = 0.0
mRight = 0.0
gyro = 0.0
penIs = False
penWidth = 5

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
	running = False
	conn.close()
	print 'connection broken'

def outString():
	penIsSize = penWidth if penIs else 0
	outey = str(mLeft)+','+str(mRight)+','+str(penIsSize)+'|'
	return outey

def parseSensors(data):
	global gyro
	senseList = data.split()
	gyro = float(senseList[0])

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