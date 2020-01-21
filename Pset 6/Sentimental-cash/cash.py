from cs50 import get_float

def main():
    counter = 0
    while True:
        cash = round(get_float("Change owed: ") * 100);
        if cash >= 0:
            break
    while cash > 0:
        if cash >= 25:
            while cash >= 25:
                cash -= 25
                counter += 1
        if cash >= 10:
            while cash >= 10:
                cash -= 10
                counter += 1
        if cash >= 5:
            while cash >= 5:
                cash -= 5
                counter += 1
        if cash >= 1:
            while cash >= 1:
                cash -= 1
                counter += 1
    print(counter)

if __name__ == "__main__":
    main()