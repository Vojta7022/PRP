#include <stdio.h>

// struct rozmery {
//     int sirka;
//     int vyska;
// };
// typedef struct rozmery rozmery_t;

typedef struct rozmery
{
    int sirka;
    int vyska;
    char vypln;
} rozmery_t;

// void print_rectangle(struct rozmery parametr)
void print_rectangle(rozmery_t parametr)
{
    for (size_t i = 0; i < parametr.vyska; i++)
    {
        for (size_t j = 0; j < paramet.sirka; j++)
        {
            printf("%c", parametr.vypln);
        }
        printf("\n");
    }
    
}

int main(int argc, char const *argv[])
{
    rozmery_t param = {.sirka = 4, .vyska = 3, .vypln = "O"};

    rozmery_t* p_param = &param;

    printf("rozmery jsou sirka %d a vyska %d", (*p_param).sirka, p_param -> vyska);
    print_rectangle(param);
    return 0;
}

