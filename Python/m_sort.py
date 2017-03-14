import no_standard_sort
import sys

def merge(array, left, m, right):
    left_start = left
    right_start = m
    temp = []
    while left_start < m and right_start < right:
        if int(array[left_start]) > int(array[right_start]):
            temp.append(array[right_start])
            right_start += 1
        else:
            temp.append(array[left_start])
            left_start += 1
    while left_start < m:
        temp.append(array[left_start])
        left_start += 1
    while right_start < right:
        temp.append(array[right_start])
        right_start += 1
    start = left
    for i in temp:
        array[start] = i
        start += 1
    return

def merge_sort(array, left, right):
    if left+1 < right:
        merge_sort(array, left, (left+right)//2)
        merge_sort(array, (left+right)//2, right)
        merge(array, left, (left+right)//2, right)
    return

def main():
    array = sys.stdin.readline().strip().split(' ')
    merge_sort(array, 0, len(array))
    for i in array:
        sys.stdout.write(str(i) + ' ')
    return

main()
