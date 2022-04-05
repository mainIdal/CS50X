from cs50 import get_int

height = 0
while(True):
    height = get_int("Height: ")
    if height > 0 and height < 9:   
        break

for row in range(0,height):
    for col in range(0,2*height+2):
        if row + col < height - 1 or col == height or col == height + 1:
            print(" ", end="")
        elif row + col >= height - 1 and col <= height + 2 + row:
            print("#", end="")    
    print()
