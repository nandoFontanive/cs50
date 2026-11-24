from cs50 import get_int

number = get_int("Insert number: ")

while number < 1 or number > 8:
    print("Enter a number between 1 and 8")
    number = get_int("Insert number: ")

for i in range(number):
    print(f" " * ((number - 1) - i), end="")
    print(f"#" * (i+1))
    i = number + 1
