 /*
    Nick Anderson
    nickleus27@gmail.com
    github.com/nickleus27
    January 2022
 */

/*  Base Class for hash pair objects
    Each pair will have an integer hash key
    and a value to pair to.
*/
 
#ifndef HASH_PAIR_H
#define HASH_PAIR_H

/* Hash Pair's attributes... */
typedef struct {
    struct HashPairVtbl const *vptr; /* <== Shape's Virtual Pointer */
    int key;
    void* value;
} HashPair;

/*Union to accept all possible types for a value
TODO: MAY WANT TO INCLUDE THIS WITHIN HAHPAIR STRUCT */
union value_t{
    int intValue;
    float fltValue;
    double dblValue;
    char* strValue;
};

/* Hash Pair's virtual table */
struct HashPairVtbl {
    int (*get_key)(HashPair const * const me);
    HashPair* (*clone)(HashPair const * const me);
    void* (*get_value)(HashPair const * const me);
    void (*put_value)(HashPair* me, union value_t newValue);
    //GET VALUE??
};

/* Hash Pair's operations (Hash Pair's interface)... */
void HashPair_ctor(HashPair * const me, int thisKey);

//stored on the heap and needs to be freed with free_HashPair
HashPair* new_HashPair(int thisKey);

void free_HashPair(HashPair * const me);

static inline int HashPair_get_key(HashPair const * const me) {
    return (*me->vptr->get_key)(me);
}
 
static inline HashPair* HashPair_clone(HashPair const * const me) {
    return (*me->vptr->clone)(me);
}

static inline void* HashPair_get_value(HashPair const * const me) {
    return (*me->vptr->get_value)(me);
}
static inline void HashPair_put_value(HashPair* me, union value_t newValue)
{
    (*me->vptr->put_value)(me, newValue);
}
/* generic operations on hash pairs */
    //goes here
    //GET VALUE??
#endif /* HASH_PAIR_H */