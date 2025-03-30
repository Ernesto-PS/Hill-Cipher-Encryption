/*============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Hill cipher
|
| To Compile:  javac pa01.java
|              gcc -o pa01 pa01.c
|              g++ -o pa01 pa01.cpp
|              go build pa01.go
|              rustc pa01.rs
|
| To Execute:  java   -> java pa01 kX.txt pX.txt
|        or    c++    -> ./pa01 kX.txt pX.txt
|        or    c      -> ./pa01 kX.txt pX.txt
|        or    go     -> ./pa01 kX.txt pX.txt
|        or    python -> python3 pa01.py kX.txt pX.txt
|                        where kX.txt is the keytext file
|                        and pX.txt is plaintext file 
|       Note:
|              All input files are simple 8 bit ASCII input
|              All execute commands above have been tested on Eustis
+===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MATRIX_MAX_SIZE 9
#define CHAR_ARR_SIZE 10000
#define LETTERS_PER_ROW 80

int main(int argc, char* argv[])
{
    FILE *keyFile, *plainTextFile;
    int matrixSize = 0;
    int charIndex = 0;
    int paddingAmount = 0;
    int totalLength = 0;
    int counter = 0;
    int ptCounter = 0;
    int vectorProduct = 0;
    int vectorSum = 0;
    int keyEncryptionMatrix[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE];
    char plainText[CHAR_ARR_SIZE];
    int cypherMatrix[MATRIX_MAX_SIZE][1];
    int cypherText[CHAR_ARR_SIZE];

    // Opens key file
    char *kFile = argv[1];
    keyFile = fopen(kFile, "r");
    if (keyFile == NULL) 
    {
        printf("Could not open key file!");
        printf("\n");
        return 0;
    }

    // Opens plain file
    char *ptFile = argv[2];
    plainTextFile = fopen(ptFile, "r");
    if (plainTextFile == NULL) 
    {
        printf("Could not open plain text file!");
        printf("\n");
        return 0;
    }

    // Reads key file
    // Stores matrix size to use for its rows and columns
    fscanf(keyFile, "%d", &matrixSize);
    while (!feof(keyFile)) 
    {
        for (int i = 0; i < matrixSize; i++) 
        {
            for (int j = 0; j < matrixSize; j++) 
            {
                // Stores the values in each index of the matrix double array
                fscanf(keyFile,"%d ", &keyEncryptionMatrix[i][j]);
            }
        }
    }

    // Prints key matrix's values
    printf("\n");
    printf("Key matrix:");
    printf("\n");
    for (int i = 0; i < matrixSize; i++) 
    {
        for (int j = 0; j < matrixSize; j++) 
        {
            printf("%4d", keyEncryptionMatrix[i][j]);
        }
    printf("\n");
    }

    // Reads plain text file
    do
    {
        int charASCII = fgetc(plainTextFile);
        // Once it reaches end of file, it will determine the necessary amount of padding
        if (feof(plainTextFile)) 
        {
            if (charIndex % matrixSize != 0) 
            {
                // Determines how many "x" are needed
                paddingAmount = (matrixSize - ((charIndex % matrixSize)));
                totalLength = charIndex + paddingAmount;
                for (int i = charIndex; i < totalLength; i++) {
                    plainText[i] = 'x';
                }
                break;
            }
            else
                break;
        }
        // Checks if the ascii value of the character read is an alphanumeric number as to ignore non-alphabet characters
        else if (isalpha(charASCII)) 
        {
            // Transforms upper alphanumeric numbers (letters) into their lowercase version and stores them in the plain text array
            if (isupper(charASCII)) 
            {
                charASCII = tolower(charASCII);
                plainText[charIndex] = charASCII;
                charIndex++;
            }
            // Ignores spaces and inputs read character into the plain text array
            else if (!isspace(charASCII)) 
            {
                plainText[charIndex] = charASCII;
                charIndex++;
            }
        }
        else
            continue;
    } while (1);

    // Prints plain text
    printf("\n");
    printf("Plaintext:");
    for (int i = 0; i < totalLength; i++) 
    {
        if (i % LETTERS_PER_ROW == 0)
            printf("\n");
        printf("%c", plainText[i]);
    }
    printf("\n");

    //Hill Cipher matrix multiplication
    while (counter < totalLength) 
    {
        for (int i = 0; i < matrixSize; i++) 
        {
            cypherMatrix[i][0] = plainText[ptCounter] % 'a';
            ptCounter++;
        }
        for (int j = 0; j < matrixSize; j++) 
        {
            for (int k = 0; k < matrixSize; k++) 
            {
                vectorProduct = keyEncryptionMatrix[j][k] * cypherMatrix[k][0];
                vectorSum += vectorProduct;
            }
            vectorSum %= 26;
            cypherText[counter] = vectorSum + 'a';
            counter++;
            vectorSum = 0;
        }
    }

    // Prints cypher text 
    printf("\n");
    printf("Ciphertext:");
    for (int i = 0; i < totalLength; i++) 
    {
        if (i % LETTERS_PER_ROW == 0)
            printf("\n");
        printf("%c", cypherText[i]);
    }
    printf("\n");

    // Closes files
    fclose(plainTextFile);
    fclose(keyFile);
    return 0;
}
