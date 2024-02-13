#include <stdio.h>
#include <libc.h>

void    fun()
{
    system("leaks main");
}


void ff(int **x)
{
    *x = malloc(10);


}

int main (int ac, char **av)
{
    char **ax;
    atexit(fun);
    // av = malloc(1000);
    av[0] = malloc(100000);
    av[1] = malloc(100000);
    av[2] = malloc(100000);
    int *a;
    ff(&a);
    exit(1);
}
