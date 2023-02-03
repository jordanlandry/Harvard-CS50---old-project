from cs50 import get_string, get_int

# American Express: 15 digits starting with 34 or 37
# MasterCard: 16 digits starting with 51, 52, 53, 54, or 55
# Visa: 13 or 16 digits starting with 4

def main():
    # Get user input
    card = get_int("Enter a card number: ")
    length = getLength(card)

    # Based on the contents, what kind of card is it
    print(getType(card, length))


# Checking if the length of the card is valid.
def getLength(card):
    if (card >= 1000000000000 and card <= 9999999999999):
        return 13

    if (card >= 100000000000000 and card <= 999999999999999):
        return 15

    if (card >= 1000000000000000 and card <= 9999999999999999):
        return 16

    return 0


# Check if the card is actually valid
def isValid(card, length):
    sum = 0
    # I want to start at length -1, to add to the sum

    # Adding from the 2nd last and multipling by 2
    for i in range(1, length, 2):
        n = (getDigit(card, length, length - i)) * 2

        # If the value is 2 digits long, then it has to add the two of the digits
        if (n < 10):
            sum += n

        else:
            # Adds the 2 digits together
            for j in range(1, 3, 1):
                a = getDigit(n, 2, j)
                sum += a


    # Add the rest of them by starting with the last digit
    for j in range(0, length, 2):
        n = (getDigit(card, length, length - j))
        sum += n

    # if the last number is 0, it is valid
    if (sum % 10 == 0):
        return True

    else:
        return False;


# Get the type of card
def getType(card, length):
    p = isValid(card, length)

    # Check if the card contents are valid
    if (isValid(card, length) == False):
        return ("INVALID")


    # Check the first number
    firstDigit = getDigit(card, length, 1)

    # Check for VISA
    if (length == 13 or length == 16):
        if (firstDigit == 4):
            return ("VISA")


    # Every other card you need the first 2 numbers so get second number
    secondDigit = getDigit(card, length, 2)

    # Check for American Express
    if (length == 15 and firstDigit == 3):
        if (secondDigit == 4 or secondDigit == 7):
            return "AMEX"

    # Check for MasterCard
    if (length == 16 and firstDigit == 5):
        if (secondDigit > 0 and secondDigit < 6):
            return "MASTERCARD"


    return "INVALID"

# Returns the n'th digit of the card
def getDigit(card, length, n):
    temp = card
    temp /= 10 ** length - n
    i = temp % 10

    return i


if __name__ == "__main__":
    main()