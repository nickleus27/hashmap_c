 /*
    Nick Anderson
    nickleus27@gmail.com
    github.com/nickleus27
    January 2022
 */

/*  Derived Class for int double pair objects
    Each pair will have an integer hash key
    and a double value to pair to.
*/

#ifndef INT_DOUBLE_H
#define INT_DOUBLE_H
#include "hash_pair.h"

/* Rectangle's attributes... */
typedef struct {
    HashPair super; /* <==inherits HashPair */
    /*attributes added to rect subclass*/
    double dValue;
} IntDoublePair;

/*inherited virtual functions */
/*
    int HashPair_get_key(HashPair const *)
    HashPair* HashPair_clone(HashPair const *)
        -->Cast to IntDoulbePair*
    void* HashPair_get_value(HashPair const *) 
        -->Cast to *(double*) for double value
        -->Currently privacy leak
*/

/* constructo prototype */
void IntDoublePair_ctor(IntDoublePair * const me, int thisKey, double thisValue);
//Object stored on heap and needs to be freed with free_IntStringPair
IntDoublePair* new_IntDoublePair(int thisKey, double thisValue);
void free_IntDoublePair(IntDoublePair* const me);

/*
//wrapper function for HashPair_get_value, MEMORY NEEDS TO BE FREED
char* IntStringPair_get_value(IntStringPair* const me);
//Wrapper function for HashPair_get_value, memory is managed internally.
int IntStringPair_get_value_byarg(IntStringPair* const me, char* string, int size);
//static const char* get_string_value(IntStringPair * const me);
int IntStringPair_get_string_size(IntStringPair* const me);
*/

  #endif /* INT_DOUBLE_H */