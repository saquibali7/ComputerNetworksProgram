
def encrypt(inp, key):
    size = len(inp)
    key_size = len(key)
    enc=''
    for i in range(size):
        x = ord(inp[i]) - 97  
        y = ord(key[ i% key_size]) - 97
        res = (x+y)%26 + 97
        enc+=chr(res)

    return enc

def decrypt(inp, key):
    size = len(inp)
    key_size = len(key)
    k=0
    dec=''
    for i in range(size):
        x = ord(inp[i]) - 97
        y = ord(key[ i% key_size]) - 97
        res = (x-y+26)%26 + 97
        dec+=chr(res)
    return dec      

inp = input("Enter the input string : ")
key = input("Enter the key : ")

enc = encrypt(inp,key)
print(enc)
dec = decrypt(enc,key)
print(dec)
