inp = input("Enter a string: ")
key = input("Enter a key: ")

def encrypt(inp, key):
    col=key
    row = len(inp)/int(key)
    row = int(row)
    table=[]
    k=0
    for _ in range(int(row)):
        temp=[]
        for _ in range(int(col)):
            temp.append(inp[k])
            k+=1
        table.append(temp)    

    print(table)  

    enc=""
    for i in range(row):
        for j in range(int(col)):
            enc+=table[j][i]
    print(enc)        
    return enc

def decrypt(inp, key):
    col = int(key)
    row = len(inp)/int(key)
    row = int(row)

    table = []
    k=0
    for _ in range(row):
        temp=[]
        for _ in range(col):
            temp.append(inp[k])
            k+=1
        table.append(temp)
    dec=""

    for i in range(row):
        for j in range(col):
            dec+=table[j][i]
        
    print(dec)  
    return dec 

enc = encrypt(inp,key)
decrypt(enc,key)
