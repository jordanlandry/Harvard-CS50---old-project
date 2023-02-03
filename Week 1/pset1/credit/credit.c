#include <cs50.h>
#include <stdio.h>
#include <math.h>

// AMEX 15 digits MASTERCARD 16 digits VISA 13 || 16 digits
int get_length(long credit);
string check(long credit, int length);
bool is_valid(long card, int length);
int get_digit(long credit, int length, int n);

int main(void)
{
    long credit = get_long("Credit Card: ");
    int length = get_length(credit);
    string card = check(credit, length);
    printf("%s\n", card);
}

// Returns the length of the card
int get_length(long credit)
{
    if (credit < 10000000000000000 && credit >= 1000000000000000)
    {
        return 16;
    }

    else if (credit >= 100000000000000)
    {
        return 15;
    }

    else if (credit >= 1000000000000 && credit < 10000000000000)
    {
        return 13;
    }

    return 0;
}

// Checks if the card is valid
bool is_valid(long card, int length)
{
    int sum = 0;
    for (int i = 1; i < length; i += 2)
    {
        int n = (get_digit(card, length, length - i)) * 2;

        // If the value is 2 digits long, then it has to add the two of the digits
        if (n < 10)
        {
            sum += n;
        }
        else
        {
            // Adds the 2 digits together
            for (int j = 1; j <= 2; j++)
            {
                int a = get_digit(n, 2, j);
                sum += a;
            }
        }
    }

    // Add the rest of them by starting with the last digit
    for (int j = 0; j < length; j += 2)
    {
        int n = (get_digit(card, length, length - j));
        sum += n;
    }

    // if the last number is 0, it is valid
    if (sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Returns the type of card
string check(long credit, int length)
{
    bool p = is_valid(credit, length);

    // Check if the card contents are valid
    if (is_valid(credit, length) == false)
    {
        return ("INVALID");
    }

    int firstDigit;
    int secondDigit;

    // Check the first number
    firstDigit = get_digit(credit, length, 1);

    // Check for VISA
    if (length == 13 || length == 16)
    {
        if (firstDigit == 4)
        {
            return ("VISA");
        }
    }

    // Every other card you need the first 2 numbers so get second number
    secondDigit = get_digit(credit, length, 2);

    // Check for American Express
    if (length == 15 && firstDigit == 3)
    {
        if (secondDigit == 4 || secondDigit == 7)
        {
            return "AMEX";
        }
    }

    // Check for MasterCard
    if (length == 16 && firstDigit == 5)
    {
        if (secondDigit > 0 && secondDigit < 6)
        {
            return "MASTERCARD";
        }
    }

    return "INVALID";
}

// Returns the n'th digit of the card
int get_digit(long credit, int length, int n)
{
    long temp = credit;
    temp /= pow(10, length - n);
    int i = temp % 10;

    return i;
}