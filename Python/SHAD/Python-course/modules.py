

def main():
    file = open('input.txt')
    lines = []
    for line in file:
        temp = line.strip().split(' ')
        for i in temp:
            lines.append(i)
        lines.append('\n')
    norm = []
    for word in lines:
        norm_word = []
        for char in word:
            if char == '.' or 'a' <= char <= 'z' or 'A' <= char <= 'Z' or char == '\n':
                norm_word.append(char)
        if len(norm_word) > 0:
            norm.append(''.join(norm_word))
    i = 0
    modules = []
    while i < len(norm):
        if norm[i] == 'from':
            if i+2 < len(norm) and norm[i+2] == 'import':
                modules.append(norm[i+1])
                i += 3
            else:
                i += 1
        elif norm[i] == 'import':
            i += 1
            if i < len(norm):
                while i < len(norm) and norm[i] != 'import' and norm[i] != '\n':
                    modules.append(norm[i])
                    i += 1
        else:
            i += 1
    res = sorted(set(modules))
    print_string = []
    for i in res:
        print_string.append(i)
        print_string.append(',')
        print_string.append(' ')
    del (print_string[-1])
    del (print_string[-1])
    print(''.join(print_string))


main()
