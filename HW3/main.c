#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
char water[9];
// int water_id;
typedef struct Lotto
{
    int recript_id;
    int receipt_price;
    char receipt_time[32];
    int lotto_set[5][7];
} lotto_t;

void Find_Water(lotto_t *my_lotto)
{
    FILE *fp;
    int ans_index;
    char buffer[10000] = {0};
    fp = fopen("record.bin", "r");
    fread(buffer, sizeof(char), sizeof(buffer), fp);
    // for (int i = 0; i < sizeof(buffer); i++)
    // {
    //     printf("%c", buffer[i]);
    // }
    for (int i = sizeof(buffer); i >= 0; i--)
    {
        if (buffer[i] == '.')
        {
            ans_index = i + 1;
            break;
        }
    }

    fclose(fp);
    // printf("ans = %d\n", ans_index);
    int sum = 0;
    for (int i = ans_index; i < ans_index + 5; i++)
    {

        // printf("buffer[i] = %c\n", buffer[i]);
        sum = sum * 10 + (buffer[i] - '0');
        // printf("sum = %d", sum);
    }
    // printf("ans = %d", ans_index);

    my_lotto->recript_id = sum + 1;
    // sprintf(water, "NO.%05d", water_id);
}

void TIME(lotto_t *my_lotto)
{
    time_t curtime;
    time(&curtime);
    char *str_time = ctime(&curtime);
    str_time[strlen(str_time) - 1] = '\0';
    for (int i = 0; str_time[i] != '\0'; i++)
    {
        char a = str_time[i];
        my_lotto->receipt_time[i] = a;
    }
}

int Random_num()
{
    int num;
    num = rand() % 69 + 1;
    return num;
}

int Chack_num(int arr[], int num)
{
    for (int i = 0; i < 7; i++)
    {
        if (num == arr[i])
        {
            return 1;
        }
    }
    return 0;
}

