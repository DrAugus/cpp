#include <stdio.h>

int main()
{
    int a, b, c;

    a= 5;
    c = (b=a+2)-(a=2);

    printf("c=%d\n", c);

    printf("c++=%d\n", c++);
    printf("c=%d\n", c);

    printf("++c=%d\n",++c);
    printf("c=%d\n", c);


    printf("%d\n", 10/3*3);
    printf("%d\n", 10.0/3*3);
    printf("%f\n", 10/3*3);
    printf("%f\n", 10.0/3*3);

    for(int i =10;i>1;i/=2)
    {
        printf("%d ",i++);
    }
    printf("\n");

    return 0;
}