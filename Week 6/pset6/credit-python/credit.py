from cs50 import get_int

# AMEX: 34 or 37 with 15 digits
# Visa: 4 with 13 or 16 digits
# Mastercard: 51, 52, 53, 54, 55, with 13 or 16 digits


def main():
    card = get_int("Enter a card: ")
    length = len(str(card))
    print(is_valid(card, length))


def is_valid(card, length):
    sum = 0

    # Multiply every other digit by 2 starting from the 2nd last
    # Then add the other numbers
    i = length - 2
    counter = 0

    # Start from 2nd last digit and multiply each by 2
    i = length - 2
    while i >= 0:
        n = str(card)[i]
        n = int(n) * 2

        if n < 10:
            sum += n
        else:
            a = str(n)[0]
            b = str(n)[1]
            sum += int(a)
            sum += int(b)

        i -= 2

    # Add the rest of the numbers to the sum
    i = length - 1
    while i >= 0:
        n = str(card)[i]
        n = int(n)
        sum += n
        i -= 2

    # Check if last number is a 0
    if (sum % 10 != 0):
        return "INVALID"

    # Visa
    if (length == 13 or length == 16) and str(card)[0] == '4':
        return 'VISA'

    # AMEX
    if length == 15 and str(card)[0] == '3':
        if str(card)[1] == '4' or str(card)[1] == '7':
            return 'AMEX'

    # Mastercard
    if length == 13 or length == 16:
        if str(card)[0] == '5':
            if str(card)[1] == '1' or str(card)[1] == '2' or str(card)[1] == '3' or str(card)[1] == '4' or str(card)[1] == '5':
                return 'MASTERCARD'

    return 'INVALID'


if __name__ == "__main__":
    main()