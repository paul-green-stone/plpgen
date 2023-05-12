#ifndef PLPGEN_H
#define PLPGEN_H

/* ================================================================ */

#include <stdint.h>
#include <time.h>

#include "guard/guard.h"

/* First/Last name size */
#define PERSON_NAME_SIZE 32
/* Person ID size */
#define PERSON_ID_SIZE 16

#define MALE (1 << 0) /* 1 */

typedef struct _person* Person_t;

/* Initialize a plpgen module */
extern void plpgen_init(void);

/* Allocate a new instance of a Person data type */
extern Person_t Person_new(u_int8_t flags);

/* Destroy a person */
extern void Person_destroy(Person_t* person);

/* Display information about a person */
extern void Person_print(const Person_t person);

/* Compute a hash value based on a person's ID */
extern size_t Person_hashpjw_id(const Person_t person, size_t modulus);

/* Get a person first name */
extern char* Person_get_Fname(const Person_t person);

/* Get a person last name */
extern char* Person_get_Lname(const Person_t person);

/* Get a person ID */
extern char* Person_get_ID(const Person_t person);

/* Generate a new ID */
extern void Person_regen_ID(Person_t person);

/* Compares two persons IDs */
extern int Person_match(const Person_t person_1, const Person_t person_2);

/* ================================================================ */

#endif