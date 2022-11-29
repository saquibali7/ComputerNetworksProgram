import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("localhost",9996))
s.listen(5)
print("Server listening !")

c, adr = s.accept()

while True:
    data = c.recv(1024).decode()
    if not data:
        break
    print("\nMessage from client : ",data)
    msg = input("Write a return message to client : ")
    c.send(msg.encode())
s.close()