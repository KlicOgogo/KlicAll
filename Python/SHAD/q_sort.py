import sys
import random

def partition(array, l, r, pivot):
    i = l
    j = r-1
    while i < j:
        if int(array[i]) <= int(pivot):
            i += 1
        else:
            array[i], array[j] = array[j], array[i]
            j -= 1
    while i < r and int(array[i]) < int(pivot):
        i += 1
    return i

def q(array,l,r):
    if l+1 < r:
        pivot = array[random.randint(0, r-1)]
        k = partition(array, l, r, pivot)
        q(array, l, k)
        q(array, k, r)
    return

def main():
    array = sys.stdin.readline().strip().split(' ')
    q(array, 0, len(array))
    for i in array:
        sys.stdout.write(str(i) + ' ')
    return

main()