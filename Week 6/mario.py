from cs50 import get_int

height = 0
while(True):
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break

for row in range(height):
    for col in range(height):
        if col + row < height - 1:
            print(" ", end="")
        else:
            print("#", end="") 
    print() 

for row in range(height):
    for col in range(height):
        if col <= row:
            print("#", end="") 
    print() 
 
