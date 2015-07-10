#include <stdio.h>

int findzeros(unsigned int n);

int main(int argv, char *argc[])
{
    unsigned int i = 0;
    unsigned int n;
    scanf("%u",&n);
    for(unsigned int j = 0; j < n; j++) {
		scanf("%u",&i);
		printf("%u\n",findzeros(i));
    }
    return 0;
}

int findzeros(unsigned int n)
{
    int result = 0;
    while ( n > 0)
    {
        n /= 5;
        result += n;
    }
    return result;
}
