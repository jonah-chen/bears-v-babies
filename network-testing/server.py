import socket

PORT = 25100
SERVER = socket.gethostbyname(socket.gethostname())

ADDR = (SERVER, PORT)
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(ADDR)


def start():
    server.listen()
    print(f"[LISTENING] Server is listening on {SERVER}")
    while True:
        conn, addr = server.accept()
        print(addr)
        conn.send(b'\x35')


print("[STARTING] server is starting...")
start()

