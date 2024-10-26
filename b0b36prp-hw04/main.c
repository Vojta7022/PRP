#include <stdio.h>
#include <stdlib.h>

#define ERROR_INPUT 100

#define MAX_SIEVE 1000000
#define MAX_PRIMES 79000

/* Function prototypes */
void eratosthenes_sieve();
void mark_multiples(int *is_prime, int prime);
void factorize(long long int num);
void print_prime_factor(int prime, int exponent);

/* Array for storing primes */
int primes[MAX_PRIMES];
int prime_count = 0;

int main(int argc, char *argv[])
{
    eratosthenes_sieve();

    long long int num;
    while (scanf("%lld", &num) == 1 && num != 0 && num > 0)
    {
        factorize(num);
    }

    if (num != 0)
    {
        fprintf(stderr, "Error: Chybny vstup!\n");
        return ERROR_INPUT;
    }

    return EXIT_SUCCESS;
}

/**
 * Eratosthenes sieve for finding primes.
 */
void eratosthenes_sieve()
{
    int is_prime[MAX_SIEVE + 1] = {0}; // 0 if prime, 1 if not prime

    for (int i = 2; i <= MAX_SIEVE; i++)
    {
        if (is_prime[i] == 0)
        {
            primes[prime_count++] = i;
            mark_multiples(is_prime, i);
        }
    }
}

/**
 * Marks multiples of a given prime as non-prime in the sieve.
 */
void mark_multiples(int *is_prime, int prime)
{
    for (int j = prime * 2; j <= MAX_SIEVE; j += prime)
    {
        is_prime[j] = 1;
    }
}

/**
 * Factorizes the number by iterating over known primes.
 * @var num - the number to factorize
 */
void factorize(long long int num)
{
    printf("Prvociselny rozklad cisla %lld je:\n", num);

    if (num == 1)
    {
        printf("1\n");
        return;
    }

    int count = 0;

    for (int i = 0; i < prime_count && primes[i] <= num; i++)
    {
        int exponent = 0;

        while (num % primes[i] == 0)
        {
            num /= primes[i];
            exponent++;
        }

        if (exponent > 0)
        {
            if (count > 0)
            {
                printf(" x ");
            }
            print_prime_factor(primes[i], exponent);
            count++;
        }
    }

    printf("\n");
}

/**
 * Prints a prime factor with its exponent.
 * @var prime - the prime factor
 * @var exponent - the exponent of the prime factor
 */
void print_prime_factor(int prime, int exponent)
{
    if (exponent == 1)
    {
        printf("%d", prime);
    }
    else
    {
        printf("%d^%d", prime, exponent);
    }
}
