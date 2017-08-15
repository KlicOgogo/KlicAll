def main():
    a = open("input.txt")
    limit = int(a.readline())
    lines = []
    for i in range(limit):
        lines.append(a.readline().strip())
    words = []
    for line in lines:
        word = []
        for i in range(len(line)):
            if line[i] == 'Ё' or line[i] == 'ё':
                word.append('е')
            elif 'А' <= line[i] <= 'я':
                if line[i] < 'а':
                    word.append(chr(ord(line[i]) + 32))
                else:
                    word.append(line[i])
        words.append(''.join(word))
    for word in words:
        if word == word[::-1]:
            print('yes')
        else:
            print('no')
    return


main()
