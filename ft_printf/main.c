#include "ft_printf.h"
#include <stdio.h>

int main ()
{
    int i  = ft_printf("sala\0m");
    printf("\n%d", i);
}