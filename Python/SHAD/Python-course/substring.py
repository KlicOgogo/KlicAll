import sys
def main():
    n = int(sys.stdin.readline())
    b = []
    length = []
    for i in range(n):
        b.append(sys.stdin.readline().strip())
        length.append(len(b[i]))
    for i in range(n):
        for dist in range(1, length[i]+1):
            for k in range(length[i]-dist+1):
                sys.stdout.write(b[i][k:k+dist] + ' ')
        sys.stdout.write('\n')
    return

main()