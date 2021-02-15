#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <cs50.h>

//will be able to use 'BYTE' as a variable type
typedef uint8_t BYTE;

//the size of the memory card is 512
#define BLOCK_SIZE 512
#define FILE_NAME_SIZE 8
//bool to see if we have started a new jpeg
bool is_start_new_jpeg(BYTE buffer[]);

int main(int argc, char *argv[])
{
    //see if there are 2 command line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image \n");
        return 1;
    }
    // opening file to read from
    FILE *infile = fopen(argv[1], "r");

    //see if file exists
    if (infile == NULL)
    {
        printf("FIle not found\n");
        return 1;
    }
    //create array to hold the buffer memory
    BYTE buffer[BLOCK_SIZE];

    bool have_found_first_jpeg = false;
    //number of jpegs found
    int file_index = 0;
    //initiate new file to hold jpegs
    FILE *outfile;

    //will loop until the end of the memory card
    while (fread(buffer, BLOCK_SIZE, 1, infile))
    {
        //checks if the bytes read are the start of a new jpeg
        if (is_start_new_jpeg(buffer))
        {
            //checks if you have found the first jpeg
            if (!have_found_first_jpeg)
            {
                have_found_first_jpeg = true;
            }
            else
            {
                fclose(outfile);
            }
            //array to hold file names
            char filename[FILE_NAME_SIZE];
            //creats file names
            sprintf(filename, "%03i.jpg", file_index++);
            //open file to hold jpegs
            outfile = fopen(filename, "w");
            //sees if file exists
            if (outfile == NULL)
            {
                return 1;
            }
            //write to the new file
            fwrite(buffer, BLOCK_SIZE, 1, outfile);
        }
        //if you already have found a jpeg, continue writing to the file
        else if (have_found_first_jpeg)
        {
            fwrite(buffer, BLOCK_SIZE, 1, outfile);
        }

    }
    //close files
    fclose(outfile);
    fclose(infile);

}

//function to see if the first 4 bytes are in sequence of a jpeg beginning
bool is_start_new_jpeg(BYTE buffer[])
{
    return buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;
}