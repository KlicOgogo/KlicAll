def main():
    n = int(input())
    if n == 0:
        print(0)
        return
    if n == 1:
        print(1)
        return
    a = 0
    b = 1
    for i in range(0, n):
        a += b
        a, b = b, a
    print(a)
    return

main()