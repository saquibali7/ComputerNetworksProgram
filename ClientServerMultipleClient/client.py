import socket

IP = socket.gethostbyname(socket.gethostname())
PORT = 12345
ADDR = (IP, PORT)

def main():
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect(ADDR)
    print(f"[CONNECTED] Client connected to server at {IP}:{PORT}")
    msg="hello"
    connected = True
    while connected:
        msg = input("Enter the message : ")
        client.send(msg.encode("utf-8"))
        if msg == 'bye':
            connected = False
        # else:
        #     msg = client.recv(1024).decode("utf-8")
        #     print(f"[SERVER] {msg}")
        data = client.recv(1024).decode("utf-8")
        print('Received from the server :',str(data.decode('ascii')))    
    client.close()   
if __name__ == "__main__":
    main()