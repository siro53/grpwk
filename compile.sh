#!/bin/bash

# 使用例
# ./compile.sh -d example -t 0 -f

# 各種設定(初期設定)
PROG=grpwk # 実行ファイル名
CC=gcc # コンパイラ
CFLAGS="-W -Wall -Wextra -Wconversion -Wshadow -O0" # ワーニング
DIR="example" # 自分で作ったgrpwk.cがあるディレクトリ
TCASE=0 # dat${TCASE}_inを参照(テストケースの選択)

# 使い方の説明
usage_exit() {
    echo "Usage: $0 [-f (-fast: no warning)] [-d <dir name>] [-t <test id>]"
}

# コマンドラインオプションを設定
while getopts :hfd:t:f OPT
do
    case $OPT in
        f) CFLAGS="-Ofast" # コンパイルをワーニングなしで実行
            echo "You are running the compiler withOUT -Wall option!"
            ;;
        d) DIR=$OPTARG;; # grpwk.cのあるディレクトリの設定(トップディレクトリとこのディレクトリしかコンパイルされないためファイル構成には注意)
        t) TCASE=$OPTARG;; # テストケースの設定：0-4
        h) usage_exit;; # ヘルプ
        \?) usage_exit;; # 例外処理
    esac
done
shift $(($OPTIND - 1)) # コマンドラインオプションで用いたものたちをargvから消去

# ファイルを探索：名前にtestを含まない*.cなものをすべて取ってくる
FILES=$(find -maxdepth 1 \( -name "*.c" \) \( -not -name "*test*" \)) # トップディレクトリ
MYFILES=$(find $DIR \( -name "*.c" \) \( -not -name "*test*" \)) # -dで設定されたディレクトリ

# コンパイル
$CC $CFLAGS -o grpwk $FILES $MYFILES
$CC -o distance test_distance.c

# 実行
echo -------------result
echo -n "time         : "
./grpwk data/dat${TCASE}_in result
./distance result data/dat${TCASE}_ref

# 実行ファイルの消去
rm distance
rm grpwk

# 出力された文字列の表示(デバッグ等に使用)
# 一般的には長すぎてターミナルが重くなってしまうためコメントアウト
# echo
# echo -------------output
# cat result

echo "done"
