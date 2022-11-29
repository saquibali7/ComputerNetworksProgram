import socket

def encrypt(inp, key):
    enc=""
    for char in inp:
        temp=ord(char)
        for i in range(int(key)):
            temp+=1
            if temp>122:
                temp=97
        enc+=chr(temp)
    return enc 

c = socket.socket()
c.connect(("localhost", 9998))

msg = input("Enter the message to send : ")

while msg!="bye":
    key = input("Enter the key : ")
    msg = encrypt(msg,key)
    # msg = msg
    # print("Message after encryption : ", msg)
    c.send(msg.encode())

    data = c.recv(1024).decode()
    print("\n Messaeg from server : ", data)

    msg = input("Enter the message to be send : ")

c.close()