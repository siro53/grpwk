#include <stdio.h>
#include <string.h>

int main()
{
    char str1[10] = "01234534";
    char *adr;

    /* 最初の"34"が発見される */
    adr = strstr(str1, "34");
    printf("adr=%s\n", adr); /* 34534 */

    /* "00"を発見できず */
    adr = strstr(str1, "00");
    printf("adr=%s\n", adr); /* NULL */
    /* NULLであることを確認してみる */
    if (strstr(str1, "00") == NULL)
    {
        printf("NULLです\n");
    }

    /* str2がNULLならば常にstr1の先頭アドレスを返す */
    adr = strstr(str1, "\0");
    printf("adr=%s\n", adr); /* 01234534 */
}