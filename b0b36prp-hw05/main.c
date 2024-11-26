#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define INIT_SIZE 5
#define ALPHABET_LENGTH 52
#define UPPERCASE_OFFSET 26
#define ERROR_INPUT 100
#define ERROR_LENGTH 101

// Function prototypes
int read_texts(char **shifted_text, char **original_text);
int read_text(char **text);
void shift_text(const char *src, char *dst, int offset);
char rotate_character(char ch, int offset);
int count_matching_letters(const char *str1, const char *str2);
int levenshtein_distance(const char *str1, const char *str2);
char *find_best_shift(const char *shifted, const char *original);
char *find_min_levenshtein(const char *shifted, const char *original);

int main(int argc, char **argv)
{
    // Check if the optional parameter is present
    int optional = argc == 2 && strcmp(argv[1], "-prp-optional") == 0 ? 1 : 0;

    char *shifted_text = NULL;
    char *original_text = NULL;

    int ret = read_texts(&shifted_text, &original_text);
    if (ret == ERROR_INPUT)
    {
        fprintf(stderr, "Error: Chybny vstup!\n");
        return ERROR_INPUT;
    }
    if (optional != 1 && ret == ERROR_LENGTH)
    {
        fprintf(stderr, "Error: Chybna delka vstupu!\n");
        free(shifted_text);
        free(original_text);
        return ERROR_LENGTH;
    }

    char *best_match = optional == 1
                           ? find_min_levenshtein(shifted_text, original_text)
                           : find_best_shift(shifted_text, original_text);

    if (best_match)
    {
        printf("%s\n", best_match);
        free(best_match);
    }

    free(shifted_text);
    free(original_text);

    return EXIT_SUCCESS;
}

/**
 * Reads two texts from the standard input.
 * @param shifted_text The shifted text.
 * @param original_text The original text.
 * @return The result of the operation.
 */
int read_texts(char **shifted_text, char **original_text)
{
    if (read_text(shifted_text) != EXIT_SUCCESS ||
        read_text(original_text) != EXIT_SUCCESS)
    {
        return ERROR_INPUT;
    }

    if (strlen(*shifted_text) != strlen(*original_text))
    {
        return ERROR_LENGTH;
    }

    return EXIT_SUCCESS;
}

/**
 * Reads a text from the standard input.
 * @param text The text to read.
 * @return The result of the operation.
 */
int read_text(char **text)
{
    int size = INIT_SIZE;
    int length = 0;
    int c;

    *text = (char *)malloc((size + 1) * sizeof(char));
    if (!*text)
    {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    while ((c = getchar()) != '\n' && c != EOF)
    {
        // Check if the input is a letter
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
        {
            free(*text);
            return ERROR_INPUT;
        }

        if (length >= size)
        {
            size *= 2;
            char *temp = (char *)realloc(*text, (size + 1) * sizeof(char));
            if (!temp)
            {
                free(*text);
                return EXIT_FAILURE;
            }
            *text = temp;
        }

        (*text)[length++] = c;
    }
    (*text)[length] = '\0';

    return EXIT_SUCCESS;
}

/**
 * Shifts a text by a given offset.
 * @param src The source text.
 * @param dst The destination text.
 * @param offset The offset to shift by.
 */
void shift_text(const char *src, char *dst, int offset)
{
    size_t len = strlen(src);
    for (size_t i = 0; i < len; i++)
    {
        dst[i] = rotate_character(src[i], offset);
    }
    dst[len] = '\0';
}

/**
 * Rotates a character by a given offset.
 * @param ch The character to rotate.
 * @param offset The offset to rotate by.
 * @return The rotated character.
 */
char rotate_character(char ch, int offset)
{
    if (ch >= 'A' && ch <= 'Z')
    {
        int pos = (ch - 'A' + offset) % ALPHABET_LENGTH;
        return (pos < UPPERCASE_OFFSET) ? 'A' + pos : 'a' + (pos - UPPERCASE_OFFSET);
    }
    else
    {
        int pos = (ch - 'a' + UPPERCASE_OFFSET + offset) % ALPHABET_LENGTH;
        return (pos < UPPERCASE_OFFSET) ? 'A' + pos : 'a' + (pos - UPPERCASE_OFFSET);
    }
}

/**
 * Counts the number of matching letters in two strings.
 * @param str1 The first string.
 * @param str2 The second string.
 * @return The number of matching letters.
 */
int count_matching_letters(const char *str1, const char *str2)
{
    int matches = 0;
    for (size_t i = 0; str1[i] != '\0'; i++)
    {
        if (str1[i] == str2[i])
        {
            matches++;
        }
    }
    return matches;
}

/**
 * Computes the Levenshtein distance using Wagner-Fischer algorithm.
 * @param str1 The first string.
 * @param str2 The second string.
 * @return The Levenshtein distance.
 */
int levenshtein_distance(const char *str1, const char *str2)
{
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    int **matrix = (int **)malloc((len1 + 1) * sizeof(int *));
    for (size_t i = 0; i <= len1; i++)
    {
        matrix[i] = (int *)malloc((len2 + 1) * sizeof(int));
    }

    for (size_t i = 0; i <= len1; i++)
    {
        matrix[i][0] = i;
    }

    for (size_t i = 0; i <= len2; i++)
    {
        matrix[0][i] = i;
    }

    for (size_t i = 1; i <= len1; i++)
    {
        for (size_t j = 1; j <= len2; j++)
        {
            int cost = (str1[i - 1] == str2[j - 1]) ? 0 : 1;

            int min = (matrix[i - 1][j] + 1 < matrix[i][j - 1] + 1) ? matrix[i - 1][j] + 1 : matrix[i][j - 1] + 1;
            matrix[i][j] = (min < matrix[i - 1][j - 1] + cost) ? min : matrix[i - 1][j - 1] + cost;
        }
    }

    int result = matrix[len1][len2];

    for (size_t i = 0; i <= len1; i++)
    {
        free(matrix[i]);
    }
    free(matrix);

    return result;
}

/**
 * Finds the best match using matching letters.
 * @param shifted The shifted text.
 * @param original The original text.
 * @return The best match.
 */
char *find_best_shift(const char *shifted, const char *original)
{
    size_t len = strlen(shifted);
    char *best_match = (char *)malloc(len + 1);
    char *temp_text = (char *)malloc(len + 1);

    if (!best_match || !temp_text)
        return NULL;

    int max_matches = 0;
    for (int i = 0; i < ALPHABET_LENGTH; i++)
    {
        shift_text(shifted, temp_text, i);
        int matches = count_matching_letters(original, temp_text);
        if (matches > max_matches)
        {
            strcpy(best_match, temp_text);
            max_matches = matches;
        }
    }

    free(temp_text);
    return best_match;
}

/**
 * Finds the best match using Levenshtein distance.
 * @param shifted The shifted text.
 * @param original The original text.
 * @return The best match.
 */
char *find_min_levenshtein(const char *shifted, const char *original)
{
    size_t len = strlen(shifted);
    char *best_match = (char *)malloc(len + 1);
    char *temp_text = (char *)malloc(len + 1);

    if (!best_match || !temp_text)
        return NULL;

    int min_distance = INT_MAX;
    for (int i = 0; i < ALPHABET_LENGTH; i++)
    {
        shift_text(shifted, temp_text, i);
        int distance = levenshtein_distance(original, temp_text);
        if (distance < min_distance)
        {
            strcpy(best_match, temp_text);
            min_distance = distance;
        }
    }

    free(temp_text);
    return best_match;
}
