from cs50 import get_int

def main():
    hashCount = 2
    while True:
        height = get_int("Height: ")
        if height >= 0 and height <= 23:
            break
    spaceCount = height - 1
    for i in range(height):
        for j in reversed(range(spaceCount)):
            print(" ", end="")
        for j in reversed(range(hashCount)):
            print("#", end="")
        print()
        spaceCount -= 1
        hashCount += 1
        
if __name__ == "__main__":
    main()