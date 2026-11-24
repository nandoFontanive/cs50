#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int HEADER_SIZE = 512;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Correct usage is: recover file.raw\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Invalid file.\n");
        return 1;
    }

    // Create a buffer for a block of data
    uint8_t buffer[HEADER_SIZE];

    int counter = 0;
    FILE *img = NULL;
    while (fread(&buffer, sizeof(buffer), 1, card) ==
           1) // fread returns the number of items successfully read. Since you’re reading one item
              // of size 512 bytes, fread should return 1 if it successfully reads a block of data.
              // If it returns 0, it means you’ve reached the end of the file.
    {
        char filename[8];

        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) &&
            ((buffer[3] & 0xf0) == 0xe0))
        {
            // printf("%02x %02x %02x %02x\n", buffer[0], buffer[1], buffer[2], buffer[3]);
            if (counter > 0)
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", counter); //%03i = int com 3 dígitos
            img = fopen(filename, "w");
            fwrite(buffer, sizeof(buffer), 1, img);
            counter++;
            printf("counter = %i\n", counter);
        }
        else if (img != NULL)
        {
            fwrite(buffer, sizeof(buffer), 1, img);
        }
    }
    fclose(img);
    fclose(card);
}
