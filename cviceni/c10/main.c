#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book_serializer.c"
#include "book.h"
 
BookList* get_example_list();
void test_list_contents();
int main() {
    test_list_contents();
    return 0;
}
 
BookList* get_example_list() {
    BookList* pl = create_book_list();
    Book* p1 = create_book(2005, "Programming in C", "Programming in C will teach you how to write programs in the C programming language.");
    Book* p2 = create_book(161, "Meditations", NULL);
    Book* p3 = create_book(-1500, "Poor Man of Nipur", "");
    add_book(pl, p1);
    add_book(pl, p2);
    add_book(pl, p3);
    FILE *f = fopen("myfile", "wb");
    if (!f)
    {
        printf("Error: Cannot open the file\n");
        return NULL;
    }
    serialize_book(f, p1);

    return pl;
}
 
void test_list_contents() {
    BookList* pl = get_example_list();
    print_book_list(pl);
    destroy_book_list(pl);
}
