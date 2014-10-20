#include <cstdio>

char * bin (unsigned long int i)
{
    static char buffer [1+sizeof (unsigned long int)*8] = { 0 };
    char *p=buffer-1+sizeof (unsigned long int)*8;
    do { *--p = '0' + (i & 1); i >>= 1; } while (i);
    return p;
}

int main(){
    unsigned char a = 0x00FF;

    if (a & (1 << 8))
        printf("true\n");
    printf("%d\n%s\n" ,a, bin(a));
};