import socket

SERVER = ("127.0.0.1", 5000)
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(SERVER)

while True:
    sock.send(b"Hello server!")
    data = sock.recv(6)
    print(data)

sock.close()