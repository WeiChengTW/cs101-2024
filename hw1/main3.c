#include <stdio.h>
int Pow(int n)
{
    int x = 1;
    if (n == 0)
    {
        return 1;
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            x = x * 2;
        }

        return x;
    }
}

int main()
{
    char a[] = "10001111";
    int n1, n2 = 0;
    char ans1, ans2;
    // printf("%c", a[7]);
    for (int i = 3; i >= 0; i--)
    {
        int num = a[i] - '0';
        if (num != 0)
        {
            // printf("7-i=%d\n", 3 - i);
            int n_pow = Pow(3 - i);
            // printf("n_pow=%d\n", n_pow);
            n1 += n_pow;
            // printf("n1=%d\n\n", n1);
        }
    }
    if (n1 > 9)
    {
        ans1 = (n1 - 10) + 'A';
        // printf("ans1=%c", ans1);
        printf("%c", ans1);
    }
    else
    {
        printf("%d", n1);
    }

    for (int i = 7; i >= 4; i--)
    {
        int num = a[i] - '0';
        if (num != 0)
        {
            // printf("7-i=%d\n", 7 - i);
            int n_pow = Pow(7 - i);
            // printf("n_pow=%d\n", n_pow);
            n2 += n_pow;
            // printf("n2=%d\n\n", n2);
        }
    }
    if (n2 > 9)
    {
        ans2 = (n2 - 10) + 'A';
        // printf("ans1=%c", ans1);
        printf("%c", ans2);
    }
    else
    {
        printf("%d", n2);
    }
}
