from sys import exit
from sys import argv
from cs50 import get_string

if len(argv) != 2:
    print("Usage: python vigenere.py k")
    exit(1)

if argv[1].isalpha() == False:
    print("k can only include alphabetic characters")
    exit(1)

k = argv[1]
k_clockSize = len(argv[1])
plaintext = get_string("plaintext: ")

print("ciphertext: ", end="")
i = 0
for char in plaintext:
    asciiValue = ord(char)
    if asciiValue >= 65 and asciiValue <= 90:
        k_asciiValue = ord(k[i % k_clockSize].upper())
        newAsciiValue = asciiValue + k_asciiValue - 65
        if (newAsciiValue > 90):
            newAsciiValue -= 26 
        print(chr(newAsciiValue), end="")
        i+=1
    elif asciiValue >= 97 and asciiValue <= 122:
        k_asciiValue = ord(k[i % k_clockSize].lower())
        newAsciiValue = asciiValue + k_asciiValue - 97
        if (newAsciiValue > 122):
            newAsciiValue -= 26 
        print(chr(newAsciiValue), end="")
        i+=1
    else:
        print(char, end="")
    

print()
exit(0)
