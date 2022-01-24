#include "int_double.h" /* IntStringPair class interface */
//#include <string.h> /* for printf() */
#include <stdlib.h>
//#include <stdio.h>
/* IntDoublePair's prototypes of its virtual functions */
/* NOTE: the "me" pointer has the type of the superclass to fit the vtable */
static int IntDoublePair_get_key_(HashPair const * const me);
static HashPair* IntDoublePair_clone_(HashPair const * const me);
static void* IntDoublePair_get_value_(HashPair const * const me);
static void IntDoublePair_put_value_(HashPair const * const me, union value_t newValue);

/* constructor */
/*
void IntDoublePair_ctor(IntDoublePair * const me, int thisKey, double thisValue)
{
    static struct HashPairVtbl const vtbl = { // vtbl of the IntStringPair class
        &IntDoublePair_get_key_,
        &IntDoublePair_clone_,
        &IntDoublePair_get_value_
    };
    HashPair_ctor(&me->super, thisKey); // call the superclass' ctor
    me->super.vptr = &vtbl; // override the vptr
    //me->dValue = thisValue;
    //me->super.value = &me->dValue;
    *(double*)me->super.value = thisValue;
}
*/


//consturctor for object stored on heap.  Needs to be freed with free_IntStringPair
IntDoublePair* new_IntDoublePair(int thiskey, double thisValue)
{
    static struct HashPairVtbl const vtbl = { // vtbl of the IntStringPair class
        &IntDoublePair_get_key_,
        &IntDoublePair_clone_,
        &IntDoublePair_get_value_,
        &IntDoublePair_put_value_
    };
    IntDoublePair* obj = (IntDoublePair*)malloc(sizeof(IntDoublePair));
    if(!obj)
        return NULL;
    HashPair_ctor(&obj->super, thiskey); // call the superclass' ctor
    obj->super.vptr = &vtbl; // override the vptr
    obj->super.value = (double*)malloc(sizeof(double));
    *(double*)obj->super.value = thisValue;
    return obj;
}

void free_IntDoublePair(IntDoublePair* const me)
{
    free(me->super.value);
    free(me);
}

// IntStringPair's class implementations of its virtual functions...
static int IntDoublePair_get_key_(HashPair const * const me){
    return me->key;
}

static HashPair* IntDoublePair_clone_(HashPair const * const me){
    IntDoublePair const * const me_ = (IntDoublePair const *)me; // explicit downcast
    IntDoublePair* obj = new_IntDoublePair(me->key, *(double*)me_->super.value);
    if(!obj)
        return NULL;
    return (HashPair*)obj;
   return NULL;
}

//privacy leak
static void* IntDoublePair_get_value_(HashPair const * const me)
{
    return me->value;
}

static void IntDoublePair_put_value_(HashPair const * const me, union value_t newValue)
{
    *(double*)me->value = newValue.dblValue;
}

/*
// wrapper function for privacy, NEED TO FREE MEMORY
char* IntStringPair_get_value(IntStringPair* const me)
{

   return (char*)HashPair_get_value( (HashPair const *)me );
}

int IntStringPair_get_value_byarg(IntStringPair* const me, char* string, int size)
{
    char* copy = (char*)HashPair_get_value( (HashPair const *)me );
    if(strlen(copy)+1 > size)
    {
        free(copy);
        //printf("IntStringPair_get_value_byarg: Size of IntStringPair value is greater than the argument string size\n");
        return 0;
    }
    strcpy(string, copy);
    free(copy);
    return 1;
}

int IntStringPair_get_string_size(IntStringPair* const me)
{
    return strlen(me->super.value);
}
*/
