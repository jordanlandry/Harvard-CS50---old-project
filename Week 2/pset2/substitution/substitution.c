#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Check if a key was provided
    if (argc != 2)
    {
        printf("%i\n", argc);
        printf("Please use 1 argument. You used %i arguments.\n", argc - 1);
        return 1;
    }

    // Store the inputted key
    string code = argv[1];

    // Make sure the key contains 26 letters
    int len = strlen(code);
    if (len != 26)
    {
        printf("Your code doesn't have 26 letters. You used %i.\n", len);
        return 1;
    }

    // Check that the key only contains letters
    for (int i = 0; code[i] != '\0'; i++)
    {
        if ((code[i] < 'a' || code[i] > 'z') && (code[i] < 'A' || code[i] > 'Z'))
        {
            printf("Your code doesn't only contain letters. Check your %i'th character\n", i + 1);
            return 1;
        }
    }

    // Check your key doesn't contain any duplicates

    // Keep track of all the letters used
    bool used_letters[26] = {false};
    int index;
    for (int i = 0; code[i] != '\0'; i++)
    {
        code[i] = tolower(code[i]);
        index = code[i] - 97;
        if (used_letters[index])
        {
            printf("Code cannot contain any duplicates.\n");
            return 1;
        }

        used_letters[index] = true;
    }

    // Prompt user for sentence
    string text = get_string("Enter the plaintext you would like to decipher: ");

    int size = strlen(text);
    char cipher[size];
    printf("ciphertext: ");

    // Swap the text
    for (int i = 0; text[i] != '\0'; i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            if (text[i] == toupper(text[i]))
            {
                index = text[i] - 65;
                cipher[i] = toupper(code[index]);
            }
            else if (text[i] == tolower(text[i]))
            {
                index = text[i] - 97;
                cipher[i] = tolower(code[index]);
            }
        }
        else
        {
            cipher[i] = text[i];
        }
        printf("%c", cipher[i]);
    }

    printf("\n");
}