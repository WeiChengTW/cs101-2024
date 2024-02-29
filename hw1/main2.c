#include <stdio.h>

int main()
{
    char a[] = "A4B1C3f3";
    char E;
    int count;
    int n = sizeof(a);
    // printf("%d", n);
    for (int i = 0; i <= n; i += 2)
    {
        // printf("%d\n\n", i);
        char E = a[i];
        int count = a[i + 1] - '0';
        // printf("%d\n", count);
        for (int j = 0; j < count; j++)
        {
            printf("%c", E);
        }
    }
}
