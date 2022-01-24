 /*
    Nick Anderson
    nickleus27@gmail.com
    github.com/nickleus27
    January 2022
 */

/*  Derived Class for int string pair objects
    Each pair will have an integer hash key
    and a string value to pair to.
*/

#ifndef INT_STRING_H
#define INT_STRING_H
#include "hash_pair.h"

/* Rectangle's attributes... */
typedef struct {
    HashPair super; /* <==inherits HashPair */
    /*attributes added to rect subclass*/
} IntStringPair;

/*inherited virtual functions */
/*
    int HashPair_get_key(HashPair const *)
    HashPair* HashPair_clone(HashPair const *)
        -->Cast to IntStringPair*
    void* HashPair_get_value(HashPair const *) 
        -->Cast to char*
        -->Returns char* on heap Needs to be freed!
*/

/* constructo prototype */
void IntStringPair_ctor(IntStringPair * const me, int thisKey, char* thisValue);
//Object stored on heap and needs to be freed with free_IntStringPair
IntStringPair* new_IntStringPair(int thisKey, const char* thisValue);
void free_IntStringPair(IntStringPair* const me);

//wrapper function for HashPair_get_value, MEMORY NEEDS TO BE FREED
char* IntStringPair_get_value(IntStringPair* const me);
//Wrapper function for HashPair_get_value, memory is managed internally.
int IntStringPair_get_value_byarg(IntStringPair* const me, char* string, int size);
//static const char* get_string_value(IntStringPair * const me);
int IntStringPair_get_string_size(IntStringPair* const me);

  #endif /* INT_STRING_H */