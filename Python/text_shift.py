import sys

def main():
    a = open("input.txt")
    limit = int(a.readline())
    c = a.read()
    i = 0
    result = []
    last_space = 0
    count = 0
    while i < len(c):
        if c[i] == '\n':
            result.append(c[i])
            count = 0
            last_space = i
        elif c[i] == ' ' and count == limit:
            while c[i] == ' ':
                i += 1
            i -= 1
            result.append('\n')
            count = 0
            last_space = i
        elif c[i] == ' ':
            last_space = i
            result.append(c[i])
            count += 1
        elif count < limit:
            result.append(c[i])
            count += 1
        elif count == limit and result[last_space] == ' ':
            result[last_space] = '\n'
            result.append(c[i])
            count = len(result) - last_space - 1
        else:
            while c[i] != ' ' and c[i] != '\n':
                result.append(c[i])
                i += 1
            result.append('\n')
            count = 0
            last_space = i
        i += 1
    for i in result:
        sys.stdout.write(i)
    return

main()