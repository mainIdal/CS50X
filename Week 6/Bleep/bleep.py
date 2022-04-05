from cs50 import get_string
from sys import argv


def main():
    if len(argv) != 2:
        print("Usage: python bleep.py dictionary")
        exit(1)

    f = open(argv[1], "r")
    print("What message would you like to censor?")
    message = get_string("").split(" ")
    message_words = dict()
    for word in message:
        message_words[word] = word.lower()
    banned_words = [word.strip('\n').lower() for word in f.readlines()]
    
    for key,value in message_words.items():
        if value in banned_words:
            message_words[key] = ''.join('*' for i in range(len(value)))
    
    for key,value in message_words.items():
        if '*' not in value:
            print(key, end=" ")
        else:
            print(value, end=" ")
    
    print()
    f.close()
    exit(0)

if __name__ == "__main__":
    main()
