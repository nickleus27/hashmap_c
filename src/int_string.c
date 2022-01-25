#include "int_string.h" /* IntStringPair class interface */
#include <string.h> /* for printf() */
#include <stdlib.h>
#include <stdio.h>
/* IntStringPair's prototypes of its virtual functions */
/* NOTE: the "me" pointer has the type of the superclass to fit the vtable */
static int IntStringPair_get_key_(HashPair const * const me);
static HashPair* IntStringPair_clone_(HashPair const * const me);
static void* IntStringPair_get_value_(HashPair const * const me);
static void IntStringPair_put_value_(HashPair* me, union value_t newValue);

/* constructor */
void IntStringPair_ctor(IntStringPair * const me, int thisKey, char* thisValue)
{
    static struct HashPairVtbl const vtbl = { /* vtbl of the IntStringPair class */
        &IntStringPair_get_key_,
        &IntStringPair_clone_,
        &IntStringPair_get_value_,
        &IntStringPair_put_value_
    };
    HashPair_ctor(&me->super, thisKey); /* call the superclass' ctor */
    me->super.vptr = &vtbl; /* override the vptr */
    me->super.value = thisValue;
    //me->super.vptrValue = me->value;
}

//consturctor for object stored on heap.  Needs to be freed with free_IntStringPair
IntStringPair* new_IntStringPair(int thiskey, const char* thisValue)
{
    static struct HashPairVtbl const vtbl = { /* vtbl of the IntStringPair class */
        &IntStringPair_get_key_,
        &IntStringPair_clone_,
        &IntStringPair_get_value_,
        &IntStringPair_put_value_
    };
    IntStringPair* obj = (IntStringPair*)malloc(sizeof(IntStringPair));
    if(!obj)
        return NULL;
    HashPair_ctor(&obj->super, thiskey); /* call the superclass' ctor */
    obj->super.vptr = &vtbl; /* override the vptr */
    obj->super.value = (char*)malloc(sizeof(char)*strlen(thisValue)+1);
    if(!obj->super.value)
        return NULL;
    strcpy(obj->super.value, thisValue);
    //obj->super.vptrValue = obj->value;
    return obj;
}

void free_IntStringPair(IntStringPair* const me)
{
    free(me->super.value);
    free(me);
}

/* IntStringPair's class implementations of its virtual functions... */
static int IntStringPair_get_key_(HashPair const * const me) {
    return me->key;
}

static HashPair* IntStringPair_clone_(HashPair const * const me) {
    IntStringPair const * const me_ = (IntStringPair const *)me; /* explicit downcast */
    IntStringPair* obj = new_IntStringPair(me->key, me_->super.value);
    if(!obj)
        return NULL;
    return (HashPair*)obj;
}

//needs to be freed from memory
static void* IntStringPair_get_value_(HashPair const * const me)
{
    char* copy = (char *) malloc(sizeof(char) * strlen( (char*)me->value +1 ) );
    strcpy(copy, (const char*)me->value );
    return copy;
}

static void IntStringPair_put_value_(HashPair* me, union value_t newValue)
{
    void* temp = NULL;
    int thiStrLen = strlen((char*)me->value), newStrLen = strlen(newValue.strValue);
    if ( thiStrLen < newStrLen)
    {
        temp = (char*)realloc(me->value, sizeof(char) * newStrLen);
        if ( temp )
            me->value = temp;
        strcpy(me->value, newValue.strValue);
    }
}

/* wrapper function for privacy
NEED TO FREE MEMORY */
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

