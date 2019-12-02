def print_table(counter):
    labels = sorted(counter[0].keys())
    data = [[d[l] if l in d else 0 for l in labels] for d in counter]
    max_len = max(max([[len(str(a)) for a in d] for d in data]))
    table = [[f'dat{i}:'] for i in range(5)]
    table.insert(0, ['     '] + [f'{l:>{max_len}}' for l in labels])
    for i, l in enumerate(data):
        table[i+1].extend([f'{d:>{max_len}}' for d in l])
    for l in table:
        print('\t'.join(l))

def total_alph_counter():
    print('total_alph_counter')
    counter = [{} for i in range(5)]
    for i, d in enumerate(counter):
        with open(f'data/dat{i}_ref', 'r') as f:
            for s in f.read():
                d.setdefault(s, 0)
                d[s] += 1
    print_table(counter)

# total_alph_counter()

def sep_len():
    print('sep_len')
    counter = [{} for i in range(5)]
    for i, d in enumerate(counter):
        with open(f'data/dat{i}_in', 'r') as f:
            for s in f.readlines()[1:]:
                slen = len(s.rstrip('\n'))
                # if slen > 20:
                #     slen = 100
                d.setdefault(slen, 0)
                d[slen] += 1
    print([max(d.keys()) for d in counter])
    print_table(counter)

# sep_len()

def x_len():
    print('x_len')
    counter = [{} for i in range(5)]
    for i, d in enumerate(counter):
        with open(f'data/dat{i}_in', 'r') as f:
            c = 0
            for s in f.read().split()[0]:
                if s == 'x':
                    c += 1
                else:
                    if c < 1:
                        continue
                    d.setdefault(c, 0)
                    d[c] += 1
                    c = 0
    print_table(counter)

# x_len()

def t_to_s_rate():
    print('t_to_s_rate')
    counter = [{} for i in range(5)]
    for i, d in enumerate(counter):
        with open(f'data/dat{i}_in', 'r') as f:
            s = f.read().split()
            d['tlen'] = len(s[0])
            d['slen'] = sum([len(c) for c in s[1:]])
            d['ratio'] = d['slen'] / d['tlen']
    print_table(counter)

# t_to_s_rate()

def t_to_x_rate():
    print('t_to_x_rate')
    counter = [{} for i in range(5)]
    for i, d in enumerate(counter):
        with open(f'data/dat{i}_in', 'r') as f:
            s = f.read().split()[0]
            d['t\'len'] = len(s)
            d['xcount'] = sum([c == 'x' for c in s])
    print_table(counter)

# t_to_x_rate()

def duplication():
    for i in range(5):
        with open(f'data/dat{i}_ref', 'r') as f:
            t = f.read()
        with open(f'data/dat{i}_in', 'r') as f:
            s = f.read().split()[1:]
        t_count = {}
        s_count = {}
        for c in t:
            t_count.setdefault(c, 0)
            t_count[c] += 1
        for si in s:
            for c in si:
                s_count.setdefault(c, 0)
                s_count[c] += 1

        for k in t_count.keys():
            if t_count[k] != s_count[k]:
                print(k)

duplication()
