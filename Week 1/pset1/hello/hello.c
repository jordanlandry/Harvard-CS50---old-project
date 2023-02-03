#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Get user input
    string name = get_string("What's your name? ");

    // Print their name
    printf("hello, %s\n", name);
}