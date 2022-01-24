//
//  hash_pair_vector.h
//  
//
//  Created by Nicholas Anderson on 9/12/21.
//

#ifndef HASH_PAIR_VECTOR_H
#define HASH_PAIR_VECTOR_H

#define INCREMENT 1

#include <stdbool.h>
#include <stdlib.h>
#include "hash_pair.h"

typedef struct HashPairVector hash_pair_vector;

hash_pair_vector* new_hashPair_v(size_t);

bool hashPair_v_push_b( hash_pair_vector *, HashPair* );

//void intv_finalizeMemory(int_string_vector *);

void free_hashPair_v(hash_pair_vector *);

//HASHPAIR_V SIZE
int hashPair_v_size(hash_pair_vector *);

//returns a clone of int_string
//this is memory allocated on the heap and needs to be freed
//HASHPAIR_V_GET
HashPair* hashPair_v_get(hash_pair_vector *, int);

//HASHPAIR_V POP
bool hashPair_v_pop(hash_pair_vector *);

//HASHPAIR_V CLEAR
void hashPair_v_clear(hash_pair_vector *);

//HASHPAIR_V_ERASE
bool hashPair_v_erase_index(hash_pair_vector *, int);

//HASHPAIR GET ID
int hashPair_v_get_key(hash_pair_vector *, int);

//HASHPAIR_GET_STRING_VALUE
//SHOULD THIS BE DONE IN THE HASHTABLE CLASS??
//returns string on heap and needs to be freed
char* hashPair_v_get_str_val(hash_pair_vector *, int);

//put function to put new value to key-value pair
bool hashPair_v_put_dbl_val(hash_pair_vector*, int, double);

#endif /* HASH_PAIR_VECTOR_H */
