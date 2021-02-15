#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
//The command-line will take arguments
int main(int argc, string argv[])
{
    //If there are more than 2 command-line arguments, then the terminal will print an error message
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    //If there is exactly two 2 arguments, the argument will run through these tests to check if it is valid
    else if (argc == 2)
    {
        //This loop will iterate through each character of the argument 
        for (int i = 0, keyLen = strlen(argv[1]); i <= keyLen; i++)
        {
            string keyString = argv[1];
            //If any of the characters are a letter or show a negative sign, the terminal will print an error message
            if (isalpha(keyString[i]) || (keyString[i] == '-'))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
    }
    //This converts the second command-line argument to an integer
    int key = atoi(argv[1]);
    //This will ask the user for an input and store it in plainText
    string plainText = get_string("plaintext: ");
    printf("ciphertext: ");
    //This iterates through each character of the input
    for (int i = 0, plainLen = strlen(plainText); i < plainLen; i++)
    {
        //If the character is a lowercase letter then it will shift it by the position determined by the key
        if (islower(plainText[i]))
        {
            printf("%c", (plainText[i] - 'a' + key) % 26 + 'a');
        }
        //If the character is a uppercase letter then it will shift it by the position determined by the key
        else if (isupper(plainText[i]))
        {
            printf("%c", (plainText[i] - 'A' + key) % 26 + 'A');
        }
        //If the character is not a letter then it will print it out exactly as it is
        else
        {
            printf("%c", plainText[i]);
        }
    }
    printf("\n");
}