//まずは２つのファイルを読み込む、１、文字列S_iを長さ順にソートしたファイル、２、T(完成形のファイル)、
//また１つのファイルに書き込む用意をする("position.txt")
//fgetsでTを配列に格納し、次に｛S_iを1行取り込み、strstrで最初に完全に一致したポインタを返す。
//そして完全に一致したときそのポインタの番地を"position.txt"にかきこみ、そのポインタが指し示す場所から文字列長分(strlen関数)'x'に置換する。｝この動作をループさせる。

//Segmentation fault (core dumped)中　segmentation fault 11(core dumped)（以下、セグフォ）とは、本来はアクセスできないメモリのアドレスにアクセスする時に起こるエラーのことを言う。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 256
#define L 400001

int main(void)
{
    FILE *fp;
    FILE *fp_T;
    FILE *fp_S_i;
    char fname[] = "dat1-1_in";
    char fname2[] = "dat1_ref";
    char str_S[N];
    char str_T[L];

    fp = fopen("position.txt", "w");

    fp_S_i = fopen(fname, "r"); // ファイルを開く。失敗するとNULLを返す。

    if (fp_S_i == NULL)
    {
        printf("%s file not open!\n", fname);
        return -1;
    }

    fp_T = fopen(fname2, "r"); // ファイルを開く。失敗するとNULLを返す。

    if (fp_T == NULL)
    {
        printf("%s file not open!\n", fname2);
        return -1;
    }

    fgets(str_T, L, fp_T); //終端文字に気をつける。Tファイルを配列に格納する(終端文字列に配慮して)

    while (fgets(str_S, N, fp_S_i) != NULL)
    {
        int i = 0;
        char *str_p;

        str_p = strstr(str_T, str_S); //

        for (i = 0; i < strlen(str_S); i++)
        {
            str_T[*str_p + i] = 'x';     //アロー演算子？
            fprintf(fp, "%d", (*str_p)); //別のfileに出力する。str_pの番地を出力したい。
        }

        //S_iファイルを文字列に格納し、完全一致を調べる。とりあえず20まで？YUKIくん調べ。strstr関数 検索対象"dat1_ref",検索文字列 配列str strstr関数は検索文字列(s2)を最初に発見した位置のポインタを返す。(ここでポインタから番地を知りたい)strstrが終了したら文字列の長さ分ポインタからxに置換する

        //終端文字に気をつける?
    }
    fclose(fp);
    fclose(fp_T);   // ファイルを閉じる
    fclose(fp_S_i); //同上

    return 0;
}

//ファイルを配列に格納する(終端文字列に配慮して)

/*完全一致を調べる(ループ)

一致を確認したらxに置換 + 先頭の数を返す

    1文字は全て同じものとする。

    strstr関数を用いる

    -- masaki Sato
*/