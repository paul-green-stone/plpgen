# plpgen

## Content

[About](#about)

[API](#api)

[Flags](#flags)

[Examples](#examples)

[Resources](#resources)

## About

**plpgen** is a module for generating random persons. It suits well for testing abstract data types, such as *[hash tables](https://github.com/paul-green-stone/hash-table)*, *[sets](https://github.com/paul-green-stone/set-ADT)*, etc. Defined as a pointer to an incomplete type, you can be sure that a user won't change the structs by direct accessing its fields. The module also provides a default function for *hashing* a person by its ID, which fits with the idea of using the module for experimenting with hash tables.

## API

### plpgen_init

```C
void plpgen_init(void);
```

The `plpgen_init` operation initializes the module, i.e., it initializes a random number generator.

**Return value**: none

### Person_new

```C
Person_t Person_new(u_int8_t flags);
```

The `Person_new` operation allocates a memory for a new instance of a person type and also randomizes it. The `flags` argument provides additional information for generating a person. In the current implementation, it supports just one flag, `MALE`, which causes the generator to choose a masculine name.

| Type | Description |
| ---- | ----------- |
| `u_int8_t flags` | The `flags` argument provides additional information for a person generator |

**Return value**: a new instance of a person type

### Person_destroy

```C
void Person_destroy(Person_t* person);
```

The `Person_destroy` operation clears a memory region occupied by `*person`, and also deallocates it, i.e., making it available for allocation again. Upon completion, `*person` is set to `NULL`.

| Type | Description |
| ---- | ----------- |
| `Person_t* person` | A pointer to a person type to destroy |

**Return value**: none

### Person_display

```C
void Person_print(const Person_t person);
```

The `Person_print` operation outputs information about a person.

| Type | Description |
| ---- | ----------- |
| `const Person_t* person` | A person to output information about |

**Return value**: none

### Person_hashpjw_id

```C
size_t Person_hashpjw_id(const Person_t person, size_t modulus);
```

The `Person_hashpjw_id` operation computes a *hash* value of a person based on its ID, which is a string, field. As its name implies, the function uses a *PJW hash function* created by Peter J. Weinberger.

| Type | Description |
| ---- | ----------- |
| `const Person_t* person` | A person of which to compute a hash value |
| `size_t modulus` | The `modulus` argument is a value used as a modulus in divison operation when computing a hash value. When you work with hash tables, the argument is the size of a hash table |

**Return value**: a hash key of a given data

### Person_match

```C
int Person_match(const Person_t person_1, const Person_t person_2)
```

The `Person_match` operation provides a way to compare two persons specified as `person_1` and `person_2`. The function compares the persons IDs fields (which is obvious, because two persons may have the same names, but never IDs). Based on a library `strcmp` function, `Person_match` returns *0* if both IDs are equal.

**Return value**: *0* if two persons IDs are the same, *-1*  if the are different

### Person_regen_ID

```C
void Person_regen_ID(Person_t person);
```

The `Person_regen_ID` generates a new random ID of the given person if the latter is not `NULL`.

### Person_get_Fname

```C
char* Person_get_Fname(const Person_t person);
```

The `Person_get_Fname` operation returns a first name of a given person if the latter is not `NULL`.

### Person_get_Lname

```C
char* Person_get_Lname(const Person_t person);
```

The `Person_get_Lname` operation returns a last name of a given person if the latter is not `NULL`.

### Person_get_ID

```C
char* Person_get_ID(const Person_t person);
```

The `Person_get_ID` operation returns a ID of a given person if the latter is not `NULL`.

## Examples

Before you start working with the module, you need to initialize a random number generator, you can do so as follows:

```C
/* Somewhere in the main function before calling plpgen functions */
plpgen_init();
```

you don't need to include `<time.t>`, it's included in the `"plpgen.h"` header file.

To generate a new person, simply call the `Person_new` function:

```C
/* to create a male person */
Person_t person_t = Person_new(MALE);

/* to create a female person */
Person_t person_f = Person_new(0);

/* ... */

/* Destroy objects after you've finished working with them */
Person_destroy(&person_m);
Person_destroy(&person_f);
```

## Flags

| Flag | Description |
| ---- | ----------- |
| `MALE` | Causes the generator to pick a masculine name. To create a female person specify *0* |

## Resources

[PJW hash function](https://en.wikipedia.org/wiki/PJW_hash_function)
