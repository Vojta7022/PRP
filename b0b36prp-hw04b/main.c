#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_DIGITS 100
#define BASE 1000000000   // 10^9
#define MAX_PRIME 1000000 // 10^6

#define ERROR_INPUT 100

typedef struct BigInt
{
    int digits[MAX_DIGITS / 9];
    int length;
} BigInt;

// Function prototypes
void bigint_from_string(BigInt *num, const char *str);
int bigint_is_zero(const BigInt *num);
int bigint_is_one(const BigInt *num);
int bigint_is_negative(const BigInt *num);
int bigint_divide_small(BigInt *a, int divisor);
void prime_factorization(BigInt num);

int main(int argc, char *argv[])
{
    while (1)
    {
        char buffer[MAX_DIGITS + 1];
        if (!fgets(buffer, sizeof(buffer), stdin))
        {
            fprintf(stderr, "Error: Chybny vstup!\n");
            return ERROR_INPUT;
        }

        buffer[strcspn(buffer, "\n")] = '\0';

        for (int i = 0; i < strlen(buffer); i++)
        {
            if (buffer[i] < '0' || buffer[i] > '9')
            {
                fprintf(stderr, "Error: Chybny vstup!\n");
                return ERROR_INPUT;
            }
        }

        BigInt num;
        bigint_from_string(&num, buffer);
        if (bigint_is_negative(&num))
        {
            fprintf(stderr, "Error: Chybny vstup!\n");
            return ERROR_INPUT;
        }
        else if (bigint_is_zero(&num))
        {
            break;
        }

        prime_factorization(num);
    }
    
    return EXIT_SUCCESS;
}

/**
 * Converts a String to a BigInt
 * @param num BigInt to store the result
 * @param str String to convert
 */
void bigint_from_string(BigInt *num, const char *str)
{
    int length = strlen(str);
    num->length = 0;
    for (int i = length; i > 0; i -= 9)
    {
        int start = (i - 9 > 0) ? i - 9 : 0;
        char buffer[10];
        strncpy(buffer, str + start, i - start);
        buffer[i - start] = '\0';
        num->digits[num->length++] = atoi(buffer);
    }
}

/**
 * Checks if a BigInt is zero
 * @param num BigInt to check
 * @return 1 if the BigInt is zero, 0 otherwise
 */
int bigint_is_zero(const BigInt *num)
{
    return num->length == 1 && num->digits[0] == 0;
}

/**
 * Checks if a BigInt is one
 * @param num BigInt to check
 * @return 1 if the BigInt is one, 0 otherwise
 */
int bigint_is_one(const BigInt *num)
{
    return num->length == 1 && num->digits[0] == 1;
}

/**
 * Checks if a BigInt is negative
 * @param num BigInt to check
 * @return 1 if the BigInt is negative, 0 otherwise
 */
int bigint_is_negative(const BigInt *num)
{
    return num->length == 1 && num->digits[0] < 0;
}

/**
 * Divides a BigInt by a small number
 * @param a BigInt to divide
 * @param divisor Number to divide by
 * @return Remainder of the division
 */
int bigint_divide_small(BigInt *a, int divisor)
{
    long long remainder = 0;
    for (int i = a->length - 1; i >= 0; i--)
    {
        long long current = a->digits[i] + remainder * BASE;
        a->digits[i] = current / divisor;
        remainder = current % divisor;
    }
    while (a->length > 1 && a->digits[a->length - 1] == 0)
    {
        a->length--;
    }
    return (int)remainder;
}

/**
 * Prints a BigInt
 * @param num BigInt to print
 */
void bigint_print(const BigInt *num)
{
    printf("%d", num->digits[num->length - 1]);
    for (int i = num->length - 2; i >= 0; i--)
    {
        printf("%09d", num->digits[i]);
    }
}

/**
 * Factorizes a number into prime factors
 * @param num Number to factorize
 */
void prime_factorization(BigInt num)
{
    printf("Prvociselny rozklad cisla ");
    bigint_print(&num);
    printf(" je:\n");

    if (bigint_is_one(&num))
    {
        printf("1\n");
        return;
    }

    for (int i = 2; i < MAX_PRIME; i++)
    {
        int exponent = 0;
        BigInt num_copy = num;
        int result = bigint_divide_small(&num_copy, i);

        while (result == 0)
        {
            exponent++;
            num = num_copy;
            result = bigint_divide_small(&num_copy, i);
        }

        if (exponent > 0)
        {
            if (exponent == 1)
            {
                printf("%d", i);
            }
            else
            {
                printf("%d^%d", i, exponent);
            }
            if (!bigint_is_one(&num))
            {
                printf(" x ");
            }
        }
        if (bigint_is_one(&num))
        {
            break;
        }
    }

    if (!bigint_is_one(&num))
    {
        printf("%d^1\n", num.digits[0]);
    }
    printf("\n");
}
