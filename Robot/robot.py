import socket
from threading import Thread
from time import sleep
import sys

HOST = '127.0.0.1'
PORT = 50007

mLeft = 0
mRight = 0
gyro = 0

running = True

def init():
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
	global running
	global mLeft
	global mRight
	while running:
	    data = conn.recv(1024)
	    if not data: break
	    conn.send(str(mLeft)+','+str(mRight)+'|')
	    parseSensors(data)
	running = False
	conn.close()
	print 'connection broken'

def parseSensors(data):
	return # add stuff

def byeBye():
	running = False

def isRunning():
	return running