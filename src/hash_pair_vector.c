//
//  hash_pair_vector.c
// 
//
//  Created by Nicholas Anderson on 9/12/21.
//

#include "hash_pair_vector.h"
#include <stdio.h>

//initialize vector with initial size argument
struct HashPairVector
{
    size_t space_left;
    size_t size;
    HashPair **ptr;
};

hash_pair_vector*
new_hashPair_v(size_t init_size )
{
    hash_pair_vector* vector = (hash_pair_vector*)malloc(sizeof(HashPair));
    vector->ptr = (HashPair**)malloc(init_size * sizeof(HashPair));//initialize array to size set to argument
    if(!vector->ptr){
        printf("Failed malloc\n");
        exit(EXIT_FAILURE);
    }
    vector->size = 0;//array is empty
    vector->space_left = init_size;//space left is initial size (16)
    return vector;
}

bool
hashPair_v_push_b( hash_pair_vector *vector, HashPair* data ){

    if( vector->space_left == 0 ){//if array is full
        HashPair **ptrTemp = NULL;
        size_t maxLength = 0;
        maxLength = vector->size<<INCREMENT;//1;//double the size of array (maxLength x 2)
        ptrTemp = (HashPair**)realloc(vector->ptr, maxLength * sizeof(HashPair) );//have vptrTemp = realloc incase not succesful
        if( ptrTemp == NULL )
        {//exit it realloc failed
            printf( "Failed realloc");
            return false;
        }
        vector->space_left = maxLength - vector->size;//space left after growing
        vector->ptr = ptrTemp;//have vector point to realloc array
    }

    vector->ptr[vector->size++] = data;//now that we have space push data to next available spot
    vector->space_left--;
    return true;
}

//This will make the memory efficient.
/*
void intv_finalizeMemory(int_vector *vector)
{
    vector->ptr = realloc(vector->ptr, vector->size * sizeof(int *));
}
*/

//free memory back to heap
void
free_hashPair_v(hash_pair_vector *vector)
{
    for(size_t i = 0; i<vector->size; i++)
    {
        free_HashPair(vector->ptr[i]);
    }
    free(vector->ptr);
    free(vector);
}

//return amount of elements in array
int
hashPair_v_size(hash_pair_vector *vector)
{
    return (int)vector->size;
}

// returns clone of data and needs to be freed
HashPair*
hashPair_v_get(hash_pair_vector *vector, int index )
{
    if(index >= vector->size || index < 0)
    {
        printf("Error: index %d out of bounds ", index);
        //int_string_v_free(vector);
        exit(EXIT_FAILURE);
    }
    else
    {
        return HashPair_clone(vector->ptr[index]);
    }
}
 
bool hashPair_v_pop(hash_pair_vector *vector)
{
    if(vector->size == 0)
        return false;
    vector->ptr[vector->size] = 0; // clear data from array
    vector->space_left++;
    return true;
}


void hashPair_v_clear(hash_pair_vector *vector)
{
    while(vector->size != 0)
    {
        vector->ptr[--vector->size] = 0;
        vector->space_left++;
    }
}

bool 
hashPair_v_erase_index(hash_pair_vector *vector, int index)
{
    if (index<0 || index>=(int)vector->size)
        return false;
    free_HashPair(vector->ptr[index]);
    while (index < vector->size-1)
    {
        vector->ptr[index] = vector->ptr[index+1];
        index++;
    }
    vector->ptr[--vector->size]=0;
    vector->space_left++;
    return true;
}

int
hashPair_v_get_key(hash_pair_vector * vector, int index)
{
        if(index >= vector->size || index < 0)
    {
        printf("Error: index %d out of bounds ", index);
        //int_string_v_free(vector);
        exit(EXIT_FAILURE);
    }
    else
    {
        return HashPair_get_key ((const HashPair*)vector->ptr[index]);
    }
}

bool
hashPair_v_put_dbl_val(hash_pair_vector* vector, int key, double dbl)
{
    for(int i = 0; i < vector->size; i++)
    {
        if(key == HashPair_get_key(vector->ptr[i]))
        {
            union value_t newValue;
            newValue.dblValue = dbl;
            HashPair_put_value(vector->ptr[i], newValue);
            return true;
        }
    }
    return false;
}

bool
hashPair_v_put_str_val(hash_pair_vector* vector, int key, char* str)
{
    for(int i = 0; i < vector->size; i++)
    {
        if(key == HashPair_get_key(vector->ptr[i]))
        {
            union value_t newValue;
            newValue.strValue = str;
            HashPair_put_value(vector->ptr[i], newValue);
            return true;
        }
    }
    return false;
}

