import sys

def main():
    p = float(sys.stdin.readline())
    a = sys.stdin.readline().strip().split(' ')
    sum = 0.
    for i in a:
        sum += abs(float(i))**p
    print(sum**(1./p))
    return

main()