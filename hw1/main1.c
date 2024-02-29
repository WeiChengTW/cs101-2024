#include <stdio.h>

int main()
{
    char a[] = "AABBBCCCCddd";
    int len_a = sizeof(a) / sizeof(a[0])-1;
    // printf("%d\n\n", len_a);
    char E = a[0];

    for (int i = 1; i < len_a; i++)
    {
        int count = 1;
        while (a[i] == E)
        {
            count += 1;
            i++;
        }
        printf("%c%d", E, count);
        E = a[i];
    }
}
