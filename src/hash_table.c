//
//  hash_table.c
//  hash_table_c
//
//  Created by Nicholas Anderson on 9/20/21.
//

#include "hash_table.h"
#include "hash_pair_vector.h"
#include <stdio.h>
#include "int_string.h"
#include "int_double.h"

struct HashTable{
    hash_pair_vector **ptr;
    size_t cap;
    size_t size;
};

struct HashPairVector
{
    size_t space_left;
    size_t size;
    HashPair **ptr;
};

hashtable* new_hashtable(size_t init_size)
{
    hashtable* table = (hashtable*)malloc(sizeof(struct HashTable));
    table->ptr = (hash_pair_vector**)malloc(init_size * sizeof(hash_pair_vector*));
    table->cap = init_size;
    table->size = 0;
    if(!table->ptr)
    {
        printf("Hashtable failed to malloc. Program Exit.");
        exit(EXIT_FAILURE);
    }
    
    for(size_t i = 0; i < table->cap; i++)
    {
        hash_pair_vector* v = new_hashPair_v(2);
        table->ptr[i] = v;
    }
    return table;
}

void
free_hashtable(hashtable *table)
{
    for(size_t i = 0; i < table->cap; i++)
        free_hashPair_v(table->ptr[i]);
    free(table->ptr);
    free(table);
}

size_t
hash(hashtable *table, int key){
    const double c = 0.618033;
    double kc = key * c;
    return (size_t)((size_t)table->cap * (kc-(size_t)kc));
}

bool
resize(hashtable * table){
    //increase hashtable capacity by 2x
    size_t maxLength = table->cap<<INCREMENT;
    if (maxLength == 0)
        maxLength = 1;
    HashPair* tempArr [table->size];
    int tempIndx = 0;
    //pull out all values into a temp array
    for(size_t i = 0; i<table->cap; i++){
        for(int j=0; j<table->ptr[i]->size; j++)
        {
            tempArr[tempIndx++] = hashPair_v_get(table->ptr[i], j);
        }
        free_hashPair_v(table->ptr[i]);
    }
    //realloc new memomry size on heap
    hash_pair_vector** ptrtemp = (hash_pair_vector**)realloc(table->ptr, maxLength * sizeof(hash_pair_vector*) );
    //table->ptr = (int_vector**)realloc(table->ptr, maxLength * sizeof(int_vector) );
    table->cap = maxLength; // <---set hashtable capacity to new increased size
    if(!ptrtemp)
    {
        printf("Hashtable failed to malloc. Program Exit.");
        return false;
    }
    
    table->ptr = ptrtemp;
    
    //re initialize vectors at each index of table
    for(size_t i = 0; i < table->cap; i++)
    {
        hash_pair_vector* v = new_hashPair_v(2);
        table->ptr[i] = v;
    }
    //re insert
    for(int i = 0; i<table->size; i++)
    {
        hashPair_v_push_b(table->ptr[hash(table, HashPair_get_key((const HashPair*)tempArr[i]))], tempArr[i]);
    }
    return true;
}

bool
insert_int_str_ht(hashtable *table, int key, const char* value)
{
    IntStringPair* d = new_IntStringPair(key, value);
    if(table->size == table->cap)
        if (!resize(table))
            return false;
    if (hashPair_v_push_b(table->ptr[hash(table, HashPair_get_key((const HashPair*)d))], (HashPair *)d))
    {
        table->size++;
        return true;
    }
    return false;
}

bool insert_int_dbl_ht(hashtable * table, int key, double val)
{
    IntDoublePair* d = new_IntDoublePair(key, val);
    if(table->size == table->cap)
        if (!resize(table))
            return false;
    if (hashPair_v_push_b(table->ptr[hash(table, HashPair_get_key((const HashPair*)d))], (HashPair *)d))
    {
        table->size++;
        return true;
    }
    return false;
}


bool
contains_ht(hashtable *table, int key)
{
    bool found = false;
    hash_pair_vector * temp = table->ptr[hash(table, key)];
    for(int i = 0; i < temp->size; i++)
        if(key == hashPair_v_get_key(temp, i))
            return true;
    return false;
}

void 
print_str_val_ht(hashtable *table)
{
    char* string;
    HashPair* copy;
    for(size_t i = 0; i<table->cap; i++)
        for(int j=0; j<table->ptr[i]->size; j++)
        {
            copy = hashPair_v_get(table->ptr[i], j);
            string = HashPair_get_value(copy);
            printf("%s\n", string);
            free(string);
            free_HashPair(copy);
        }
}

void
print_dbl_val_ht(hashtable *table)
{
    double* dbl;
    HashPair* copy;
    for(size_t i = 0; i<table->cap; i++)
        for(int j=0; j<table->ptr[i]->size; j++)
        {
            copy = hashPair_v_get(table->ptr[i], j);
            dbl = (double*)HashPair_get_value(copy);
            printf("%f\n", *dbl);
            //free(dbl);
            free_HashPair(copy);
        }
}

int
key_erase_ht(hashtable * table, int key)
{
    int found = 0;
    hash_pair_vector * temp = table->ptr[hash(table, key)];
    for(int i = 0; i < temp->size && !found; i++)
    {
        HashPair* copy =  hashPair_v_get(temp, i);
        if(key == HashPair_get_key(copy))
        {
            found = key;
            hashPair_v_erase_index(temp, i);
            free_HashPair(copy);
            return found;
        }
        free_HashPair(copy);
    }
    return found;
}

char*
get_str_value_ht(hashtable* table, int key)
{
    hash_pair_vector * temp = table->ptr[hash(table, key)];
    for(int i = 0; i < temp->size; i++){
        if(key == hashPair_v_get_key(temp, i)){
            HashPair* copy = hashPair_v_get(temp, i);
            char* str = (char*)HashPair_get_value(copy);
            free_HashPair(copy);
            return str;
        }
    }
    return NULL;
}

double
get_dbl_value_ht(hashtable* table, int key)
{
    hash_pair_vector * temp = table->ptr[hash(table, key)];
    for(int i = 0; i < temp->size; i++){
        if(key == hashPair_v_get_key(temp, i)){
            HashPair* copy = hashPair_v_get(temp, i);
            double dbl = *(double*)HashPair_get_value(copy);
            free_HashPair(copy);
            return dbl;
        }
    }
    return 0.0;
}

bool
put_dbl_value_ht(hashtable* table, int key, double newValue)
{
    hash_pair_vector* temp_v = table->ptr[hash(table, key)];
    if( hashPair_v_put_dbl_val(temp_v, key, newValue) )
        return true;
    else
        return false;
}