要点まとめ

変更点：
s_iのconst修飾子を除外（ソートの必要性があるため）
t_outの型をchar型からstring_out型に変更（既に一致済のs_iに関する情報を持っておきたかった）

BM.cの動作はボイヤームーアとほぼ同じだが虫食いのため微妙に違う動作をする。
そのためソースコードがネット上に転がってるものとだいぶ違うことに注意。
例えば
t:abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_0:abcddbcdbcbaaaabcccaabaaada
s_1:bdaabaadaacbdbcaad
s_2:....
のとき、以下のような動作をする。
ここで、t_idはt_inにおけるs_iの最後尾,comp_varはs_iのどこを比較しているかをあらわしている。
１５文字以上一致したらそこで比較を打ち切り成功探索とみなしている。


udemegane@DESKTOP-K5R8CJ6:~/work/grpwk/example$ ./a.out
Whether or not already matched|character:x
Did not match
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:abcddbcdbcbaaaabcccaabaaada
cmp:                          ^
t_id:26  comp_var:0
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:abcddbcdbcbaaaabcccaabaaada
cmp:                         ^
t_id:26  comp_var:1
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:abcddbcdbcbaaaabcccaabaaada
cmp:                        ^
t_id:26  comp_var:2
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:abcddbcdbcbaaaabcccaabaaada
cmp:                       ^
t_id:26  comp_var:3
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:abcddbcdbcbaaaabcccaabaaada
cmp:                      ^
t_id:26  comp_var:4
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:abcddbcdbcbaaaabcccaabaaada
cmp:                     ^
t_id:26  comp_var:5
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:abcddbcdbcbaaaabcccaabaaada
cmp:                    ^
t_id:26  comp_var:6
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:abcddbcdbcbaaaabcccaabaaada
cmp:                   ^
t_id:26  comp_var:7
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:abcddbcdbcbaaaabcccaabaaada
cmp:                  ^
t_id:26  comp_var:8
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:abcddbcdbcbaaaabcccaabaaada
cmp:                 ^
t_id:26  comp_var:9
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:abcddbcdbcbaaaabcccaabaaada
cmp:                ^
t_id:26  comp_var:10
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:abcddbcdbcbaaaabcccaabaaada
cmp:               ^
t_id:26  comp_var:11
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:abcddbcdbcbaaaabcccaabaaada
cmp:              ^
t_id:26  comp_var:12
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:abcddbcdbcbaaaabcccaabaaada
cmp:             ^
t_id:26  comp_var:13
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:abcddbcdbcbaaaabcccaabaaada
cmp:            ^
t_id:26  comp_var:14
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:abcddbcdbcbaaaabcccaabaaada
cmp:           ^
t_id:26  comp_var:15
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:abcddbcdbcbaaaabcccaabaaada
cmp:          ^
t_id:26  comp_var:16

Detected the exact position of s_i!!
Before s_i assignment:xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
After  s_i assignment:abcddbcdbcbaaaabcccaabaaadaxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


Whether or not already matched|character:c
Caution|Already matched:Character is not 'x',shifts s_i position
out:abcddbcdbcbaaaabcccaabaaadaxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                           bdaabaadaacbdbcaad
cmp:                                            ^
t_id:44  comp_var:0
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                           bdaabaadaacbdbcaad
cmp:                                           ^
t_id:44  comp_var:1
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                           bdaabaadaacbdbcaad
cmp:                                          ^
t_id:44  comp_var:2
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                           bdaabaadaacbdbcaad
cmp:                                         ^
t_id:44  comp_var:3

Shift s_i by 1

Whether or not already matched|character:x
Did not match
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                            bdaabaadaacbdbcaad
cmp:                                             ^
t_id:45  comp_var:0

Shift s_i by 1

Whether or not already matched|character:x
Did not match
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                             bdaabaadaacbdbcaad
cmp:                                              ^
t_id:46  comp_var:0

Shift s_i by 1

Whether or not already matched|character:x
Did not match
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                              bdaabaadaacbdbcaad
cmp:                                               ^
t_id:47  comp_var:0

Shift s_i by 3

Whether or not already matched|character:x
Did not match
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                                 bdaabaadaacbdbcaad
cmp:                                                  ^
t_id:50  comp_var:0
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                                 bdaabaadaacbdbcaad
cmp:                                                 ^
t_id:50  comp_var:1
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                                 bdaabaadaacbdbcaad
cmp:                                                ^
t_id:50  comp_var:2
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                                 bdaabaadaacbdbcaad
cmp:                                               ^
t_id:50  comp_var:3
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                                 bdaabaadaacbdbcaad
cmp:                                              ^
t_id:50  comp_var:4

Shift s_i by 4

Whether or not already matched|character:x
Did not match
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                                     bdaabaadaacbdbcaad
cmp:                                                      ^
t_id:54  comp_var:0
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                                     bdaabaadaacbdbcaad
cmp:                                                     ^
t_id:54  comp_var:1
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                                     bdaabaadaacbdbcaad
cmp:                                                    ^
t_id:54  comp_var:2
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                                     bdaabaadaacbdbcaad
cmp:                                                   ^
t_id:54  comp_var:3
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                                     bdaabaadaacbdbcaad
cmp:                                                  ^
t_id:54  comp_var:4
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                                     bdaabaadaacbdbcaad
cmp:                                                 ^
t_id:54  comp_var:5
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                                     bdaabaadaacbdbcaad
cmp:                                                ^
t_id:54  comp_var:6
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                                     bdaabaadaacbdbcaad
cmp:                                               ^
t_id:54  comp_var:7
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                                     bdaabaadaacbdbcaad
cmp:                                              ^
t_id:54  comp_var:8
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                                     bdaabaadaacbdbcaad
cmp:                                             ^
t_id:54  comp_var:9
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                                     bdaabaadaacbdbcaad
cmp:                                            ^
t_id:54  comp_var:10
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                                     bdaabaadaacbdbcaad
cmp:                                           ^
t_id:54  comp_var:11
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                                     bdaabaadaacbdbcaad
cmp:                                          ^
t_id:54  comp_var:12
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                                     bdaabaadaacbdbcaad
cmp:                                         ^
t_id:54  comp_var:13
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                                     bdaabaadaacbdbcaad
cmp:                                        ^
t_id:54  comp_var:14
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                                     bdaabaadaacbdbcaad
cmp:                                       ^
t_id:54  comp_var:15
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                                     bdaabaadaacbdbcaad
cmp:                                      ^
t_id:54  comp_var:16
t  :abcddxxxxcbaxxabcccaabaaadaaaaabcbxxxbdaabaadaacxxxxxaddaaadabbxxxdaadadbcbxxxxaaadaadada
s_i:                                     bdaabaadaacbdbcaad
cmp:                                     ^
t_id:54  comp_var:17

Detected the exact position of s_i!!
Before s_i assignment:abcddbcdbcbaaaabcccaabaaadaxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
After  s_i assignment:abcddbcdbcbaaaabcccaabaaadaxxxxxxxxxxbdaabaadaacbdbcaadxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


BM complete: abcddbcdbcbaaaabcccaabaaadaxxxxxxxxxxbdaabaadaacbdbcaadxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

It continues... 