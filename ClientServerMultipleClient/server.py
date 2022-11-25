import socket
import threading

IP = socket.gethostbyname(socket.gethostname())
PORT = 12345
ADDR = (IP, PORT)

def handle_client(conn, addr):
    print('new conncetion established with address: ', addr)

    connected = True
    while connected:
        msg = conn.recv(1024).decode("utf-8")
        if msg == 'bye':
            connected = False
   
        print('Received from the client  : '+str(msg)) 
        msg = f"Msg received: {msg}"
        msg = input('Enter the message : ')
        conn.send(msg.encode("utf-8"))

    conn.close()

def main():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(ADDR)
    server.listen()
    print(f"[LISTENING] Server is listening on {IP}:{PORT}")

    while True:
        conn, addr = server.accept()
        thread = threading.Thread(target=handle_client, args=(conn, addr))
        thread.start()
        print(f"[ACTIVE CONNECTIONS] {threading.activeCount() - 1}")

if __name__ == "__main__":
    main()