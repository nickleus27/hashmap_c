//gtk+ example
//nick anderson
//nickleus27@gmail.com

//#include "int_double.h"
#include "hash_table.h"
#include <stdio.h>

int
main(int argc, char **argv)
{

/*
    IntDoublePair* dd = new_IntDoublePair(100, 1.1111);
    union value_t  uv;
    uv.dblValue = 9.99999;
    HashPair_put_value((HashPair const *)dd, uv);
   printf("this is val aftetr put %f\n", *(double*)HashPair_get_value((HashPair const *)dd));
   */

    hashtable* t = new_hashtable(0);
    char * string;
    for(int i = 0; i<9; i++)
        insert_int_str_ht(t, i, "hello");
    insert_int_str_ht(t, 2, "world");
    insert_int_str_ht(t, 95, "new string");
    if(contains_ht(t, 95)){
        string =  get_str_value_ht(t, 95);
        printf("found 95 %s\n", string);
        free(string);
    }
    print_str_val_ht(t);
    printf("delete %d\n", key_erase_ht(t, 2));
    print_str_val_ht(t);
    //free_hashtable(t);


    /*int-double hashtable*/
    hashtable* dbl = new_hashtable(0);
    for(double i = 0; i<20; i++)
        insert_int_dbl_ht(dbl, (int)i, i);
    print_dbl_val_ht(dbl);
    printf("this is double key 5 value %f\n", get_dbl_value_ht(dbl, 5));
    if(contains_ht(dbl, 1))
        printf("1 is in ht\n");
    else
        printf("1 is not in ht\n");
    if(put_dbl_value_ht(dbl, 1, 500.555))
        printf("the value put was changed\n");
    else
        printf("not changed\n");
    printf("this is dbl key 1 after changed value %f\n", get_dbl_value_ht(dbl, 1));
    print_dbl_val_ht(dbl);
//done with dbl

//printing str again
    print_str_val_ht(t);

    //free both tables
    free_hashtable(dbl);
    free_hashtable(t);

    return 0;  
}