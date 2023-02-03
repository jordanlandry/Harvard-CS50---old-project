#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int checkScore(string phrase);

int main(void)
{
    // Get text from the user
    string sentence = get_string("Input a sentence: ");

    // Find out the grade
    int grade = checkScore(sentence);

    // Print out the grade
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

int checkScore(string phrase)
{
    /*
        index = 0.0588 * L - 0.296 * S - 15.8
        L is the average letters per 100 words
        S is average number of sentences per 100 words
    */


    // Next word is just a ' '
    // Iterate through every letter and when there's a space that's a new word
    // Every '.', '!', '?', is a new sentence

    int words = 1;
    int letters = 0;
    int sentences = 0;

    for (int i = 0; phrase[i] != '\0'; i++)
    {
        if (phrase[i] == ' ')
        {
            words++;
        }
        else if (phrase[i] == '!' || phrase[i] == '.' || phrase[i] == '?')
        {
            sentences++;
        }
        else if (tolower(phrase[i]) >= 'a' && tolower(phrase[i]) <= 'z')
        {
            letters++;
        }
    }

    // If I have 10 words I need to multiply by 10, I need 100 / number of words then multiply that by the final number of letters and sentences
    float avg = (float) 100.0 / words;
    float L = avg * letters;
    float S = avg * sentences;

    float score = (0.0588 * L) - (0.296 * S) - 15.8;

    // printf("%f\n", score);

    // Automatically round the number
    if ((int)(score * 10) % 10 >= 5)
    {
        score = (int) score + 1;
    }

    return (int) score;
}