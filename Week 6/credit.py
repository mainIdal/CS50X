from cs50 import get_int

valid = False
number = str(get_int("Number: "))
digits = [int(digit) for digit in number]

digit_number = len(number)
summation = 0

if digit_number % 2 == 0:
    for even_digit in range(0,digit_number,2):
        num = digits[even_digit] * 2
        while num > 0:
            summation += (num % 10)
            num //= 10
        summation += digits[even_digit+1]
else:
    for odd_digit in range(1,digit_number,2):
        num = digits[odd_digit] * 2
        while num > 0:
            summation += (num % 10)
            num //= 10
        summation += digits[odd_digit-1]
    summation += digits[digit_number-1]
if summation % 10 == 0:
    valid = True

if digit_number == 15 and valid == True and (digits[0] == 3 and (digits[1] == 4 or digits[1] == 7)):
    print("AMEX")

elif digit_number == 16 and valid == True and (digits[0] == 5 and (digits[1] == 1 or digits[1] == 2 
or digits[1] == 3 or digits[1] == 4 or digits[1] == 5)):
    print("MASTERCARD")

elif digit_number in [13,16] and digits[0] == 4:
    print("VISA")

else:
    print("INVALID")
