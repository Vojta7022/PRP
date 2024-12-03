#include "book_serializer.h"
#include <stdio.h>

void serialize_abstract(FILE *f, char abstract[])
{
    size_t abstract_length = strlen(abstract);
    fwrite(abstract_length, sizeof(size_t), 1, f);
    fwrite(abstract, abstract_length, 1, f);
}

void serialize_year(FILE *f, int year)
{
    fwrite(&year, sizeof(int), 1, f);
}

void serialize_title(FILE *f, char title[MAX_NAME_SIZE])
{
    fwrite(title, MAX_NAME_SIZE, 1, f);
}

void serialize_book(FILE* f, Book* book)
{
    serialize_year(f, book->year);
    serialize_title(f, book->title);
    serialize_abstract(f, book->abstract);
}
