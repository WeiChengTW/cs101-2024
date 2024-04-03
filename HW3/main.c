#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
char water[9];
int water_id;
typedef struct Lotto
{
    int recript_id;
    int receipt_price;
    // char receipt_time[32];
    int lotto_set[5][7];
} lotto_t;

void Find_Water()
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

    water_id = sum + 1;
    sprintf(water, "NO.%05d", water_id);
}

char *TIME()
{
    time_t curtime;
    time(&curtime);
    char *str_time = ctime(&curtime);
    str_time[strlen(str_time) - 1] = '\0';
    return str_time;
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

void record_writefile(lotto_t my_lotto, int num, char *str_time)
{
    FILE *fp;
    fp = fopen("record.bin", "r+");
    if (fp == NULL)
    {
        // printf("New\n");
        fp = fopen("record.bin", "w");
        water_id = 1;
        sprintf(water, "NO.%05d", water_id);
        // printf("ANO.%05d\n", water_id);
    }
    else
    {

        // printf("NO.%05d\n", water_id);
        Find_Water();
        fp = fopen("record.bin", "a");
    }
    fprintf(fp, "========= %s =========\n", water);
    fprintf(fp, "= %s =\n", str_time);
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
    // fprintf(fp, "========= csie@CGU =========\n", draw);
    fclose(fp);
}
void lotto_writefile(lotto_t my_lotto, int num, char *str_time)
{
    FILE *fp;
    char filename[17];
    // lotto[00001].txt
    // lotto[%05d].txt,i
    sprintf(filename, "lotto[%05d].txt", water_id);
    fp = fopen(filename, "w");
    fprintf(fp, "========= lotto649 =========\n");
    fprintf(fp, "========+ %s +========\n", water);
    fprintf(fp, "= %s =\n", str_time);

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
    char *Str_Time = TIME();
    lotto_t my_lotto;
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

    record_writefile(my_lotto, num, Str_Time);
    lotto_writefile(my_lotto, num, Str_Time);
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
    while (i < 21)
    {
        if (Arr[i] == ' ')
        {
            int num = (Arr[i + 1] - '0') * 10 + Arr[i + 2] - '0';
            // printf("num = %d\n", num);
            if (num == winNum[0] || num == winNum[1] || num == winNum[2])
            {
                return 1;
                break;
            }
            i += 3;
        }
    }
    return 0;
}

int main()
{
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
            if (winnum[i] < 10)
            {
                printf("%02d ", winnum[i]);
            }
            else
            {
                printf("%d ", winnum[i]);
            }
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
    while (i < sizeof(buffer))
    {
        if (buffer[i] == '=' && buffer[i + 1] == '=')
        {
            NO = CtoI(buffer, i);
            // printf("NO.%d", NO);
            i += 27;
        }
        else if (buffer[i] == '=' && buffer[i + 1] == ' ')
        {

            i += 1;

            for (int k = 0; k < 50; k++, i++)
            {
                if (buffer[i] == '=')
                {
                    ans_time[k + 1] = '=';
                    break;
                }
                char tmp = buffer[i];
                // printf("tmp=%c\n", tmp);
                ans_time[k] = tmp;
            }
        }
        else if (buffer[i] == '[' && buffer[i + 5] != '_')
        { // 42 45 56 05 57 62 25
            char NowCheckArr[22] = {0};
            i += 4;
            int k = 0;
            while (k < 22)
            {
                char tmp = buffer[i];
                // printf("tmp=%c\n", tmp);
                NowCheckArr[k] = tmp;
                i++, k++;
            }
            // printf("\n\n%s", NowCheckArr);
            if (CheckWin(NowCheckArr, winnum))
            {
                printf("\n彩卷 NO. %d\n", NO);
                printf("售出時間:");

                for (int j = 0; ans_time[j] != '='; j++)
                {
                    printf("%c", ans_time[j]);
                }

                printf("\n號碼:");
                for (int j = 0; j < 22; j++)
                {
                    printf("%c", NowCheckArr[j]);
                }
            }
        }
        i++;
    }
    return 0;
}
