# TODO
from cs50 import get_int

h = 0
while h < 1 or h > 8:
    h = get_int("Height: ")

for i in range(1, h + 1):
    for j in range(1, h + 1):

        # Start printing # after correct number of spaces
        if j > (h - i):
            print("#", end="")
        else:
            print(" ", end="")

        # Print middle space and remaining #
        if j == h:
            print(" ", "#" * i, end="")
    print()
