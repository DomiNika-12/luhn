#include <iostream>

#include <stdio.h>
#include <stdlib.h>

// This program computes checksum and validates input using Luhn algorithm
// Source:
// https://en.wikipedia.org/wiki/Luhn_algorithm

//7992739871

#define MAX_BUFFER_SIZE 3

//
// This function computes the checksum using Luhn algorithm
//

int ComputeCheckSum(int* pPayload, int PayloadSize, int* pChecksum) {
    int temp = 0;
    int sum = 0;

    for (int i = 0; i < PayloadSize; i++) {
        temp = pPayload[i];

        //
        // Double the value and sum the digits for every other digit starting from the rightmost one
        //

        if ((i % 2) != 0) {
            printf("temp double: %d, i %d\n", temp, i);
            temp = temp * 2;
            if (temp > 9) {
                temp = temp - 9;
            }
        }
        sum = sum + temp;
        temp = 0;
    }
    printf("s: %d\n", sum);
    *pChecksum = (10 - (sum % 10));
    return 0;
}

//
// This function validates the given number
//

int ValidateCheckDigit(int* pPayload, int PayloadSize)
{
    int givenChecksum = pPayload[PayloadSize];
    int computedChecksum = 0;
    ComputeCheckSum(pPayload, PayloadSize, &computedChecksum);
    if (givenChecksum == computedChecksum)
    {
        return 0;
    }
    if (givenChecksum > computedChecksum)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main(int argc, char *argv[]) {

    int count = 0;
    char c = '\0';
    int BufferSize = 0;
    int *pBuffer = NULL;
    int Checksum = 0;
    int Error = 0;

    //
    // Get user's input while dynamically allocating enough memory
    //

GetInput:
    count = 0;
    c = '\0';
    BufferSize = (int)MAX_BUFFER_SIZE;

    pBuffer = (int *) malloc(sizeof(int) * BufferSize);
    memset(pBuffer, 0, BufferSize * sizeof(int));

    printf("Insert a number: \n");
    while (1) {
        if (count >= BufferSize) {
            BufferSize = BufferSize * 2;
            pBuffer = (int *) realloc(pBuffer, BufferSize);
            int* startZero = pBuffer + ((count));
            int lenZero = (BufferSize - count) * sizeof(int);
            memset(startZero, 0, lenZero);
        }
        c = getc(stdin);
        if (c == 0x0A) {
            pBuffer[count] = '\n';
            break;
        }
        if (c < 0x30 || c > 0x39) {
            printf("Invalid input! Try again\n");
            fflush(stdin);
            free(pBuffer);
            goto GetInput;
        }
        pBuffer[count] = (int) (c - 48);
        count++;
    }

    printf("\n");
    printf("\n");
    Error = ComputeCheckSum(pBuffer, count, &Checksum);
    if(Error != 0)
    {
        goto Exit;
    }
    printf("Checksum: %d\n", Checksum);

Exit:
    free(pBuffer);
    return 0;
}
