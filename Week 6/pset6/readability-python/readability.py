import math
import string as strloop


def main():
    # Get the user input
    sentence = input("Sentence: ")
    grade = getGrade(sentence)

    # Different prints if it is greater than 15 or less than 1
    if grade < 1:
        print("Before Grade 1")
    elif grade > 15:
        print("Grade 16+")
    else:
        print(f'Grade {grade}')


def getGrade(string):
    sentences = 0
    letters = 0
    words = 1   # Last word will have no space so I need to start at 1

    # Run through each letter
    for letter in string:
        if letter == "!" or letter == "?" or letter == ".":
            sentences += 1
        elif letter in strloop.punctuation:
            continue
        elif letter in strloop.whitespace:
            words += 1
        else:
            letters += 1

    # Average letters and sentences per 100 words
    L = letters / words * 100
    S = sentences / words * 100

    # Coleman-Liau index formula
    return round(0.0588 * L - 0.296 * S - 15.8)


main()
