from cs50 import get_float

# coins available are quarters (25¢), dimes (10¢), nickels (5¢), and pennies (1¢)
number = get_float("Change: ")
print(number)
counter = 0

while number <= 0.0:
    number = get_float("Change: ")

number *= 100
while number >= 25:
    counter += 1
    number -= 25
    print(number)
while number >= 10:
    counter += 1
    number -= 10
    print(number)
while number >= 5:
    counter += 1
    number -= 5
    print(number)
while number >= 1:
    counter += 1
    number -= 1
    print(number)

print(counter)
