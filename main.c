#include "plpgen.h"

int main(int argc, char** argv) {
    /* Random number generator initialization */
    time_t t;

    srand((unsigned) time(&t));


    Person_t person_m = Person_new(MALE);
    Person_t person_f = Person_new(0);

    Person_print(person_m);
    Person_print(person_f);

    printf("Old ID hash value: %zu\n", Person_hashpjw_id(person_m, 1999));
    printf("%zu\n", Person_hashpjw_id(person_f, 1999));

    Person_regen_ID(person_m);
    printf("New ID hash value: %zu\n", Person_hashpjw_id(person_m, 1999));
    Person_print(person_m);

    printf("First name: %s\n", Person_get_Fname(person_m));
    printf("Last name: %s\n", Person_get_Lname(person_m));
    printf("ID: %s\n", Person_get_ID(person_m));

    Person_destroy(&person_m);
    Person_destroy(&person_f);

    return EXIT_SUCCESS;
}