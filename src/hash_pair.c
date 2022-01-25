/* base class for hash pairs
    Nick Anderson
    nickleus27@gmail.com
    January 2022
*/

#include "hash_pair.h"
#include <assert.h>
#include <stdlib.h>

/* HashPair's prototypes of its virtual functions */
static int get_key_(HashPair const * const me);
static HashPair* HashPair_clone_(HashPair const * const me);
static void* get_value_(HashPair const * const me);
static void put_value_(HashPair* me, union value_t newValue);

/* constructor */
void HashPair_ctor(HashPair * const me, int thisKey) {
    static struct HashPairVtbl const vtbl = { /* vtbl of the HashPair class */
        &get_key_,
        &HashPair_clone_,
        &get_value_,
        &put_value_
    };
    me->vptr = &vtbl; /* "hook" the vptr to the vtbl */
    me->key = thisKey;
    me->value = NULL;
}
HashPair* new_HashPair(int thisKey){
    HashPair* obj = (HashPair*)malloc(sizeof(HashPair));
    static struct HashPairVtbl const vtbl = { /* vtbl of the HashPair class */
        &get_key_,
        &HashPair_clone_
    };
    obj->vptr = &vtbl;
    obj->key = thisKey;
    obj->value = NULL;
    return obj;
}

void free_HashPair(HashPair* const me)
{
    free(me->value);
    free(me);
}

/* HashPair class implementations of its virtual functions... */
 static int get_key_(HashPair const * const me) {
    assert(0); /* purely-virtual function should never be called */
    return 0U; /* to avoid compiler warnings */
}

static HashPair* HashPair_clone_(HashPair const * const me) {
    assert(0); /* purely-virtual function should never be called */
    return 0U; /* to avoid compiler warnings */
}

 static void* get_value_(HashPair const * const me) {
    assert(0); /* purely-virtual function should never be called */
    return 0U; /* to avoid compiler warnings */
}

static void put_value_(HashPair* me, union value_t newValue)
{
    assert(0);/* purely-virtual function should never be called */
}