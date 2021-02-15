#include <cs50.h>
#include <stdio.h>

int main(void)
{    
    //Declaring variable for user input.
    int height;
    do
    {
        //getting input from user.
        height = get_int("Height: \n");
    }
   //setting restrictions for user input
   while (height > 8 || height < 1);

   //loop for rows
   for (int i = 1; i <= height; i++)
   {
       //loop for columns
       for (int j = height - i; j > 0; j--)
       {
           printf(" ");
            //spaces infront of hashes
       }
       for (int hashes = 1; hashes <= i; hashes ++) 
           {
               //printing hashes
               printf("#");
           }        
       //printing sapces between the hashes
       printf ("  ");
       
       //loop for second pyramid
       for (int hashes = 0; hashes < i; hashes++)
       {
           //printing hashes
           printf("#");
       }
       printf("\n");
   }
}
