def main():
    data = open('input.txt', 'r').read().strip().split(' ')
    k = int(data[0])
    m = int(data[1])
    d = int(data[2])
    days = 0
    zbs = True
    cur = m
    for i in range(8-d):
        if i + d < 6:
            cur += k
        cur -= i+1
        if cur < 0:
            zbs = False
            break
        days += 1
    out = open('output.txt', 'w')
    if not zbs:
        out.write(str(days))
        out.close()
    else:
        w = max((10 * k - 14 * days - 7) // 49, 0)
        kk = 7 * w
        cur += 5 * k * w
        lel = (2 * days + kk + 1) * kk // 2
        cur -= lel
        days += kk
        i = 1
        while cur >= 0:
            if i % 7 != 6 and i % 7 != 0:
                cur += k
            cur -= days + 1
            days += 1
            i += 1
        out.write(str(days - 1))
        out.close()


if __name__ == '__main__':
    main()

