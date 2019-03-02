import socket
from machine import UART 

addr=socket.getaddrinfo(wlan.ifconfig()[0], 80)[0][-1]
s=socket.socket()
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind(addr)
s.listen(5)
speed = 38400
uart=UART(1,speed)
uart.init(speed, bits=8, parity=None, stop=1)
while True:
	cs, addr=s.accept()   
	print(addr)
	data=cs.recv(1024) 
	print("%s<"%(data.split()[1]))
	uart.write("%s<"%(data.split()[1]))
	cs.close() 

s.close() 