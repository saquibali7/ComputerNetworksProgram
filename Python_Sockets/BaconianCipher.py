map = {
    'a': 'aaaaa', 'b': 'aaaab', 'c': 'aaaba', 'd': 'aaabb', 'e': 'aabaa',
    'f': 'aabab', 'g': 'aabba', 'h': 'aabbb', 'i': 'abaaa', 'j': 'abaab',
    'k': 'ababa', 'l': 'ababb', 'm': 'abbaa', 'n': 'abbab', 'o': 'abbba',
    'p': 'abbbb', 'q': 'baaaa', 'r': 'baaab', 's': 'baaba', 't': 'baabb',
    'u': 'babaa', 'v': 'babab', 'w': 'babba', 'x': 'babbb', 'y': 'bbaaa', 'z': 'bbaab'
}

def encrypt(message, ref):
    cipher = ''
    for letter in message:
        if(letter != ' '):
            cipher += map[letter]
        else:
            cipher += ' '

    enc=""
    k=0
    for i in range(len(ref)):
        if(k==len(cipher)):
            break
        if(ref[i]==' '):
            enc+=' '
            continue
        elif(cipher[k]=='b'):
            enc+=ref[i].upper()
            k+=1
        else :
            enc+=ref[i].lower()   
            k+=1

    return enc
def  decrypt(message):
    decipher = ''
    i = 0
    while True:
        if(i < len(message) - 4):
            substr = message[i:i + 5]
            if(substr == ' '):
                decipher += ' '
                i += 1
            enc=""
            for char in substr:
                if(char.isupper()):
                    enc+='b'
                else :
                    enc+='a'    
            else:
                decipher += list(map.keys())[list(map.values()).index(enc)]
                i += 5
        else:
            break
    return decipher

def main():
    s = input("Enter the message to be encrypted: ")
    ref = input("Enter the reference text : ")
    encode = encrypt(s,ref)
    print(encode)

    s = input("Enter the message to be decrypted: ")
    result = decrypt(encode)
    print(result)

if __name__ == '__main__':
    main()