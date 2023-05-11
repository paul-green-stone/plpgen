#include "plpgen.h"

/* ================================ */

#define MAP_SEX(person) ( ((person->flags & MALE) > 0) ? "M" : "F" )

static char* male_names[] = {
    "James", "Robert", "John",
    "Michael", "David", "William",
    "Richard", "Joseph", "Thomas",
    "Charles", "Christopher", "Daniel",
    "Matthew", "Anthony", "Mark",
    "Donald", "Steven", "Paul",
    "Andrew", "Joshua", "Kenneth",
    "Kevin", "Brian", "George",
};

static char* female_names[] = {
    "Mary", "Patricia", "Jennifer",
    "Linda", "Lisa", "Barbara",
    "Susan", "Jessica", "Sarah",
    "Karen", "Betty", "Nancy",
    "Margaret", "Sandra", "Ashley",
    "Kimberly", "Emily", "Donna",
    "Michelle", "Carol", "Amanda",
    "Dorothy", "Melissa", "Deborah",
};

static char* last_names[] = {
    "Adams", "Allen", "Anderson",
    "Armstrong", "Bailey", "Barker",
    "Baker", "Ball", "Clarke",
    "Cole", "Collins", "Cook",
    "Davidson", "Davies", "Dixon",
    "Dawson", "Edwards", "Elliott",
    "Evans", "Fisher", "Fletcher",
    "Ford", "Foster", "Gibson",
    "Graham", "Grant", "Hall",
    "Hamilton", "Harris", "Harvey",
    "Jackson", "James", "Jenkins",
    "Kelly", "Kennedy", "Knight",
    "Lawrence", "Lee", "Lewis",
    "Marshall", "Martin", "Mason",
    "McDonald", "Owen", "Parker",
    "Palmer", "Payne", "Pearson",
    "Reid", "Reynolds", "Richardson",
    "Rogers", "Saunders", "Scott",
    "Shaw", "Simpson", "Spencer",
    "Taylor", "Thomas", "Thompson",
    "Walker", "Walsh", "Ward",
    "Young",
};

struct _person {
    /* Person first name */
    char first_n[PERSON_NAME_SIZE];
    /* Person last name */
    char last_n[PERSON_NAME_SIZE];
    /* Person ID */
    char id[PERSON_ID_SIZE];

    /* Additional information [0000 0000] */
    u_int8_t flags;
};

/* ================================================================ */
/* ================================================================ */
/* ================================================================ */

static void generate_ID(char* buffer) {
    if (buffer != NULL) {
        for (size_t i = 0; i < PERSON_ID_SIZE - 1; i++) {
            if (((i + 1) % 4) == 0) {
                *(buffer + i) = '-';

                continue ;
            }
            else if (i % 2 == 0) {
                /* Get a random capital letter */
                *(buffer + i) = 65 + rand() % 26;

                continue ;
            }

            /* Get a random number */
            *(buffer + i) = 48 + rand() % 10;
        }
    }

    return ;
}

/* ================================================================ */
/* ================================================================ */
/* ================================================================ */

Person_t Person_new(u_int8_t flags) {
    Person_t person = NULL;

    if ((person = (Person_t) malloc(sizeof(struct _person))) != NULL) {
        /* Pick a random firt name */
        strncpy(person->first_n, ((flags & MALE) > 0) ? male_names[rand() % 24] : female_names[rand() % 24], PERSON_NAME_SIZE);
        /* Pick a random last name */
        strncpy(person->last_n, last_names[rand() % 64], PERSON_NAME_SIZE);
        /* Generate a random ID */
        generate_ID(person->id);

        person->flags = flags;
    }
    else {
        warn_with_sys_msg(__func__);
    }

    return person;
}

/* ================================ */

void Person_destroy(Person_t* person) {
    if ((person != NULL) && (*person != NULL)) {
        /* Clear memory */
        memset(*person, 0, sizeof(struct _person));
        /* Dealloce memory */
        free(*person);
    }
    else {
        warn_with_user_msg(__func__, "provided person pointer and/or person is NULL");
    }

    /* Explicitly set to NULL */
    *person = NULL;

    return ;
}

/* ================================ */

void Person_print(const Person_t person) {
    if (person != NULL) {
        printf("Name: %s %s\n", person->first_n, person->last_n);
        printf("ID: %s\n", person->id);
        printf("sex: %s\n", MAP_SEX(person));
    }
    else {
        warn_with_user_msg(__func__, "provided person is NULL");
    }

    return ;
}

/* ================================ */

size_t Person_hashpjw_id(const Person_t person, size_t modulus) {
    /* Hash value for the given data */
    size_t hash_key = 0;
    size_t temp;

    if (person != NULL) {
        for (size_t i = 0; i < PERSON_ID_SIZE - 1; i++) {
            /* Do not compute dishes */
            if (((i + 1) % 4) == 0) {
                continue ;
            }

            hash_key = (hash_key << 4) + *(person->id + i);

            if ((temp = (hash_key & 0xF0000000))) {
                hash_key = hash_key ^ (temp >> 24);
                hash_key = hash_key ^ temp;
            }
        }
    }
    else {
        warn_with_user_msg(__func__, "provided person is NULL");
    }

    return hash_key % modulus;
}

/* ================================ */

char* Person_get_Fname(const Person_t person) {
    return ((person != NULL) ? person->first_n : NULL);
}

/* ================================ */

char* Person_get_Lname(const Person_t person) {
    return ((person != NULL) ? person->last_n : NULL);
}

/* ================================ */

extern char* Person_get_ID(const Person_t person) {
    return ((person != NULL) ? person->id : NULL);
}

/* ================================ */

void Person_regen_ID(Person_t person) {
    if (person != NULL) {
        generate_ID(person->id);
    }
    else {
        warn_with_user_msg(__func__, "provided person is NULL");
    }

    return ;
}

/* ================================ */

int Person_match(const Person_t person_1, const Person_t person_2) {
    int result = -1;

    if ((person_1 != NULL) && (person_2 != NULL)) {
        return (result = strcmp(person_1->id, person_2->id));
    }
    else {
        warn_with_user_msg(__func__, "provided person is NULL");
    }

    return result;
}