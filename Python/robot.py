import socket
from threading import Thread

HOST = '127.0.0.1'
PORT = 50007

mLeft = 0.0
mRight = 0.0
gyro = 0.0

running = True

global s
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((HOST, PORT))
s.listen(1)

def waitForStart():
	global conn
	global addr
	print 'waiting for start...'
	conn, addr = s.accept()
	print 'connected to simulator'

	thread = Thread(target=beginSim, args =[])
	thread.start()

def beginSim():
	global running, mLeft, mRight
	while running:
	    data = conn.recv(1024)
	    if not data: break
	    conn.send(str(mLeft)+','+str(mRight)+'|')
	    parseSensors(data)
	running = False
	conn.close()
	print 'connection broken'

def parseSensors(data):
	global gyro
	senseList = data.split()
	gyro = float(senseList[0])
	return # add stuff

def byeBye():
	running = False

def isRunning():
	return running