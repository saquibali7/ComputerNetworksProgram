from string import ascii_lowercase, ascii_uppercase

inp = input("Enter a string: ")
key = input("Enter a key: ")

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

def decode(inp, key):
    dec=""
    for char in inp:
        temp=ord(char)
        for i in range(int(key)):
            temp-=1
            if temp<97:
                temp=122
        dec+=chr(temp)
    return dec    

encrypption = encrypt(inp, key)
print("Encrypted string: ", encrypption)
decrypt = decode(encrypption, key)
print("Decrypted string: ", decrypt)