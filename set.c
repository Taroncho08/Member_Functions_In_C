#include "vector.h"
//#define ADDRESS 5;



int set(int x, int y)
{
    struct vector *vec = (struct vector*)ADDRESS;       
    vec->x = x;
    vec->y = y;
}



