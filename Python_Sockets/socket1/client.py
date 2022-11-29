import socket

          
c = socket.socket()
c.connect(("localhost",9996))

msg = input("Write a message to server : ")

while msg.lower() != "bye":
    c.send(msg.encode())
    
    data = c.recv(1024).decode()
    print("\nMessage from server : ", data)

    msg = input("Write a message to server : ")

c.close()