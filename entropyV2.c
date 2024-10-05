#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

static double calculateEntropy(const char *hex, const size_t length);

int main()
{
    //This is the provided hex:
    const char hex_strings[20][65] = {
        "6f6664797a7179636f75797362636c6c6b686d68797a6d",
        "67686c666a776874726979726e726a7361796d766b787a",
        "65736167686d777975796a7563676a7a6a63616b6a656e",
        "61647a6e7566687373677571717763736b746a716d6c67",
        "76796378616f786875776c62706d6d676c6a6767696a6e",
        "6d78717275756b726466657975626675766f6a6370697a",
        "666b6764636b706c6662717676776979676879726f7276",
        "7371716868747576706a6c636f68796b78667473797279",
        "79616a65777070756572737575717470726f696d686d66",
        "70696e656170706c6520756e6465722074686520736561",
        "61617678707576776a6e6962746b757768776464617870",
        "63756c666f7364706267717462706c7a7463686d6e7672",
        "646d7376787569626364736c7a69636467796264766368",
        "756b7872716c69666a656271787a6e626464796c667066",
        "7976716769666a6a73776977796a7a68746c6f7a6c6a7a",
        "6b74666a6e6376646862757a6c6c76657870717773776e",
        "72617a6967706b62746179716e6e676368677567686d74",
        "7074766b646d6f6a7579756a776a677a75786275667871",
        "6970757868717866756e677763697067696e746e6b7870",
        "726a696273707a69726a67756c71666c77737779746d72"};

    //The rest of the "main" function body iterates over each hex string and displays them along with their entropy value
    size_t num_strings = sizeof(hex_strings) / sizeof(hex_strings[0]);
    int min_index = 0;
    double min_entropy = __DBL_MAX__;

    for (size_t i = 0; i < num_strings; i++)
    {
        size_t length = strlen(hex_strings[i]);
        if (length % 2 == 0)
        {
            double entropy = calculateEntropy(hex_strings[i], length);

            //condtion to find and keep the lowest entropy hex and its value
            if (entropy < min_entropy)
            {
                min_index = i;
                min_entropy = entropy;
            }

            printf("Hex: %s -> Shannon Entropy: %f\n", hex_strings[i], entropy);
        }
    }

    //Displays the hex with the lowest entropy
    printf("\nMost likely hex to be String (lowest entropy):\nHex: %s -> Shannon Entropy: %f\n", hex_strings[min_index], min_entropy);
}

static double calculateEntropy(const char *hex, size_t length)
{
    //Declares most commonly used values as variables
    uint8_t frequency[256] = {0};
    size_t bytes_count = length / 2;


    //for loop to count the number of occurrences(frequency) of a char
    for (size_t i = 0; i < bytes_count; i++)
    {
        char string[3] = {hex[i * 2], hex[i * 2 + 1], '\0'};
        int index = (int)strtol(string, NULL, 16);


        //Index out of bouds checking
        if (index >= 256)
        {
            fprintf(stderr, "Error: Index out of bounds\n");
            return -1;
        }

        frequency[index]++;
    }
    
    //calulates the shannon entropy value of the String from character frequency
    double entropy = 0.0;

    for (int i = 0; i < 256; i++)
    {

        //Checks to skip invalid numbers.
        if (frequency[i] <= 0)
        {
            continue;
        }

        //Shannon entropy value calculation
        double probability = (double)frequency[i] / bytes_count;
        entropy -= probability * log2(probability);
    }

    return entropy;
}
