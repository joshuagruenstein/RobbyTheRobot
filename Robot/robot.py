import socket

HOST = '127.0.0.1'
PORT = 50007

mLeft = 50.0;
mRight = 50.0;

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

def updateSim(m1,m2):
    data = conn.recv(1024)
    if not data: return False
    conn.send('('+str(m1)+','+str(m2)+')')
    return True

init()
waitForStart()

while 1:
	if not updateSim(mLeft,mRight): break


conn.close()
print 'connection broken'