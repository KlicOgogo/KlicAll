import sys
import random

def partition(array, left, right, pivot):
    i = left
    j = right-1
    while i < j:
        if int(array[i]) <= int(pivot):
            i += 1
        else:
            array[i], array[j] = array[j], array[i]
            j -= 1
    while i < right and int(array[i]) < int(pivot):
        i += 1
    return i

def quick_sort(array, left, right):
    if left+1 < right:
        pivot = array[random.randint(0, right-1)]
        k = partition(array, left, right, pivot)
        quick_sort(array, left, k)
        quick_sort(array, k, right)
    return

def main():
    array = sys.stdin.readline().strip().split(' ')
    quick_sort(array, 0, len(array))
    for i in array:
        sys.stdout.write(str(i) + ' ')
    return

main()
