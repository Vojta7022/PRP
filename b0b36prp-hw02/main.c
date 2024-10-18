#include <stdio.h>
#include <stdlib.h>

#define ERROR_INTERVAL 100
#define MIN -10000
#define MAX 10000

/* Function prototypes */
void calculateCounts(int num, int *count, int *countPos, int *countNeg,
                     int *countEven, int *countOdd, int *totalSum, int *min,
                     int *max);
void printStatistics(int num, int count, int countPos, int countNeg,
                     int countEven, int countOdd, int totalSum, int min,
                     int max);

int main(int argc, char *argv[])
{
    int num; // number read from input
    int count = 0, countPos = 0, countNeg = 0;
    int countEven = 0, countOdd = 0;
    int totalSum = 0, min = MAX + 1, max = MIN - 1;

    while (scanf("%d", &num) == 1)
    {
        if (!(num >= MIN && num <= MAX))
        {
            printf("\nError: Vstup je mimo interval!\n");
            return ERROR_INTERVAL;
        }

        if (count > 0)
            printf(", ");
        printf("%d", num);

        calculateCounts(num, &count, &countPos, &countNeg, &countEven,
                        &countOdd, &totalSum, &min, &max);
    }

    printStatistics(num, count, countPos, countNeg, countEven, countOdd,
                    totalSum, min, max);

    return EXIT_SUCCESS;
}

/**
 * Calculates the counts of numbers.
 * @var num - the number to calculate
 * @var count - the count of numbers
 * @var countPos - the count of positive numbers
 * @var countNeg - the count of negative numbers
 * @var countEven - the count of even numbers
 * @var countOdd - the count of odd numbers
 * @var totalSum - the total sum of numbers
 * @var min - the minimum number
 * @var max - the maximum number
 */
void calculateCounts(int num, int *count, int *countPos, int *countNeg,
                     int *countEven, int *countOdd, int *totalSum, int *min,
                     int *max)
{
    (*count)++;
    if (num > 0)
        (*countPos)++;
    if (num < 0)
        (*countNeg)++;

    num % 2 == 0 ? (*countEven)++ : (*countOdd)++;

    *totalSum += num;
    if (num < *min)
        *min = num;
    if (num > *max)
        *max = num;
}

/**
 * Prints the statistics.
 * @var num - the number to print
 * @var count - the count of numbers
 * @var countPos - the count of positive numbers
 * @var countNeg - the count of negative numbers
 * @var countEven - the count of even numbers
 * @var countOdd - the count of odd numbers
 * @var totalSum - the total sum of numbers
 * @var min - the minimum number
 * @var max - the maximum number
 */
void printStatistics(int num, int count, int countPos, int countNeg,
                     int countEven, int countOdd, int totalSum, int min,
                     int max)
{
    printf("\nPocet cisel: %d\n", count);
    printf("Pocet kladnych: %d\n", countPos);
    printf("Pocet zapornych: %d\n", countNeg);

    double positivePercentage = (count > 0) ? (countPos / (double)count) * 100
                                            : 0;
    double negativePercentage = (count > 0) ? (countNeg / (double)count) * 100
                                            : 0;
    printf("Procento kladnych: %.2f\n", positivePercentage);
    printf("Procento zapornych: %.2f\n", negativePercentage);

    printf("Pocet sudych: %d\n", countEven);
    printf("Pocet lichych: %d\n", countOdd);

    double evenPercentage = (count > 0) ? (countEven / (double)count) * 100 : 0;
    double oddPercentage = (count > 0) ? (countOdd / (double)count) * 100 : 0;
    printf("Procento sudych: %.2f\n", evenPercentage);
    printf("Procento lichych: %.2f\n", oddPercentage);

    double average = count > 0 ? totalSum / (double)count : 0;
    printf("Prumer: %.2f\n", average);
    printf("Maximum: %d\n", max);
    printf("Minimum: %d\n", min);
}
