import sys


def main():
    a = open('input.txt')
    lines = []
    for line in a:
        lines.append(line)
    lang_ended = False
    lang = {}
    query = []
    for line in lines:
        if line == '\n':
            lang_ended = True
        elif line != '\n' and not lang_ended:
            lang_info = line.strip().split(' ')
            lang[lang_info[0]] = set(lang_info[1].lower())
        else:
            query.append(line.strip().lower().split(' '))
    counts = {}
    result = []
    for i in query:
        lang_list = []
        for j in i:
            for t in lang.keys():
                counts[t] = 0
            for k in j:
                for m in lang.keys():
                    if k in lang[m]:
                        counts[m] += 1
            max_ = 0
            key = ''
            for m in lang.keys():
                if counts[m] > max_ or (counts[m] == max_ and m < key):
                    max_ = counts[m]
                    key = m
            lang_list.append(key)
        result.append(sorted(set(lang_list)))
    for i in result:
        for j in i:
            sys.stdout.write(j + ' ')
        sys.stdout.write('\n')


main()
