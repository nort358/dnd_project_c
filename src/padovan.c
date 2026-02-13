#include "padovan.h"
int isPadovan(int n)
{
    return isPadovanRec(1,1,1,n);
}
int isPadovanRec(int a, int b, int c, int n)
{
 if (c>n){
     return 0;
 }
 if (c==n){
     return 1;
 }
 return isPadovanRec(b,c,a+b,n);
}
