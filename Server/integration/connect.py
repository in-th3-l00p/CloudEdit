import socket

SERVER = ("127.0.0.1", 5000)

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(SERVER)

sock.close()