void record_writefile(lotto_t my_lotto, int num)
{
    FILE *fp;
    fp = fopen("record.bin", "r+");
    if (fp == NULL)
    {
        // printf("New\n");
        fp = fopen("record.bin", "w");
        my_lotto.recript_id = 1;
        sprintf(water, "NO.%05d", my_lotto.recript_id);
        // printf("ANO.%05d\n", water_id);
    }
    else
    {

        // printf("NO.%05d\n", water_id);
        Find_Water(&my_lotto);
        fp = fopen("record.bin", "a");
    }
    sprintf(water, "NO.%05d", my_lotto.recript_id);
    fprintf(fp, "%s\n", water);

    // fprintf(fp, "= ");
    for (int i = 0; i < my_lotto.receipt_time[i] != '\0'; i++)
    {
        fprintf(fp, "%c", my_lotto.receipt_time[i]);
    }
    // fprintf(fp, " =\n");
    fprintf(fp, "\n");
    fprintf(fp, "%d\n", my_lotto.receipt_price);

    for (int i = 0; i < num; i++)
    {
        // fprintf(fp, "[%d]: ", i + 1);
        for (int j = 0; j < 7; j++)
        {
            if (my_lotto.lotto_set[i][j] < 10)
            {
                fprintf(fp, "0%d ", my_lotto.lotto_set[i][j]);
            }
            else
            {
                fprintf(fp, "%2d ", my_lotto.lotto_set[i][j]);
            }
        }
        fprintf(fp, "\n");
    }

    for (int i = num; i < 5; i++)
    {
        // fprintf(fp, "[%d]: ", i + 1);
        for (int j = 0; j < 7; j++)
        {

            fprintf(fp, "__ ");
        }
        fprintf(fp, "\n");
    }
    // fprintf(fp, "========= csie@CGU =========\n", draw);
    fclose(fp);
}
void lotto_writefile(lotto_t my_lotto, int num)
{
    FILE *fp;
    char filename[17];
    // lotto[00001].txt
    // lotto[%05d].txt,i
    sprintf(filename, "lotto[%05d].txt", my_lotto.recript_id);
    fp = fopen(filename, "w");
    fprintf(fp, "========= lotto649 =========\n");
    sprintf(water, "NO.%05d", my_lotto.recript_id);
    fprintf(fp, "========+ %s +========\n", water);

    fprintf(fp, "= ");
    for (int i = 0; i < my_lotto.receipt_time[i] != '\0'; i++)
    {
        fprintf(fp, "%c", my_lotto.receipt_time[i]);
    }
    fprintf(fp, " =\n");

    for (int i = 0; i < num; i++)
    {
        fprintf(fp, "[%d]: ", i + 1);
        for (int j = 0; j < 7; j++)
        {
            if (my_lotto.lotto_set[i][j] < 10)
            {
                fprintf(fp, "0%d ", my_lotto.lotto_set[i][j]);
            }
            else
            {
                fprintf(fp, "%2d ", my_lotto.lotto_set[i][j]);
            }
        }
        fprintf(fp, "\n");
    }

    for (int i = num; i < 5; i++)
    {
        fprintf(fp, "[%d]: ", i + 1);
        for (int j = 0; j < 7; j++)
        {

            fprintf(fp, "__ ");
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "========= csie@CGU =========\n");
    fclose(fp);
}

void Main_lotto(int num)
{

    // printf("請問您要買幾組樂透彩：");

    // printf("%d", num);
    //  int num;
    //  scanf("%d", &num);
    //  if (num > 5 || num < 1)
    //  {
    //      printf("請輸入1~5之間的數字\n");
    //      return 0;
    //  }

    lotto_t my_lotto;
    my_lotto.receipt_price = 100 * num;
    TIME(&my_lotto);
    int random_num = 0;
    for (int i = 0; i < num; i++)
    {
        my_lotto.recript_id = i + 1;
        for (int j = 0; j < 7; j++)
        {

            random_num = Random_num();
            while (Chack_num(my_lotto.lotto_set[i], random_num))
            {
                random_num = Random_num();
            }
            // printf("%d ", random_num);
            my_lotto.lotto_set[i][j] = random_num;
        }
    }

    record_writefile(my_lotto, num);
    lotto_writefile(my_lotto, num);
}

void reset()
{
    FILE *fp;
    char filename[17];
    // lotto[00001].txt
    // lotto[%05d].txt,i

    for (int i = 1; i < 100; i++)
    {
        sprintf(filename, "lotto[%05d].txt", i);
        fp = fopen(filename, "r+");

        if (fp != NULL)
        {
            fclose(fp);
            remove(filename);
        }
        fclose(fp);
    }

    fp = fopen("record.bin", "r+");
    if (fp != NULL)
    {
        fclose(fp);
        remove("record.bin");
    }
    fclose(fp);
}

int CtoI(char *arr, int n)
{
    int num = 0;
    int i = n + 13;
    while (arr[i] >= '0' && arr[i] <= '9')
    {

        num = num * 10 + (arr[i] - '0');
        // printf("num = %d\n", num);
        i++;
    }
    return num;
}
int CheckWin(char *Arr, int *winNum)
{
    int i = 0;
    while (i < 20)
    {

        int num = (Arr[i] - '0') * 10 + Arr[i + 1] - '0';
        // printf("num = %d\n", num);
        if (num == winNum[0] || num == winNum[1] || num == winNum[2])
        {
            return 1;
            break;
        }
        i += 3;
    }
    return 0;
}

int main()
{
    srand(1);
    printf("歡迎光臨長庚樂透購買機台\n");
    reset();
    int n;
    printf("請問你要買幾組樂透彩:");
    scanf("%d", &n);

    while (n != 0)
    {
        // sprintf(water, "NO.%05d", water_id);
        Main_lotto(n);
        printf("請問你要買幾組樂透彩:");
        scanf("%d", &n);
        // water_id++;
    }

    printf("\n請輸入中獎號碼(最多三個):");
    int winnum[3] = {0};

    int counter = 0;
    do
    {
        scanf("%d", &winnum[counter]);
        counter++;
    } while (getchar() != '\n');

    printf("\n輸入的中獎號碼:");
    // printf("\n輸入的中獎號碼:01 02 07");
    for (int i = 0; i < 3; i++)
    {
        if (winnum[i] == 0)
        {
            break;
        }
        else
        {
            printf("%02d ", winnum[i]);
        }
    }

    // int winnum[3] = {1, 2, 7};

    printf("\n以下是中獎彩卷:");
    FILE *record_fp;
    record_fp = fopen("record.bin", "r");
    char buffer[1000] = {0};
    fread(buffer, 1, sizeof(buffer), record_fp);
    int NO = 0;
    int i = 0;
    char ans_time[50];
    char ans_num[50];
    int line = 0;
    lotto_t lotto;
    Find_Water(&lotto);
    // printf("%d", lotto.recript_id);
    while (line < (lotto.recript_id - 1) * 8)
    {
        // printf("i = %d\n", i);
        if (line % 8 == 0)
        {
            NO = 0;
            if (buffer[i] == '.')
            {
                i += 1;
                for (int j = i; i < j + 5; i++)
                {
                    // printf("i = %d\n", i);
                    NO = NO * 10 + (buffer[i] - '0');
                    // printf("%d ", NO);
                }

                line++;
            }
            // printf("Aline = %d\n", line);
        }
        else if (line % 8 == 1)
        {
            // printf("i = %d\n", i);
            int j = 0;
            for (; buffer[i] != '\n'; j++, i++)
            {
                char a = buffer[i];
                ans_time[j] = a;
            }
            char a = buffer[i];
            ans_time[j] = a;
            line++;
            // printf("Bline = %d\n", line); 
        }
        else if (line % 8 == 2)
        {

            //    printf("i = %d\n", i);
            //     printf("%c", buffer[i]);
            //     printf("%c", buffer[i + 1]);
            //     printf("%c", buffer[i + 2]);
            i += 3;
            // printf("\n");
            line++;
        }
        else
        {
            if (buffer[i] != '_')
            {
                int j = 0;
                for (; buffer[i] != '\n'; j++, i++)
                {
                    char a = buffer[i];
                    ans_num[j] = a;
                }
                char a = buffer[i];
                ans_num[j] = a;
                // printf("Cline = %d\n", line);
                if (CheckWin(ans_num, winnum) == 1)
                {
                    printf("\n彩卷 NO. %d\n", NO);
                    printf("售出時間:");
                    for (int j = 0; ans_time[j] != '\n'; j++)
                    {
                        printf("%c", ans_time[j]);
                    }
                    printf("\n號碼:");
                    for (int j = 0; ans_num[j] != '\n'; j++)
                    {
                        printf("%c", ans_num[j]);
                    }
                }
            }
            line++;
        }
        i++;
    }
    return 0;
}
