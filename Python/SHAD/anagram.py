import operator
import sys


def main():
    a = open("input.txt")
    limit = int(a.readline())
    words = []
    letters = []
    for i in range(limit):
        word = a.readline().strip().lower()
        words.append(word)
        letters.append(''.join(sorted(word)))
    word_dict = {}
    for i in range(limit):
        if not letters[i] in word_dict:
            word_dict[letters[i]] = []
        word_dict[letters[i]].append(words[i])
    for i in word_dict.keys():
            word_dict[i] = sorted(set(word_dict[i]))
    od = sorted(word_dict.items(), key=operator.itemgetter(1))
    for i in od:
        if len(i[1]) > 1:
            for j in i[1]:
                sys.stdout.write(j+' ')
            sys.stdout.write('\n')

main()
