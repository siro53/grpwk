for j in range(5):
    input_path = "dat" + str(j) + "_in"
    ans_path = "dat" + str(j) + "_ref"
    f = open(input_path)
    g = open(ans_path)

    tmp = f.readline()
    s = tmp
    ans = f.read()

    abcd = [0, 0, 0, 0]

    for i in range(len(s)):
        if s[i] == 'x':
            if ans[i] == 'a':
                abcd[0] += 1
            if ans[i] == 'b':
                abcd[1] += 1
            if ans[i] == 'c':
                abcd[2] += 1
            if ans[i] == 'd':
                abcd[3] += 1
    print("入力データ" + str(j) + "個目")
    print("a: " + str(abcd[0]) + "個")
    print("b: " + str(abcd[1]) + "個")
    print("c: " + str(abcd[2]) + "個")
    print("d: " + str(abcd[3]) + "個")
    print("a: " + str(abcd[0]/len(ans)))
    print("b: " + str(abcd[1]/len(ans)))
    print("c: " + str(abcd[2]/len(ans)))
    print("d: " + str(abcd[3]/len(ans)))