//
//  hash_table.h
//  hash_table_c
//
//  Created by Nicholas Anderson on 9/20/21.
//

#ifndef hash_table_h
#define hash_table_h
#include <stdlib.h>
#include <stdbool.h>
typedef struct HashTable hashtable;

//needs to be freed from heap
hashtable* new_hashtable(size_t);
//frees hashtable off of heap
void free_hashtable(hashtable *);
bool insert_int_str_ht(hashtable *, int, const char*);
bool insert_int_dbl_ht(hashtable *, int, double);
bool contains_ht(hashtable *, int);
//need print functions for int, float, double...
void print_str_val_ht(hashtable *);
void print_dbl_val_ht(hashtable *);
int key_erase_ht(hashtable *, int);
//returns string on heap and needs to be freed
char* get_str_value_ht(hashtable*, int);
double get_dbl_value_ht(hashtable*, int);
//put new value for key-value pair
bool put_dbl_value_ht(hashtable*, int, double);
#endif /* hash_table_h */
