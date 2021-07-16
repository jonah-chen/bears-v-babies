import socket

PORT = 25100
SERVER = socket.gethostbyname(socket.gethostname()) 
ADDR = (SERVER, PORT)

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(ADDR)
print(client.recv(1))

