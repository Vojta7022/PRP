#include "calc.h"

void print_number(number_t *num) 
{
    size_t start = 0;
    for (start = 0; start < NUMBER_LENGTH; start++) 
    {
        if (num->number[start]) 
        {
            break;
        }
    }
    for (size_t i = start; i < NUMBER_LENGTH; i++) 
    {
        printf("%c", num->number[i] ? '1' : '0');
    }
    printf("\n");
}

bool is_equal(number_t *num1, number_t *num2) 
{
    for (size_t i = 0; i < NUMBER_LENGTH; i++) 
    {
        if (num1->number[i] != num2->number[i]) 
        {
            return false;
        }
    }
    return true;
}

void sum(number_t *num1, number_t *num2)
{
    bool carry = false;
    for (int i = NUMBER_LENGTH - 1; i >= 0; i--)
    {
        if (carry)
        {
            if (num1->number[i] & num2->number[i] )
            {
                num1->number[i] = true;
            }
            else if(num1->number[i] | num2->number[i])
            {
                num1->number[i] = false;
            }
            else
            {
                carry = false;
                num1->number[i] = true;
            }
        }
        else
        {
            if (num1->number[i] & num2->number[i] )
            {
                num1->number[i] = false;
                carry = true;
            }
            else if(num1->number[i] | num2->number[i])
            {
                num1->number[i] = true;
            }
            else
            {
                num1->number[i] = false;
            }
        }
        
    }
}
