import no_standard_sort
import sys

def merge(array, l, m, r):
    l_start = l
    r_start = m
    temp = []
    while l_start < m and r_start < r:
        if int(array[l_start]) > int(array[r_start]):
            temp.append(array[r_start])
            r_start += 1
        else:
            temp.append(array[l_start])
            l_start += 1
    while l_start < m:
        temp.append(array[l_start])
        l_start += 1
    while r_start < r:
        temp.append(array[r_start])
        r_start += 1
    start = l
    for i in temp:
        array[start] = i
        start += 1
    return

def m(array, l, r):
    if l+1 < r:
        m(array, l, (l+r)//2)
        m(array, (l+r)//2, r)
        merge(array, l, (l+r)//2, r)
    return

def main():
    array = sys.stdin.readline().strip().split(' ')
    m(array, 0, len(array))
    for i in array:
        sys.stdout.write(str(i) + ' ')
    return

main()