import socket

def decrypt(inp, key):
    dec=""
    for char in inp:
        temp=ord(char)
        for i in range(int(key)):
            temp-=1
            if temp<97:
                temp=122
        dec+=chr(temp)
    return dec 

s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("localhost", 9998))
s.listen(5)
print("server listening! ")

c,adr = s.accept()

while True:
    data = c.recv(1024).decode()
    key = input("\nEnter the key : ")
    data = decrypt(data,key)
    if not data:
        break
    print("\nMessage from client : ",data)
    msg = input("Enter the message to send : ")
    c.send(msg.encode())
s.close()    
