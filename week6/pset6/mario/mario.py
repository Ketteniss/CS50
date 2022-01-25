from cs50 import get_int

while(True):
    h = get_int("Height: ")
    if (h > 0 and h < 9):
        break
    else:
        print("Invalid input, please type in positive integer between 1 and 8.")
for i in range(h):
    print(" "*((h-1)-i) + "#"*i + "  " + "#"*i)