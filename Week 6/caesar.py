from sys import exit
from sys import argv
from cs50 import get_string

if len(argv) != 2:
    print("Usage: python caesar.py k")
    exit(1)

k = int(argv[1])
text = get_string("plaintext: ")

print("ciphertext: ", end="")
for char in text:
    asciiValue = ord(char)
    if asciiValue >= 65 and asciiValue <= 90:
        newAsciiValue = asciiValue + k % 26
        if (newAsciiValue > 90):
            newAsciiValue -= 26 
        print(chr(newAsciiValue), end="")
    elif asciiValue >= 97 and asciiValue <= 122:
        newAsciiValue = asciiValue + k % 26
        if (newAsciiValue > 122):
            newAsciiValue -= 26 
        print(chr(newAsciiValue), end="")
    else:
        print(char, end="")
print()
exit(0)
