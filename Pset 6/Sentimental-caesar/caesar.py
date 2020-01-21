from cs50 import get_string
import sys

def main():
    if len(sys.argv) != 2:
        print("The program only accepts a single command-line argument. Please re-run the program and insert a non-negative integer as an argument")
        sys.exit(1)
    key = int(sys.argv[1])
    if key >= 26:
        key %= 26
    plaintext = get_string("plaintext:  ")
    encrypted = ""
    for c in range(len(plaintext)):
        char = plaintext[c]
        if plaintext[c].islower():
            char = ord(char)
            char -= 96
            char += key
            if char > 26:
                char -= 26
            char += 96
            char = chr(char)
        elif plaintext[c].isupper():
            char = ord(char)
            char += key
            if char > 90:
                char -= 26
            char = chr(char)
        encrypted += char
    print(f"ciphertext: {encrypted}")

if __name__ == "__main__":
    main()