import sys

def main():
    a = open("input.txt")
    c = a.read()
    b = []
    d = []
    for i in range(26):
        b.append(0)
        d.append(chr(97+i))
    for i in c:
        if ord(i) > 64 and ord(i) < 91:
            b[ord(i) - 65] += 1
        elif ord(i) > 96 and ord(i) < 123:
            b[ord(i) - 97] += 1
    for i in range(1, 26):
        for j in range(26-i):
            if (b[j] < b[j+1]):
                b[j], b[j+1] = b[j+1], b[j]
                d[j], d[j+1] = d[j+1], d[j]
    for i, j in zip(b, d):
        if (i > 0):
            sys.stdout.write(j+': ' + str(i))
            sys.stdout.write('\n')
    return

main()