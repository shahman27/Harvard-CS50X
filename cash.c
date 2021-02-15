#include <cs50.h>
#include <stdio.h>
#include <math.h>

float askPositiveFloat(void)
{
    float positiveFloat;
    //negative until proven positive
    bool negative = true;

    while (negative)
    {
        positiveFloat = get_float("Change Owed: \n");

        if (positiveFloat > 0) 
        {
            //sets false if our number is positive
            negative = false;
        }
    }
    return positiveFloat;
}
//This function will preform the tracking of coins i've couted and return it as an integer
int coinNum()
{
    //Stores total cents
    int totalCents = round(askPositiveFloat() * 100);
    //Store coin count
    int numOfCoins = 0;
    //Declare variable to store the remainders
    int remainder1 = 0;
    //Stores temp number
    int tempNum;
    
    //Declare variables to store coin values
    int quarter = 25;
    int dime = 10;
    int nickle = 5;
    int penny = 1;

    //if totalCents is greater than OR EQUAL to the value of a quarter
    if (totalCents >= quarter)
    {
        remainder1 = totalCents % quarter;
        tempNum = totalCents - remainder1;

        numOfCoins = numOfCoins + (tempNum / quarter);

        totalCents = remainder1;
    }
    //if totalCents is greater than OR EQUAL to the value of a dime
    if (totalCents >= dime)
    {
        remainder1 = totalCents % dime;
        tempNum = totalCents - remainder1;

        numOfCoins = numOfCoins + (tempNum / dime);

        totalCents = remainder1;
    }
    //if totalCents is greater than OR EQUAL to the value of a nickel    
    if (totalCents >= nickle)
    {
        remainder1 = totalCents % nickle;
        tempNum = totalCents - remainder1;

        numOfCoins = numOfCoins + (tempNum / nickle);

        totalCents = remainder1;
    }
    //if totalCents is greater than OR EQUAL to the value of a penny    
    if (totalCents >= penny)
    {
        remainder1 = totalCents % penny;
        tempNum = totalCents - remainder1;

        numOfCoins = numOfCoins + (tempNum / penny);

        totalCents = remainder1;
    }
    return numOfCoins;
}

int main(void)
{
    printf("%i\n", coinNum());
}
