#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define L 400001

int main(void)
{
    FILE *fp_T;
    char fname2[] = "dat1_ref";
    char str_T[L];

    fp_T = fopen(fname2, "r"); // ファイルを開く。失敗するとNULLを返す。

    if (fp_T == NULL)
    {
        printf("%s file not open!\n", fname2);
        return -1;
    }

    fgets(str_T, L, fp_T); //終端文字に気をつける。Tファイルを配列に格納する(終端文字列に配慮して)
    puts(str_T);
    /*    for (i = 0; i < strlen(str_S); i++)
        {
            str_T[*str_p + i] = 'x';     //アロー演算子？
            fprintf(fp, "%d", (*str_p)); //別のfileに出力する。str_pの番地を出力したい。
        } */

    //S_iファイルを文字列に格納し、完全一致を調べる。とりあえず20まで？YUKIくん調べ。strstr関数 検索対象"dat1_ref",検索文字列 配列str strstr関数は検索文字列(s2)を最初に発見した位置のポインタを返す。(ここでポインタから番地を知りたい)strstrが終了したら文字列の長さ分ポインタからxに置換する

    //終端文字に気をつける?
    fclose(fp_T); // ファイルを閉じる

    return 0;
}
